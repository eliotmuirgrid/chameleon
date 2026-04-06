//---------------------------------------------------------------------------
// Copyright (C) 2026 Eliot Muir. All rights reserved.
//
// Module: tracker
//
// Command-line entry: load a TSV file (for example docs/concepts/health/foods.tsv).
//---------------------------------------------------------------------------
#include <BAS/BAScommandLine.h>
#include <BAS/BASfile.h>
#include <BAS/BAStrace.h>
#include <BAS/BASwriter.h>
#include <TSV/TSVreadWrite.h>

BAS_TRACE_INIT;

int main(int argc, const char** argv) {
   BAS_FUNCTION(main);
   BAScommandLine Cmd;
   BASstring ParseError;

   BASaddTraceOption(&Cmd);
   Cmd.add("help", "Show usage and exit.");
   Cmd.add("file", "Path to a TSV file to load.", "path");

   if (!Cmd.parse(argc, argv, &ParseError)) {
      BASout << ParseError << newline;
      BASout << Cmd;
      return 1;
   }
   BASapplyTraceOption(Cmd);

   if (Cmd.has("help")) {
      BASout << Cmd;
      return 0;
   }

   if (!Cmd.has("file")) {
      BASout << "Missing required --file <path>." << newline;
      BASout << Cmd;
      return 1;
   }

   const BASstring& Path = Cmd.get("file");
   BASstring FileBytes;
   if (!BASfileRead(Path, &FileBytes, &ParseError)) {
      BASout << ParseError << newline;
      return 1;
   }
   TSVtable Table;
   if (!TSVparse(FileBytes, &Table, &ParseError)) {
      BASout << ParseError << newline;
      return 1;
   }

   const int RowCount = Table.size();
   BASout << "Rows: " << RowCount << newline;
   if (RowCount > 0) {
      const int ColumnCount = Table[0].size();
      BASout << "Columns (row 0): " << ColumnCount << newline;
   }
   return 0;
}
