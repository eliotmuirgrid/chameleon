#pragma once
//-------------------------------------------------------
// Copyright (C) 2026 Eliot Muir.  All rights reserved.
//
// BASdestinationStandardOut
//
// Destination which writes to standard output.
//-------------------------------------------------------

#include <BAS/BASdestination.h>

class BASdestinationStandardOut : public BASdestination{
public:
   BASdestinationStandardOut();
   virtual ~BASdestinationStandardOut();

   virtual void write(const char* pData, int Size);
   virtual void flush();
};
