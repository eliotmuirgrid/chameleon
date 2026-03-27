#pragma once
//------------------------------------------------------------------------
// Copyright (C) 2026 Eliot Muir.  All rights reserved.
//
// Module:  CORcommandLine
// 
// Description
//
// Utility class for parsing command line flags and positional parameters.
//
// Register expected flags first, then call parseArgs(), then query the
// parsed flags and extra arguments.
//
// Author: Eliot Muir
//---------------------------------------------------------------------------
#include <COR/CORarray.h>
#include <COR/CORauto.h>
#include <COR/CORlist.h>

class CORostream;

class CORcommandLine{
public:
   CORcommandLine();
   ~CORcommandLine();

   // Parse flags and positional arguments.
   void parseArgs(int argc, const char** ppArg);
   
   // Return argv[0].
   const CORstring& programName() const;

   // Number of positional arguments.
   int countOfExtraArgument() const;

   // Positional argument by index.
   const CORstring& extraArgument(int ArgumentIndex) const;

   // Positional argument by declared parameter name.
   const CORstring& extraArgument(const CORstring& Parameter) const;

   // True if a registered flag was present.
   bool isFlagPresent(const CORstring& FlagName) const;

   // Register a flag with no argument.
   void addFlagWithoutArgument(const CORstring& FlagName, const CORstring& Description);

   // Register a flag with an argument.
   // ArgumentName is a usage label such as "<file>".
   void addFlagWithArgument(const CORstring& FlagName, const CORstring& ArgumentName);

   // Register a flag with an argument and usage description.
   void addFlagWithArgument(const CORstring& FlagName,
                            const CORstring& ArgumentName,
                            const CORstring& Description);

   // Retrieve a flag argument. Returns "" if the flag has no argument.
   void flagArgument(const CORstring& FlagName, CORstring& Argument) const;

   const CORstring& flagArgument(const CORstring& FlagName) const;

   // Print usage for registered flags and parameters.
   void showUsage(CORostream& OutStream) const;

   // Hide a flag from showUsage().
   void hideFlag(const CORstring& FlagName);
   
   // Return true and write an error summary if parsing found a problem.
   bool parsingErrorsPresent(CORostream& ErrorStream) const;

   void addExtraParamDescription(const CORstring& Parameter, const CORstring& Description);
   void addExtraParamDescriptionRequired(const CORstring& Parameter, const CORstring& Description);
   void setDescription(const CORstring& Description);

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
   CORstring RepeatedFlagName;

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
