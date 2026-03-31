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
#include <BAS/BASstream.h>
#include <BAS/BASstring.h>

int main() {
   BASstring Message("Hello world from BASstring.");
   BASout << Message << newline;
   return 0;
}
