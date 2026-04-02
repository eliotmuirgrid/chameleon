#pragma once
//-------------------------------------------------------
// Copyright (C) 2026 Eliot Muir.  All rights reserved.
//
// BASassert
//
// Abort-based assertion helpers.
//-------------------------------------------------------

#include <BAS/BASdestinationString.h>
#include <BAS/BASstream.h>

void BASabortWithMessage(const BASstring& Message);

#define BAS_ASSERT(Condition) \
   if (!(Condition)) { \
      BASdestinationString Destination; \
      BASstream Stream(Destination); \
      Stream << __FILE__ << ':' << __LINE__ << " Assertion failed: " << #Condition; \
      BASabortWithMessage(Destination.string()); \
   }

#define BAS_FAIL(Message) \
   BASdestinationString Destination; \
   BASstream Stream(Destination); \
   Stream << Message << " " << __FILE__ << ':' << __LINE__; \
   BASabortWithMessage(Destination.string());

