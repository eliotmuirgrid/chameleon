#pragma once
//-------------------------------------------------------
// Copyright (C) 2026 Eliot Muir.  All rights reserved.
//
// BASdictOrdered and the AVL tree helpers in this file (nodes, iterators, etc.).
//
// Picture a searchable notebook: each entry has a label (key) and something stored
// under that label (value). You can add entries, look them up, and flip through
// them from smallest label to largest. The program keeps the tree balanced (AVL)
// so lookups stay quick even with many entries. Optional video on the idea:
// https://www.youtube.com/watch?v=vRwi_UcZGjU
//-------------------------------------------------------

#include <BAS/BASassert.h>
#include <BAS/BASwriter.h>

class BASstring;

// Max AVL height for n nodes is < 2 log2(n+2); 128 covers any practical tree size here.
enum { kBASavlIteratorStackDepth = 128 };

class BASavlNode{
public:
   BASavlNode();
   virtual ~BASavlNode();

   virtual void copy(BASavlNode& Orig)=0;
   BASavlNode* m_pLeft;
   BASavlNode* m_pRight;
   // Subtree height: 1 for a leaf, 1 + max(left height, right height) for internal nodes.
   int m_Height;
};

template<class KType, class VType>
class BASavlNodeT : public BASavlNode{
public:
   BASavlNodeT(KType Key, VType Value) : BASavlNode(), m_Key(Key), m_Value(Value) {}
   BASavlNodeT(KType Key) : BASavlNode(), m_Key(Key) {}

   virtual void copy(BASavlNode& Orig){
      m_Value = ((BASavlNodeT<KType, VType>&)Orig).m_Value;
   }

   KType m_Key;
   VType m_Value;
};

class BASavlIterator{
public:
   BASavlIterator(BASavlNode* pRoot);

   struct Link{
      Link(Link* pParent, BASavlNode* pNode) : m_pParent(pParent), m_pNode(pNode) {}
      Link* m_pParent;
      BASavlNode* m_pNode;
   };
   void first();
   void end() { m_StackPos = 0;}
   bool next();

   bool operator++() { return next(); }

   // In-order predecessor. From end(), moves to the largest key; returns false if the
   // tree is empty or if already before the smallest key (same representation as end()).
   bool prev();
   bool operator--() { return prev(); }

   bool operator==(const BASavlIterator& Rhs) const { return root() == Rhs.root(); }
   bool operator!=(const BASavlIterator& Rhs) const { return root() != Rhs.root(); }
private:
   void pop();
   void goRight();
   void goLeft();
   bool downLeft();
   bool downRight();
   bool upRight();
   bool upLeft();
   inline BASavlNode* root() { return m_Stack[m_StackPos];}
   inline const BASavlNode* root() const { return m_Stack[m_StackPos];}

   inline BASavlNode* parent() { return m_Stack[m_StackPos-1];}

   BASavlNode* m_Stack[kBASavlIteratorStackDepth];
   int m_StackPos;
};

template<class KType, class VType>
class BASavlIteratorT : public BASavlIterator{
public:
   BASavlIteratorT(BASavlNode* pRoot) : BASavlIterator(pRoot) {}

   KType& key() { return ((BASavlNodeT<KType, VType>*)root())->m_Key; }
   const KType& key() const { return ((BASavlNodeT<KType, VType>*)root())->m_Key; }
   VType& value() { return ((BASavlNodeT<KType, VType>*)root())->m_Value; }
   const VType& value() const { return ((BASavlNodeT<KType, VType>*)root())->m_Value; }
};

template<class KType, class VType>
class BASavlConstIteratorT {
public:
   BASavlConstIteratorT(BASavlNode* pRoot) : m_Iterator(pRoot) {}

   void first() { m_Iterator.first(); }
   void end()   { m_Iterator.end(); }
   bool operator++() { return ++m_Iterator; }
   bool operator--() { return --m_Iterator; }

   bool operator==(const BASavlConstIteratorT& Rhs) const { return m_Iterator == Rhs.m_Iterator; }
   bool operator!=(const BASavlConstIteratorT& Rhs) const { return m_Iterator != Rhs.m_Iterator; }

   const KType& key()   const { return m_Iterator.key(); }
   const VType& value() const { return m_Iterator.value(); }
private:
   BASavlIteratorT<KType, VType> m_Iterator;
};

