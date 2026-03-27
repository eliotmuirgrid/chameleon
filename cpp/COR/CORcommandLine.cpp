//------------------------------------------------------------------------
// Copyright (C) 2026 Eliot Muir.  All rights reserved.
//
// Module:  CORcommandLine
// 
// Description
//
// Implementation of a utility class which makes it easy to get command line
// arguments.  
//
// Author: Eliot Muir
//
//---------------------------------------------------------------------------
#include <COR/CORcommandLine.h>

#include <COR/CORlog.h>
COR_LOG_MODULE;

// On Windows, this tells the C runtime to pass wildcard arguments like "*.txt"
// through unchanged so CORcommandLine sees the raw command line text.
int _CRT_glob = 0; 

// Number of spaces between the argument and description columns.
static const CORuint32 kPaddingSpaces = 2;
// Maximum width of output when showing usage.
static const CORuint32 kShowUsageWidth = 75;

CORcommandLine::CORflagEntry::CORflagEntry(const CORstring& iName)
   : Name(iName),
     IsPresent(false),
     WasExpected(false),
     HasArgument(false),
     ArgumentName("") {
}

CORcommandLine::CORflagEntry* CORcommandLine::createFlagIfNotInList(const CORstring& FlagName) {
   CORflagEntry* pFlag = flag(FlagName);
   if (NULL == pFlag)
   {
      FlagList.add(CORauto<CORflagEntry>(new CORflagEntry(FlagName)));
      pFlag = flag(FlagName);
   }
   return pFlag;
}

CORcommandLine::CORflagEntry* CORcommandLine::addPresentFlag(const char* pArgument) {
   CORstring FlagName = pArgument;
   FlagName = FlagName.strip(CORstring::Leading, '-');

   CORflagEntry* pFlag = flag(FlagName);
   if (NULL == pFlag)
   {
      FlagList.add(CORauto<CORflagEntry>(new CORflagEntry(FlagName)));
      pFlag = flag(FlagName);
   }
   else if (pFlag->IsPresent)
   {
      if (RepeatedFlagName.is_null()) {
         RepeatedFlagName = FlagName;
      }
   }
   pFlag->IsPresent = true;

   return pFlag;
}

const CORcommandLine::CORflagEntry* CORcommandLine::flag(const CORstring& FlagName) const {
   for (CORlistPlace Place = FlagList.first(); Place != NULL; Place = FlagList.next(Place))
   {
      if (FlagList[Place]->Name == FlagName)
      {
         return FlagList[Place].get();
      }
   }

   return NULL;
}

CORcommandLine::CORflagEntry* CORcommandLine::flag(const CORstring& FlagName) {
   return const_cast<CORflagEntry*>(static_cast<const CORcommandLine*>(this)->flag(FlagName));
}

bool CORcommandLine::isFlagInList(const CORstring& FlagName) const {
   return NULL != flag(FlagName);
}

void CORcommandLine::addArgument(const char* pArgument) {
   ExtraArgs.push_back(pArgument);  
}

CORcommandLine::CORcommandLine()
   : HasParsed(false) {
}

CORcommandLine::~CORcommandLine() {
}

bool CORcommandLine::isFlag(const char* pArgument) const {
   // flags begin with at least 1 dash (ie. -FlagName, --FlagName).
   if (strlen(pArgument) <= 1)
   {
      return false;
   }
   if (pArgument[0] == '-')
   {
      CORstring FlagString(pArgument);
      if (FlagString.strip(CORstring::Leading, '-').is_null())
      {
         return false;
      }
      else
      {
         return true;
      }
   }
   else
   {
      return false;
   }
}

void CORcommandLine::addExtraParamDescriptionRequired(const CORstring& Parameter, const CORstring& Description) {
   ParamDescription.push_back(CORparameterDescriptionEntry(Parameter, Description, true));
}

