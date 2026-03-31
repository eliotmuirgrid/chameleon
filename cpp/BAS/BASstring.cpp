//-------------------------------------------------------
// Copyright (C) 2026 Eliot Muir.  All rights reserved.
//
// BASstring
// 
// Implementation
//-------------------------------------------------------
#include <BAS/BASstring.h>
#include <BAS/BASstream.h>
#include <BAS/BASsink.h>

// To get tracing working with BASstring one really has to do
// it by calling the trace function directly since BASargParser
// uses BASstring so tracing will be switched off before one gets
// here.

#include <BAS/BAStrace.h>
BAS_TRACE_INIT;

#include <string.h>

BASstring::BASstring(){
   init();
   BAS_VAR3(m_Capacity, m_Size, data());
}

BASstring::BASstring(const char* pString){
   BAS_METHOD(BASstring::BAString-char constructor);
   BAS_VAR(pString);
   init();
   append(pString, strlen(pString));
}

BASstring::BASstring(const char* pString, int Size){
   BAS_METHOD(BASstring::BASstring pString + Size);
   BAS_VAR2(pString, Size);
   init();
   append(pString, Size);
}

BASstring::BASstring(const BASstring& Orig){
   BAS_METHOD(BASstring::BASstring - BASstring);
   init();
   append(Orig.data(), Orig.size());
}

BASstring& BASstring::operator=(const char* pString){
   BAS_METHOD(BASstring::operator= pString);
   m_Size = 0;
   append(pString, strlen(pString));
   return *this;
}

// TODO - could optimize more for small strings.
BASstring& BASstring::operator=(const BASstring& Orig){
   BAS_METHOD(BASstring::operator= BASstring);
   m_Size = 0;
   append(Orig.data(), Orig.size());
   return *this;
}

BASstring::~BASstring(){
   BAS_METHOD(BASstring::~BASstring);
   if (m_Capacity >= sizeof(m_pData.ShortBuffer)){
      BAS_TRC("Deleting heap");
      delete []m_pData.pHeap;
   } else{
      BAS_TRC("Short string - so no heap.");
   }
}

BASstring& BASstring::append(const char* pData){
   BAS_METHOD(BASstring::append-nosize);
   return append(pData, strlen(pData));
}

BASstring& BASstring::append(const char* pData, int AddSize){
   BAS_METHOD(BASstring::append);
   BAS_VAR2(m_Capacity, m_Size);
   BAS_VAR2(pData,AddSize);
   BAS_VAR(data());
   if (m_Size + AddSize > m_Capacity){
      BAS_TRC("Increase capacity");
      setCapacity(BASupperPowerOfTwo(m_Size+AddSize+1));
   }
   BAS_TRC("Before copy");
   strncpy((data() + m_Size), pData, AddSize);
   BAS_TRC("After copy");
   m_Size += AddSize;
   data()[m_Size] = 0;  // NULL terminate
   BAS_VAR2(m_Size, m_Capacity); 
   BAS_VAR(data());
   return *this;   
}


// Short --> Short
// Short --> Long
// Long --> Short
// Long --> Long
void BASstring::setCapacity(int NewCapacity){
   BAS_METHOD(BASstring::setCapacity);
   BAS_VAR4(m_Capacity, m_Size, NewCapacity, data());
   if (m_Capacity < sizeof(m_pData.ShortBuffer)){
      if (NewCapacity < sizeof(m_pData.ShortBuffer)){
         BAS_TRC("Short to short");
         m_Capacity = NewCapacity;
      } else {
         BAS_TRC("Short to long");
         char* pNewHeap = new char[NewCapacity];
         strncpy(pNewHeap, data(), m_Size+1);
         m_Capacity = NewCapacity;
         m_pData.pHeap = pNewHeap;
      }
      BAS_VAR3(m_Capacity, m_Size, data());
      return;
   }
   // Coming from Long
   if (NewCapacity < sizeof(m_pData.ShortBuffer)){
      BAS_TRC("Long to Short");
      char* pOldHeap = m_pData.pHeap;
      m_Capacity = NewCapacity;
      strncpy(m_pData.ShortBuffer, pOldHeap, m_Size+1);
      delete pOldHeap;
   } else {
      BAS_TRC("Long to Long");
      char* pOldHeap = m_pData.pHeap;
      char* pNewHeap = new char[NewCapacity];
      strncpy(pNewHeap, pOldHeap, m_Size+1);
      m_Capacity = NewCapacity;
      m_pData.pHeap = pNewHeap;
      delete pOldHeap;
   }
   
   BAS_VAR3(m_Capacity, m_Size, data());
}

BASstring& BASstring::operator+=(const char* pData){
   return append(pData, strlen(pData));
}

BASstring& BASstring::operator+=(const BASstring& Orig){
   return append(Orig.data(), Orig.size());
}

int BASstring::compare(const BASstring& Lhs) const { 
   BAS_METHOD(BASstring::compare);
   return strcmp(data(), Lhs.data());
}

bool BASstring::operator!=(const char* pData) const{
   return strcmp(data(), pData) != 0;
}

bool BASstring::operator==(const BASstring& Rhs) const{
   if (size() != Rhs.size()){
      return false;
   }
   return memcmp(data(), Rhs.data(), size()) == 0; 
}



BASstring operator+(const BASstring& Lhs, const char*   pRhs  ) { BASstring X(Lhs); X+= pRhs; return X;}
BASstring operator+(const BASstring& Lhs, const BASstring& Rhs) { BASstring X(Lhs); X+= Rhs; return X;}


BASstream& operator<<(BASstream& Stream, const BASstring& String){
   Stream.sink()->write(String.data(), String.size());
   return Stream;
}

unsigned int BASupperPowerOfTwo(unsigned int v){
   BAS_FUNCTION(BASupperPowerOfTwo);
   BAS_VAR(v);
   v--;
   v |= v >> 1;
   v |= v >> 2;
   v |= v >> 4;
   v |= v >> 8;
   v |= v >> 16;
   v++;
   BAS_VAR(v);
   return v;
}
