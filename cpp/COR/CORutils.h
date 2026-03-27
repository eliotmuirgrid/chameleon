#pragma once
//---------------------------------------------------------------------------
// Copyright (C) 2026 Eliot Muir.  All rights reserved.
//
// Module: CORutils
//
// Description:
//
// CORutils - At the moment it just has CORsleep.  Probably will get
// rid of CORmath.h at some state and put that code in here.
//
// Author: Eliot Muir
//---------------------------------------------------------------------------

#include "CORstring.h"

class CORvar;

// This function is correctly implemented under POSIX and Windows
// and will wait for the number of milliseconds given.
//
// Note - there are no hard guarantees on the sleep duration on any platform.
// CORsleep may be interrupted and return early, or sleep slightly longer
// than requested - especially is the machine is under CPU load.
//
// Be aware that the minimum granularity of sleeping on Windows is 15ms.
// Time granularlity on POSIX varies from platform to platform - it may be
// 10ms, 1ms, or some other value. For Linux in particular, the minimum sleep
// duration depends on what HZ setting the kernel was compiled with.
//
// A CORsleep(0) may be useful for yielding the thread, much like an I/O operation.
void CORsleep(int TimeOutInMilliseconds);

// Environment variable expansion function.
//
// Replace all occurances of sub-strings of the form "${VAR}" with the values
// of the environment variables of the same name. If the environment variable is
// not set, it will be replaced with "", an empty string.
//
// Note: This is a SINGLE PASS function that will expand as many ${VARIABLE}s as 
// it finds in the string. It will not attempt to replace any ${VARIABLE}s that arise
// as result of the single-pass expansion.
//
// Also note: this function will has no facility to avoid escaping string literals
// of the form "${VARIABLE}".
CORstring CORexpandEnvironmentVariables(const CORstring&);

// This is similar to CORexpandEnvironmentVariables but expands them using the CachedVars provided.
CORstring CORexpandEnvironmentVariablesUsingCache(const CORstring& Original, const CORvar& CachedVars);

// A simple glob-like matching function.
//
// ListOfGlobs is a whitespace separated list of glob-like patterns.
// If a glob begins with '-', then it is an exclusionary pattern.
// Globs in ListOfGlobs are evaluated from left to right.
//
// For example:
//
//  CORglobMatch("AB* CA* -ABCdef -CAR* -CAT* BIRD CATS", "ABc") == true
//  CORglobMatch("AB* CA* -ABCdef -CAR* -CAT* BIRD CATS", "CAB") == true
//  CORglobMatch("AB* CA* -ABCdef -CAR* -CAT* BIRD CATS", "ABCdef") == false
//  CORglobMatch("AB* CA* -ABCdef -CAR* -CAT* BIRD CATS", "ABCde") == true
//  CORglobMatch("AB* CA* -ABCdef -CAR* -CAT* BIRD CATS", "CARP") == false
//  CORglobMatch("AB* CA* -ABCdef -CAR* -CAT* BIRD CATS", "CAT") == false
//  CORglobMatch("AB* CA* -ABCdef -CAR* -CAT* BIRD CATS", "CATS") == true
//  CORglobMatch("AB* CA* -ABCdef -CAR* -CAT* BIRD CATS", "BIRD") == true
//  CORglobMatch("AB* CA* -ABCdef -CAR* -CAT* BIRD CATS", "BIRDs") == false
//  CORglobMatch("AB* CA* -ABCdef -CAR* -CAT* BIRD CATS", "CART") == false
//
bool CORglobMatch(const char* ListOfGlobs, const char* ModuleToMatch);

