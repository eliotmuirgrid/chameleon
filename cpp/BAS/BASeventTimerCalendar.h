#pragma once
//-------------------------------------------------------
// Copyright (C) 2026 Eliot Muir. All rights reserved.
//
// BASeventTimerCalendar — min-heap of one-shot timers ordered by expiry (monotonic
// microseconds). Heap storage is a BASarray of pointers; each BASeventTimerEntry is
// allocated by the caller (typically with new). clearDeletingCalls() deletes each
// entry's BAScall0 and the entry — used on shutdown.
//-------------------------------------------------------

#include <stdint.h>

#include <BAS/BASarray.h>

class BAScall0;

struct BASeventTimerEntry {
   uint64_t expiry_us;
   BAScall0* pCall;
};

class BASeventTimerCalendar {
public:
   BASeventTimerCalendar();
   ~BASeventTimerCalendar();

   BASeventTimerCalendar(const BASeventTimerCalendar&) = delete;
   BASeventTimerCalendar& operator=(const BASeventTimerCalendar&) = delete;

   bool empty() const { return m_Heap.empty(); }
   uint64_t earliestExpiryUs() const;

   void push(BASeventTimerEntry* pEntry);
   BASeventTimerEntry* popIfDue(uint64_t now_us);

   void clearDeletingCalls();

private:
   BASeventTimerEntry* popMinRaw();
   void siftUp(int index);
   void siftDown(int index);

   BASarray<BASeventTimerEntry*> m_Heap;
};
