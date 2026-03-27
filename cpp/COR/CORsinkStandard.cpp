//---------------------------------------------------------------------------
// Copyright (C) 2026 Eliot Muir.  All rights reserved.
//
// Module: CORsinkStandard
//
// Description:
//
// CORsink objects for standard out and standard error and also
// a trace sink for use in _WIN32
//
// Author: Eliot Muir
//---------------------------------------------------------------------------
#include "CORsinkStandard.h"
#include "CORstring.h"

#ifdef _WIN32
   #include <io.h>
   #include <FCNTL.h>
#endif

CORuint32 CORsinkFileHandle::write(const void* cpBuffer, CORuint32 SizeOfBuffer) {
   if (SizeOfBuffer) { fwrite(cpBuffer, 1, SizeOfBuffer, m_pFileHandle); }
   return SizeOfBuffer;
}

CORuint32 CORsinkFileHandle::writeString(const CORstring& String) {
   return this->write(&String, String.size());
}

void CORsinkFileHandle::flush() {
   fflush(m_pFileHandle);
}

void CORsetBinaryModeOnFileHandle(FILE* pHandle, bool Set) {
#ifdef _WIN32  // We only need this on Windows. Unix does not do translations.
   _setmode(_fileno(pHandle), Set ? _O_BINARY : _O_TEXT);
#endif 
}

void  CORsinkFileHandle::setBinaryMode(bool Set) { CORsetBinaryModeOnFileHandle(m_pFileHandle, Set); }
void CORsinkStandardOut::setBinaryMode(bool Set) { CORsetBinaryModeOnFileHandle(stdout, Set);        }
void CORsinkStandardErr::setBinaryMode(bool Set) { CORsetBinaryModeOnFileHandle(stderr, Set);        }