typedef int (*BASavlCompare)(const void* pRKey, const void* pLKey);
typedef const void* (*BASavlExtractKey)(const BASavlNode* pNode);


class BASavlTreeBase{
public:
   BASavlTreeBase(BASavlCompare pCompFunc, BASavlExtractKey pFunc);
   virtual ~BASavlTreeBase();

   int size() const { return m_Size; }

protected:
   void insert(BASavlNode* pNewNode);
   BASavlNode* find(const void* Key) const;

   BASavlNode* m_pRoot;
private:
   BASavlCompare    m_pCompareFunc;
   BASavlExtractKey m_pKeyFunc;
   int              m_Size;
};

BASwriter& operator<<(BASwriter& Writer, const BASavlNode& Node);

// Default ordering for built-in number types. For other key types (e.g. BASstring),
// this project defines BASsCompare in a .cpp file; for your own key type, add one
// BASsCompare overload in a single .cpp file so the linker finds it.
template<class KType>
int BASsCompare(const KType& Rhs, const KType& Lhs){
   return Rhs - Lhs;
}

int BASsCompare(const BASstring& Rhs, const BASstring& Lhs);

// BASdictOrdered<KType, VType>  -- plain-language guide
//
// The two names in angle brackets
// -------------------------------
// KType = what you use as the label (the key), for example int or BASstring.
// VType = what you store (the value), for example int, double, or another type.
// Together they mean "a notebook where each KType label maps to one VType value."
// You cannot have two entries with the same key; if you try to add the same key
// again, the new value replaces the old one (the number of entries does not grow).
//
// "Template" here just means: you pick KType and VType once when you declare the
// variable, and the compiler builds the right kind of notebook for those types.
//
// How keys are sorted
// -------------------
// Entries are kept in order by key (like sorting a list by the first column).
// For built-in number types, smaller numbers sort before larger ones. For
// BASstring, normal string ordering is used (defined in this project's .cpp file).
// If you invent your own key type, you must supply a BASsCompare function for it
// in one .cpp file so the tree knows which key is "less than" which.
//
// Example A -- student ID to score (int -> int)
// ----------------------------------------------
//   BASdictOrdered<int, int> scores;
//   scores.add(1024, 88);           // student 1024 has score 88
//   scores.add(1024, 90);           // same ID again: replaces 88 with 90
//   if (scores.has(1024)) {         // check before using value() if unsure
//      int s = scores.value(1024);  // read the score (debug build checks key exists)
//   }
//
// Example B -- operator[] creates a value if missing
// ---------------------------------------------------
//   BASdictOrdered<int, int> counts;
//   counts[7]++;                    // if 7 was missing, it starts at 0, then becomes 1
//   // VType must be something that can start empty (e.g. int starts at 0).
//
// Example C -- walk all entries from smallest key to largest
// ----------------------------------------------------------
//   BASdictOrdered<int, int> m;
//   m.add(2, 200);
//   m.add(1, 100);                 // keys are stored sorted: loop visits 1 then 2
//   for (auto it = m.begin(); it != m.end(); ++it) {
//      int k = it.key();           // 1, then 2
//      int v = it.value();         // 100, then 200
//   }
//   end() means "after the last item" -- only use it != m.end() in the for line,
//   not it.key() / it.value() on the end position itself.
//
// Example D -- largest key to smallest (--it from end())
// ------------------------------------------------------
//   // Put --it inside the loop body after the end iterator: end() is not a real
//   // element, so you step back before reading key() / value().
//   for (auto it = m.end(); it != m.begin(); ) {
//      --it;
//      // it.key() / it.value() here: last key down to first
//   }
//   // Same idea with cend() / cbegin() for read-only access.
//   // Do not use key()/value() on it when it still equals end() before the first --it.
//   // Stepping back from begin() (-- on the smallest key) is undefined; prev() returns
//   // false and leaves the iterator in an end-like state.
//
// Names you will see
// ------------------
// add(key, value)  -- insert or replace.
// has(key)         -- true if that key is in the notebook.
// value(key)       -- read the value; in debug builds, missing key is an error.
// operator[](key)  -- get the value slot; creates key with a default value if new.
// begin / end      -- forward order (Example C); use --it from end for reverse (Example D).
// cbegin / cend    -- same idea, but you only read values, you do not change them.
//
// BASavlTree is another name for the same class type if you prefer that name.
//
// size() (from the base class) tells you how many key/value pairs are stored.
//
// Rare edge case: the iterator uses a small fixed stack inside; only absurdly deep
// trees could hit its limit. Normal use is fine.
//
// AVL trees, duplicates, and this class
// ---------------------------------------
// Many AVL explanations and implementations treat the tree as a sorted set or map:
// each key appears once. When people do need duplicate keys, common options are:
// (1) store a count or list inside one node, (2) pick a tie-break so "equal" keys
// always go left or right (so the tree still has a strict ordering rule), or
// (3) use a different container for "many values per key" and keep the AVL unique.
//
// BASdictOrdered follows the unique-key map model on purpose. One key maps to one
// value: lookup and size stay easy to reason about, and inserting the same key
// again simply updates the value instead of growing the tree or branching the API
// for ranges of equal keys. If you need several independent values for the same key,
// that is a different problem (often a multimap or a map from key to a list); this
// class stays small and predictable rather than baking duplicate-key policy into
// the AVL core here.
//
template<class KType, class VType>
class BASdictOrdered : public BASavlTreeBase{
public:
   BASdictOrdered() : BASavlTreeBase(&compare, &key) {}

