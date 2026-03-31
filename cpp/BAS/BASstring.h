#pragma once
//-------------------------------------------------------
// Copyright (C) 2026 Eliot Muir.  All rights reserved.
//
// BASstring
//
// Core owned string / byte-buffer class.
// - Small string optimization
// - Binary safe
// - Always null terminated
// - Minimal interface
//
// Design goals:
// - Easy for humans to understand
// - Easy for AI tools to understand
// - Keep storage separate from algorithms
//-------------------------------------------------------

class BASstream;

//=============================================================================
// Literal optimization.
//
// Use BAS_T("abc") to construct or append string literals without calling
// strlen() at runtime.
//
// Example:
//    BASstring S = BAS_T("abc");
//    S += BAS_T("def");
//
// Do not use BAStextLiteral directly outside the BAS library.
//=============================================================================

struct BAStextLiteral {
   constexpr BAStextLiteral(const char* pData, int Length)
      : m_pData(pData), m_Length(Length) {}

   const char* m_pData;
   int         m_Length;
};

#define BAS_T(X_) BAStextLiteral((X_), (int)(sizeof(X_) - 1))

//=============================================================================

class BASstring {
public:
   BASstring();
   BASstring(const BASstring& Orig);
   BASstring(const char* pString);
   BASstring(const char* pData, int Size);
   BASstring(BAStextLiteral Literal);

   ~BASstring();

   //-------------------------------------------------------------------------
   // Basic properties
   //-------------------------------------------------------------------------

   int  size() const     { return m_Size; }
   int  length() const   { return m_Size; }
   bool empty() const    { return m_Size == 0; }

   // Capacity is the number of bytes available excluding the trailing nil.
   // capacity() is always >= size().
   int  capacity() const { return m_Capacity; }

   // Ensure capacity for at least NewCapacity bytes of content.
   // Actual capacity may be larger.
   void setCapacity(int NewCapacity);

   // Reduce size to zero, but retain capacity.
   void clear();

   // Reset to empty and release heap storage if any.
   void zero();

   //-------------------------------------------------------------------------
   // Data access
   //-------------------------------------------------------------------------

   // Returns pointer to string data. Buffer is always nil terminated.
   char*       data()       { return isSmall() ? m_Data.Small : m_Data.pHeap; }
   const char* data() const { return isSmall() ? m_Data.Small : m_Data.pHeap; }

   // Alias for string-oriented APIs.
   const char* c_str() const { return data(); }

   // Direct indexing. No bounds checking.
   char&       operator[](int Index)       { return data()[Index]; }
   const char& operator[](int Index) const { return data()[Index]; }

   //-------------------------------------------------------------------------
   // Assignment
   //-------------------------------------------------------------------------

   BASstring& operator=(const BASstring& Orig);
   BASstring& operator=(const char* pString);
   BASstring& operator=(BAStextLiteral Literal);

   void set(const char* pData, int Size);

   //-------------------------------------------------------------------------
   // Append
   //-------------------------------------------------------------------------

   BASstring& append(const char* pData, int Size); // binary safe
   BASstring& append(const char* pString);         // null-terminated string
   BASstring& append(const BASstring& Orig);
   BASstring& append(BAStextLiteral Literal);
   BASstring& append(int Count, char FillChar);

   BASstring& operator+=(const char* pString)       { return append(pString); }
   BASstring& operator+=(const BASstring& Orig)     { return append(Orig); }
   BASstring& operator+=(BAStextLiteral Literal)    { return append(Literal); }
   BASstring& operator+=(char Ch)                   { return append(1, Ch); }

   //-------------------------------------------------------------------------
   // Mutation helpers
   //-------------------------------------------------------------------------

   // Set logical size. String remains nil terminated.
   // NewSize must be >= 0 and <= capacity().
   // Intended for controlled low-level use.
   void setSize(int NewSize);

   // Swap contents in O(1) time.
   void swap(BASstring* pOther);

   //-------------------------------------------------------------------------
   // Comparison
   //-------------------------------------------------------------------------
   // Note:
   // compare()/operator== with BASstring are binary safe.
   // compare()/operator== with const char* assume pString is nil terminated.

   int  compare(const BASstring& Rhs) const;
   int  compare(const char* pString) const;

   bool equals(const BASstring& Rhs) const { return compare(Rhs) == 0; }
   bool equals(const char* pString) const  { return compare(pString) == 0; }

   bool operator==(const BASstring& Rhs) const { return equals(Rhs); }
   bool operator!=(const BASstring& Rhs) const { return !equals(Rhs); }

   bool operator==(const char* pString) const  { return equals(pString); }
   bool operator!=(const char* pString) const  { return !equals(pString); }

private:
   enum { kSmallCapacity = 15 }; // 15 chars + trailing nil in 16-byte buffer

   void init();
   void ensureCapacity(int DesiredCapacity);

   bool isSmall() const { return m_Capacity <= kSmallCapacity; }

private:
   int m_Size;      // bytes in string excluding trailing nil
   int m_Capacity;  // usable bytes excluding trailing nil

   union Data {
      char  Small[kSmallCapacity + 1];
      char* pHeap;

      Data() {}
      ~Data() {}
   } m_Data;
};

//=============================================================================
// Non-member helpers
//=============================================================================

int BASgrowCapacity(int* pCapacity, int DesiredCapacity);
unsigned int BASupperPowerOfTwo(unsigned int v);

// Concatenation
BASstring operator+(const BASstring& Lhs, const BASstring& Rhs);
BASstring operator+(const BASstring& Lhs, const char* pRhs);
BASstring operator+(const char* pLhs, const BASstring& Rhs);
BASstring operator+(const BASstring& Lhs, BAStextLiteral Rhs);
BASstring operator+(BAStextLiteral Lhs, const BASstring& Rhs);

// Stream output
BASstream& operator<<(BASstream& Stream, const BASstring& String);