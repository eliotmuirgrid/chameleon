//---------------------------------------------------------------------------
// Copyright (C) 2026 Eliot Muir.  All rights reserved.
//
// Module: CORostream
//
// Description:
//
// Implementation
//
// Author: Eliot Muir
//---------------------------------------------------------------------------
#include <COR/CORostream.h>
#include <COR/CORerror.h>
#include <COR/CORsinkStandard.h>
#include <COR/CORsinkString.h>

// Eliot at the moment I don't think this code is working.  Does it matter?
// Probably not since we don't have a lot of static objects with destructors that
// we need to trace though - I try not to have these at all since they are a headache - Eliot

#ifdef COR_ENABLE_TRACING
// CORcerr and CORcout resources must be leaked to accommodate
// CORlog tracing after exit() in static object destructors.
CORostream CORcerr(new CORsinkStandardErr(), false, false);
CORostream CORcout(new CORsinkStandardOut(), false, false);
#else
CORostream CORcerr(new CORsinkStandardErr(), true);
CORostream CORcout(new CORsinkStandardOut(), true);
#endif

CORostream CORclog(new CORsinkStandardOut(), true);

class CORostreamPrivate {
public:
   CORostreamPrivate(CORsink* ipSink, bool Owner)
    : IndentContent("   "),
#ifdef _WIN32 // #6155
      NewLine("\r\n"),
      NewLineAndIndent("\r\n"),
#else // POSIX
      NewLine("\n"),
      NewLineAndIndent("\n"),
#endif
      CountOfIndent(0),
      pSink(ipSink),
      NumberBase_(CORostream::Decimal),
#ifdef COR_ENABLE_TRACING
      m_Delete_pMember(true),
#endif
      IsSinkOwner(Owner)
   {
   }
   ~CORostreamPrivate(){}

   CORostream::ENumberBase NumberBase_;
   CORstring NewLine;
   CORstring IndentContent;
   CORstring NewLineAndIndent;
   CORsink*  pSink;
   CORuint32 CountOfIndent;
   bool      IsSinkOwner;

#ifdef COR_ENABLE_TRACING
   bool m_Delete_pMember;
#endif

   inline bool isDec() const { return NumberBase_ == CORostream::Decimal; }

   void makeIndentString() {
      // TODO - this is not at all optimized - Eliot
      NewLineAndIndent = NewLine;
      for (CORuint32 IndentIndex = 0; IndentIndex < CountOfIndent; IndentIndex++) {
         NewLineAndIndent += IndentContent;
      }
   }
};

CORostream::CORostream(CORsink* pSink, bool Owner) {
   pMember = new CORostreamPrivate(pSink, Owner);
}

CORostream::CORostream(CORsink& Sink) {
   pMember = new CORostreamPrivate(&Sink, false); // not the owner
}

CORostream::CORostream(CORstring& String){
   pMember = new CORostreamPrivate(new CORsinkString(String), true);
}

CORostream::CORostream(CORstring* pString, bool Owner){
   pMember = new CORostreamPrivate(new CORsinkString(pString, Owner), true);
}

#ifdef COR_ENABLE_TRACING
CORostream::CORostream(CORsink* pSink, bool Owner, bool Delete_pMember) {
   pMember = new CORostreamPrivate(pSink, Owner);
   pMember->m_Delete_pMember = false;
}
#endif

CORostream::~CORostream() {
#ifdef COR_ENABLE_TRACING
   // this may be needed by the leaked CORcout and CORcerr instances?
   // if (!pMember->m_Delete_pMember) { pMember->pSink->flush(); }
#endif
   if (pMember->IsSinkOwner) {
      delete pMember->pSink;
   }
#ifdef COR_ENABLE_TRACING
   if (pMember->m_Delete_pMember)
#endif
   {
      delete pMember;
   }
}

