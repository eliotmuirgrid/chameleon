#pragma once
//-------------------------------------------------------
// Copyright (C) 2026 Eliot Muir. All rights reserved.
//
// BASeventLoop — single-threaded run loop with posted tasks (BAScall0) and one-shot
// timers (BAScall0), plus a cross-thread wakeup. Platform I/O for wakeup/wait is
// BASeventLoopDispatch (epoll+kqueue, etc.).
//
// Ownership: postTask() and scheduleTimer() take ownership of the BAScall0* (delete
// after run). Run the loop from one thread; post/schedule/stop may be called from any.
//
// Tasks: BASlinkedList<BAScall0*>; timers: BASeventTimerCalendar.
//-------------------------------------------------------

#include <stdint.h>

#include <BAS/BASeventTimerCalendar.h>
#include <BAS/BASlinkedList.h>
#include <BAS/BASpass.h>

class BAScall0;
class BASstring;
class BASeventLoopDispatch;

class BASeventLoop {
public:
   BASeventLoop();
   ~BASeventLoop();

   bool init(BASstring* pError = nullptr);
   void shutdown();

   void run();
   void stop();

   void postTask(BAScall0* pCall);
   void scheduleTimer(uint64_t delay_us, BAScall0* pCall);

   static uint64_t nowMonotonicUs();

private:
   BASeventLoop(const BASeventLoop&);
   BASeventLoop& operator=(const BASeventLoop&);

   void wakeup();
   void drainWakeup();
   int pollWait(int timeout_ms);
   void processPostedTasks();
   void processDueTimers(uint64_t now_us);

   BASeventLoopDispatch* m_pDispatch;
   BASpass m_Pass;

   BASlinkedList<BAScall0*> m_Tasks;
   BASeventTimerCalendar m_Calendar;

   volatile int m_RunRequested;
   volatile int m_StopRequested;
   int m_Initialized;
};