void CORcommandLine::addExtraParamDescription
(
   const CORstring& Parameter, 
   const CORstring& Description
) {
   ParamDescription.push_back(CORparameterDescriptionEntry(Parameter, Description, false));
}

void CORcommandLine::setDescription(const CORstring& Description) {
   this->Description = Description;
}

bool CORcommandLine::parseArgs(int argc, const char** ppArg, CORstring* pError) {
   CORPRECONDITION(!HasParsed);
   CORPRECONDITION(pError != NULL);
   HasParsed = true;
   CORPRECONDITION(argc != 0);
   pError->clear();
   ProgramName = ppArg[0];
   if (argc == 1) {
      return true;
   }
   bool InFlagMode = true;
   CORint32 ArgIndex = 1;
   while (InFlagMode && (ArgIndex < argc)){
      // In the case of a help flag, eg -help, /? that's not a standard flag,
      // add it to the table anyways and set it to be unexpected,
      // so a program can test for unknownFlagPresent and do a showUsage().
      if (isHelpArgument(ppArg[ArgIndex])){
         CORflagEntry* pFlag = addPresentFlag(ppArg[ArgIndex]);
         pFlag->WasExpected = false;
         ArgIndex++;
      }

      // Otherwise it's a normal flag, add it to the table if it doesn't
      // already exist
      else if (isFlag(ppArg[ArgIndex])) {
         CORflagEntry* pFlag = addPresentFlag(ppArg[ArgIndex]);
         if (pFlag->HasArgument){
            // at present, a flag can have at most one argument following it
            ArgIndex++;
            if (ArgIndex < argc){ // we can't assume that the the last flag's argument will be there if needed!
               pFlag->Argument = ppArg[ArgIndex];
            } else {
               *pError = "Argument missing for flag ";
               *pError += ppArg[ArgIndex - 1];
               return false;
            }
         }
         ArgIndex++;
      } else{ // Not a flag
         InFlagMode = false;
      }      
   }
   
   while (ArgIndex < argc){ // Add the plain arguments to the list
      addArgument(ppArg[ArgIndex]);
      ArgIndex++;
   }
   if (!RepeatedFlagName.is_null()) {
      *pError = "Flag ";
      *pError += RepeatedFlagName;
      *pError += " used more than once.";
      return false;
   }

   CORstring FlagName;
   const CORflagEntry* pCommandLineFlag;
   for (CORlistPlace Place = FlagList.first(); Place != NULL; Place = FlagList.next(Place)) {
      pCommandLineFlag = FlagList[Place].get();
      FlagName = pCommandLineFlag->Name;
      if (!pCommandLineFlag->WasExpected) {
         // #10739 We don't want to see this warning when a help flag is found, and only show the usage.
         // This is not an ideal solution, but the help flag is only known to the command line parser
         // and we don't want to change the code for all our command line applications.
         if (!isHelpFlag(pCommandLineFlag->Name)) {
            *pError = "Unknown flag ";
            *pError += FlagName;
            *pError += " encountered.";
            return false;
         }
      }
   }
   return true;
}

const CORstring& CORcommandLine::programName() const {
   return ProgramName;
}

// This is the count of extra arguments actually found 
int CORcommandLine::countOfExtraArgument() const {
   return ExtraArgs.size();
}

// retrieve the value of an extra argument
const CORstring& CORcommandLine::extraArgument(int ArgumentIndex) const {
   return ExtraArgs[ArgumentIndex]; 
}

// retrieve the value of an extra argument
const CORstring& CORcommandLine::extraArgument(const CORstring& Parameter) const {
   for (CORuint32 ExtraArgIndex = 0; ExtraArgIndex < static_cast<CORuint32>(ParamDescription.size()); ++ExtraArgIndex)
   {
      if (Parameter == ParamDescription[ExtraArgIndex].ParamName)
      {
         return ExtraArgs[ExtraArgIndex];
      }
   }
   static const CORstring EmptyString;
   return EmptyString;
}

