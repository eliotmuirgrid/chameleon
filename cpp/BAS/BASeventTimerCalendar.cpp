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
   if (m_Heap.empty()) {
      return 0;
   }
   return m_Heap[0]->expiry_us;
}

void BASeventTimerCalendar::siftUp(int index) {
   while (index > 0) {
      const int parent = (index - 1) / 2;
      if (m_Heap[parent]->expiry_us <= m_Heap[index]->expiry_us) {
         break;
      }
      BASeventTimerEntry* t = m_Heap[index];
      m_Heap[index] = m_Heap[parent];
      m_Heap[parent] = t;
      index = parent;
   }
}

void BASeventTimerCalendar::siftDown(int index) {
   for (;;) {
      const int left = index * 2 + 1;
      const int right = left + 1;
      int smallest = index;
      const int n = m_Heap.size();
      if (left < n && m_Heap[left]->expiry_us < m_Heap[smallest]->expiry_us) {
         smallest = left;
      }
      if (right < n && m_Heap[right]->expiry_us < m_Heap[smallest]->expiry_us) {
         smallest = right;
      }
      if (smallest == index) {
         break;
      }
      BASeventTimerEntry* t = m_Heap[index];
      m_Heap[index] = m_Heap[smallest];
      m_Heap[smallest] = t;
      index = smallest;
   }
}

void BASeventTimerCalendar::push(BASeventTimerEntry* pEntry) {
   if (!pEntry) {
      return;
   }
   m_Heap.push(pEntry);
   siftUp(m_Heap.size() - 1);
}

BASeventTimerEntry* BASeventTimerCalendar::popMinRaw() {
   if (m_Heap.empty()) {
      return nullptr;
   }
   BASeventTimerEntry* root = m_Heap[0];
   if (m_Heap.size() == 1) {
      m_Heap.pop();
      return root;
   }
   m_Heap[0] = m_Heap[m_Heap.size() - 1];
   m_Heap.pop();
   siftDown(0);
   return root;
}

BASeventTimerEntry* BASeventTimerCalendar::popIfDue(uint64_t now_us) {
   if (m_Heap.empty()) {
      return nullptr;
   }
   if (m_Heap[0]->expiry_us > now_us) {
      return nullptr;
   }
   return popMinRaw();
}

void BASeventTimerCalendar::clearDeletingCalls() {
   while (!m_Heap.empty()) {
      BASeventTimerEntry* e = popMinRaw();
      if (e) {
         if (e->pCall) {
            delete e->pCall;
         }
         delete e;
      }
   }
}
