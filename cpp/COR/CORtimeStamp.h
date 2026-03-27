#pragma once
//---------------------------------------------------------------------------
// Copyright (C) 2026 Eliot Muir.  All rights reserved.
//
// Module: CORdateTime
//
// Description:
//
// CORtimeStamp is useful for some operations
// 
// Author:  Eliot Muir
//---------------------------------------------------------------------------

class CORstring;
class CORostreaam;

#include <time.h>

// a timestamp structure - just plain old data - no ctor, no dtor.
struct CORtimeStamp{
   CORuint64 tv_sec;  // time_t compatible
   CORuint64 tv_usec; // microseconds - NOT milliseconds!
   time_t asTimeT() const { return (time_t)tv_sec; }
   int milliseconds() const { return (int)(tv_usec / 1000); }
   void addMilliseconds(int Milliseconds);
};

bool operator==(const CORtimeStamp& a, const CORtimeStamp& b);
bool operator<=(const CORtimeStamp& a, const CORtimeStamp& b);
bool operator<(const CORtimeStamp& Lhs, const CORtimeStamp& Rhs);
bool operator==(const CORtimeStamp& Lhs, const CORtimeStamp& Rhs);
CORostream& operator<<(CORostream& Stream, const CORtimeStamp& Time);

int CORtimeStampDiffInMillisecond(const CORtimeStamp& Lhs, const CORtimeStamp& Rhs);

// Populate the CORtimeStamp with the current time with microsecond resolution
void CORcurrentTimeStamp(CORtimeStamp*);

// Convert from CORtimeStamp to year, month, day, hour, minute, second, millisecond
void CORtimeStampToComponents(
   const CORtimeStamp& TimeStamp,
   CORuint32& Year,
   CORuint32& Month,
   CORuint32& Day,
   CORuint32& Hour,
   CORuint32& Min,
   CORuint32& Sec,
   CORuint32& Ms
);

