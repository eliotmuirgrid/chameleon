#pragma once
//---------------------------------------------------------------------------
// Copyright (C) 2026 Eliot Muir.  All rights reserved.
//
// Module: CORlocker
//
// Description:
//
// RA II Locker class - designed to provide safe, exception-proof locking
// of mutexes.
// i.e. imagine we have class Foo which has a mutex member
// and we are in a method of class Foo called X....
// void Foo::X()  {
//   CORlocker Lock(m_Mutex);
//   // The constructor of the the CORlocker object has locked the
//   // mutex
//   // :
//   // We do some stuff, an error is encountered and an exception is
//   // is thrown.
//   // Because the Lock object is always destroyed when we exit the 
//   // function we are guaranteed to always unlock the mutex
//   // as we exit.
// }
// Without CORlocker...
// void Foo::X() {
//    m_Mutex.lock();
//    // we do some stuff, an error is encountered and an exception is thrown
//    // so we *never* call the next line:
//    m_Mutex.unlock();
//    // oh bugger, the application freezes because the mutex is
//    // is locked and other threads which try and invoke the lock() method
//    // will hang indefinitely.
// }
// 
// Author: Eliot Muir
//---------------------------------------------------------------------------

#include "CORmutex.h"

class CORlocker{
public:
   CORlocker(CORmutex& Mutex);
   ~CORlocker(); 
private:
   CORmutex* m_pMutex;
   CORlocker(const CORlocker& Orig);
   CORlocker& operator=(const CORlocker& Orig);
};

// inline all methods because call overhead is huge for this class

inline CORlocker::CORlocker(CORmutex& Mutex) : m_pMutex(&Mutex) {
   // No need to check for exceptions here - it never fails.
   m_pMutex->lock();
}

inline CORlocker::~CORlocker() {
   // No need to check for exceptions here - it never fails.
   m_pMutex->unlock();
}


