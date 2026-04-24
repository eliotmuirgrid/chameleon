//-------------------------------------------------------
// Copyright (C) 2026 Eliot Muir.  All rights reserved.
//
// BAStrace
// 
// Implementation
//-------------------------------------------------------

#include <BAS/BAStrace.h>
BAS_TRACE_INIT;

#include <BAS/BAScommandLine.h>
#include <BAS/BASdestinationFilePipe.h>
#include <BAS/BASmatchPattern.h>

#include <time.h>
#include <stdio.h>  // for printf

#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

BASpass s_TracePass;

BASwriter BAStrace(new BASdestinationFilePipe(STDOUT_FILENO), false);  // purposely leaked.

static thread_local int s_BASindentLevel=0;

// TODO - how do we get millisecond timing?
void  BAStimeStampOld() {
   time_t TimeValue = time(NULL);
   struct tm* LocalTime = localtime(&TimeValue);
   char LineBuffer[64];
   strftime(LineBuffer, sizeof(LineBuffer), "T %H:%M:%S ", LocalTime);
   BAStrace << LineBuffer;
}

long BASthreadId(){
   return (long)pthread_self();
}

void BAStimeStamp(const char* pModule){
   int            Milliseconds;
   time_t          Seconds;
   struct timespec ClockSpec;

   clock_gettime(CLOCK_REALTIME, &ClockSpec);

   Seconds  = ClockSpec.tv_sec;
   Milliseconds = round(ClockSpec.tv_nsec / 1.0e6); // Convert nanoseconds to milliseconds
   if (Milliseconds > 999) {
       Seconds++;
       Milliseconds = 0;
   }
   struct tm* LocalTime = localtime(&Seconds);
   char LineBuffer[64];
   strftime(LineBuffer, sizeof(LineBuffer), "\nT %H:%M:%S", LocalTime);  // prepend newline.
   BAStrace << LineBuffer << ".";
   char Buffer[4];
   snprintf(Buffer, sizeof(Buffer), "%03i", Milliseconds);  // zero pad the millseconds
   BAStrace << Buffer << " " << (void*)BASthreadId() << " ";
   BAStrace << pModule << " ";  // TODO should output size.
   BASwriteIndent(BAStrace.destination(), s_BASindentLevel);
}

BASmodule::BASmodule(const char* pFileName){
   int Length = strlen(pFileName)-4;
   strncpy(ModuleName, pFileName, Length);
   char* EndPtr = ModuleName + sizeof(ModuleName)-2;
   for (char* i = ModuleName + Length; i != EndPtr; i++){
      *i = ' ';
   }
   ModuleName[sizeof(ModuleName)-1] = 0;
}

static const char* s_TracePattern = "";
static const char* s_pTraceDescription = "Turn on debug tracing of C++ code using glob match expression for files. i.e. --trace \"* -BASstring\" (match everything, exclude BASstring).";

void BASsetTracePattern(const char* pPattern){
   s_TracePattern = strdup(pPattern);  // purposely leaked.
}

void BASaddTraceOption(BAScommandLine* pCommandLine){
   pCommandLine->add("trace", s_pTraceDescription, "glob match expression");
}

void BASapplyTraceOption(const BAScommandLine& CommandLine){
   if (CommandLine.has("trace")){
      BASsetTracePattern(CommandLine.get("trace").data());
   }
}

bool BASloggingEnabled(const char* ModuleName, int* pResult){
   if (BASmatchPattern(ModuleName, s_TracePattern)){
      *pResult = 1;
      return true;
   } else {
      *pResult = -1;
      return false;
   }
}

BASraiiFunc::BASraiiFunc(const char* Name, const char* pModule, int Line, bool Trace) : m_pModule(pModule), m_pName(Name), m_Trace(Trace) {
   if (Trace){
      BASpassHold TracePassHold(s_TracePass);
      BAStimeStamp(pModule); BAStrace << ">" << Name << " Line:" << Line;
      s_BASindentLevel++;
   }
}

BASraiiFunc::BASraiiFunc(const char* Name, const char* pModule, int Line, const void* pInstance, bool Trace) : m_pModule(pModule), m_pName(Name), m_Trace(Trace) {
   if (Trace){
      BASpassHold TracePassHold(s_TracePass);
      BAStimeStamp(pModule); BAStrace << ">" << Name << " Line:" << Line << " this=" << pInstance;
      s_BASindentLevel++;
   }
}

BASraiiFunc::~BASraiiFunc(){
   if (m_Trace){
      s_BASindentLevel--;
      BASpassHold TracePassHold(s_TracePass);
      BAStimeStamp(m_pModule); BAStrace << "<" << m_pName;
   }
}

#define G ". . . . . . . . . . . . . . . . . . . . . . . . . "
static const char* s_pIndent = G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G;

void BASwriteIndent(BASdestination* pDestination, int Level){
   pDestination->write(s_pIndent, Level*2);
}