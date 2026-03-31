//-------------------------------------------------------
// Copyright (C) 2026 Eliot Muir.  All rights reserved.
//
// BASerror
// 
// Implementation
//-------------------------------------------------------

#include <BAS/BASerror.h>
#include <BAS/BAStrace.h>
BAS_TRACE_INIT;

BASerror::BASerror(const BASstring& Message, int Code) : m_Message(Message), m_Code(Code){
   BAS_METHOD(BASerror::BASerror);
   BAS_VAR(m_Message);
}

BASerror::BASerror(const BASerror& Orig) : m_Message(Orig.m_Message), m_Code(Orig.m_Code) {
   BAS_METHOD(BASerror::BASerror);
   BAS_VAR(m_Message);
}

BASerror::~BASerror(){

}

BASstream& operator<<(BASstream& Stream, const BASerror& Error){
   Stream << "Exception: " << Error.message() << " (" << Error.code() << ")";
   return Stream;
}
