#pragma once
//---------------------------------------------------------------------------
// Copyright (C) 2026 Eliot Muir.  All rights reserved.
//
// Module: CORsinkString
//
// Description:
//
// CORstring sink object.  The data gets written into a CORstring.  Originally
// CORsink was implemented directly into CORstring - which had the negative of
// putting vtable overhead into CORstring directly.
//
// Author: Eliot Muir
//---------------------------------------------------------------------------

#include <COR/CORsink.h>
#include <COR/CORstring.h>

class CORsinkString : public CORsink {
public:
   CORsinkString();
   CORsinkString(CORstring& StringRef);
   CORsinkString(CORstring* pString);
   CORsinkString(CORstring* pString, bool IsOwner);

   virtual ~CORsinkString();

   virtual CORuint32 write(const void* cpBuffer, CORuint32 SizeOfBuffer);
   virtual CORuint32 writeString(const CORstring& String);
   virtual void flush();

   CORstring& string()             { return *m_pString; }
   const CORstring& string() const { return *m_pString; }
private:
   CORstring* m_pString;
   bool m_IsOwner;

   CORsinkString(const CORsinkString& Orig); // not allowed
   CORsinkString& operator=(const CORsinkString& Orig); // not allowed
};

