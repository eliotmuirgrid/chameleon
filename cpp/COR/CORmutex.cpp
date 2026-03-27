//---------------------------------------------------------------------------
// Copyright (C) 2026 Eliot Muir.  All rights reserved.
//
// Module: CORmutex
//
// Description:
//
// Implementation. 
//
// Author: Eliot Muir
//---------------------------------------------------------------------------
#include "CORmutex.h"

#ifdef _WIN32
#include "CORwindows.h"

class CORmutexPrivate{
public:
   CORmutexPrivate() { ::InitializeCriticalSection(&CriticalSectionHandle);       } // Mostly void functions - no return code      
   ~CORmutexPrivate(){ ::DeleteCriticalSection(&CriticalSectionHandle);           } 
   bool tryLock()    { return !!::TryEnterCriticalSection(&CriticalSectionHandle);}
   void lock()       { ::EnterCriticalSection(&CriticalSectionHandle);            }  
   void unlock()     { ::LeaveCriticalSection(&CriticalSectionHandle);            } 
   void* handle()    { return (void*)&CriticalSectionHandle;                      }
   CRITICAL_SECTION CriticalSectionHandle;
};
#else  // POSIX

#include <pthread.h>
#include <stdio.h>
#include <errno.h>

class CORmutexPrivate{
public:
   CORmutexPrivate(){
      //No point checking error codes here - see ticket #10168
      pthread_mutexattr_t recursiveAttr;
      pthread_mutexattr_init(&recursiveAttr);
      pthread_mutexattr_settype(&recursiveAttr, PTHREAD_MUTEX_RECURSIVE);
      pthread_mutex_init(&Mutex, &recursiveAttr);
      pthread_mutexattr_destroy(&recursiveAttr);
   }

   ~CORmutexPrivate() {pthread_mutex_destroy(&Mutex); }

   bool tryLock() { return pthread_mutex_trylock(&Mutex) == 0;}
   void lock()    { pthread_mutex_lock(&Mutex);        }
   void unlock()  { pthread_mutex_unlock(&Mutex);      }
   
   void* handle(){ return (void*)&Mutex; }

private:
   pthread_mutex_t Mutex;
   CORmutexPrivate(const CORmutexPrivate& Orig);
   CORmutexPrivate& operator=(const CORmutexPrivate& Orig); 
};
#endif  // end of POSIX implementation.

CORmutex::CORmutex()     { pMember = new CORmutexPrivate(); }
CORmutex::~CORmutex()    { delete pMember;                  }
void  CORmutex::lock()   { pMember->lock();                 }
void  CORmutex::unlock() { pMember->unlock();               }
void* CORmutex::handle() { return pMember->handle();        }

// In ticket #10168 - comment from Andrew Vajoczki 
// Mutexes created with PTHREAD_MUTEX_RECURSIVE will never return EDEADLK in 
// locking a single mutex by design (it's recursive).
//
// Multi-lock deadlock detection is not done in any pthread implementation that 
// I'm am aware of. It would be too computationally expensive to implement in a
// standard threading library, and would slow multithreaded applications down considerably.
//
// Checking the return code of pthread_mutex_init could be done, but it is unlikely to 
// ever fail because most major operating system's pthread libraries implement it in a
// way that doesn't require any memory allocation or operating system resources.
