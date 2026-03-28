#pragma once
//---------------------------------------------------------------------------
// Copyright (C) 2026 Eliot Muir.  All rights reserved.
//
// Module: CORlocker
//
// Description:
//
// RAII Locker class - ensures that a mutex is properly unlocked
// when execution leaves a scope, regardless of how the scope is exited.
// Usage is recommended even in codebases without exceptions, because
// it guarantees the mutex is always released even if you return early:
//
// Example usage:
// void Foo::X()  {
//   CORlocker Lock(m_Mutex);
//   // Critical section begins
//   // ... do work ...
//   // if we return early, the Lock destructor will unlock the mutex
//   if (shouldExitEarly) return;
//   // ... continue work ...
//   // Critical section ends when Lock goes out of scope,
//   // unlocking the mutex automatically
// }
//
// Without CORlocker, manual lock/unlock ordering is error-prone:
// void Foo::X() {
//   m_Mutex.lock();
//   // ... do work ...
//   if (shouldExitEarly) return;  // Mutex is not unlocked!
//   m_Mutex.unlock();
// }
//
// Using CORlocker avoids mutex leaks in all code paths.
// 
// Author: Eliot Muir
//---------------------------------------------------------------------------

#include <COR/CORmutex.h>

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


