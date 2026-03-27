#pragma once
//------------------------------------------------------------------------
// Copyright (C) 2026 Eliot Muir.  All rights reserved.
//
// Module:  CORcommandLine
// 
// Description
//
// This is utility class which makes it easy to get command line
// arguments.  
//
// The command line has the following general form:
//
// ApplicationName [--flag1 [argument1]] [--flag2 [argument2]] ... [--flagN [argumentN]]
//    [extraArgument1] [extraArgument2] ... [extraArgumentM]
//
// where the square brackets denote that the value is optional.  Flags are denoted by
// two dashes '--', and at present a flag may have zero or one arguments following it.
// A string in the command line which is not a flag, and which is not the argument of
// a flag, is classified as an 'extra argument'.  All such extra arguments should appear
// in the command line after all the flags, as shown.
//
// Best usage: 
//
// For each flag which your parser handles, use addFlagWithoutArgument(FlagName, Description)
// or addFlagWithArgument(FlagName, ArgumentName, Description) to register the flag with
// the parser.  Then, for each registered flag, have a conditional:
// if (LineParser.isFlagPresent("FlagName"))
// {
//    implementation details
// } 
// (Avoid using flagPresent to implicitly register flags without arguments with the parser, since there
// is no equivalent method for flags with arguments, and it leads to code that is more confusing than
// it needs to be.)  

// The interface for the CORcommandLine class also refers to 'parameters'.  Parameters are
// arguments which are not associated with a flag.  That is, they look just like 'extra
// arguments' on the command line, but they can have a description associated with them,
// and they can be required or optional.  
//
// TODO - it is probably needlessly confusing to have flags, arguments, parameters, 
// and extra arguments.  Perhaps parameters could be recast as flags with arguments.
//
// TODO
//  - Would be nice if optional flags/arguments could be assigned default values.
//  - Would be nice if flags/arguments could be typed (at least for basic built-in types).
//  - Treating help flags as unknown arguments is not user friendly.
//  - Neither parseArgs, nor parsingErrorsPresent check for required "extra arguments".
//  - Cleaner object model would have three classes: schema -> parser -> results.
//    See Boost's Program Options library for an example.
//
// Author: Eliot Muir
//
//---------------------------------------------------------------------------
#include <COR/CORarray.h>
#include <COR/CORauto.h>
#include <COR/CORlist.h>
#include <COR/CORlog.h>

class CORostream;

class CORcommandLine{
public:
   CORcommandLine();
   ~CORcommandLine();

   // Parses the command line.  It registers the flags that are present, and builds
   // a vector of 'extra arguments'.
   // This method will return false it if fails - it will also
   // output an error message to stderr - the user should check the return
   // value of this class.
   void parseArgs(int argc, const char** ppArg);
   void parseArgsNoTrace(int argc, const char** ppArg);
   
   // returns the program name - argv[0] - which was stored upon parsing above
   const CORstring& programName() const;

   // Returns the number of extra arguments found 
   int countOfExtraArgument() const;

   // Retrieves the value of an extra argument
   const CORstring& extraArgument(int ArgumentIndex) const;

   // Retrieves the value of an extra argument
   const CORstring& extraArgument(const CORstring& Parameter) const;

   // Is a flag present? - true/false -- new one, use this one from now on.
   // Differs from flagPresent in that it only checks the FlagTable for the
   // presence of FlagName, and does not try to register the flag.
   bool isFlagPresent(const CORstring& FlagName) const;


   // Registers a flag without any arguments.  The Description is used
   // by showUsage().
   void addFlagWithoutArgument(const CORstring& FlagName,
                               const CORstring& Description);

   // Registers a flag which has an argument. 
   // There seems to be some confusion in the libraries about the use
   // of this method.  ArgumentName is not a substitute for a flag description,
   // though it has sometimes been erroneously used that way.  Instead, 
   // ArgumentName should give the form of the argument.  A description can
   // - and should - be added using flagPresent(FlagName, Description) or, better
   // yet, use the method below which takes 3 parameters.  Both
   // the ArgumentName and the Description are used by showUsage().
   //
   // For instance, suppose we have a flag '--mailto' which, when present, means
   // that the output of the command line utility is mailed to a particular
   // email address.  In this case FlagName = "mailto", ArgumentName might be
   // something like "user@host", and Description might be "Mail output to 
   // specified email address."
   void addFlagWithArgument(const CORstring& FlagName, 
                            const CORstring& ArgumentName);

