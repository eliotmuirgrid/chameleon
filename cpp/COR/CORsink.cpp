//---------------------------------------------------------------------------
// Copyright (C) 2026 Eliot Muir.  All rights reserved.
//
// Module: CORsink
//
// Description:
//
// Implementation.
//
// Author: Eliot Muir
//---------------------------------------------------------------------------

// We should get rid of CORsource

#include <COR/CORsink.h>

CORsink::CORsink(){
   // do nothing
}

CORsink::~CORsink() {
  // do nothing - we used to flush but it's very bad to
  // call virtual functions in destructors
}


void CORsink::flush() {
   // do nothing. - we do this because other wise the compiler links the symbol
   // in multiple times which causes problems when CORsink is in DLL.  Hope there
   // is a way around this problem.
}

void CORsink::onEndStream() {
   // do nothing. - we do this because other wise the compiler links the symbol
   // in multiple times which causes problems when CORsink is in DLL.  Hope there
   // is a way around this problem.
}

CORuint32 CORsink::writeString(const CORstring& String) {
   return 0;
}
