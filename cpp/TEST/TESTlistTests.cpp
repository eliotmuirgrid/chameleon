//---------------------------------------------------------------------------
// Copyright (C) 2026 Eliot Muir.  All rights reserved.
//
// Module: TESTlistTests
//
// Author: Eliot Muir
//
//
// Description:
//
// Implementation
//---------------------------------------------------------------------------
#include "TESTlistTests.h"

#include <FIL/FILutils.h>

#include <COR/CORmap.h>
#include <COR/CORlog.h>
COR_LOG_MODULE;

void TESTlistTests(const CORmap<CORstring, CORauto<CORclosure0> >& Tests){
   COR_FUNCTION(TESTlistTests);
   CORcout << "Available tests:" << newline;
   for (auto i = Tests.cbegin(); i != Tests.cend(); i++){
      CORcout << i->first << newline;

   } 
}
