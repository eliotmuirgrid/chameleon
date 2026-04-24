#pragma once
//-------------------------------------------------------
// Copyright (C) 2026 Eliot Muir. All rights reserved.
//
// BASeventLoop — single-threaded run loop with posted tasks (BAScall0) and one-shot
// timers (BAScall0), plus a cross-thread wakeup. Platform I/O for wakeup/wait is
// BASeventLoopDispatch (epoll+kqueue, etc.).
//
// Ownership: postTask() and scheduleTimer() take ownership of the BAScall0* (delete
// after run or cancel). Run the loop from one thread; post/schedule/stop may be called from any.
// scheduleTimer returns the timer name (empty if scheduling failed). A non-empty Name must be
// unique among pending timers; if Name is default/empty, a unique BASguid name is assigned.
//
// Tasks: BASlinkedList<BAScall0*>; timers: BASeventTimerCalendar.
//-------------------------------------------------------

#include <stdint.h>

#include <BAS/BASstring.h>
#include <BAS/BASeventTimerCalendar.h>
#include <BAS/BASlinkedList.h>
#include <BAS/BASpass.h>

class BAScall0;
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
   BASstring scheduleTimer(uint64_t delay_us, BAScall0* pCall, const BASstring& Name = BASstring());
   bool cancelTimer(const BASstring& Name);

private:
   BASeventLoop(const BASeventLoop&);
   BASeventLoop& operator=(const BASeventLoop&);

   void wakeup();
   void drainWakeup();
   int pollWait(int timeout_ms);
   void processPostedTasks();
   void processDueTimers(uint64_t now_us);

   static uint64_t nowMonotonicUs();

   BASeventLoopDispatch* m_pDispatch;
   BASpass m_Pass;

   BASlinkedList<BAScall0*> m_Tasks;
   BASeventTimerCalendar m_Calendar;

   volatile int m_RunRequested;
   volatile int m_StopRequested;
   int m_Initialized;
};