   // Register a flag which has an argument, and provide a usage description.
   void addFlagWithArgument(const CORstring& FlagName,
                            const CORstring& ArgumentName,
                            const CORstring& Description);

   // sets RepeatOk for the given flag
   void setFlagRepeatOk(const CORstring& FlagName, bool RepeatOk);

   // number of repeated arguments for the given flag
   int flagRepeatCount(const CORstring& FlagName) const;

   // get a given repeated argument for the given flag
   const CORstring& flagRepeatValue(const CORstring& FlagName, int RepeatIndex) const;

   //get argument for a flag. returns "" if flag doesn't have arguments
   void flagArgument(const CORstring& FlagName, CORstring& Argument) const;

   const CORstring& flagArgument(const CORstring& FlagName) const;

   // This command will display the list of flags that the class knows about
   void showUsage(CORostream& OutStream) const;

   // hides a flag from the showUsage and --kissbook call
   void hideFlag(const CORstring& FlagName);
   
   // If an error was encountered while parsing the arguments, return true.
   // Also, will write a summary of the error to ErrorStream.
   // Possible errors are:
   //  * An undefined flag was present
   //  * A flag was used more than once
   bool parsingErrorsPresent(CORostream& ErrorStream) const;

   void addExtraParamDescription(const CORstring& Parameter, const CORstring& Description);
   void addExtraParamDescriptionRequired(const CORstring& Parameter, const CORstring& Description);
   void setDescription(const CORstring& Description);

#ifdef COR_ENABLE_TRACING
   void addRuntimeConditionalLoggingFlags(); // for CORlog support
#endif

private:
   struct CLIextraParamDescription {
      CLIextraParamDescription() : ParamRequired(false) {}
      CLIextraParamDescription(const CORstring& Name, const CORstring& Description, bool IsRequired)
         : ParamName(Name), ParamDescription(Description), ParamRequired(IsRequired) {}
      CORstring ParamName;
      CORstring ParamDescription;
      bool ParamRequired;
   };

   struct CLIlineFlag {
      explicit CLIlineFlag(const CORstring& iName);
      CORstring   Name;
      CORstring   Description;
      bool  HasArgument;
      bool  IsPresent;
      bool  WasExpected;
      CORstring   Argument;
      CORstring   ArgumentName;
      bool  IsHidden;
      bool  WasRepeated;
      CORarray<CORstring> ValueList;
      bool  RepeatOk;
   private:
      CLIlineFlag(const CLIlineFlag& Orig);
      CLIlineFlag& operator=(const CLIlineFlag& Orig);
   };

   CORstring Description;
   CORstring ProgramName;
   bool HasParsed;
   CORarray<CORstring> ExtraArgs;
   CORarray<CLIextraParamDescription> ParamDescription;
   CORlist<CORauto<CLIlineFlag> > FlagList;
   CORstring NullString;

   bool isFlag(const char* pArgument) const;
   CLIlineFlag* createFlagIfNotInList(const CORstring& FlagName);
   CLIlineFlag* addPresentFlag(const char* pArgument);
   CLIlineFlag* flag(const CORstring& FlagName);
   const CLIlineFlag* flag(const CORstring& FlagName) const;
   bool isFlagInList(const CORstring& FlagName) const;
   void addArgument(const char* pArgument);
   bool isHelpArgument(const CORstring& FlagName) const;
   bool isHelpFlag(const CORstring& FlagName) const;

   CORcommandLine(const CORcommandLine& Orig);
   CORcommandLine& operator=(const CORcommandLine& Orig);
};

void CORcommandLineRepeatValueList(CORarray<CORstring>& ValueList, const CORcommandLine& LineParser, const CORstring& FlagName);
