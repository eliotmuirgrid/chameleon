#pragma once
//-------------------------------------------------------
// Copyright (C) 2026 Eliot Muir.  All rights reserved.
//
// BASdestination
//
// Destination virtual interface (where BASstream output is written).
//-------------------------------------------------------

class BASdestination{
public:
   BASdestination() {}
   virtual ~BASdestination() {}

   virtual void write(const char* pData, int Size) = 0;
   virtual void flush() = 0;
};
