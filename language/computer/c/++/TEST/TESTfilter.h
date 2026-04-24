#pragma once
//---------------------------------------------------------------------------
// Copyright (C) 2026 Eliot Muir.  All rights reserved.
//
// Module: TESTfilter
//
// Author: Eliot Muir
//
//
// Description:
//
// Functions related to filtering the tests - implementation only.
//---------------------------------------------------------------------------
class CORstring;

#include <TEST/TESTapp.h>

void TESTfilterTests(const CORstring& Glob, CORmap<CORstring, CORauto<CORclosure0> >* pTests);

