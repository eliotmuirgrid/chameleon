//---------------------------------------------------------------------------
// Copyright (C) 2026 Eliot Muir. All rights reserved.
//
// Module: tracker
//
// Command-line entry: load a TSV (e.g. foods.tsv), optional name search.
//---------------------------------------------------------------------------
#include <BAS/BASarray.h>
#include <BAS/BAScommandLine.h>
#include <BAS/BASfile.h>
#include <BAS/BASmatchPattern.h>
#include <BAS/BASstring.h>
#include <BAS/BAStrace.h>
#include <BAS/BASwriter.h>
#include <TSV/TSVreadWrite.h>

BAS_TRACE_INIT;

static void TrackerSplitTokens(const BASstring& Source, BASarray<BASstring>* pTokens) {
   pTokens->clear();
   const int N = Source.size();
   int Start = -1;
   for (int I = 0; I < N; ++I) {
      const char C = Source[I];
      if (C == ' ' || C == ',' || C == '\t') {
         if (Start >= 0) {
            pTokens->push(BASstring(Source.data() + Start, I - Start));
            Start = -1;
         }
      } else {
         if (Start < 0) {
            Start = I;
         }
      }
   }
   if (Start >= 0) {
      pTokens->push(BASstring(Source.data() + Start, N - Start));
   }
}

/// When the user does not use `*`, each query word becomes `*word*` and all words must match.
static bool TrackerNameMatchesWrappedPatterns(
   const char* NameLower, const BASarray<BASstring>& Patterns) {
   for (int P = 0; P < Patterns.size(); ++P) {
      if (!BASmatchPattern(NameLower, Patterns[P].c_str())) {
         return false;
      }
   }
   return true;
}

int main(int argc, const char** argv) {
   BAS_FUNCTION(main);
   BAScommandLine Cmd;
   BASstring ParseError;

   BASaddTraceOption(&Cmd);
   Cmd.add("help", "Show usage and exit.");
   Cmd.add("add",
           "Search column 0 (food names) with BASmatchPattern. If the pattern "
           "has no *, each word is wrapped as *word* (substring); all words must "
           "match. If you use *, the pattern is unchanged (space-separated tokens "
           "are OR in BASmatchPattern).",
           "pattern");

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

   BASstring FileBytes;
   if (!BASfileRead("foods.tsv", &FileBytes, &ParseError)) {
      BASout << ParseError << newline;
      return 1;
   }
   TSVtable Table;
   if (!TSVparse(FileBytes, &Table, &ParseError)) {
      BASout << ParseError << newline;
      return 1;
   }

   const int RowCount = Table.size();
   if (Cmd.has("add")) {
      if (RowCount < 2) {
         BASout << "Need a header row and at least one data row for --add." << newline;
         return 1;
      }
      const BASstring& Query = Cmd.get("add");
      if (Query.size() == 0) {
         BASout << "--add needs a non-empty pattern." << newline;
         return 1;
      }
      BASstring QueryLower(Query);
      QueryLower.toLowercase();
      bool HasStar = false;
      for (int I = 0; I < QueryLower.size(); ++I) {
         if (QueryLower[I] == '*') {
            HasStar = true;
            break;
         }
      }
      BASarray<BASstring> PatternsNoStar;
      if (!HasStar) {
         BASarray<BASstring> Words;
         TrackerSplitTokens(QueryLower, &Words);
         for (int W = 0; W < Words.size(); ++W) {
            if (Words[W].size() == 0) {
               continue;
            }
            BASstring Wrapped;
            Wrapped += '*';
            Wrapped += Words[W];
            Wrapped += '*';
            PatternsNoStar.push(Wrapped);
         }
      }
      BASstring NameLower;
      int MatchCount = 0;
      for (int R = 1; R < RowCount; ++R) {
         if (Table[R].size() < 1) {
            continue;
         }
         const BASstring& Name = Table[R][0];
         NameLower = Name;
         NameLower.toLowercase();
         bool RowMatches = false;
         if (HasStar) {
            RowMatches = BASmatchPattern(NameLower.c_str(), QueryLower.c_str());
         } else if (PatternsNoStar.size() > 0) {
            RowMatches =
               TrackerNameMatchesWrappedPatterns(NameLower.c_str(), PatternsNoStar);
         }
         if (RowMatches) {
            BASout << Name << newline;
            ++MatchCount;
         }
      }
      if (MatchCount == 0) {
         BASout << "No matches." << newline;
      }
      return 0;
   }

   BASout << "Rows: " << RowCount << newline;
   if (RowCount > 0) {
      const int ColumnCount = Table[0].size();
      BASout << "Columns (row 0): " << ColumnCount << newline;
   }
   return 0;
}
