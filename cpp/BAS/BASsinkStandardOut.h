#pragma once
//-------------------------------------------------------
// Copyright (C) 2026 Eliot Muir.  All rights reserved.
//
// BASsinkStandardOut
// 
// Sink which writes to standard out.
//-------------------------------------------------------

#include <BAS/BASsink.h>

class BASsinkStandardOut : public BASsink{
public:
   BASsinkStandardOut();
   virtual ~BASsinkStandardOut();

   virtual void write(const char* pData, int Size); 
   virtual void flush();
};

