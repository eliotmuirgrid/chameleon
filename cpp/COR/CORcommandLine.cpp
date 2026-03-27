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

// NOTE https://willus.com/mingw/_globbing.shtml
// 0 turns off globbing; 1 turns it on
int _CRT_glob = 0; 

//Number of spaces between the Name of the Argument and its description columns
static const CORuint32 CLI_NUMBER_OF_PADDING_SPACES = 2;
//Maximum width of output when showing usage
static const CORuint32 CLI_SHOW_USAGE_WIDTH = 75;

CORcommandLine::CLIlineFlag::CLIlineFlag(const CORstring& iName)
   : Name(iName),
     IsHidden(false),
     IsPresent(false),
     WasExpected(false),
     HasArgument(false),
     ArgumentName(""),
     WasRepeated(false),
     RepeatOk(false) {
}

CORcommandLine::CLIlineFlag* CORcommandLine::createFlagIfNotInList(const CORstring& FlagName) {
   CLIlineFlag* pFlag = flag(FlagName);
   if (NULL == pFlag)
   {
      FlagList.add(CORauto<CLIlineFlag>(new CLIlineFlag(FlagName)));
      pFlag = flag(FlagName);
   }
   return pFlag;
}

CORcommandLine::CLIlineFlag* CORcommandLine::addPresentFlag(const char* pArgument) {
   CORstring FlagName = pArgument;
   FlagName = FlagName.strip(CORstring::Leading, '-');

   CLIlineFlag* pFlag = flag(FlagName);
   if (NULL == pFlag)
   {
      FlagList.add(CORauto<CLIlineFlag>(new CLIlineFlag(FlagName)));
      pFlag = flag(FlagName);
   }
   else if (pFlag->IsPresent)
   {
      pFlag->WasRepeated = true;
   }
   pFlag->IsPresent = true;

   return pFlag;
}

const CORcommandLine::CLIlineFlag* CORcommandLine::flag(const CORstring& FlagName) const {
   for (CORlistPlace Place = FlagList.first(); Place != NULL; Place = FlagList.next(Place))
   {
      if (FlagList[Place]->Name == FlagName)
      {
         return FlagList[Place].get();
      }
   }

   return NULL;
}

CORcommandLine::CLIlineFlag* CORcommandLine::flag(const CORstring& FlagName) {
   return const_cast<CLIlineFlag*>(static_cast<const CORcommandLine*>(this)->flag(FlagName));
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
   ParamDescription.push_back(CLIextraParamDescription(Parameter, Description, true));
}

void CORcommandLine::addExtraParamDescription
(
   const CORstring& Parameter, 
   const CORstring& Description
) {
   ParamDescription.push_back(CLIextraParamDescription(Parameter, Description, false));
}

void CORcommandLine::setDescription(const CORstring& Description) {
   this->Description = Description;
}

void CORcommandLine::parseArgs(int argc, const char** ppArg) {
   if (HasParsed){
      COR_ERROR_STREAM_PLAIN("CORcommandLine::parseArgs() has been called more than once.", 0);
   }
   HasParsed = true;
   CORPRECONDITION(argc != 0);
   ProgramName = ppArg[0];
   if (argc == 1) {
      return;
   }
   bool InFlagMode = true;
   CORint32 ArgIndex = 1;
   while (InFlagMode && (ArgIndex < argc)){
      // In the case of a help flag, eg -help, /? that's not a standard flag,
      // add it to the table anyways and set it to be unexpected,
      // so a program can test for unknownFlagPresent and do a showUsage().
      if (isHelpArgument(ppArg[ArgIndex])){
         CLIlineFlag* pFlag = addPresentFlag(ppArg[ArgIndex]);
         pFlag->WasExpected = false;
         ArgIndex++;
      }

      // Otherwise it's a normal flag, add it to the table if it doesn't
      // already exist
      else if (isFlag(ppArg[ArgIndex])) {
         CLIlineFlag* pFlag = addPresentFlag(ppArg[ArgIndex]);
         if (pFlag->HasArgument){
            // at present, a flag can have at most one argument following it
            ArgIndex++;
            if (ArgIndex < argc){ // we can't assume that the the last flag's argument will be there if needed!
               pFlag->Argument = ppArg[ArgIndex];
               pFlag->ValueList.push_back() = ppArg[ArgIndex];
            } else {
               COR_ERROR_STREAM_PLAIN("Argument missing for flag " << ppArg[ArgIndex-1], 0);
            }
         }
         ArgIndex++;
      } else{ // Not a flag
         InFlagMode = false;
      }      
   }
   
   while (ArgIndex < argc) // Add the plain arguments to the list
   {
      addArgument(ppArg[ArgIndex]);
      ArgIndex++;
   }   
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
   if (!isFlagInList(FlagName)) {
      // This flag has not been installed by the users of this class
      COR_ERROR_STREAM("EXCEPTION: isFlagPresent was asked to check for the presence of flag " << FlagName << " which was not installed. "
                        << "A flag should be first installed using either addFlagWithArgument or addFlagWithoutArgument before it is checked for.", 0);
   }
   return flag(FlagName)->IsPresent;
}

// Add a flag with argument 
void CORcommandLine::addFlagWithArgument ( const CORstring& FlagName, const CORstring& ArgumentName) {
   CLIlineFlag* pFlag = createFlagIfNotInList(FlagName);
   pFlag->WasExpected = true;
   pFlag->HasArgument = true;
   pFlag->ArgumentName = ArgumentName;
}

// Add a flag with argument, and provide a description 
void CORcommandLine::addFlagWithArgument(const CORstring& FlagName, const CORstring& ArgumentName, const CORstring& Description) {
   CLIlineFlag* pFlag = createFlagIfNotInList(FlagName);
   pFlag->WasExpected = true;
   pFlag->HasArgument = true;
   pFlag->ArgumentName = ArgumentName;
   pFlag->Description = Description;
}

