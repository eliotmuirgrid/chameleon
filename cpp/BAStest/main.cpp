//---------------------------------------------------------------------------
// Copyright (C) 2026 Eliot Muir.  All rights reserved.
//
// Module: BAStest
//
// Description:
//
// Basic BAS test application.
//
// Author: Eliot Muir
//---------------------------------------------------------------------------
#include <BAS/BAScommandLine.h>
#include <BAS/BASdictOrdered.h>
#include <BAS/BASdictUnordered.h>
#include <BAS/BASwriter.h>
#include <BAS/BAStrace.h>
#include <BAS/BAScall.h>
#include <BAS/BASstring.h>

static void BAShello(const BASstring& Prefix, int Value) {
   BASout << Prefix << " " << Value << newline;
}

static void BASrunGreeting(BAScall1<const BASstring&>* pCall) {
   pCall->run(BASstring("Greeting"));
}

class BASexample {
public:
   void print(const BASstring& Prefix, int Value) {
      BASout << Prefix << " " << Value << newline;
   }
};

int main(int argc, const char** argv) {
   BAScommandLine Args;
   BASstring Error;
   BASaddTraceOption(&Args);
   Args.add("help", "Show usage and exit.");
   if (!Args.parse(argc, argv, &Error)) {
      if (!Error.empty()) {
         BASout << Error << newline;
      }
      BASout << Args;
      return 1;
   }
   BASapplyTraceOption(Args);
   if (Args.has("help")) {
      BASout << Args;
      return 0;
   }

   BASstring Message("Hello world from BASstring.");
   BASout << Message << newline;

   BASout << "BAScall example: bind the trailing arguments, then run with the leading arguments." << newline;

   BASexample Example;
   auto pFreeCall = BAScallBind1(&BAShello, 42);
   BASrunGreeting(pFreeCall);
   delete pFreeCall;

   auto pMethodCall = BAScallBind1(&Example, &BASexample::print, 99);
   BASrunGreeting(pMethodCall);
   delete pMethodCall;

   BASout << "BASwriter operator<< on dictionaries (same keys, different layouts):" << newline;

   BASdictUnordered<BASstring, int> Unordered(8);
   Unordered[BASstring("gamma")] = 3;
   Unordered[BASstring("alpha")] = 1;
   Unordered[BASstring("beta")] = 2;
   BASout << "BASdictUnordered (size, buckets, then entries per bucket):" << newline;
   BASout << Unordered << newline;

   BASdictOrdered<BASstring, int> Ordered;
   Ordered[BASstring("gamma")] = 3;
   Ordered[BASstring("alpha")] = 1;
   Ordered[BASstring("beta")] = 2;
   BASout << "BASdictOrdered (size, then key = value in ascending key order):" << newline;
   BASout << Ordered << newline;

   return 0;
}
