#pragma once
//-------------------------------------------------------
// Copyright (C) 2026 Eliot Muir.  All rights reserved.
//
// BASassert
//
// Abort-based assertion helpers.
//-------------------------------------------------------

#include <BAS/BASdestinationString.h>
#include <BAS/BASwriter.h>

void BASabortWithMessage(const BASstring& Message);

#define BAS_ASSERT(Condition) \
   if (!(Condition)) { \
      BASdestinationString Destination; \
      BASwriter Writer(Destination); \
      Writer << __FILE__ << ':' << __LINE__ << " Assertion failed: " << #Condition; \
      BASabortWithMessage(Destination.string()); \
   }

#define BAS_FAIL(Message) \
   BASdestinationString Destination; \
   BASwriter Writer(Destination); \
   Writer << Message << " " << __FILE__ << ':' << __LINE__; \
   BASabortWithMessage(Destination.string());