   static const void* key(const BASavlNode* pNode){
      return &((BASavlNodeT<KType, VType>*)pNode)->m_Key;
   }

   static int compare(const void* pRKey, const void* pLKey){
      return BASsCompare(*((const KType*)pRKey), *((const KType*)pLKey));
   }

   // Put key and value in the map, or overwrite the value if that key was already there.
   void add(KType Key, VType Value){
      insert(new BASavlNodeT<KType, VType>(Key, Value));
   }

   // Returns whether this key is already in the map.
   bool has(const KType& Key) const {
      return find((const void*)&Key) != 0;
   }

   // Read the value for this key. In debug builds, missing key is treated as an error.
   const VType& value(const KType& Key) const{
      const BASavlNode* pFound = find((const void*)&Key);
      BAS_ASSERT(pFound != nullptr);
      return ((BASavlNodeT<KType, VType>*)pFound)->m_Value;
   }

   // Same as const value(), but you may change the stored value.
   VType& value(const KType& Key){
      BASavlNode* pFound = find((const void*)&Key);
      BAS_ASSERT(pFound != nullptr);
      return ((BASavlNodeT<KType, VType>*)pFound)->m_Value;
   }

   // Get the value for this key; if the key was missing, it is added with a "zero-like" default.
   VType& operator[](const KType& Key){
      BASavlNodeT<KType, VType>* pNode = ((BASavlNodeT<KType, VType>*)find((const void*)&Key));
      if (!pNode){
         pNode = new BASavlNodeT<KType, VType>(Key);
         insert(pNode); // TODO - could optimize this!
      }
      return pNode->m_Value;
   }

   // Where to start and stop when looping with a for (...; it != end(); ++it) pattern.
   BASavlIteratorT<KType, VType> begin() { BASavlIteratorT<KType, VType> i(m_pRoot); i.first(); return i; }
   // After the last item: do not read key/value until you --it (see Example D in the comment block above).
   BASavlIteratorT<KType, VType> end()   { BASavlIteratorT<KType, VType> i(m_pRoot); i.end(); return i; }

   // Same loop idea as begin/end, but you may not change values through these iterators.
   BASavlConstIteratorT<KType, VType> cbegin() const { BASavlConstIteratorT<KType, VType> i(m_pRoot); i.first(); return i; }
   BASavlConstIteratorT<KType, VType> cend()   const { BASavlConstIteratorT<KType, VType> i(m_pRoot); i.end(); return i; }

   // Human-readable dump: size, then key = value lines in ascending key order (requires << for KType and VType).
   void printOn(BASwriter& Writer) const {
      Writer << "Size: " << size() << newline;
      for (BASavlConstIteratorT<KType, VType> Iter = cbegin(); Iter != cend(); ++Iter) {
         Writer << Iter.key() << " = " << Iter.value() << newline;
      }
   }
};

template<class KType, class VType>
BASwriter& operator<<(BASwriter& Writer, const BASdictOrdered<KType, VType>& Dict) {
   Dict.printOn(Writer);
   return Writer;
}

template<class KType, class VType>
using BASavlTree = BASdictOrdered<KType, VType>;
