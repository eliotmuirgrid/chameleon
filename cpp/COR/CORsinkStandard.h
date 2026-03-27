#pragma once
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

#include <COR/CORsink.h>

#include <stdio.h>

class CORsinkFileHandle : public CORsink{
public:
   CORsinkFileHandle(FILE* pFileHandle) : m_pFileHandle(pFileHandle) {}
   virtual ~CORsinkFileHandle() {}
      
   virtual CORuint32 write(const void* cpBuffer, CORuint32 SizeOfBuffer);
   virtual CORuint32 writeString(const CORstring& String);

   virtual void flush();

   // We only need this on Windows. Unix does not do translations.
   void setBinaryMode(bool Set=true);
private:
   FILE* m_pFileHandle;
};

class CORsinkStandardOut : public CORsinkFileHandle{
public:
   CORsinkStandardOut() : CORsinkFileHandle(stdout) {}
   virtual ~CORsinkStandardOut() {}

   // Eliot - here for backward compatibility
   static void setBinaryMode(bool Set=true);
};

class CORsinkStandardErr : public CORsinkFileHandle{
public:
   CORsinkStandardErr() : CORsinkFileHandle(stderr) {}
   virtual ~CORsinkStandardErr() {}

   // Eliot - here for backward compatibility
   static void setBinaryMode(bool Set=true);
};