// Is a flag present - true/false -- new one, use this one from now on
// i.e. --BLAH
bool CORcommandLine::isFlagPresent(const CORstring& FlagName) const {
   CORMSGPRECONDITION(isFlagInList(FlagName), "Flag must be registered before it is queried");
   return flag(FlagName)->IsPresent;
}

// Add a flag with argument 
void CORcommandLine::addFlagWithArgument ( const CORstring& FlagName, const CORstring& ArgumentName) {
   CORflagEntry* pFlag = createFlagIfNotInList(FlagName);
   pFlag->WasExpected = true;
   pFlag->HasArgument = true;
   pFlag->ArgumentName = ArgumentName;
}

// Add a flag with argument, and provide a description 
void CORcommandLine::addFlagWithArgument(const CORstring& FlagName, const CORstring& ArgumentName, const CORstring& Description) {
   CORflagEntry* pFlag = createFlagIfNotInList(FlagName);
   pFlag->WasExpected = true;
   pFlag->HasArgument = true;
   pFlag->ArgumentName = ArgumentName;
   pFlag->Description = Description;
}

// Add a flag without any arguments
void CORcommandLine::addFlagWithoutArgument ( const CORstring& FlagName, const CORstring& Description) {
   CORflagEntry* pFlag = createFlagIfNotInList(FlagName);
   pFlag->WasExpected = true;
   pFlag->HasArgument = false;
   pFlag->Description = Description;   
}

