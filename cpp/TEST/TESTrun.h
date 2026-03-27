#pragma once
//---------------------------------------------------------------------------
// Copyright (C) 2026 Eliot Muir.  All rights reserved.
//
// Module: TESTrun
//
// Author: Eliot Muir
//
//
// Description:
//
// Functions related to running the tests.  Not required for users of the
// the library - use TESTapp.h instead.
//---------------------------------------------------------------------------

#include <TEST/TESTapp.h>

class SCKloop;

class TESTsummary{
public:
   TESTsummary(int Count) : Hung(false), TimeoutTimerId(-1), TestCount(Count), CountOfFail(Count) {}
   ~TESTsummary();
   CORmap<CORstring, CORstring> m_FailedBuilds;


   int TestCount;
   int CountOfFail;
   bool Hung;
   int TimeoutTimerId;
};

int TESTrunTestCollection(const CORmap<CORstring, CORauto<CORclosure0> >& Tests);
int TESTrunSingleThreadedTestCollection(const CORmap<CORstring, CORauto<CORclosure0> >& Tests);