void CORostream::newline() {
   // TODO - one of these days we should performance tune CORostream...Eliot
   pMember->pSink->write((CORuint8*)pMember->NewLineAndIndent.c_str(), pMember->NewLineAndIndent.size());
}

void CORostream::setNewLine(const char* NewLine) {
   pMember->NewLine = NewLine;
   pMember->makeIndentString();
}

const char* CORostream::getNewLine() const {
   return pMember->NewLine.c_str();
}

void CORostream::setIndentContent(const CORstring& IndentContent) {
   pMember->IndentContent = IndentContent;
   pMember->makeIndentString();
}

const CORstring& CORostream::indentContent() const {
   return pMember->IndentContent;
}

void CORostream::indent() {
   pMember->CountOfIndent++;
   pMember->makeIndentString();
}

void CORostream::unindent() {
   if (pMember->CountOfIndent > 0) {
      pMember->CountOfIndent--;
   }
   pMember->makeIndentString();
}

void CORostream::resetIndent() {
   setCountOfIndent(0);
}

void CORostream::setCountOfIndent(CORuint32 NewValue) {
   pMember->CountOfIndent = NewValue;
   pMember->makeIndentString();
}

CORuint32 CORostream::countOfIndent() const {
   return pMember->CountOfIndent;
}

void CORostream::flush() {
   pMember->pSink->flush();
}

bool CORostream::isSinkOwner() const {
   return pMember->IsSinkOwner;
}

CORsink* CORostream::sink() {
   return pMember->pSink;
}

CORsink* CORostream::setSink(CORsink* pSink, bool IsOwner) {
   CORPRECONDITION(pSink != NULL);
   if (pMember->IsSinkOwner)
   {
      delete pMember->pSink;
   }
   pMember->pSink = pSink;
   pMember->IsSinkOwner = IsOwner;
   return pSink;
}

CORostream::ENumberBase CORostream::numberBase() const {
   return pMember->NumberBase_;
}

void CORostream::setNumberBase(ENumberBase Base) {
   pMember->NumberBase_ = Base;
}

CORostream& CORostream::operator<<(CORostream&(*Stream)(CORostream&)) {
   Stream(*this);
   return *this;
}

CORostream& CORostream::operator<<(CORostream&(*Stream)(CORostream&, int n)) {
   return *this;
}

CORostream& CORostream::operator<<(unsigned char Character) {
   pMember->pSink->write(&Character, 1);
   return *this;
}

CORostream& CORostream::operator<<(char Character) {
   pMember->pSink->write((CORuint8*)&Character,1);
   return *this;
}

CORostream& CORostream::operator<<(const char* pString) {
   if (pString) {
      pMember->pSink->write((CORuint8*)pString, strlen(pString));
   }
   return *this;
}

CORostream& CORostream::operator <<(const CORstring& String) {
   pMember->pSink->write(String.c_str(), String.size());
   return *this;
}

CORostream& CORostream::write(const void* Data, int Length) {
   pMember->pSink->write((const char*)Data, Length);
   return *this;
}

CORostream& CORostream::operator<<(CORint32 Number) {
   char Buffer[32];
   int CountOfChar = snprintf(Buffer, 32, pMember->isDec()? "%i": "%X", Number);
   pMember->pSink->write((CORuint8*)Buffer, CountOfChar);
   return *this;
}

CORostream& CORostream::operator<<(CORuint32 Number) {
   char Buffer[32];
   int CountOfChar = snprintf(Buffer, 32, pMember->isDec()? "%u": "%X", Number);
   pMember->pSink->write((CORuint8*)Buffer, CountOfChar);
   return *this;
}

CORostream& CORostream::operator<<(CORint16 Number) {
   char Buffer[32];
   int CountOfChar = snprintf(Buffer, 32, pMember->isDec()? "%hi": "%hX", Number);
   pMember->pSink->write((CORuint8*)Buffer, CountOfChar);
   return *this;
}

