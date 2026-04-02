//-------------------------------------------------------
// Copyright (C) 2026 Eliot Muir. All rights reserved.
//
// BASarray
//
// Implementation
//-------------------------------------------------------

#include <BAS/BASarray.h>
#include <BAS/BASassert.h>
#include <BAS/BAStrace.h>
BAS_TRACE_INIT;

void BAScheckBoundary(int i, int Size){
   //BAS_FUNCTION(BAScheckBoundary);
   if (i >= Size){
      BAS_FAIL("Array index " << i << " must be less than size " << Size);
   }
}

// Copy pasted from BASstring deliberately so we get tracing
unsigned int BAScalculateCapacity(unsigned int v){
   BAS_FUNCTION(BAScalculateCapacity);
   BAS_VAR(v);
   v--;
   v |= v >> 1;
   v |= v >> 2;
   v |= v >> 4;
   v |= v >> 8;
   v |= v >> 16;
   v++;
   BAS_VAR(v);
   return v;
}
