#pragma once
//-------------------------------------------------------
// Copyright (C) 2026 Eliot Muir.  All rights reserved.
//
// BASassert
//
// Abort-based assertion helpers.
//-------------------------------------------------------

#include <BAS/BASsinkString.h>
#include <BAS/BASstream.h>

void BASabortWithMessage(const BASstring& Message);

#define BAS_ASSERT(Condition) \
   if (!(Condition)) { \
      BASsinkString Sink; \
      BASstream Stream(Sink); \
      Stream << __FILE__ << ':' << __LINE__ << " Assertion failed: " << #Condition; \
      BASabortWithMessage(Sink.string()); \
   }

#define BAS_FAIL(Message) \
   BASsinkString Sink; \
   BASstream Stream(Sink); \
   Stream << Message << " " << __FILE__ << ':' << __LINE__; \
   BASabortWithMessage(Sink.string());

