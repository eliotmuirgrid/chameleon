#pragma once
//---------------------------------------------------------------------------
// Copyright (C) 2026 Eliot Muir.  All rights reserved.
//
// Module: CORmutex
//
// Description:
//
// A mutex object - use in conjunction with CORlocker
// This is the one thread object that we have in the COR library because
// it is necessary to implement many of the objects with the COR library.
// For the rest of the threading objects you should look in the MT library.
//
// Renamed from CORcriticalSection.
//
// It's useful to read this over.
//
// Author: Eliot Muir
//---------------------------------------------------------------------------

#include "CORcore.h"

class CORmutexPrivate;

class CORmutex{
public:
   CORmutex();
   ~CORmutex();

   void lock();
   void unlock();

   // pointer to the raw mutex structure or handle - implementation only!
   void* handle();  
private:
   CORmutexPrivate* pMember;

   CORmutex(const CORmutex& Orig);
   CORmutex& operator=(const CORmutex& Orig);
};
