//-------------------------------------------------------
// Copyright (C) 2026 Eliot Muir. All rights reserved.
//
// BASeventLoop
//-------------------------------------------------------

#include <BAS/BASeventLoop.h>
#include <BAS/BASarray.h>
#include <BAS/BAScall.h>
#include <BAS/BASeventLoopDispatch.h>
#include <BAS/BASguid.h>
#include <BAS/BASstring.h>

#include <new>

#ifndef _WIN32
#include <time.h>
#endif

#include <BAS/BAStrace.h>
BAS_TRACE_INIT;

static uint64_t BASeventLoopNowMonotonicUs() {
#ifndef _WIN32
   struct timespec ts;
   if (clock_gettime(CLOCK_MONOTONIC, &ts) != 0) {
      return 0;
   }
   return (uint64_t)ts.tv_sec * 1000000ULL + (uint64_t)ts.tv_nsec / 1000ULL;
#else
   return 0;
#endif
}

static BAScall0* BASeventLoopPopFrontTask(BASlinkedList<BAScall0*>& Tasks) {
   if (Tasks.size() == 0) {
      return nullptr;
   }
   BASlink* h = Tasks.head();
   BAScall0* p = static_cast<BASlinkT<BAScall0*>*>(h)->Value;
   Tasks.removeItem(h);
   return p;
}

BASeventLoop::BASeventLoop()
   : m_pDispatch(nullptr),
     m_RunRequested(0),
     m_StopRequested(0),
     m_Initialized(0) {
}

BASeventLoop::~BASeventLoop() {
   shutdown();
}

bool BASeventLoop::init(BASstring* pError) {
   BAS_METHOD(BASeventLoop::init);
   if (pError) {
      pError->clear();
   }
   if (m_Initialized) {
      return true;
   }
   m_pDispatch = BASeventLoopDispatch::create(pError);
   if (!m_pDispatch) {
      return false;
   }
   m_Initialized = 1;
   return true;
}

void BASeventLoop::shutdown() {
   BAS_METHOD(BASeventLoop::shutdown);
   if (!m_Initialized) {
      return;
   }
   stop();
   m_RunRequested = 0;
   delete m_pDispatch;
   m_pDispatch = nullptr;
   {
      BASpassHold Hold(m_Pass);
      while (m_Tasks.size() > 0) {
         BAScall0* p = BASeventLoopPopFrontTask(m_Tasks);
         if (p) {
            delete p;
         }
      }
      m_Calendar.clearDeletingCalls();
   }
   m_Initialized = 0;
}

void BASeventLoop::wakeup() {
   if (!m_Initialized || !m_pDispatch) {
      return;
   }
   m_pDispatch->signal();
}

void BASeventLoop::drainWakeup() {
   if (!m_Initialized || !m_pDispatch) {
      return;
   }
   m_pDispatch->drain();
}

int BASeventLoop::pollWait(int timeout_ms) {
   if (!m_Initialized || !m_pDispatch) {
      return -1;
   }
   return m_pDispatch->wait(timeout_ms);
}

void BASeventLoop::processPostedTasks() {
   BASarray<BAScall0*> batch;
   {
      BASpassHold Hold(m_Pass);
      while (m_Tasks.size() > 0) {
         BAScall0* p = BASeventLoopPopFrontTask(m_Tasks);
         if (p) {
            batch.push(p);
         }
      }
   }
   for (int i = 0; i < batch.size(); ++i) {
      BAScall0* p = batch[i];
      p->run();
      delete p;
   }
}

void BASeventLoop::processDueTimers(uint64_t now_us) {
   for (;;) {
      BASeventTimerEntry* due = nullptr;
      {
         BASpassHold Hold(m_Pass);
         due = m_Calendar.popIfDue(now_us);
      }
      if (!due) {
         return;
      }
      if (due->pCall) {
         due->pCall->run();
         delete due->pCall;
      }
      delete due;
   }
}

