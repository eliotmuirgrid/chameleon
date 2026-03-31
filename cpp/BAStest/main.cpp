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
#include <BAS/BASclosure.h>
#include <BAS/BASstring.h>

static void BAShello(const BASstring& Prefix, int Value) {
   BASout << Prefix << " " << Value << newline;
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

   BASout << "BAScall example: bind the trailing arguments, then call with the leading arguments." << newline;

   auto pFreeCall = BAScall<const BASstring&>::create(&BAShello, 42);
   pFreeCall->call(BASstring("Free function call"));
   delete pFreeCall;

   BASexample Example;
   auto pMethodCall = BAScall<const BASstring&>::create(&Example, &BASexample::print, 99);
   pMethodCall->call(BASstring("Method call"));
   delete pMethodCall;

   BASout << "BASclosure example: bind the trailing arguments, then run with the leading arguments." << newline;

   auto pFreeClosure = BASnewClosure1(&BAShello, 42);
   pFreeClosure->run(BASstring("Free function closure"));
   delete pFreeClosure;

   auto pMethodClosure = BASnewClosure1(&Example, &BASexample::print, 99);
   pMethodClosure->run(BASstring("Method closure"));
   delete pMethodClosure;

   return 0;
}
