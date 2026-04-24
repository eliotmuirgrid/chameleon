//-------------------------------------------------------
// Copyright (C) 2026 Eliot Muir.  All rights reserved.
//
// BASstring
//
// Implementation
//-------------------------------------------------------
#include <BAS/BASstring.h>
#include <BAS/BASwriter.h>
#include <BAS/BASdestination.h>

// To get tracing working with BASstring one really has to do
// it by calling the trace function directly since BAScommandLine
// uses BASstring so tracing will be switched off before one gets
// here.

#include <BAS/BAStrace.h>
BAS_TRACE_INIT;

#include <string.h>

static const int kBASSmallCapacity = 15;

void BASstring::init() {
   m_Size = 0;
   m_Capacity = kSmallCapacity;
   m_Data.Small[0] = 0;
}

void BASstring::ensureCapacity(int DesiredCapacity) {
   if (DesiredCapacity > m_Capacity) {
      int NewCapacity = m_Capacity;
      BASgrowCapacity(&NewCapacity, DesiredCapacity);
      setCapacity(NewCapacity);
   }
}

BASstring::BASstring() {
   init();
   BAS_VAR3(m_Capacity, m_Size, data());
}

BASstring::BASstring(const BASstring& Orig) {
   BAS_METHOD(BASstring::BASstring-copy);
   init();
   append(Orig);
}

BASstring::BASstring(const char* pString) {
   BAS_METHOD(BASstring::BASstring-char);
   BAS_VAR(pString);
   init();
   append(pString);
}

BASstring::BASstring(const char* pString, int Size) {
   BAS_METHOD(BASstring::BASstring-bytes);
   BAS_VAR2(pString, Size);
   init();
   set(pString, Size);
}

BASstring::BASstring(BAStextLiteral Literal) {
   BAS_METHOD(BASstring::BASstring-literal);
   init();
   append(Literal);
}

BASstring::~BASstring() {
   BAS_METHOD(BASstring::~BASstring);
   if (!isSmall()) {
      BAS_TRC("Deleting heap");
      delete [] m_Data.pHeap;
   } else {
      BAS_TRC("Short string - so no heap.");
   }
}

BASstring& BASstring::operator=(const BASstring& Orig) {
   BAS_METHOD(BASstring::operator=-BASstring);
   if (this != &Orig) {
      set(Orig.data(), Orig.size());
   }
   return *this;
}

BASstring& BASstring::operator=(const char* pString) {
   BAS_METHOD(BASstring::operator=-char);
   if (pString == NULL) {
      clear();
   } else {
      set(pString, static_cast<int>(strlen(pString)));
   }
   return *this;
}

BASstring& BASstring::operator=(BAStextLiteral Literal) {
   BAS_METHOD(BASstring::operator=-literal);
   set(Literal.m_pData, Literal.m_Length);
   return *this;
}

void BASstring::set(const char* pData, int Size) {
   BAS_METHOD(BASstring::set);
   clear();
   append(pData, Size);
}

void BASstring::setCapacity(int NewCapacity) {
   BAS_METHOD(BASstring::setCapacity);
   BAS_VAR4(m_Capacity, m_Size, NewCapacity, data());
   if (NewCapacity < m_Size) {
      NewCapacity = m_Size;
   }
   if (NewCapacity <= kSmallCapacity) {
      if (isSmall()) {
         m_Capacity = kSmallCapacity;
      } else {
         char* pOldHeap = m_Data.pHeap;
         ::memcpy(m_Data.Small, pOldHeap, static_cast<size_t>(m_Size) + 1);
         delete [] pOldHeap;
         m_Capacity = kSmallCapacity;
      }
      BAS_VAR3(m_Capacity, m_Size, data());
      return;
   }

   char* pNewHeap = new char[static_cast<size_t>(NewCapacity) + 1];
   ::memcpy(pNewHeap, data(), static_cast<size_t>(m_Size) + 1);
   if (!isSmall()) {
      delete [] m_Data.pHeap;
   }
   m_Data.pHeap = pNewHeap;
   m_Capacity = NewCapacity;
   BAS_VAR3(m_Capacity, m_Size, data());
}

void BASstring::clear() {
   BAS_METHOD(BASstring::clear);
   m_Size = 0;
   data()[0] = 0;
}

void BASstring::zero() {
   BAS_METHOD(BASstring::zero);
   if (!isSmall()) {
      delete [] m_Data.pHeap;
   }
   init();
}

BASstring& BASstring::append(const char* pString) {
   BAS_METHOD(BASstring::append-string);
   if (pString == NULL) {
      return *this;
   }
   return append(pString, static_cast<int>(strlen(pString)));
}

