#pragma once
//-----------------------------------------------------------------------------
// Copyright (C) 2026 Eliot Muir. All rights reserved.
//
// BASarray: A Resizable, Typed Container
//
// ANALOGY: Think of this as a row of gym lockers or a pill organiser.
// 1. TYPED: Each locker is built for one specific type of item (VType).
// 2. ONE PER SLOT: Every index holds exactly one item; no "cramming" allowed.
// 3. RESIZABLE: If you run out of lockers, the wall "expands" automatically 
//    to make room for more, keeping all your gear in one continuous row.
//
// Example usage (illustrative; adapt types and BASwriter destination as needed). Locals use
// leading capitals to match project style.
//
//   // Start empty, then pre-size if you already know roughly how many items are coming.
//   BASarray<int> Empty;
//   BASarray<int> PreSized(16);        // capacity is rounded up; size still 0 until you push
//   PreSized.push(10);
//   PreSized.push(20);
//   PreSized.emplace(30);              // construct in place (here: one int, same idea as push for int)
//   PreSized.insert(0, 5);             // [5, 10, 20, 30] — slides existing elements right
//   PreSized[1] = 7;                   // bounds-checked index
//   int Last = PreSized.back();        // peek at the final element (30 after inserts/edits)
//   PreSized.erase(0);                 // remove first; everything else shifts left
//   PreSized.pop();                    // drop last; size shrinks, capacity kept for reuse
//   PreSized.resize(4);                // logical length; storage grows only if needed
//
//   int Count = PreSized.size();
//   if (!PreSized.empty()) {
//      int Sum = 0;
//      for (int* Cursor = PreSized.begin(); Cursor != PreSized.end(); ++Cursor) { Sum += *Cursor; }
//      // const BASarray<int>& View = PreSized;  then View.cbegin() / View.cend() for read-only
//   }
//
//   PreSized.clear();                  // size 0, buffer kept — fast to fill again on the next pass
//   PreSized.push(1); PreSized.push(2);
//   PreSized.zero();                   // free memory; size and capacity both 0
//
//   BASarray<int> Source;
//   Source.push(1); Source.push(2); Source.push(3);
//   BASarray<int> Copy(Source);       // deep copy: Copy and Source both hold [1,2,3]
//   BASarray<int> Stolen(BASmove(Source));   // Source empty; Stolen owns [1,2,3]
//   BASarray<int> Target;
//   Target = Copy;                    // Target duplicates Copy's elements
//   Target = BASmove(Stolen);         // Target takes Stolen's buffer; Stolen empty
//   BASout << Target << newline;      // dump size, capacity, and each index for debugging
//-----------------------------------------------------------------------------

#include <BAS/BASwriter.h>

// Internal helper templates for move semantics
template<typename T> struct BASRemoveReference      { typedef T Type; };
template<typename T> struct BASRemoveReference<T&>  { typedef T Type; };
template<typename T> struct BASRemoveReference<T&&> { typedef T Type; };

// BASmove: Tells the compiler it's okay to "steal" the contents of a locker
template<typename T>
typename BASRemoveReference<T>::Type&& BASmove(T&& t) {
   return static_cast<typename BASRemoveReference<T>::Type&&>(t);
}

// BASforward: Safely passes along instructions to build an item inside a locker
template<typename T>
T&& BASforward(typename BASRemoveReference<T>::Type& t) {
   return static_cast<T&&>(t);
}

void BAScheckBoundary(int i, int m_Size);
unsigned int BAScalculateCapacity(unsigned int v);

