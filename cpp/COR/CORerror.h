#pragma once
//--------------------------------------------------------------------------
// Copyright (C) 2026 Eliot Muir.  All rights reserved.
//
// Module: Error support
//
// Description:
//
// Abort, assertion, and error helper declarations.
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


// Implementation macros for abort-based precondition checks.

#undef COR_ABORT_IMPL
#define COR_ABORT_IMPL(Condition, Message) \
   if (!(Condition)){\
      CORsinkString _ErrorSink;\
      CORostream ErrorStringStream_(_ErrorSink);\
      ErrorStringStream_ << Message << " " << __FILE__ << ':' << __LINE__ << " Assertion failed: " << #Condition;\
      CORabortWithMessage(_ErrorSink.string());\
   }

#undef COR_ABORT_PRECONDITION
#define COR_ABORT_PRECONDITION(Condition, ConditionStr) COR_ABORT_IMPL(Condition, "Failed precondition: " << ConditionStr);

#undef COR_ABORT_MSG_PRECONDITION
#define COR_ABORT_MSG_PRECONDITION(Condition, ConditionStr, Message) COR_ABORT_IMPL(Condition, "Failed precondition: " << ConditionStr << ", " << Message);


#ifdef COR_ASSERTS_ON
   #define CORPRECONDITION(Condition) COR_ABORT_PRECONDITION(Condition, #Condition)
   #define CORMSGPRECONDITION(Condition, Message) COR_ABORT_MSG_PRECONDITION(Condition, #Condition, Message)
#else
   #define CORPRECONDITION(Condition)
   #define CORMSGPRECONDITION(Condition, Message)
#endif

