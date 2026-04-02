#pragma once
//-------------------------------------------------------
// Copyright (C) 2026 Eliot Muir.  All rights reserved.
//
// BASdestinationString
//
// Destination which appends into a BASstring.
//-------------------------------------------------------

#include <BAS/BASdestination.h>
#include <BAS/BASstring.h>

class BASdestinationString : public BASdestination{
public:
   BASdestinationString() {}
   virtual ~BASdestinationString() {}

   virtual void write(const char* pData, int Size) { m_String.append(pData, Size); }
   virtual void flush() {}

   const BASstring& string() { return m_String; }

private:
   BASstring m_String;
};
