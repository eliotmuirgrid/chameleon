#pragma once
//---------------------------------------------------------------------------
// Copyright (C) 2026 Eliot Muir.  All rights reserved.
//
// Module: TESTlastFailed
//
// Author: Eliot Muir
//
//
// Description:
//
// Code that is used to implement logic for saving the tests that need to
// be re-run.  Implementation only - users use TESTapp.h instead.
//---------------------------------------------------------------------------

#include <TEST/TESTapp.h>

class TESTsummary;

void TESTfilterFailedTests(CORmap<CORstring, CORauto<CORclosure0> >* pTests);
void TESTsaveFailedTests(const TESTsummary& Summary);

