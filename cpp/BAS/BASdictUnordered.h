#pragma once
//-------------------------------------------------------
// Copyright (C) 2026 Eliot Muir.  All rights reserved.
//
// BASdictUnordered
//
// An unordered dictionary implemented as a hash table.
//
// As of yet no automatic resizing of the hash buckets.
// You can stream the hash table against a BASstream ala:
// BASdictUnordered<BASstring, int> Table(30);  // set bucket size of 30
//
// BAS_VAR(Table);
//
// This will show it's internal contents and hash structure
// Helpful for tranparency.
// Table.setBucketCount(4);  // change the bucket size - might be expensive?
//-------------------------------------------------------

#include <BAS/BASstring.h>
#include <BAS/BASassert.h>

class BASstream;

// First we define our hash function
unsigned long BASdjb2Hash(const char* str, int Size);
inline unsigned long BAShash(const BASstring& pObject){ return BASdjb2Hash(pObject.data(), pObject.size()); }
inline unsigned long BAShash(const int& Int){ return (unsigned long)Int;}  // Is this a bad hash function?  Hard to say?  Seems to work fine.  Certainly fast.

template<typename T> inline unsigned long BAShash(const T& Object){ return BASdjb2Hash((const char*)&Object, sizeof(T)); }

class BASitem{
public:
   BASitem() : m_pNext(0) {}
   virtual ~BASitem() {}
   virtual void show(BASstream& Stream) const=0;
   BASitem* m_pNext;
};

class BAShashTableBase{
public:
   BAShashTableBase(int BucketCount);
   virtual ~BAShashTableBase();
   int size() const { return m_Size; }
   void clear();
   void printOn(BASstream& Stream) const;
   int bucketCount() const { return m_BucketCount; }
   void setBucketCount(int NewCount);
protected:
   friend class BAShashTableBaseIterator;
   BASitem* insert(unsigned long Hash, BASitem* pItem);
   virtual bool keyEqual(void* pKey, BASitem* pItem2) const=0;
   virtual void destroyItem(BASitem* pItem)=0;
   virtual unsigned long hashItem(BASitem* pItem)=0;
   const BASitem* getItem(unsigned long Hash, void* pKey) const;
   bool removeItem(unsigned long Hash, void* pKey);
private:
   int m_BucketCount;
   BASitem** m_pBuckets;
   int m_Size;
};

class BAShashTableBaseIterator{
public:
   BAShashTableBaseIterator(BAShashTableBase* pTable);
   BAShashTableBaseIterator(BAShashTableBase* pTable, const BASitem* pItem);   // trick for making end()
   virtual ~BAShashTableBaseIterator();
   void first() ;
   void end() ;
   void operator++();
   bool operator!=(const BAShashTableBaseIterator& Rhs) const;
   void show(BASstream& Stream) const;
protected:
  BASitem* m_pItem;
private:
   int m_BucketIndex;
   BAShashTableBase* m_pTable;
};

template<typename KType, typename VType>
class BASdictUnordered : public BAShashTableBase {
public:
   BASdictUnordered(int BucketCount=23) : BAShashTableBase(BucketCount) {}
   virtual ~BASdictUnordered() {clear(); }

   bool has(const KType& Key) const { return getItem(BAShash(Key), (void*)&Key) !=0; }
   bool remove(const KType& Key) { return removeItem(BAShash(Key), (void*)&Key); }

   class BASitemT : public BASitem{
   public:
      BASitemT(const KType& Key, const VType& Value) : m_Key(Key), m_Value(Value) {}
      BASitemT(const KType& Key) : m_Key(Key) {}
      virtual ~BASitemT() {}
      virtual void show(BASstream& Stream) const { Stream << m_Key << " = " << m_Value;}
      KType m_Key;
      VType m_Value;
   };

   class BAShashTableIterator : public BAShashTableBaseIterator{
   public:
       BAShashTableIterator(BAShashTableBase* pTable) : BAShashTableBaseIterator(pTable) { }
       BAShashTableIterator(BAShashTableBase* pTable, const BASitem* pDummy) : BAShashTableBaseIterator(pTable, pDummy) { }
       const KType& key() const   { return ((BASitemT*)m_pItem)->m_Key;   }
       const VType& value() const { return ((BASitemT*)m_pItem)->m_Value; }
       VType& value()             { return ((BASitemT*)m_pItem)->m_Value; }
   };

   class BASconstHashTableIterator {
   public:
      BASconstHashTableIterator(BAShashTableBase* pTable) : m_Iterator(pTable) { }
      BASconstHashTableIterator(BAShashTableBase* pTable, const BASitem* pDummy) : m_Iterator(pTable, pDummy) { }
      const KType& key() const   { return m_Iterator.key();   }
      const VType& value() const { return m_Iterator.value(); }
      void operator++() { ++m_Iterator; }
      bool operator!=(const BASconstHashTableIterator& Rhs) const { return m_Iterator != Rhs.m_Iterator; }
   private:
      BAShashTableIterator m_Iterator;
   };

   BAShashTableIterator begin() { return BAShashTableIterator(this);    }
   BAShashTableIterator end()   { return BAShashTableIterator(this, 0); }
   BASconstHashTableIterator cbegin() const { return BASconstHashTableIterator((BAShashTableBase*)this);    }
   BASconstHashTableIterator cend()   const { return BASconstHashTableIterator((BAShashTableBase*)this, 0); }

   const VType& operator[](const KType& Key) const{
      const BASitem* pItem = getItem(BAShash(Key), (void*)&Key);
      if (!pItem){
        BAS_FAIL("Key: " << Key << " not defined.");
      }
      return ((BASitemT*)pItem)->m_Value;
   }

   VType& operator[](const KType& Key){
      const BASitem* pItem = getItem(BAShash(Key), (void*)&Key);
      if (!pItem){
         unsigned long Hash = BAShash(Key);
         pItem = insert(Hash, new BASitemT(Key));
      }
      return ((BASitemT*)pItem)->m_Value;
   }
   virtual bool keyEqual(void* pKey, BASitem* pItem2) const{ return *((KType*)pKey) == ((BASitemT*)pItem2)->m_Key ; }
   virtual void destroyItem(BASitem* pItem){ delete ((BASitemT*)pItem); }
   virtual unsigned long hashItem(BASitem* pItem){ return BAShash(((BASitemT*)pItem)->m_Key);}
private:
};

template<typename KType, typename VType>
using BAShashTable = BASdictUnordered<KType, VType>;

BASstream& operator<<(BASstream& Stream, const BAShashTableBase& Table);
