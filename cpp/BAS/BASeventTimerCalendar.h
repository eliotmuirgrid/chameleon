#pragma once
//-------------------------------------------------------
// Copyright (C) 2026 Eliot Muir. All rights reserved.
//
// BASeventTimerCalendar — one-shot timers ordered by expiry (monotonic microseconds).
// Timers with the same expiry share one AVL key; values are BASeventTimerEntry*
// pointers in a BASarray (BASdictOrderedValues). Optional unique names (per calendar)
// are indexed in m_ByName for debugging and cancel-by-name. earliestExpiryUs() is the
// smallest key; popIfDue removes one due entry. clearDeletingCalls() deletes each
// entry's BAScall0 and the entry — used on shutdown.
//-------------------------------------------------------

#include <stdint.h>

#include <BAS/BASdictOrdered.h>
#include <BAS/BASdictUnordered.h>
#include <BAS/BASstring.h>

class BAScall0;

struct BASeventTimerEntry {
   uint64_t expiry_us;
   BAScall0* pCall;
   BASstring name;
};

class BASeventTimerCalendar {
public:
   BASeventTimerCalendar();
   ~BASeventTimerCalendar();

   BASeventTimerCalendar(const BASeventTimerCalendar&) = delete;
   BASeventTimerCalendar& operator=(const BASeventTimerCalendar&) = delete;

   bool empty() const { return m_ByExpiry.size() == 0; }
   uint64_t earliestExpiryUs() const;

   bool push(BASeventTimerEntry* pEntry, BASstring* pError = nullptr);
   BASeventTimerEntry* popIfDue(uint64_t now_us);

   bool hasTimerName(const BASstring& name) const;
   bool detachNamedTimer(const BASstring& name, BASeventTimerEntry** ppOut);

   void clearDeletingCalls();

private:
   bool removeEntry(BASeventTimerEntry* pEntry);

   BASdictOrderedValues<uint64_t, BASeventTimerEntry*> m_ByExpiry;
   BASdictUnordered<BASstring, BASeventTimerEntry*> m_ByName;
};
