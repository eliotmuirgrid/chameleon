#pragma once
//---------------------------------------------------------------------------
// Copyright (C) 2026 Eliot Muir.  All rights reserved.
//
// Module: TESTapp
//
// Author: Eliot Muir
//
//
// Description:
//
// This is the public interface to the TEST framework.
//---------------------------------------------------------------------------

#include <COR/CORostream.h>
#include <COR/CORmap.h>
#include <COR/CORclosure.h>
#include <COR/CORauto.h>

typedef void (*TESTtest)();

class TESTfailure{
public:
   TESTfailure() {}
   explicit TESTfailure(const CORstring& Description) : m_Description(Description) {}

   const CORstring& description() const { return m_Description; }

private:
   CORstring m_Description;
};

inline CORostream& operator<<(CORostream& Stream, const TESTfailure& Failure) {
   Stream << Failure.description();
   return Stream;
}

class TESTapp{
public:
   TESTapp() {}
   ~TESTapp() {}

   void add       (const CORstring& Name, TESTtest     pTestFunc   );
   void addClosure(const CORstring& Name, CORclosure0* pTestClosure); // Takes ownership

   int run(int argc,const char** argv);
   int runSingleThreaded(int argc,const char** argv);

   CORmap<CORstring, CORauto<CORclosure0> >& map() { return m_TestCollection; }
private:
   CORmap<CORstring, CORauto<CORclosure0> > m_TestCollection;
};

#define TEST_ASSERT_EQUALS(_EXPECTED, _ACTUAL) \
   if (_EXPECTED!=(_ACTUAL))  { \
      CORstring  __ErrorString; \
      CORostream __Stream(__ErrorString); \
      __Stream << "Expected should be equal to actual." << newline; \
      __Stream << "Assert:      [" << #_EXPECTED  << " == " << #_ACTUAL << "]" << newline; \
      __Stream << "Expected:    [" << _EXPECTED << "]" << newline; \
      __Stream << "Actual:      [" << (_ACTUAL) << "]";  \
      throw TESTfailure(__ErrorString); \
   } 

#define TEST_ASSERT_MESSAGE(_EXPRESSION,_MESSAGE_ON_FAIL) \
   if (!(_EXPRESSION))  {\
      CORstring  __ErrorString; \
      CORostream __Stream(__ErrorString); \
      __Stream << _MESSAGE_ON_FAIL << newline; \
      __Stream << "Assert:      [" << #_EXPRESSION << "]" << newline; \
      throw TESTfailure(__ErrorString); \
   }

#define TEST_ASSERT(_EXPRESSION) \
   if (!(_EXPRESSION))  {\
      CORstring __ErrorString; \
      CORostream __Stream(__ErrorString); \
      __Stream << "Assert:      [" << #_EXPRESSION << "]" << newline; \
      throw TESTfailure(__ErrorString); \
   }