template<typename VType> class BASarray {
public:
   // Creates an empty organiser with no physical slots yet.
   BASarray() : m_pItems(0), m_Size(0), m_Capacity(0) {}

   // Pre-builds a row of lockers to a specific length.
   // Why: Adding lockers one by one later requires building a whole new wall and 
   // moving every item. Starting with enough lockers avoids this "moving day" cost.
   explicit BASarray(int DesiredCapacity) : m_Size(0) {
      m_Capacity = BAScalculateCapacity(DesiredCapacity);
      m_pItems = new VType[m_Capacity];
   }

   // Copy Constructor: Builds a brand new, identical row of lockers elsewhere.
   BASarray(const BASarray& Other) : m_Size(Other.m_Size), m_Capacity(Other.m_Capacity) {
      m_pItems = (m_Capacity > 0) ? new VType[m_Capacity] : 0;
      for (int i = 0; i < m_Size; ++i) { m_pItems[i] = Other.m_pItems[i]; }
   }

   // Move Constructor: Hands over the "deed" to the existing lockers instantly.
   BASarray(BASarray&& Other) 
      : m_pItems(Other.m_pItems), m_Size(Other.m_Size), m_Capacity(Other.m_Capacity) {
      Other.m_pItems = 0;
      Other.m_Size = 0;
      Other.m_Capacity = 0;
   }

   // Copy Assignment: Demolishes current lockers and builds copies of the other row.
   BASarray& operator=(const BASarray& Other) {
      if (this != &Other) {
         VType* pNewSpace = (Other.m_Capacity > 0) ? new VType[Other.m_Capacity] : 0;
         for (int i = 0; i < Other.m_Size; ++i) { pNewSpace[i] = Other.m_pItems[i]; }
         delete[] m_pItems;
         m_pItems = pNewSpace;
         m_Size = Other.m_Size;
         m_Capacity = Other.m_Capacity;
      }
      return *this;
   }

   // Move Assignment: Swaps ownership of the locker row with another.
   BASarray& operator=(BASarray&& Other) {
      if (this != &Other) {
         delete[] m_pItems;
         m_pItems = Other.m_pItems;
         m_Size = Other.m_Size;
         m_Capacity = Other.m_Capacity;
         Other.m_pItems = 0;
         Other.m_Size = 0;
         Other.m_Capacity = 0;
      }
      return *this;
   }

   // Tears down the locker bank and destroys all items inside.
   ~BASarray() { delete []m_pItems; }

   // Build an item directly inside a locker so you don't have to carry it there.
   template<typename... Args>
   VType& emplace(Args&&... args) {
      checkCapacity(m_Size + 1);
      m_pItems[m_Size] = VType(BASforward<Args>(args)...);
      return m_pItems[m_Size++];
   }

   // Adds an item to the next available locker. 
   // If the wall is full, it automatically adds more lockers first.
   VType& push(const VType& Value) {
      checkCapacity(m_Size + 1);
      m_pItems[m_Size] = Value;
      return m_pItems[m_Size++];
   }

   // Closes the last locker door (the item is "gone" but the locker remains).
   void pop() { if (m_Size > 0) m_Size--; }

   // Returns the number of lockers currently in use.
   int size() const { return m_Size; }

   // Returns true if no lockers are currently being used.
   bool empty() const { return m_Size == 0; }

   // Empties the lockers but keeps the physical wall standing for reuse.
   void clear() { m_Size = 0; }

   // Demolishes the wall entirely. Use this to give all memory back to the system.
   void zero() {
      delete[] m_pItems;
      m_pItems = 0;
      m_Size = 0;
      m_Capacity = 0;
   }

   // Adjusts the "In-Use" count. Expands the wall if NewSize exceeds current capacity.
   void resize(int NewSize) { 
      checkCapacity(NewSize); 
      m_Size = NewSize; 
   }

   // Access a specific locker by its number (Index).
   VType& operator[](int i) { BAScheckBoundary(i, m_Size); return m_pItems[i]; }
   const VType& operator[](int i) const { BAScheckBoundary(i, m_Size); return m_pItems[i]; }

   // Peek inside the very last occupied locker.
   VType& back() { BAScheckBoundary(m_Size - 1, m_Size); return m_pItems[m_Size - 1]; }

   // Ensures the row has enough physical lockers. 
   // If expansion is needed, it "migrates" everything to a new, larger wall.
   void checkCapacity(int DesiredCapacity) {
      if (DesiredCapacity <= m_Capacity) return;
      int NewCapacity = BAScalculateCapacity(DesiredCapacity);
      VType* pNewSpace = new VType[NewCapacity];
      
      // Migration: "Move" items to the new lockers instead of copying them.
      for (int i = 0; i < m_Size; ++i) { 
         pNewSpace[i] = BASmove(m_pItems[i]); 
      }
      
      delete []m_pItems;
      m_pItems = pNewSpace;
      m_Capacity = NewCapacity;
   }
   // Slides all items from 'i' onwards to the right to make a gap for a new item.
   // Analogy: Moving everyone down the row of lockers to free up a specific spot.
   VType& insert(int i, const VType& Value) {
      // 1. Safety first: check if we are within the current items or just at the end.
      BAScheckBoundary(i, m_Size + 1);
      
      // 2. Make sure we have a physical locker available at the end of the row.
      checkCapacity(m_Size + 1);

      // 3. The Slide: Start at the end and move everyone one door to the right.
      // We go backwards so we don't overwrite the person next to us.
      for (int j = m_Size; j > i; --j) {
         m_pItems[j] = BASmove(m_pItems[j - 1]);
      }

      // 4. Place the new item in the now-empty locker.
      m_pItems[i] = Value;
      m_Size++;
      return m_pItems[i];
   }
   
   // Removes the item at index 'i' and slides all subsequent items left to fill the gap.
   // Analogy: When someone leaves their locker, everyone to the right moves one door
   // to the left so the row stays continuous without any "holes."
   void erase(int i) {
      // 1. Safety: Make sure the locker is actually occupied.
      BAScheckBoundary(i, m_Size);

      // 2. The Slide: Start from the gap and pull everyone from the right into it.
      // We go forward this time so each locker is filled by its neighbour on the right.
      for (int j = i; j < m_Size - 1; ++j) {
         m_pItems[j] = BASmove(m_pItems[j + 1]);
      }

      // 3. Mark the last locker as "available" again.
      m_Size--;
   }

   // Helpers for walking through the lockers from start to finish.
   const VType* cbegin() const { return m_pItems; }
   const VType* cend()   const { return m_pItems + m_Size; }
   VType* begin() { return m_pItems; }
   VType* end()   { return m_pItems + m_Size; }

   // Ensures a specific number of lockers are physically built.
   // This does NOT change the size (how many items are inside).
   void reserve(int DesiredCapacity) {
      checkCapacity(DesiredCapacity);
   }

   void printOn(BASwriter& Writer) const {
      Writer << "Array Size=" << m_Size << ", Capacity=" << m_Capacity;
      for (int i = 0; i < m_Size; ++i) {
         Writer << newline << " " << i << " " << m_pItems[i];
      }
   }

private:
   VType* m_pItems;   // The physical row of lockers
   int    m_Size;     // How many lockers are currently occupied
   int    m_Capacity; // The total number of lockers built
};

// Writer output: write a human-readable dump of this array to a BASwriter (size,
// capacity, one line per index). Returns the writer so you can chain: out << a << x.
template<typename VType>
BASwriter& operator<<(BASwriter& Writer, const BASarray<VType>& Array) {
   Array.printOn(Writer);
   return Writer;
}