// This command will display the list of flags that the class knows about.
// TODO - clean this up!
void CORcommandLine::showUsage(CORostream* pOutStream) const {
   CORPRECONDITION(pOutStream != NULL);
   CORostream& OutStream = *pOutStream;
   // Output the usage line that displays all the possible flags/arguments
   // TODO - this output does not wrap, but the output for "known flags" wraps. Create a printWrap function?
   OutStream << Description;
   OutStream << newline << "Usage:" << newline;
   OutStream << ProgramName;

   CORstring FlagName;
   const CORflagEntry* pCommandLineFlag;

   CORuint32 MaxFlagLength = 0;
   CORuint32 MaxDescriptionLength = 0;

   if (FlagList.size() > 0)
   {
      for (CORlistPlace Place = FlagList.first(); Place != NULL; Place = FlagList.next(Place))
      {
         pCommandLineFlag = FlagList[Place].get();
         FlagName = pCommandLineFlag->Name;
         if (pCommandLineFlag->WasExpected)
         {
            if (pCommandLineFlag->HasArgument) {
               OutStream << "  [--" << FlagName << ' ' << pCommandLineFlag->ArgumentName << ']'; 
            } else {
               OutStream << "  [--" << FlagName << ']'; 
            }
            
            //Get the maximum length of the command line flag and its description; used to
            //pad the output columns to make a nicer output
            if(FlagName.size() > MaxFlagLength) {
               MaxFlagLength = static_cast<CORuint32>(FlagName.size());
            }
            if(pCommandLineFlag->Description.size() > MaxDescriptionLength) {
               MaxDescriptionLength = static_cast<CORuint32>(pCommandLineFlag->Description.size());
            }

         }
      } 
   }
   int ExtraArgIndex=0;
   for (ExtraArgIndex=0; ExtraArgIndex < static_cast<CORuint32>(ParamDescription.size()); ExtraArgIndex++) {
      if (ParamDescription[ExtraArgIndex].ParamRequired) {
         OutStream << ' ' << ParamDescription[ExtraArgIndex].ParamName;
      } else {
         OutStream << " <" << ParamDescription[ExtraArgIndex].ParamName << '>';
      }
   }

   OutStream << newline;
   for (ExtraArgIndex=0; ExtraArgIndex < static_cast<CORuint32>(ParamDescription.size()); ExtraArgIndex++) {
      OutStream << "   " << ParamDescription[ExtraArgIndex].ParamName << 
                   " - " << ParamDescription[ExtraArgIndex].ParamDescription << newline;
   }
   if (FlagList.size() == 0) {
      return;
   }
   
   // Print out the flags together with their descriptions
   OutStream << "Known flags:" << newline;

   CORuint32 MaxLineLength = kShowUsageWidth; // width of output TODO - can we get this to be dynamic?

   for (CORlistPlace Place = FlagList.first(); Place != NULL; Place = FlagList.next(Place)) {
      pCommandLineFlag = FlagList[Place].get();
      FlagName = pCommandLineFlag->Name;
      if (pCommandLineFlag->WasExpected) {
         CORPRECONDITION(FlagName.size() <= MaxFlagLength);
         CORstring PaddingSpaces(MaxFlagLength - FlagName.size() + kPaddingSpaces, ' ');
         CORstring FlagInfo = "  --" + FlagName + PaddingSpaces;
         CORstring FlagDescription = pCommandLineFlag->Description;
         if (pCommandLineFlag->HasArgument) {
            // If the flag has a non empty description, we need a space!
            FlagDescription += FlagDescription.compare("") == 0 ? "": ". ";
            FlagDescription += "Requires argument " + pCommandLineFlag->ArgumentName + ".";
         }
         
         OutStream << FlagInfo;

         CORstring RemainingDescription = FlagDescription;
         CORstring DescriptionToStream;
         while (FlagInfo.size() + RemainingDescription.size() > MaxLineLength) {
            // find first carriage return in RemainingDescription
            if (RemainingDescription.find("\n") < (MaxLineLength - FlagInfo.size())) {
               RemainingDescription.split(DescriptionToStream, RemainingDescription, "\n");
            } else {
               // Description must be split onto two or more lines for proper formatting
               CORuint32 SplitIndex = static_cast<CORuint32>(RemainingDescription.rfind(" ", MaxLineLength - FlagInfo.size()));
               RemainingDescription.splitAtIndex(DescriptionToStream, RemainingDescription, SplitIndex + 1);
            }

            OutStream << DescriptionToStream << newline << CORstring(FlagInfo.size(), ' ');
         }
         
         if (RemainingDescription.find("\n") < RemainingDescription.size()) {
            // there is a carriage return somewhere in the middle of this last line
            RemainingDescription.split(DescriptionToStream, RemainingDescription, "\n");
            OutStream << DescriptionToStream << newline << CORstring(FlagInfo.size(), ' ');
         }
         OutStream << RemainingDescription << newline;
      }
   }
}

const CORstring& CORcommandLine::flagArgument(const CORstring& FlagName) const {
   CORMSGPRECONDITION(isFlagInList(FlagName), "Flag must be registered before its argument is queried");
   if(flag(FlagName)->HasArgument) {
      return flag(FlagName)->Argument;
   }
   return NullString;
}

//get argument for a flag. returns "" if flag doesn't have arguments
void CORcommandLine::flagArgument(const CORstring& FlagName, CORstring* pArgument) const {
   CORMSGPRECONDITION(isFlagInList(FlagName), "Flag must be registered before its argument is queried");
   CORPRECONDITION(pArgument != NULL);
   if(flag(FlagName)->HasArgument) {
      *pArgument = flag(FlagName)->Argument;
   } else {
      *pArgument = "";
   }
}

bool CORcommandLine::isHelpArgument(const CORstring& FlagString) const {
   if(FlagString == "--help"|| FlagString == "-help" || FlagString == "-?" || FlagString == "--?"|| FlagString == "/?"|| FlagString == "-h") {
      return true;
   }
   return false;
}

bool CORcommandLine::isHelpFlag(const CORstring& FlagString) const {
   if(FlagString == "help"|| FlagString == "?" || FlagString == "/?"|| FlagString == "h") {
      return true;
   }
   return false;
}
