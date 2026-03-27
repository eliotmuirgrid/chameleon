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
// If this class doesn't meet your requirements please bugger off and don't alter it. 
// Write something else to meet your needs.  This is a simple solution to a simple problem.
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

   // Configure usage text, parameters, and flags before parsing.
   void setDescription(const CORstring& Desc);
   void addExtraParamDescription(const CORstring& Param, const CORstring& Desc);
   void addExtraParamDescriptionRequired(const CORstring& Param, const CORstring& Desc);
   void addFlagWithoutArgument(const CORstring& Flag, const CORstring& Desc);
   void addFlagWithArgument(const CORstring& Flag, const CORstring& Arg);
   void addFlagWithArgument(const CORstring& Flag, const CORstring& Arg, const CORstring& Desc);

   // Parse flags and positional arguments.
   void parseArgs(int argc, const char** argv);

   // Error reporting and usage output after parsing.
   bool parsingErrorsPresent(CORostream& Out) const;
   void showUsage(CORostream& Out) const;
   
   // Query parsed values.
   const CORstring& programName() const;
   int countOfExtraArgument() const;
   const CORstring& extraArgument(int Index) const;
   const CORstring& extraArgument(const CORstring& Param) const;
   bool isFlagPresent(const CORstring& Flag) const;
   void flagArgument(const CORstring& Flag, CORstring& Arg) const;
   const CORstring& flagArgument(const CORstring& Flag) const;

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
