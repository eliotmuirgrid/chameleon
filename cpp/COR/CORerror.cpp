//---------------------------------------------------------------------------
// Copyright (C) 2026 Eliot Muir.  All rights reserved.
//
// Module: Error support
//
// Description: Implementation
//
// Author: Eliot Muir
//
//---------------------------------------------------------------------------
#include <COR/CORerror.h>
#include <COR/CORlog.h>
#include <COR/CORstring.h>

COR_LOG_MODULE;

#ifdef _WIN32
   #include <COR/CORwindows.h>
#else
   #include <errno.h>
   #include <execinfo.h>
   #include <stdio.h>
   #include <stdlib.h>
   #include <unistd.h>
#endif

bool CORdebugInit(CORstring* pError) {
   (void)pError;
   return true;
}

bool CORdebugShutdown(CORstring* pError) {
   (void)pError;
   return true;
}

CORstring CORbacktrace() {
#ifdef _WIN32
   return CORstring();
#else
   void* buffer[128];
   int n = backtrace(buffer, static_cast<int>(sizeof buffer / sizeof buffer[0]));
   char** symbols = backtrace_symbols(buffer, n);
   if (!symbols) {
      return CORstring();
   }
   CORstring s;
   for (int i = 0; i < n; ++i) {
      if (i > 0) {
         s += "\n";
      }
      s += symbols[i];
   }
   free(symbols);
   return s;
#endif
}

void CORbacktrace2(CORostreamString& bt) {
   bt << CORbacktrace();
}

CORstring CORerrorString(long ErrorCode){
#ifdef _WIN32
   char* MessageBuffer;
   DWORD dwFormatFlags = FORMAT_MESSAGE_ALLOCATE_BUFFER |
                         FORMAT_MESSAGE_IGNORE_INSERTS |
                         FORMAT_MESSAGE_FROM_SYSTEM;

   ::FormatMessage(dwFormatFlags,
      NULL,
      static_cast<DWORD>(ErrorCode),
      MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
      (char*) &MessageBuffer,
      0,
      NULL);
   CORstring Result = MessageBuffer;
   LocalFree(MessageBuffer);
   return Result;
#else
   CORstring Result;
   Result.setCapacity(255);
   strerror_r(static_cast<int>(ErrorCode), Result.get_buffer(), Result.capacity() - 1);
   Result.setSize(strlen(Result.c_str()));
   return Result;
#endif
}

#ifdef _WIN32
void CORthrowWin32Error(long ErrorCode, const char* Description, int LineNumber, const char* FileName){
   CORsinkString ErrorSink;
   CORostream MessageStream(ErrorSink);
   if (Description){
      MessageStream << Description;
   }
   if (LineNumber != -1 && (FileName != NULL)){
      MessageStream << " on line " << LineNumber << " in " << FileName << " - ";
   }
      MessageStream << CORerrorString(ErrorCode);
      throw ErrorSink.string();
}
#endif

long CORlastError(){
#ifdef _WIN32
   return static_cast<long>(::GetLastError());
#else
   return errno;
#endif
}

CORstring CORlastErrorAsString(){
   int LastError = static_cast<int>(CORlastError());
   COR_FUNCTION(CORlastErrorAsString);
   return CORerrorString(LastError);
}

extern "C" void CORabort(){
   abort();
}

void CORdefaultAbortCallback(const CORstring& ErrorString){
   COR_FUNCTION(CORdefaultAbortCallback);
   COR_ERR(ErrorString << CORbacktrace());
   CORcout << "Fatal Error. Abort with message: " << ErrorString << CORbacktrace() << flush;
}

CORabortCallback s_pAbortCallback = &CORdefaultAbortCallback;

void CORsetAbortCallback(CORabortCallback pAbortCallback){
   COR_FUNCTION(CORsetAbortCallback);
   COR_VAR(pAbortCallback);
   s_pAbortCallback = pAbortCallback;
}

void CORabortWithMessage(const CORstring& ErrorString){
   COR_FUNCTION(CORabortWithMessage);
   (*s_pAbortCallback)(ErrorString);
   abort();
}

CORstring s_CORdebugSearchPath;

void CORsetDebugSearchPath(const CORstring& Path){
   COR_FUNCTION(CORsetDebugSearchPath);
   COR_VAR(Path);
   s_CORdebugSearchPath = Path;
}

CORstring CORdebugSearchPath(){
   COR_FUNCTION(CORdebugSearchPath);
   return s_CORdebugSearchPath;
}
