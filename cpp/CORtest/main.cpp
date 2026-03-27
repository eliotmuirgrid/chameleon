//---------------------------------------------------------------------------
// Copyright (C) 2026 Eliot Muir.  All rights reserved.
//
// Module: CORtest
//
// Description: 
//
// CORtest tests application.
//
// Author: Eliot Muir
//
//---------------------------------------------------------------------------
#include <COR/CORcommandLine.h>

#include <COR/CORlog.h>

COR_LOG_MODULE;

int main(int argc, const char** argv) {
   CORcommandLine Line;
   Line.setDescription("CORtest");
   CORlogAddCommandLineFlags(Line);
   Line.addFlagWithoutArgument("help", "Show usage and exit.");
   Line.parseArgs(argc, argv);
   if (Line.parsingErrorsPresent(CORcout)) {
      Line.showUsage(CORcout);
      return 1;
   }
   COR_LOG_INIT(argc, argv);
   if (Line.isFlagPresent("help")) {
      Line.showUsage(CORcout);
      return 0;
   }
   return 0;
}
