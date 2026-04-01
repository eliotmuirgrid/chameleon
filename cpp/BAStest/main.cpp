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
#include <BAS/BASargParser.h>
#include <BAS/BASstream.h>
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
   BASargParser Args;
   Args.addFlag("help", "Show usage and exit.");
   if (!Args.parse(argc, argv)) {
      BASout << Args;
      return 1;
   }
   if (Args.present("help")) {
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

   return 0;
}
