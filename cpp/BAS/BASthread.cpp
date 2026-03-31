//-------------------------------------------------------
// Copyright (C) 2021 Eliot Muir.  All Rights Reserved
//
// BASthread
// 
// Implementation
//-------------------------------------------------------

#include "BASthread.h"

#include "BAStrace.h"
BAS_TRACE_INIT;


void BASsleep(int Milliseconds){
   BAS_FUNCTION(BASsleep);
#ifdef WIN32
   Sleep(Milliseconds);
#else
   BAS_VAR(Milliseconds);
   struct timespec Time;
   Time.tv_sec = Milliseconds / 1000;
   Time.tv_nsec = (Milliseconds % 1000) * 1000000;
   nanosleep(&Time, &Time);
#endif
}

BASthread::BASthread() {
   
}

BASthread::~BASthread(){

}

void BASthread::start(BASthreadFunc pFunc, void* pData){
   BAS_METHOD(BASthread::start);
   BAS_VAR((void*)pFunc);
   BAS_VAR(pData);
   int Result = 0;
   Result = pthread_create(&m_ThreadHandle, NULL, pFunc, pData);
   BAS_VAR(Result);
   BAS_TRC("After pthread create.");
}

void BASthread::join(){
   void* Result = NULL;
   pthread_join(m_ThreadHandle, &Result);
}