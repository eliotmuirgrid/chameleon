//---------------------------------------------------------------------------
// Copyright (C) 2026 Eliot Muir.  All rights reserved.
//
// Module: CORtimeStamp implementation
//
// Description:
//
// CORtimeStamp implementation
//
// Author: Eliot Muir 
//---------------------------------------------------------------------------

//TODO change all simple types!
//the naming conventions are all wrong...need to unit
//this baby first though to make sure we don't break anything!

#include <math.h>
#include "CORhashmap.h"

#ifdef _WIN32
#  define CHM_FILETIME
#endif

#include "CORmutex.h"
#include "CORlocker.h"
#include "CORlog.h"
COR_LOG_MODULE;

#include <stdio.h>

#ifdef _WIN32
#   include <windows.h>
#   include <process.h>
#else
#   include <sys/select.h>
#   include <sys/time.h>
#   include <unistd.h>
#   include <sched.h>
#endif

#include "CORtimeStamp.h"

#ifdef _WIN32
static inline void FileTimeToUnixTime(CORuint64* result, const FILETIME* in) {
   const CORuint64 DELTA_EPOCH_IN_USEC = 11644473600000000 /*LL*/;
   CORuint64 v = in->dwHighDateTime;
   v = v << 32;
   v |= in->dwLowDateTime;
   v /= 10;   // convert from 100 nanosecond periods to microseconds
   v -= DELTA_EPOCH_IN_USEC;  // convert to Unix epoch
   *result = v;
}
#endif

// #11252 get a millisecond resultion timestamp consistent with CORdateTime/time(0)/localtime().
// Do not use GetLocalTime().
void CORcurrentTimeStamp(CORtimeStamp* out) {
#ifdef _WIN32
   FILETIME ftime;
# ifndef _WIN32_WCE
   GetSystemTimeAsFileTime(&ftime);
# else
   SYSTEMTIME st;
   GetSystemTime(&st);
   SystemTimeToFileTime(&st, &ftime);
# endif
   CORuint64 now = 0;
   FileTimeToUnixTime(&now, &ftime);
   out->tv_sec  = now / 1000000;
   out->tv_usec = now % 1000000;
#else
   // UNIX
   struct timeval tv;
   ::gettimeofday(&tv, 0);
   out->tv_sec  = tv.tv_sec;
   out->tv_usec = tv.tv_usec;
#endif
}

void CORtimeStampToComponents (
   const CORtimeStamp& TimeStamp,
   CORuint32& Year,
   CORuint32& Month,
   CORuint32& Day,
   CORuint32& Hour,
   CORuint32& Min,
   CORuint32& Sec,
   CORuint32& Ms
)
{
   time_t TimeT = TimeStamp.asTimeT();
   struct tm tm;
#ifdef _WIN32
   tm = *::localtime(&TimeT); // threadsafe on Windows: uses thread local storage
#else
   localtime_r(&TimeT, &tm);
#endif
   Year  = tm.tm_year + 1900;
   Month = tm.tm_mon + 1;
   Day   = tm.tm_mday;
   Hour  = tm.tm_hour;
   Min   = tm.tm_min;
   Sec   = tm.tm_sec;
   Ms    = TimeStamp.milliseconds();
}

void CORtimeStamp::addMilliseconds(int Milliseconds){
   COR_METHOD(CORtimeStamp::addMilliseconds);
   COR_VAR2(tv_sec, tv_usec);
   tv_sec  += Milliseconds / 1000;
   tv_usec += (Milliseconds % 1000) * 1000;
   if (tv_usec >= 1000000){
      tv_sec += tv_usec / 1000000;
      tv_usec = tv_usec % 1000000;
   }
   COR_VAR2(tv_sec, tv_usec);
}

bool operator==(const CORtimeStamp& a, const CORtimeStamp& b){
   return ((a.tv_sec == b.tv_sec) && (a.tv_usec == b.tv_usec)) ? true : false;
}

bool operator<=(const CORtimeStamp& a, const CORtimeStamp& b){
   if (a.tv_sec < b.tv_sec){ return true; }
   else if (a.tv_sec == b.tv_sec){
      if (a.tv_usec <= b.tv_usec){ return true; }
   }
   return false;
}

bool operator<(const CORtimeStamp& Lhs, const CORtimeStamp& Rhs){
   if (Lhs.tv_sec < Rhs.tv_sec){ return true; }
   else if (Lhs.tv_sec == Rhs.tv_sec){
      if (Lhs.tv_usec < Rhs.tv_usec){ return true; }
   }
   return false;
}

int CORtimeStampDiffInMillisecond(const CORtimeStamp& Lhs, const CORtimeStamp& Rhs){
   COR_FUNCTION(CORtimeStampDiffInMillisecond);
   int Seconds = Lhs.tv_sec - Rhs.tv_sec;
   COR_VAR(Seconds);
   int Microseconds = Lhs.tv_usec - Rhs.tv_usec;
   COR_VAR(Microseconds);
   if (Microseconds < 0 && Seconds > 0){
      Microseconds += 1000000;
      Seconds -= 1;
   }
   return (Seconds * 1000) + (Microseconds / 1000);\
}

CORostream& operator<<(CORostream& Stream, const CORtimeStamp& Time) {
   Stream << "Time: " << Time.tv_sec << " seconds and " << Time.tv_usec << " microseconds";
   return Stream;
}