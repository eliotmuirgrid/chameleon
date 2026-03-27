#pragma once
//--------------------------------------------------------------------------
// Copyright (C) 2026 Eliot Muir.  All rights reserved.
//
// Module: CORerror
//
// Description:
//
// Standard Error Class
//
// Author: Eliot Muir
//---------------------------------------------------------------------------

#include <COR/CORostream.h>
#include <COR/CORsinkString.h>

#include <stdlib.h>

class CORvar;

bool CORdebugInit(CORstring* pError);
bool CORdebugShutdown(CORstring* pError);

// Artificially trigger an abort if env var COR_ERR_ABORT is set to the current function name (__func__)
#define COR_ABORT_HERE_IF_ENV_VAR_IS_SET() \
   { \
      CORstring Crash = getenv("COR_ERR_ABORT"); \
      if (__func__ == Crash) { \
         CORcout << "Artificially abort application in " << __func__ << " as specified by environment variable COR_ERR_ABORT." << newline; \
         CORASSERT(false); \
      } \
   }
// Artificially trigger a segfault if env var COR_ERR_CRASH is set to the current function name (__func__)
#define COR_CRASH_HERE_IF_ENV_VAR_IS_SET() \
   { \
      CORstring Crash = getenv("COR_ERR_CRASH"); \
      if (__func__ == Crash) { \
         CORcout << "Artificially crash application in " << __func__ << " as specified by environment variable COR_ERR_CRASH." << newline; \
         int* pInt = NULL; \
         *pInt = 42; \
      } \
   }
#define COR_CRASH_HERE_IF_ENV_VAR_IS_SET_ON_CALL(N) \
   { \
      CORstring Crash = getenv("COR_ERR_CRASH"); \
      if (__func__ == Crash) { \
         static int i = 1; \
         if (i++ == N) { \
            CORcout << "Artificially crash application in " << __func__ << " as specified by environment variable COR_ERR_CRASH." << newline; \
            int* pInt = NULL; \
            *pInt = 42; \
         } \
      } \
   }
CORstring CORbacktrace();
void CORbacktrace2(CORostreamString& bt);

void CORsetDebugSearchPath(const CORstring& Path);
CORstring CORdebugSearchPath();

long CORlastError();  //GetLastError on WIN32 and errno on POSIX

// Calls strerror under the hood for POSIX and the equivalent routine for
CORstring CORerrorString(long ErrorCode);

CORstring CORlastErrorAsString();

class CORerror{
public:
   CORerror(const CORstring& Message, int Line, const char* File, int Code);
   CORerror(const CORstring& Message="", int Code=0);
   CORerror(const CORerror& Error, int Code);
   CORerror(const CORerror& Error);

   virtual ~CORerror();

   const CORstring& description() const { return m_Description; }
   int code() const { return m_Code; }
   const CORstring& file() const { return m_File; }
   int line() const { return m_Line; }

   void setDescription(const CORstring& Description);
   void setCode(int NewCode);

   virtual CORerror& operator=(const CORerror& Error);
   virtual bool operator==(const CORerror& Rhs) const;

protected:
   CORstring m_Description;
   int m_Code;
   CORstring m_File;
   int m_Line;
};

CORostream& operator<<(CORostream& Stream, const CORerror& Error);

#define COR_ERROR_STREAM(_Message, Number){\
   CORsinkString _ErrorSink;\
   CORostream Stream(_ErrorSink);\
   Stream << _Message;\
   throw CORerror(_ErrorSink.string(), __LINE__, __FILE__, Number);\
}

// Same as COR_ERROR_STREAM except without the File and Line information.  Use this in
// cases when the __FILE__ and __LINE__ macros do not actually provide good context information
// i.e. when the code is within a commonly used library and the actual problem is not in the library
// but results from application code using the library.
#define COR_ERROR_STREAM_PLAIN(Message, Number){\
   CORsinkString _ErrorSink;\
   CORostream ColErrorStream(_ErrorSink);\
   ColErrorStream << Message;\
   throw CORerror(_ErrorSink.string(), Number);\
}

// Aliases for the COR_ERROR_STREAM* macros that don't require you to explicitly
// set an error code.
#define COR_ERR_STREAM(Message) COR_ERROR_STREAM(Message, 0)
#define COR_ERR_STREAM_PLAIN(Message) COR_ERROR_STREAM_PLAIN(Message, 0)

// #13609 Wrapper around abort() to improve DBG crash dumps on Windows.
// For some reason, crash dumps do not include the stack frame calling abort()
// unless the CRT PDBs are available.  By using CORabort, the desired stack frame
// is captured, and the irrelevant CORabort() frame is lost instead.
// extern "C" for use from python.
extern "C" void CORabort();

void CORabortWithMessage(const CORstring& ErrorString);

typedef void (*CORabortCallback)(const CORstring& ErrorString);

void CORsetAbortCallback(CORabortCallback pAbortCallback);

#undef CORASSERT
#define COR_ASSERTS_ON
#ifdef COR_ASSERTS_ON
#define CORASSERT(Condition) \
   if (!(Condition)){\
      CORsinkString _ErrorSink;\
      CORostream ErrorStringStream_(_ErrorSink);\
      ErrorStringStream_ << __FILE__ << ':' << __LINE__ << " Assertion failed: " << #Condition;\
      CORabortWithMessage(_ErrorSink.string());\
   }
#else
#define CORASSERT(Condition)
#endif

#define COR_ABORT(Message)\
      CORsinkString _ErrorSink;\
      CORostream ErrorStringStream_(_ErrorSink);\
      ErrorStringStream_ << Message << " " << __FILE__ << ':' << __LINE__;\
      CORabortWithMessage(_ErrorSink.string());


// Implementation macros for CORPRECONDITION .

#undef COR_THROW_IMPL
#define COR_THROW_IMPL(Condition, Message, AssertType) \
   if (!(Condition)){\
      CORsinkString _ErrorSink;\
      CORostream ErrorStringStream_(_ErrorSink);\
      ErrorStringStream_ << Message << " " << __FILE__ << ':' << __LINE__ << " Assertion failed: " << #Condition;\
      CORabortWithMessage(_ErrorSink.string());\
   }

#undef COR_THROW_PRECONDITION
#define COR_THROW_PRECONDITION(Condition, ConditionStr) COR_THROW_IMPL(Condition, "Failed precondition: " << ConditionStr, 0);

#undef COR_THROW_MSG_PRECONDITION
#define COR_THROW_MSG_PRECONDITION(Condition, ConditionStr, Message) COR_THROW_IMPL(Condition, "Failed precondition: " << ConditionStr << ", " << Message, 0);


#ifdef COR_ASSERTS_ON
   #define CORPRECONDITION(Condition) COR_THROW_PRECONDITION(Condition, #Condition)
   #define CORMSGPRECONDITION(Condition, Message) COR_THROW_MSG_PRECONDITION(Condition, #Condition, Message)
#else
   #define CORPRECONDITION(Condition)
   #define CORMSGPRECONDITION(Condition, Message)
#endif

