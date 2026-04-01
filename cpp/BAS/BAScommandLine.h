#pragma once
//-------------------------------------------------------
// Copyright (C) 2026 Eliot Muir.  All rights reserved.
//
// BAScommandLine
// 
// Human-friendly command line argument parser
//
// Deliberately minimalistic.  If you need more features, write your own.
//-------------------------------------------------------

#include <BAS/BASdictOrdered.h>
#include <BAS/BASstring.h>

class BASstream;

class BAScommandLine {
public:
   BAScommandLine();
   ~BAScommandLine();

   // 1. Setup: Register what the program can do
   // If placeholder is empty, it's a simple toggle (e.g., --verbose)
   // If placeholder has text, it expects a value (e.g., --port 8080)
   void add(const BASstring& Name, const BASstring& Description, const BASstring& Placeholder = "");

   // 2. Action: Process the raw arguments from main()
   bool parse(int argc, const char** argv, BASstring* pError = nullptr);

   // 3. Retrieval: Ask questions about what the user typed
   bool has(const BASstring& Name) const;
   const BASstring& get(const BASstring& Name) const;

   // 4. Help: Get a formatted string for users who need guidance
   BASstring usage() const;

private:
   struct BASoption {
      BASoption(const BASstring& Desc, const BASstring& PlaceHolder)
         : Description(Desc), Placeholder(PlaceHolder), IsPresent(false) {}

      BASstring Description;
      BASstring Placeholder; // If not empty, this option requires a value
      bool IsPresent;
      BASstring Value;
   };

   BASstring m_BinaryName;
   BASdictOrdered<BASstring, BASoption> m_Options;
};

// Allow easy printing of usage via streams
BASstream& operator<<(BASstream& stream, const BAScommandLine& cmd);

