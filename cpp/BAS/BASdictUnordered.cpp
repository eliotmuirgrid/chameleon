//-------------------------------------------------------
// Copyright (C) 2026 Eliot Muir.  All rights reserved.
//
// BASdictUnordered
//
// Implementation
//-------------------------------------------------------

#include <BAS/BASdictUnordered.h>
#include <BAS/BAStrace.h>
BAS_TRACE_INIT;

#include <string.h>

//http://www.cse.yorku.ca/~oz/hash.html
unsigned long BASdjb2Hash(const char* str, int Size){
   unsigned long hash = 5381;
   int c;
   const char* pEnd = str+Size;
   for (;str != pEnd; str++){
      c = *str;
      hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
   }
   return hash;
}

BAShashTableBase::BAShashTableBase(int BucketCount) : m_BucketCount(BucketCount), m_Size(0) {
   BAS_METHOD(BAShashTableBase::BAShashTableBase);
   BAS_VAR(m_BucketCount)
   m_pBuckets = new BASitem*[m_BucketCount+1];  // TODO - do we need +1?
   for (int i=0; i < m_BucketCount; i++){
      m_pBuckets[i] = NULL;
   }
}

BAShashTableBase::~BAShashTableBase(){
   BAS_METHOD(BAShashTableBase::~BAShashTableBase);
   delete []m_pBuckets;
}

void BAShashTableBase::clear(){
   BAS_METHOD(BAShashTableBase::clear);
   for (int i=0; i < m_BucketCount; i++){
      BASitem* pItem = m_pBuckets[i];
      while (pItem){
         BASitem* pNext = pItem->m_pNext;
         destroyItem(pItem);
         pItem = pNext;
      }
      m_pBuckets[i] = NULL;
   }
   m_Size = 0;
}

BASitem* BAShashTableBase::insert(unsigned long Hash, BASitem* pItem){
   BAS_METHOD(BAShashTableBase::insert);
   BAS_VAR(Hash);
   int i = Hash % m_BucketCount;
   BAS_VAR(i);
   pItem->m_pNext = m_pBuckets[i];
   m_pBuckets[i]= pItem;
   m_Size++;
   return pItem;
}

const BASitem* BAShashTableBase::getItem(unsigned long Hash, void* pKey) const{
   BAS_METHOD(BAShashTableBase::getItem);
   BAS_VAR(Hash);
   int i = Hash % m_BucketCount;
   BAS_VAR(i);
   BASitem* pItem = m_pBuckets[i];
   for (; pItem !=NULL; pItem = pItem->m_pNext){
      if (keyEqual(pKey, pItem)){
         BAS_TRC("Found key.");
         return pItem;
      }
   }
   BAS_TRC("Key not present.");
   return NULL;
}

bool BAShashTableBase::removeItem(unsigned long Hash, void* pKey) {
   BAS_METHOD(BAShashTableBase::removeItem);
   BAS_VAR(Hash);
   int i = Hash % m_BucketCount;
   BAS_VAR(i);
   BASitem* pItem = m_pBuckets[i];
   BASitem** ppLastNext = &m_pBuckets[i];
   for (; pItem !=NULL; pItem = pItem->m_pNext){
      BAS_VAR2(*ppLastNext, pItem);
      if (keyEqual(pKey, pItem)){
         BAS_TRC("Found key to remove");
         BAS_VAR(pItem->m_pNext);
         *ppLastNext = pItem->m_pNext;
         destroyItem(pItem);
         m_Size--;
         return true;
      }
      ppLastNext = &pItem;
   }
   BAS_TRC("Key not present.");
   return false;
}

void BAShashTableBase::printOn(BASwriter& Writer) const{
   int Count = 0;
   Writer << "Size:   " << m_Size << newline
         <<  "Buckets:" << m_BucketCount << newline;
   for (int i=0; i < m_BucketCount; i++){
      BASitem* pItem = m_pBuckets[i];
      Writer << "Bucket[" << i << "]" << newline;
      while (pItem){
         Count++;
         Writer << " ";
         pItem->show(Writer);
         Writer << newline;
         pItem = pItem->m_pNext;
      }
   }
   Writer << "Count: " << Count << newline;
   if (Count != m_Size){
      Writer << "CRAP - count of items != size" << newline;
   }
}

void BAShashTableBase::setBucketCount(int NewCount){
   BAS_METHOD(BASdictUnordered::setBucketCount);
   BAS_VAR(NewCount);
   BASitem** ppNewBuckets = new BASitem*[NewCount+1];
   for (int i=0; i < NewCount; i++){
      ppNewBuckets[i] = NULL;
   }
   BAS_TRC("Cleared buckets.");
   for (int i=0; i < m_BucketCount; i++){
      BASitem* pItem = m_pBuckets[i];
      BAS_VAR2(i, pItem);
      while (pItem){
         BASitem* pNextItem = pItem->m_pNext;
         int j = hashItem(pItem) % NewCount;
         BAS_VAR2(j, pNextItem);
         pItem->m_pNext = ppNewBuckets[j];
         ppNewBuckets[j]= pItem;
         pItem = pNextItem;
      }
   }

   delete []m_pBuckets;
   m_pBuckets = ppNewBuckets;
   m_BucketCount = NewCount;
}

BASwriter& operator<<(BASwriter& Writer, const BAShashTableBase& Table){
   Table.printOn(Writer);
   return Writer;
}

BAShashTableBaseIterator::BAShashTableBaseIterator(BAShashTableBase* pTable) : m_pTable(pTable){
   BAS_METHOD(BAShashTableBaseIterator);
   first();
}

BAShashTableBaseIterator::BAShashTableBaseIterator(BAShashTableBase* pTable, const BASitem* pDummy) : m_pTable(pTable){
   BAS_METHOD(BAShashTableBaseIterator);
   end();
}


BAShashTableBaseIterator::~BAShashTableBaseIterator(){
   BAS_METHOD(~BAShashTableBaseIterator);
}

void BAShashTableBaseIterator::first() {
   BAS_METHOD(BAShashTableBaseIterator::first);
   m_pItem = m_pTable->m_pBuckets[0];
   m_BucketIndex = 0;
   ++(*this);
}

void BAShashTableBaseIterator::end() {
   BAS_METHOD(BAShashTableBaseIterator::end);
   m_pItem = NULL;
   m_BucketIndex = m_pTable->bucketCount();
}


void BAShashTableBaseIterator::operator++(){
   BAS_METHOD(BAShashTableBase::operator++);
   BAS_VAR2(m_pItem, m_BucketIndex);
   if (m_pItem){
      m_pItem = m_pItem->m_pNext;
   }
   while (m_pItem == NULL && m_BucketIndex < m_pTable->bucketCount()){
      m_pItem = m_pTable->m_pBuckets[m_BucketIndex];
      m_BucketIndex++;
   }
   BAS_VAR2(m_pItem, m_BucketIndex);
}

bool BAShashTableBaseIterator::operator!=(const BAShashTableBaseIterator& Rhs) const{
   BAS_METHOD(BAShashTableBaseIterator::operator!=);
   return !(m_BucketIndex == Rhs.m_BucketIndex && m_pItem == Rhs.m_pItem);
}


void BAShashTableBaseIterator::show(BASwriter& Writer) const{
   m_pItem->show(Writer);
}
