#pragma once
//-------------------------------------------------------
// Copyright (C) 2026 Eliot Muir.  All rights reserved.
//
// BASsinkString
// 
// Sink which writes to A BASstring
//-------------------------------------------------------

#include <BAS/BASsink.h>
#include <BAS/BASstring.h>

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

