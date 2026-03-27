//---------------------------------------------------------------------------
// Copyright (C) 2026 Eliot Muir.  All rights reserved.
//
// Module: CORsinkString
//
// Description:
//
// Implementation
//
// Author: Eliot Muir
//---------------------------------------------------------------------------
#include <COR/CORsinkString.h>

#include <COR/CORlog.h>
COR_LOG_MODULE;

CORsinkString::CORsinkString() : m_pString(new CORstring()), m_IsOwner(true) {
}

CORsinkString::CORsinkString(CORstring& StringRef) : m_pString(&StringRef), m_IsOwner(false) {
}

CORsinkString::CORsinkString(CORstring* pString) : m_pString(pString), m_IsOwner(true) {
}

CORsinkString::CORsinkString(CORstring* pString, bool IsOwner) : m_pString(pString), m_IsOwner(IsOwner) {
}

CORsinkString::~CORsinkString(){
   if (m_IsOwner){
      delete m_pString;
   }
}

CORuint32 CORsinkString::write(const void* cpBuffer, CORuint32 SizeOfBuffer){
   m_pString->append((const char*)cpBuffer, SizeOfBuffer);
   return SizeOfBuffer;
}

CORuint32 CORsinkString::writeString(const CORstring& String){
   return this->write(String.get_buffer(), String.size());
}

void CORsinkString::flush() {
}
