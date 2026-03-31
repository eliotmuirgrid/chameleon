#ifndef _BAS_THREAD_H_
#define _BAS_THREAD_H_
//-------------------------------------------------------
// Copyright (C) 2021 Eliot Muir.  All Rights Reserved
//
// BASthread
// 
// Thread operating system wrapper.
//-------------------------------------------------------

typedef void* (*BASthreadFunc)(void*);

#include <pthread.h>


class BASthread{
public:
   BASthread();
   ~BASthread();

   void start(BASthreadFunc pFunc, void* pArg);

   void join();
private:
   pthread_t m_ThreadHandle;

   BASthread(const BASthread& Orig);
   BASthread& operator=(const BASthread& Orig);
};

void BASsleep(int Milliseconds);

#endif


