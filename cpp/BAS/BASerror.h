#pragma once
//-------------------------------------------------------
// Copyright (C) 2026 Eliot Muir.  All rights reserved.
//
// BASerror
// 
// Exception class - KISS design.
//-------------------------------------------------------

#include <BAS/BASstring.h>
#include <BAS/BASsinkString.h>
#include <BAS/BASstream.h>

class BASerror{
public:
   BASerror(const BASstring& Message, int Code);
   BASerror(const BASerror& Orig);
   ~BASerror();

   const BASstring& message() const{ return m_Message; } 
   int code() const                { return m_Code;    }
private:
   int m_Code;
   BASstring m_Message;
};

BASstream& operator<<(BASstream& Stream, const BASerror& Error);

#define BAS_RAISE_ERROR(X, C) {\
      BASsinkString Sink;\
      BASstream Stream(Sink);\
      Stream << X;\
      throw BASerror(Sink.string(), C);\
   }