CORostream& CORostream::operator<<(CORuint16 Number) {
   char Buffer[32];
   int CountOfChar = snprintf(Buffer, 32, pMember->isDec()? "%hu": "%hX", Number);
   pMember->pSink->write((CORuint8*)Buffer, CountOfChar);
   return *this;
}

CORostream& CORostream::operator<<(CORint64 Number) {
   char Buffer[64];
   int CountOfChar = snprintf(Buffer, 64, pMember->isDec()? "%lli": "%llX", Number);
   pMember->pSink->write((CORuint8*)Buffer, CountOfChar);
   return *this;
}

CORostream& CORostream::operator<<(CORuint64 Number) {
   char Buffer[64];
   int CountOfChar = snprintf(Buffer, 64, pMember->isDec()? "%llu": "%llX", Number);
   pMember->pSink->write((CORuint8*)Buffer, CountOfChar);
   return *this;
}

CORostream& CORostream::operator<<(CORfloat32 Number) {
   char Buffer[512]; // take no chances with outputting doubles
   int CountOfChar = snprintf(Buffer, 512, "%f", Number);
   pMember->pSink->write((CORuint8*)Buffer, CountOfChar);
   return *this;
}

CORostream& CORostream::operator<<(CORfloat64 Number) {
   char CharBuffer[512]; // take no chances with outputting doubles
   int CountOfChar = snprintf(CharBuffer, 512, "%f", Number);
   pMember->pSink->write(CharBuffer, CountOfChar);
   return *this;
}

CORostream& CORostream::operator<<(const void* Pointer) {
   char CharBuffer[32];
   // %p is portable, but doesn't output in a standard format
   // int CountOfChar = snprintf(CharBuffer, 32, "%p", Pointer);
#ifdef _WIN32 //Needed for MSVC and MSYS2 toolchains, mingw toolchain is compliant and does not need this
   int CountOfChar = snprintf(CharBuffer, 32, "0x%I64x", Pointer);
#else
   int CountOfChar = snprintf(CharBuffer, 32, "0x%lx", (unsigned long)Pointer);
#endif
   pMember->pSink->write(CharBuffer, CountOfChar);
   return *this;
}

CORostream& CORostream::operator<<(bool Boolean) {
   if (Boolean) {
      return operator<<("True");
   }
   return operator<<("False");
}

CORostream& flush(CORostream& _outs) {
   _outs.flush();
   return _outs;
}

CORostream& newline(CORostream& _outs) {
   _outs.newline();
   return _outs;
}

CORostream& hex(CORostream& _outs) {
   _outs.setNumberBase(CORostream::Hexadecimal);
   return _outs;
}

CORostream& decimal(CORostream& _outs) {
   _outs.setNumberBase(CORostream::Decimal);
   return _outs;
}

void __set_indent(CORostream& OutStream, const CORstring& IndentContent) {
   OutStream.setIndentContent(IndentContent);
}

CORostream& indent(CORostream& OutStream) {
   OutStream.indent();
   return OutStream;
}

CORostream& unindent(CORostream& OutStream) {
   OutStream.unindent();
   return OutStream;
}

CORostream& reset_indent(CORostream& OutStream) {
   OutStream.resetIndent();
   return OutStream;
}

CORostreamManip::~CORostreamManip() {
}

CORostreamManip* set_indent(const CORstring& TagName) {
   return new CORostreamManip1<CORstring>(__set_indent, TagName);
}

// To avoid a heap allocated CORstring, the address of the yet-to-be-constructed
// CORostreamString.m_String data member is passed to the parent CORostream's
// constructor. This is okay because that pointer to the CORstring member
// is not directly or indirectly used by CORostreamString's ctor or dtor.
// There is a test in CORexample to verify this assumption with valgrind.
//
CORostreamString::CORostreamString() : CORostream(m_String) {
}

CORostreamString::~CORostreamString() {
}

const char* CORostreamString::c_str() const {
   return m_String.c_str();
}

const CORstring& CORostreamString::str() const {
   return m_String;
}
