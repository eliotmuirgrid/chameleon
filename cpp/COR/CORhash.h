#pragma once
//---------------------------------------------------------------------------
// Copyright (C) 2026 Eliot Muir.  All rights reserved.
//
// Module: CORhash
//
// Description:
//
// The default hash functions. It is a template specialized to allow easy specification
// for our simple types.
//
// This is an example of using it:
//
// CORhashmap<CORstring, CORstring> StudentTable(CORhash<CORstring>::defaultHash);
//
// Of course if you need more specialized hash function you can always write them
// and use CORhashmap independently of CORhash.
//
// Author: Nasron Cheong
//---------------------------------------------------------------------------
#include <COR/CORcore.h>

class CORstring;

//supported default hash implementations
//
// CORuint32/int32
// CORuint64/int64
// CORuint16/int16
// CORuint8/int8  <- this usually is unsigned char/char
// CORstring

template <class T>
struct CORhash{
   static CORindex defaultHash(const T& Key);
   //default compare defers the the types equal operator
   static bool equalKey(const T& Key1, const T& Key2){
      return (Key1 == Key2) != 0;
   }
};

template <> CORindex CORhash<CORuint64>::defaultHash(const CORuint64& Key);
template <> CORindex CORhash<CORint64>:: defaultHash(const CORint64&  Key);
template <> CORindex CORhash<CORuint32>::defaultHash(const CORuint32& Key);
template <> CORindex CORhash<CORint32>:: defaultHash(const CORint32&  Key);
template <> CORindex CORhash<CORuint16>::defaultHash(const CORuint16& Key);
template <> CORindex CORhash<CORint16>:: defaultHash(const CORint16&  Key);
template <> CORindex CORhash<CORuint8>:: defaultHash(const CORuint8&  Key);
template <> CORindex CORhash<CORint8>::  defaultHash(const CORint8&   Key);
template <> CORindex CORhash<CORstring>::defaultHash(const CORstring& Key);

template <typename T>
struct CORhashPointer{
   static CORindex defaultHash(const T& Key){
      return CORhash<CORuint64>::defaultHash((CORuint64)Key);
   }

   static bool equalKey(const T& Key1, const T& Key2){
      return (Key1 == Key2) != 0;
   }
};

