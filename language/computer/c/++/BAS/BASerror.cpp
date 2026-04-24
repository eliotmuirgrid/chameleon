//-------------------------------------------------------
// Copyright (C) 2026 Eliot Muir. All rights reserved.
//
// BASerror
//
// Implementation
//-------------------------------------------------------
#include <BAS/BASerror.h>

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void BASabortWithMessage(const BASstring& Message) {
   fprintf(stderr, "Fatal Error. Abort with message: %s\n", Message.c_str());
   abort();
}

BASstring BASerrorStringFromErrno(int Errno) {
   if (Errno == 0) {
      return BASstring();
   }
#ifdef _WIN32
   char Buffer[256];
   if (strerror_s(Buffer, sizeof(Buffer), Errno) != 0) {
      return BASstring("Unknown error");
   }
   return BASstring(Buffer);
#else
   char Buffer[256];
   Buffer[0] = '\0';
#if defined(__GLIBC__) && defined(_GNU_SOURCE)
   // GNU libc: strerror_r returns char* (may point at Buffer or static storage).
   char* Message = strerror_r(Errno, Buffer, sizeof(Buffer));
   return BASstring(Message ? Message : Buffer);
#else
   // POSIX/XSI (macOS, musl, etc.): strerror_r returns int; message in Buffer on success.
   if (strerror_r(Errno, Buffer, sizeof(Buffer)) != 0) {
      return BASstring("Unknown error");
   }
   return BASstring(Buffer);
#endif
#endif
}
