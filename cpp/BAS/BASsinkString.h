#ifndef _BAS_SINK_STRING_H_
#define _BAS_SINK_STRING_H_
//-------------------------------------------------------
// Copyright (C) 2021 Eliot Muir.  All Rights Reserved
//
// BASsinkString
// 
// Sink which writes to A BASstring
//-------------------------------------------------------

#include "BASsink.h"
#include "BASstring.h"

class BASsinkString : public BASsink{
public:
   BASsinkString() {}
   virtual ~BASsinkString() {}

   virtual void write(const char* pData, int Size) { m_String.append(pData, Size); }
   virtual void flush() {}

   const BASstring& string() { return m_String; }
private:
   BASstring m_String;
};

#endif
