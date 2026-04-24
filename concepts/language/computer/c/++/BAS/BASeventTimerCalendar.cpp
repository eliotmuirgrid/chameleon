//-------------------------------------------------------
// Copyright (C) 2026 Eliot Muir. All rights reserved.
//
// BASeventTimerCalendar
//-------------------------------------------------------

#include <BAS/BASeventTimerCalendar.h>
#include <BAS/BAScall.h>

BASeventTimerCalendar::BASeventTimerCalendar() {
}

BASeventTimerCalendar::~BASeventTimerCalendar() {
   clearDeletingCalls();
}

uint64_t BASeventTimerCalendar::earliestExpiryUs() const {
   if (m_ByExpiry.size() == 0) {
      return 0;
   }
   return m_ByExpiry.cbegin().key();
}

bool BASeventTimerCalendar::push(BASeventTimerEntry* pEntry, BASstring* pError) {
   if (!pEntry) {
      return false;
   }
   if (!pEntry->name.empty()) {
      if (m_ByName.has(pEntry->name)) {
         if (pError) {
            pError->clear();
            pError->append("duplicate timer name: ");
            pError->append(pEntry->name);
         }
         return false;
      }
   }
   m_ByExpiry.add(pEntry->expiry_us, pEntry);
   if (!pEntry->name.empty()) {
      m_ByName[pEntry->name] = pEntry;
   }
   return true;
}

BASeventTimerEntry* BASeventTimerCalendar::popIfDue(uint64_t now_us) {
   if (m_ByExpiry.size() == 0) {
      return nullptr;
   }
   const uint64_t exp = m_ByExpiry.cbegin().key();
   if (exp > now_us) {
      return nullptr;
   }
   BASarray<BASeventTimerEntry*>& arr = m_ByExpiry.values(exp);
   BASeventTimerEntry* e = arr.back();
   arr.pop();
   if (!e->name.empty()) {
      m_ByName.remove(e->name);
   }
   if (arr.size() == 0) {
      m_ByExpiry.erase(exp);
   }
   return e;
}

bool BASeventTimerCalendar::hasTimerName(const BASstring& name) const {
   if (name.empty()) {
      return false;
   }
   return m_ByName.has(name);
}

bool BASeventTimerCalendar::detachNamedTimer(const BASstring& name, BASeventTimerEntry** ppOut) {
   if (!ppOut || name.empty()) {
      return false;
   }
   if (!m_ByName.has(name)) {
      return false;
   }
   BASeventTimerEntry* e = m_ByName[name];
   if (!removeEntry(e)) {
      return false;
   }
   *ppOut = e;
   return true;
}

bool BASeventTimerCalendar::removeEntry(BASeventTimerEntry* pEntry) {
   if (!pEntry) {
      return false;
   }
   const uint64_t exp = pEntry->expiry_us;
   if (!m_ByExpiry.has(exp)) {
      return false;
   }
   BASarray<BASeventTimerEntry*>& arr = m_ByExpiry.values(exp);
   for (int i = 0; i < arr.size(); ++i) {
      if (arr[i] != pEntry) {
         continue;
      }
      arr.erase(i);
      if (!pEntry->name.empty()) {
         m_ByName.remove(pEntry->name);
      }
      if (arr.size() == 0) {
         m_ByExpiry.erase(exp);
      }
      return true;
   }
   return false;
}

void BASeventTimerCalendar::clearDeletingCalls() {
   while (m_ByExpiry.size() > 0) {
      const uint64_t k = m_ByExpiry.cbegin().key();
      BASarray<BASeventTimerEntry*>& arr = m_ByExpiry.values(k);
      while (arr.size() > 0) {
         BASeventTimerEntry* e = arr.back();
         arr.pop();
         if (e) {
            if (!e->name.empty()) {
               m_ByName.remove(e->name);
            }
            if (e->pCall) {
               delete e->pCall;
            }
            delete e;
         }
      }
      m_ByExpiry.erase(k);
   }
}
