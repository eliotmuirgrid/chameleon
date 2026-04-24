//-------------------------------------------------------
// Copyright (C) 2026 Eliot Muir. All rights reserved.
//
// BASguid
//-------------------------------------------------------

#include <BAS/BASguid.h>

#include <stdio.h>

#if defined(_WIN32)
#include <windows.h>
#include <ntsecapi.h>
#pragma comment(lib, "advapi32.lib")
#endif

static bool BASguidFillRandom(void* pOut, size_t len) {
#if defined(_WIN32)
   return RtlGenRandom(pOut, static_cast<ULONG>(len)) != FALSE;
#else
   FILE* f = fopen("/dev/urandom", "rb");
   if (!f) {
      return false;
   }
   bool ok = fread(pOut, 1, len, f) == len;
   fclose(f);
   return ok;
#endif
}

static void BASguidAppendHexByte(BASstring* pOut, unsigned char v) {
   static const char kHex[] = "0123456789abcdef";
   pOut->append(1, kHex[(v >> 4) & 0x0f]);
   pOut->append(1, kHex[v & 0x0f]);
}

static void BASguidFormatUuidV4(const unsigned char b[16], BASstring* pOut) {
   pOut->clear();
   for (int i = 0; i < 4; ++i) {
      BASguidAppendHexByte(pOut, b[i]);
   }
   pOut->append("-");
   for (int i = 4; i < 6; ++i) {
      BASguidAppendHexByte(pOut, b[i]);
   }
   pOut->append("-");
   for (int i = 6; i < 8; ++i) {
      BASguidAppendHexByte(pOut, b[i]);
   }
   pOut->append("-");
   for (int i = 8; i < 10; ++i) {
      BASguidAppendHexByte(pOut, b[i]);
   }
   pOut->append("-");
   for (int i = 10; i < 16; ++i) {
      BASguidAppendHexByte(pOut, b[i]);
   }
}

static void BASguidFormatHexDigits(const unsigned char* pBytes, int nBytes, int maxHexChars,
   BASstring* pOut) {
   static const char kHex[] = "0123456789abcdef";
   pOut->clear();
   int hexWritten = 0;
   for (int i = 0; i < nBytes && hexWritten < maxHexChars; ++i) {
      unsigned char v = pBytes[i];
      if (hexWritten < maxHexChars) {
         pOut->append(1, kHex[(v >> 4) & 0x0f]);
         hexWritten++;
      }
      if (hexWritten < maxHexChars) {
         pOut->append(1, kHex[v & 0x0f]);
         hexWritten++;
      }
   }
}

BASstring BASguid(int Size) {
   BASstring out;
   enum { kMaxSize = 4096 };
   if (Size <= 0 || Size > kMaxSize) {
      return out;
   }
   if (Size == 36) {
      unsigned char b[16];
      if (!BASguidFillRandom(b, 16)) {
         return out;
      }
      b[6] = static_cast<unsigned char>((b[6] & 0x0f) | 0x40);
      b[8] = static_cast<unsigned char>((b[8] & 0x3f) | 0x80);
      BASguidFormatUuidV4(b, &out);
      return out;
   }
   if (Size == 32) {
      unsigned char b[16];
      if (!BASguidFillRandom(b, 16)) {
         return out;
      }
      b[6] = static_cast<unsigned char>((b[6] & 0x0f) | 0x40);
      b[8] = static_cast<unsigned char>((b[8] & 0x3f) | 0x80);
      BASguidFormatHexDigits(b, 16, 32, &out);
      return out;
   }
   const int nBytes = (Size + 1) / 2;
   unsigned char buf[2048];
   if (nBytes > static_cast<int>(sizeof(buf))) {
      return out;
   }
   if (!BASguidFillRandom(buf, static_cast<size_t>(nBytes))) {
      return out;
   }
   BASguidFormatHexDigits(buf, nBytes, Size, &out);
   return out;
}
