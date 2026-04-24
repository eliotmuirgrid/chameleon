#pragma once
//-------------------------------------------------------
// Copyright (C) 2026 Eliot Muir. All rights reserved.
//
// BASerror
//
// Abort-based assertion helpers and errno-to-text. OS surface stays small: C/POSIX
// errno only (strerror_r / strerror_s). Win32 GetLastError / FormatMessage is
// deliberately not here; add a separate helper if native Win32 codes matter.
//-------------------------------------------------------

#include <BAS/BASdestinationString.h>
#include <BAS/BASstring.h>
#include <BAS/BASwriter.h>

void BASabortWithMessage(const BASstring& Message);

// Text for a C/POSIX errno value (0 yields an empty string). Thread-safe where
// the C library supports it. On Windows this is CRT errno, not GetLastError codes.
BASstring BASerrorStringFromErrno(int Errno);

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
