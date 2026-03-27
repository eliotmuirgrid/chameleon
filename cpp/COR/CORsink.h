#pragma once
//---------------------------------------------------------------------------
// Copyright (C) 2026 Eliot Muir.  All rights reserved.
//
// Module: CORsink
//
// Description:
//
// This is the base class for all objects that can act as
// a data sink. 
//
// CORostreams can also be used to stream data to CORsinks
// using the << operator.
//
// Subclasses only need to implement the write() method
// found on this interface. 
//
// Author: Eliot Muir
//---------------------------------------------------------------------------
#include "CORcore.h"

class CORstring;

class CORsink{
public:
   CORsink();
   virtual ~CORsink();
   // write() should return the amount of bytes
   // actually written from cpBuffer.
   virtual CORuint32 write( const void* cpBuffer, 
                            CORuint32 SizeOfBuffer ) = 0;
   virtual CORuint32 writeString(const CORstring& String);
   virtual void flush();
   virtual void onEndStream();
};