void CORcommandLine::setFlagRepeatOk(const CORstring& FlagName, bool RepeatOk) {
   CLIlineFlag* pFlag = flag(FlagName);
   CORMSGPRECONDITION(pFlag, "setFlagRepeatOk(): Flag " << FlagName << " not yet defined");
   CORMSGPRECONDITION(pFlag->HasArgument, "setFlagRepeatOk(): Flag " << FlagName << " doesn't have argument");
   pFlag->RepeatOk = RepeatOk;
}

// Add a flag without any arguments
void CORcommandLine::addFlagWithoutArgument ( const CORstring& FlagName, const CORstring& Description) {
   CLIlineFlag* pFlag = createFlagIfNotInList(FlagName);
   pFlag->WasExpected = true;
   pFlag->HasArgument = false;
   pFlag->Description = Description;   
}

// This command will display the list of flags that the class knows about.
// TODO - clean this up!
void CORcommandLine::showUsage(CORostream& OutStream) const {
   // Output the usage line that displays all the possible flags/arguments
   // TODO - this output does not wrap, but the output for "known flags" wraps. Create a printWrap function?
   OutStream << Description;
   OutStream << newline << "Usage:" << newline;
   OutStream << ProgramName;

   CORstring FlagName;
   const CLIlineFlag* pCommandLineFlag;

   CORuint32 MaxFlagLength = 0;
   CORuint32 MaxDescriptionLength = 0;

   if (FlagList.size() > 0)
   {
      for (CORlistPlace Place = FlagList.first(); Place != NULL; Place = FlagList.next(Place))
      {
         pCommandLineFlag = FlagList[Place].get();
         FlagName = pCommandLineFlag->Name;
         if (pCommandLineFlag->WasExpected && !pCommandLineFlag->IsHidden)
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

   CORuint32 MaxLineLength = 70; // width of output TODO - can we get this to be dynamic?

   for (CORlistPlace Place = FlagList.first(); Place != NULL; Place = FlagList.next(Place)) {
      pCommandLineFlag = FlagList[Place].get();
      FlagName = pCommandLineFlag->Name;
      if (pCommandLineFlag->WasExpected && !pCommandLineFlag->IsHidden) {
         if(FlagName.size() <= MaxFlagLength) {
            CORstring PaddingSpaces(MaxFlagLength - FlagName.size() + CLI_NUMBER_OF_PADDING_SPACES, ' ');
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
         } else {
            COR_ERROR_STREAM("Flag " << FlagName << " length exceeds the maximum flag length of "<< MaxFlagLength,0)
         }
      }
   }
}

const CORstring& CORcommandLine::flagArgument(const CORstring& FlagName) const {
   if (!isFlagInList(FlagName)) {
      COR_ERROR_STREAM(FlagName << " not defined.", 0);
   }
   if(flag(FlagName)->HasArgument) {
      return flag(FlagName)->Argument;
   }
   return NullString;
}

//get argument for a flag. returns "" if flag doesn't have arguments
void CORcommandLine::flagArgument(const CORstring& FlagName,CORstring& Argument) const {
   if (!isFlagInList(FlagName)) {
      COR_ERROR_STREAM(FlagName << " not defined.", 0);
   } else {
      if(flag(FlagName)->HasArgument) {
         Argument = flag(FlagName)->Argument;
      } else {
         Argument = "";
      }
   }
}

int CORcommandLine::flagRepeatCount(const CORstring& FlagName) const {
   if (!isFlagInList(FlagName)) {
      COR_ERROR_STREAM(FlagName << " not defined.", 0);
   }
   return flag(FlagName)->ValueList.size();
}

const CORstring& CORcommandLine::flagRepeatValue(const CORstring& FlagName, int RepeatIndex) const {
   if (!isFlagInList(FlagName)) {
      COR_ERROR_STREAM(FlagName << " not defined.", 0);
   }
   CORPRECONDITION(RepeatIndex >= 0 && RepeatIndex < flag(FlagName)->ValueList.size());
   return flag(FlagName)->ValueList[RepeatIndex];
}

bool CORcommandLine::parsingErrorsPresent(CORostream& ErrorStream) const {
   CORstring FlagName;
   const CLIlineFlag* pCommandLineFlag;

   for (CORlistPlace Place = FlagList.first(); Place != NULL; Place = FlagList.next(Place)) {
      pCommandLineFlag = FlagList[Place].get();
      FlagName = pCommandLineFlag->Name;
      if (!pCommandLineFlag->WasExpected) {
         // #10739 We don't want to see this warning when a help flag is found, and only show the usage.
         // This is not an ideal solution, but the help flag is only known to the command line parser
         // and we don't want to change the code for all our command line applications.
         if (!isHelpFlag(pCommandLineFlag->Name)) {
            ErrorStream << "Unknown flag " << FlagName << " encountered." << newline;
         }
         return true;
      }
      if (pCommandLineFlag->WasRepeated && !pCommandLineFlag->RepeatOk) {
         ErrorStream << "Flag " << FlagName << " used more than once." << newline;
         return true;
      }
   }
   return false;
}

void CORcommandLine::hideFlag(const CORstring& FlagName) {
   if (isFlagInList(FlagName)) {
      flag(FlagName)->IsHidden = true;
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

void CORcommandLineRepeatValueList(CORarray<CORstring>& ValueList, const CORcommandLine& LineParser, const CORstring& FlagName) {
   for(int ValueIndex=0; ValueIndex < LineParser.flagRepeatCount(FlagName); ValueIndex++){
      ValueList.push_back() = LineParser.flagRepeatValue(FlagName, ValueIndex);
   }
}