void BASeventLoop::run() {
   BAS_METHOD(BASeventLoop::run);
   if (!m_Initialized || !m_pDispatch) {
      return;
   }
   m_RunRequested = 1;
   m_StopRequested = 0;
   while (m_RunRequested) {
      int timeout_ms = -1;
      {
         BASpassHold Hold(m_Pass);
         if (m_StopRequested) {
            break;
         }
         const bool hasTasks = m_Tasks.size() > 0;
         const uint64_t now_us = BASeventLoopNowMonotonicUs();
         if (hasTasks) {
            timeout_ms = 0;
         } else if (!m_Calendar.empty()) {
            const uint64_t exp = m_Calendar.earliestExpiryUs();
            if (exp <= now_us) {
               timeout_ms = 0;
            } else {
               const uint64_t delta_us = exp - now_us;
               const uint64_t delta_ms = delta_us / 1000ULL;
               if (delta_ms > (uint64_t)0x7fffffff) {
                  timeout_ms = 0x7fffffff;
               } else {
                  timeout_ms = (int)delta_ms;
                  if (timeout_ms == 0 && delta_us > 0) {
                     timeout_ms = 1;
                  }
               }
            }
         }
      }

      (void)pollWait(timeout_ms);

      drainWakeup();

      processPostedTasks();

      const uint64_t after_us = BASeventLoopNowMonotonicUs();
      processDueTimers(after_us);

      {
         BASpassHold Hold(m_Pass);
         if (m_StopRequested) {
            break;
         }
      }
   }
}

void BASeventLoop::stop() {
   BAS_METHOD(BASeventLoop::stop);
   if (!m_Initialized || !m_pDispatch) {
      return;
   }
   {
      BASpassHold Hold(m_Pass);
      m_StopRequested = 1;
      m_RunRequested = 0;
   }
   wakeup();
}

void BASeventLoop::postTask(BAScall0* pCall) {
   BAS_METHOD(BASeventLoop::postTask);
   if (!m_Initialized || !m_pDispatch || !pCall) {
      if (pCall) {
         delete pCall;
      }
      return;
   }
   {
      BASpassHold Hold(m_Pass);
      m_Tasks.add(pCall);
   }
   wakeup();
}

BASstring BASeventLoop::scheduleTimer(uint64_t delay_us, BAScall0* pCall, const BASstring& Name) {
   BAS_METHOD(BASeventLoop::scheduleTimer);
   BASstring result;
   if (!m_Initialized || !m_pDispatch || !pCall) {
      if (pCall) {
         delete pCall;
      }
      return result;
   }
   BASeventTimerEntry* te = nullptr;
   try {
      te = new BASeventTimerEntry();
   } catch (const std::bad_alloc&) {
      delete pCall;
      return result;
   }
   te->pCall = pCall;
   const bool userNamed = !Name.empty();
   if (userNamed) {
      te->name = Name;
   } else {
      te->name = BASguid(36);
   }
   {
      BASpassHold Hold(m_Pass);
      te->expiry_us = BASeventLoopNowMonotonicUs() + delay_us;
      BASstring err;
      int autoNameRetries = 0;
      for (;;) {
         if (m_Calendar.push(te, &err)) {
            result = te->name;
            break;
         }
         if (userNamed) {
            delete te;
            delete pCall;
            return result;
         }
         if (++autoNameRetries > 16) {
            delete te;
            delete pCall;
            return result;
         }
         te->name = BASguid(36);
      }
   }
   wakeup();
   return result;
}

bool BASeventLoop::cancelTimer(const BASstring& name) {
   BAS_METHOD(BASeventLoop::cancelTimer);
   if (!m_Initialized || !m_pDispatch || name.empty()) {
      return false;
   }
   BASeventTimerEntry* e = nullptr;
   {
      BASpassHold Hold(m_Pass);
      if (!m_Calendar.detachNamedTimer(name, &e)) {
         return false;
      }
   }
   if (e->pCall) {
      delete e->pCall;
   }
   delete e;
   wakeup();
   return true;
}
