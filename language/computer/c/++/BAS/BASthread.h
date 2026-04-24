#pragma once
//-------------------------------------------------------
// Copyright (C) 2026 Eliot Muir.  All rights reserved.
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

