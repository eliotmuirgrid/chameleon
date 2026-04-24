#pragma once
//-------------------------------------------------------
// Copyright (C) 2026 Eliot Muir.  All rights reserved.
//
// BAScommandLine
// 
// Human-friendly command line argument parser.
//
// The idea is:
// 1. Declare the options your program understands.
// 2. Parse argv.
// 3. Ask questions about what the user actually supplied.
// 4. Show usage or act on the answers.
//
// BAScommandLine is intentionally small. It does not try to guess the shape
// of your program. The calling code stays in control of what options exist,
// what they mean, and what happens after parsing.
//
// Typical usage:
//
//    #include <BAS/BAScommandLine.h>
//    #include <BAS/BAStrace.h>
//
//    BAScommandLine Cmd;
//    BASstring Error;
//
//    // Add the standard trace option explicitly if this program wants it.
//    BASaddTraceOption(&Cmd);
//
//    // Add the options that matter for this program.
//    Cmd.add("help", "Show usage and exit.");
//    Cmd.add("port", "Port to listen on.", "number");
//
//    if (!Cmd.parse(argc, argv, &Error)) {
//       BASout << Error << newline;
//       BASout << Cmd;
//       return 1;
//    }
//
//    // Apply tracing explicitly after parsing if this program wants tracing.
//    BASapplyTraceOption(Cmd);
//
//    if (Cmd.has("help")) {
//       BASout << Cmd;
//       return 0;
//    }
//
//    if (Cmd.has("port")) {
//       BASstring Port = Cmd.get("port");
//       // The program decides what to do with it.
//    }
//
// Notes:
// - `add("name", "desc")` declares a toggle like `--help`.
// - `add("name", "desc", "value")` declares an option that expects a value
//   like `--port 8080`.
// - `has()` tells you whether the user supplied an option.
// - `get()` returns the parsed value for an option that takes an argument.
// - The BAStrace helpers are optional. They are explicit on purpose so the
//   program chooses whether tracing belongs in its command line interface.
//
// Deliberately minimalistic. If you need more features, write your own.
//-------------------------------------------------------

#include <BAS/BASdictOrdered.h>
#include <BAS/BASstring.h>

class BASwriter;

class BAScommandLine {
public:
   BAScommandLine();
   ~BAScommandLine();

   // Register an option.
   // If Placeholder is empty, this is a toggle like `--help`.
   // If Placeholder has text, this option expects a value like `--port 8080`.
   void add(const BASstring& Name, const BASstring& Description, const BASstring& Placeholder = "");

   // Parse the raw arguments from main().
   // Returns false on any parse error and optionally writes a human-readable
   // explanation to pError.
   bool parse(int argc, const char** argv, BASstring* pError = nullptr);

   // Ask whether the user supplied this option.
   bool has(const BASstring& Name) const;

   // Get the value supplied for an option that takes an argument.
   // Returns an empty string if the option was not supplied.
   const BASstring& get(const BASstring& Name) const;

   // Build a human-readable usage string from the registered options.
   BASstring usage() const;

private:
   struct BASoption {
      BASoption(const BASstring& Desc, const BASstring& PlaceHolder)
         : Description(Desc), Placeholder(PlaceHolder), IsPresent(false) {}

      BASstring Description;
      BASstring Placeholder; // If not empty, this option requires a value.
      bool IsPresent;
      BASstring Value;
   };

   BASstring m_BinaryName;
   BASdictOrdered<BASstring, BASoption> m_Options;
};

// Write the same text returned by usage().
BASwriter& operator<<(BASwriter& writer, const BAScommandLine& cmd);

