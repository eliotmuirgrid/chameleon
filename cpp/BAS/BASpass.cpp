//-------------------------------------------------------
// Copyright (C) 2026 Eliot Muir. All rights reserved.
//
// BASpass — OS primitives for exclusive pass (POSIX pthreads or Windows).
//-------------------------------------------------------

#include <BAS/BASpass.h>

#ifndef WIN32

#include <pthread.h>
#include <stdlib.h>

// POSIX pthread names contain "mutex"; they implement the same "one holder" idea as BASpass.
static_assert(sizeof(pthread_mutex_t) <= 64, "BASpass::m_Handle too small; increase m_Handle in BASpass.h");

#define BASPASS_POSIX_LOCK_PTR (reinterpret_cast<pthread_mutex_t*>(m_Handle))

BASpass::BASpass(){
   pthread_mutexattr_t Attribute;
   pthread_mutexattr_init(&Attribute);
   pthread_mutexattr_settype(&Attribute, PTHREAD_MUTEX_RECURSIVE);
   pthread_mutex_init(BASPASS_POSIX_LOCK_PTR, &Attribute);
   pthread_mutexattr_destroy(&Attribute);
}

BASpass::~BASpass(){
   pthread_mutex_destroy(BASPASS_POSIX_LOCK_PTR);
}

void BASpass::takePass(){
   pthread_mutex_lock(BASPASS_POSIX_LOCK_PTR);
}

void BASpass::returnPass(){
   pthread_mutex_unlock(BASPASS_POSIX_LOCK_PTR);
}

#else

#define LEAN_AND_MEAN
#include <windows.h>

#define BASPASS_CS (reinterpret_cast<CRITICAL_SECTION*>(m_Handle))

BASpass::BASpass(){
   InitializeCriticalSection(BASPASS_CS);
}

BASpass::~BASpass(){
   DeleteCriticalSection(BASPASS_CS);
}

void BASpass::takePass(){
   EnterCriticalSection(BASPASS_CS);
}

void BASpass::returnPass(){
   LeaveCriticalSection(BASPASS_CS);
}

#endif