BASstring& BASstring::append(const char* pData, int AddSize) {
   BAS_METHOD(BASstring::append-bytes);
   BAS_VAR2(m_Capacity, m_Size);
   BAS_VAR2(pData, AddSize);
   if (pData == NULL || AddSize <= 0) {
      return *this;
   }

   const char* pCurrentData = data();
   bool IsSelfAppend = (pData >= pCurrentData) && (pData < pCurrentData + m_Size);
   if (IsSelfAppend) {
      BASstring Copy(pData, AddSize);
      return append(Copy.data(), Copy.size());
   }

   ensureCapacity(m_Size + AddSize);
   ::memcpy(data() + m_Size, pData, static_cast<size_t>(AddSize));
   m_Size += AddSize;
   data()[m_Size] = 0;
   BAS_VAR2(m_Size, m_Capacity);
   BAS_VAR(data());
   return *this;
}

BASstring& BASstring::append(const BASstring& Orig) {
   BAS_METHOD(BASstring::append-BASstring);
   return append(Orig.data(), Orig.size());
}

BASstring& BASstring::append(BAStextLiteral Literal) {
   BAS_METHOD(BASstring::append-literal);
   return append(Literal.m_pData, Literal.m_Length);
}

BASstring& BASstring::append(int Count, char FillChar) {
   BAS_METHOD(BASstring::append-fill);
   if (Count <= 0) {
      return *this;
   }
   ensureCapacity(m_Size + Count);
   ::memset(data() + m_Size, FillChar, static_cast<size_t>(Count));
   m_Size += Count;
   data()[m_Size] = 0;
   return *this;
}

void BASstring::setSize(int NewSize) {
   BAS_METHOD(BASstring::setSize);
   if (NewSize < 0) {
      NewSize = 0;
   }
   ensureCapacity(NewSize);
   m_Size = NewSize;
   data()[m_Size] = 0;
}

void BASstring::swap(BASstring* pOther) {
   BAS_METHOD(BASstring::swap);
   if (pOther == NULL || pOther == this) {
      return;
   }
   BASstring Temp(*this);
   *this = *pOther;
   *pOther = Temp;
}

void BASstring::toLowercase() {
   BAS_METHOD(BASstring::toLowercase);
   char* p = data();
   for (int I = 0; I < m_Size; ++I) {
      if (p[I] >= 'A' && p[I] <= 'Z') {
         p[I] = static_cast<char>(p[I] - 'A' + 'a');
      }
   }
}

void BASstring::toUppercase() {
   BAS_METHOD(BASstring::toUppercase);
   char* p = data();
   for (int I = 0; I < m_Size; ++I) {
      if (p[I] >= 'a' && p[I] <= 'z') {
         p[I] = static_cast<char>(p[I] - 'a' + 'A');
      }
   }
}

int BASstring::compare(const BASstring& Rhs) const {
   BAS_METHOD(BASstring::compare-BASstring);
   const int SharedSize = m_Size < Rhs.m_Size ? m_Size : Rhs.m_Size;
   const int CompareResult = SharedSize > 0 ? ::memcmp(data(), Rhs.data(), static_cast<size_t>(SharedSize)) : 0;
   if (CompareResult != 0) {
      return CompareResult;
   }
   if (m_Size == Rhs.m_Size) {
      return 0;
   }
   return m_Size < Rhs.m_Size ? -1 : 1;
}

int BASstring::compare(const char* pString) const {
   BAS_METHOD(BASstring::compare-char);
   if (pString == NULL) {
      pString = "";
   }
   return ::strcmp(data(), pString);
}

int BASgrowCapacity(int* pCapacity, int DesiredCapacity) {
   BAS_FUNCTION(BASgrowCapacity);
   if (pCapacity == NULL) {
      return DesiredCapacity <= kBASSmallCapacity ? kBASSmallCapacity :
         static_cast<int>(BASupperPowerOfTwo(static_cast<unsigned int>(DesiredCapacity + 1))) - 1;
   }
   if (DesiredCapacity <= kBASSmallCapacity) {
      *pCapacity = kBASSmallCapacity;
   } else {
      *pCapacity = static_cast<int>(BASupperPowerOfTwo(static_cast<unsigned int>(DesiredCapacity + 1))) - 1;
   }
   return *pCapacity;
}

BASstring operator+(const BASstring& Lhs, const BASstring& Rhs) {
   BASstring X(Lhs);
   X += Rhs;
   return X;
}

BASstring operator+(const BASstring& Lhs, const char* pRhs) {
   BASstring X(Lhs);
   X += pRhs;
   return X;
}

BASstring operator+(const char* pLhs, const BASstring& Rhs) {
   BASstring X(pLhs);
   X += Rhs;
   return X;
}

BASstring operator+(const BASstring& Lhs, BAStextLiteral Rhs) {
   BASstring X(Lhs);
   X += Rhs;
   return X;
}

BASstring operator+(BAStextLiteral Lhs, const BASstring& Rhs) {
   BASstring X(Lhs);
   X += Rhs;
   return X;
}

BASwriter& operator<<(BASwriter& Writer, const BASstring& String) {
   Writer.destination()->write(String.data(), String.size());
   return Writer;
}

unsigned int BASupperPowerOfTwo(unsigned int v) {
   BAS_FUNCTION(BASupperPowerOfTwo);
   BAS_VAR(v);
   if (v == 0) {
      return 1;
   }
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
