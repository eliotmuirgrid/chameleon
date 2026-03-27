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
   bool parseArgs(int argc, const char** argv, CORstring* pError);

   // Usage output after parsing.
   void showUsage(CORostream* pOut) const;
   
   // Query parsed values.
   const CORstring& programName() const;
   int countOfExtraArgument() const;
   const CORstring& extraArgument(int Index) const;
   const CORstring& extraArgument(const CORstring& Param) const;
   bool isFlagPresent(const CORstring& Flag) const;
   void flagArgument(const CORstring& Flag, CORstring* pArg) const;
   const CORstring& flagArgument(const CORstring& Flag) const;

private:
   struct CORparameterDescriptionEntry {
      CORparameterDescriptionEntry() : ParamRequired(false) {}
      CORparameterDescriptionEntry(const CORstring& Name, const CORstring& Description, bool IsRequired)
         : ParamName(Name), ParamDescription(Description), ParamRequired(IsRequired) {}
      CORstring ParamName;
      CORstring ParamDescription;
      bool ParamRequired;
   };

   struct CORflagEntry {
      explicit CORflagEntry(const CORstring& iName);
      CORstring   Name;
      CORstring   Description;
      bool  HasArgument;
      bool  IsPresent;
      bool  WasExpected;
      CORstring   Argument;
      CORstring   ArgumentName;
   private:
      CORflagEntry(const CORflagEntry& Orig);
      CORflagEntry& operator=(const CORflagEntry& Orig);
   };

   CORstring Description;
   CORstring ProgramName;
   bool HasParsed;
   CORarray<CORstring> ExtraArgs;
   CORarray<CORparameterDescriptionEntry> ParamDescription;
   CORlist<CORauto<CORflagEntry> > FlagList;
   CORstring NullString;
   CORstring RepeatedFlagName;

   bool isFlag(const char* pArgument) const;
   CORflagEntry* createFlagIfNotInList(const CORstring& FlagName);
   CORflagEntry* addPresentFlag(const char* pArgument);
   CORflagEntry* flag(const CORstring& FlagName);
   const CORflagEntry* flag(const CORstring& FlagName) const;
   bool isFlagInList(const CORstring& FlagName) const;
   void addArgument(const char* pArgument);
   bool isHelpArgument(const CORstring& FlagName) const;
   bool isHelpFlag(const CORstring& FlagName) const;

   CORcommandLine(const CORcommandLine& Orig);
   CORcommandLine& operator=(const CORcommandLine& Orig);
};
