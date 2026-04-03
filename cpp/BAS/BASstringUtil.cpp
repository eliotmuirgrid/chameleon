//-------------------------------------------------------
// Copyright (C) 2026 Eliot Muir.  All rights reserved.
//
// BASstringUtil
//
// Implementation
//-------------------------------------------------------

#include <BAS/BASstringUtil.h>

#include <BAS/BASerror.h>

// Single pass: simple and cache-friendly for small results. An alternative is to count
// delimiters first (segment count = delimiter count + 1), then pLines->reserve(...) before
// pushing, which avoids BASarray reallocations when there are many segments at the cost of
// a second scan over Source.
void BASstringSplit(const BASstring& Source, char Delimiter, BASarray<BASstring>* pLines) {
   BAS_ASSERT(pLines);
   pLines->clear();
   const int ByteCount = Source.size();
   int Start = 0;
   for (int i = 0; i < ByteCount; ++i) {
      if (Source[i] == Delimiter) {
         pLines->push(BASstring(Source.data() + Start, i - Start));
         Start = i + 1;
      }
   }
   pLines->push(BASstring(Source.data() + Start, ByteCount - Start));
}
