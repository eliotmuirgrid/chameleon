#pragma once
//-------------------------------------------------------
// Copyright (C) 2026 Eliot Muir.  All rights reserved.
//
// BASstring
//
// Plain language:
//   A self-contained holder for text or raw bytes. The string owns its storage; you do not
//   manage a separate buffer. Short strings are stored compactly; any byte pattern is allowed
//   (binary safe). The buffer is always followed by a trailing zero for C-style interop.
//
// Background (readable without knowing C):
//   - Text lives in memory as a sequence of bytes. Any time you handle text, you need to know
//     how long it is (how many bytes belong to this string), not only where it starts.
//   - A pointer is "where the bytes start." By itself it does not say how large the buffer is,
//     who may modify it, who must release the storage when finished, or how long the pointer
//     stays valid. Those questions are about ownership and lifetime.
//   - Ownership: something obtained the storage; it remains valid for a span of time. Using it
//     after that span ends is wrong; never releasing reusable storage when you are done with it
//     wastes memory (a leak).
//   - If you write more bytes than fit in the space reserved for the string, you overrun the
//     buffer; classic bug. You need both a starting place and a bound (size or capacity).
//   - Two common ways to know "how long": (1) keep an explicit byte count, or (2) pick a
//     special byte value that means "end here" and scan until you see it (a sentinel). The
//     usual C convention is a zero byte (often written '\0') as that sentinel.
//   - If the real payload can contain the same value as the sentinel (for example a zero in the
//     middle of binary data), scanning for the sentinel does not give the true length; you need
//     a stored count. That is why "binary safe" and explicit length matter.
//   - Appending can require more contiguous space than you started with: something must obtain
//     a larger buffer, copy the old content, and discard the old buffer. BASstring handles
//     that growth; raw pointers do not, by themselves.
//
// Why use this instead of plain C strings (const char* / char*)?
//   A C string is only a pointer to bytes; length is implied by scanning for the first '\0'.
//   That makes it easy to get wrong: buffer overruns if the buffer is too small, use-after-free
//   if someone frees memory you still point at, leaks if you allocate but never free, and
//   ambiguity about who owns the storage when pointers are passed around.
//   BASstring keeps one clear owner for the storage, tracks length explicitly (so embedded '\0'
//   bytes and arbitrary binary payloads are representable), grows the buffer when you append,
//   and releases heap memory automatically when the string is destroyed or reset. You still
//   get c_str() / data() when you need to call C APIs.
//
// Syntax examples (illustrative; not a complete API list):
//
//   BASstring a;                          // empty
//   BASstring b("hello");                 // from a C string (copied)
//   BASstring c("ab\0cd", 4);             // four bytes, may contain embedded '\0'
//   BASstring d = BAS_T("literal");       // compile-time length (no strlen at runtime)
//
//   b += ", world";                       // append C string
//   b += BAS_T("!");                      // append literal
//   b += c;                               // append another BASstring
//   BASstring path = a + "/" + b;         // concatenation (also: char* on either side)
//
//   if (b == BASstring("hello, world!"))  // compare to BASstring
//   if (b == "hello, world!")             // compare to C string (nil-terminated)
//
//   int n = b.size();                     // byte length excluding the trailing nil
//   const char* p = b.c_str();            // pointer to data; remains valid until b changes
//   char ch = b[0];                       // unchecked index
//
//   b.clear();                            // length to zero, keep capacity
//   b.zero();                             // release heap storage if any, back to empty
//
//   BASout << b << newline;               // formatted output (needs BASwriter overload in scope)
//
// Technical summary:
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

class BASwriter;

// Literal optimization.
//
// Use BAS_T("abc") to construct or append string literals without calling
// strlen() at runtime.
//
// Why avoid strlen here: strlen walks the bytes until it finds '\0', so the cost is O(n)
// and paid every time you need the length. A string literal is fixed at compile time; its
// length is sizeof("literal") - 1 (the compiler counts bytes, including the trailing '\0',
// then we subtract one). BAS_T passes pointer + length into BAStextLiteral so copies and
// appends use that count directly with no scan.
//
// Example:
//    BASstring S = BAS_T("abc");
//    S += BAS_T("def");
//
// Do not use BAStextLiteral directly outside the BAS library.

struct BAStextLiteral {
   constexpr BAStextLiteral(const char* pData, int Length)
      : m_pData(pData), m_Length(Length) {}

   const char* m_pData;
   int         m_Length;
};

#define BAS_T(X_) BAStextLiteral((X_), (int)(sizeof(X_) - 1))

class BASstring {
public:
   BASstring();
   BASstring(const BASstring& Orig);
   BASstring(const char* pString);
   BASstring(const char* pData, int Size);
   BASstring(BAStextLiteral Literal);
   ~BASstring();
   // Basic properties
   int  size() const     { return m_Size; }
   int  length() const   { return m_Size; }
   bool empty() const    { return m_Size == 0; }
   // Capacity is the number of bytes available excluding the trailing nil.
   // capacity() is always >= size().
   int  capacity() const { return m_Capacity; }
   // Ensure capacity for at least NewCapacity bytes of content. Actual capacity may be larger.
   void setCapacity(int NewCapacity);
   // Reduce size to zero, but retain capacity.
   void clear();
   // Reset to empty and release heap storage if any.
   void zero();
   // Returns pointer to string data. Buffer is always nil terminated.
   char*       data()       { return isSmall() ? m_Data.Small : m_Data.pHeap; }
   const char* data() const { return isSmall() ? m_Data.Small : m_Data.pHeap; }
   // Alias for string-oriented APIs.
   const char* c_str() const { return data(); }
   // Direct indexing. No bounds checking.
   char&       operator[](int Index)       { return data()[Index]; }
   const char& operator[](int Index) const { return data()[Index]; }
   // Assignment
   BASstring& operator=(const BASstring& Orig);
   BASstring& operator=(const char* pString);
   BASstring& operator=(BAStextLiteral Literal);
   void set(const char* pData, int Size);
   // Append
   BASstring& append(const char* pData, int Size); // binary safe
   BASstring& append(const char* pString);         // null-terminated string
   BASstring& append(const BASstring& Orig);
   BASstring& append(BAStextLiteral Literal);
   BASstring& append(int Count, char FillChar);

   BASstring& operator+=(const char* pString)       { return append(pString); }
   BASstring& operator+=(const BASstring& Orig)     { return append(Orig); }
   BASstring& operator+=(BAStextLiteral Literal)    { return append(Literal); }
   BASstring& operator+=(char Ch)                   { return append(1, Ch); }
   // Mutation helpers
   // Set logical size. String remains nil terminated. NewSize must be >= 0 and <= capacity().
   // Intended for controlled low-level use.
   void setSize(int NewSize);
   // Swap contents in O(1) time.
   void swap(BASstring* pOther);

   // Comparison
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

// Non-member helpers
int BASgrowCapacity(int* pCapacity, int DesiredCapacity);
unsigned int BASupperPowerOfTwo(unsigned int v);

// Concatenation
BASstring operator+(const BASstring& Lhs, const BASstring& Rhs);
BASstring operator+(const BASstring& Lhs, const char* pRhs);
BASstring operator+(const char* pLhs, const BASstring& Rhs);
BASstring operator+(const BASstring& Lhs, BAStextLiteral Rhs);
BASstring operator+(BAStextLiteral Lhs, const BASstring& Rhs);

// Writer output
BASwriter& operator<<(BASwriter& Writer, const BASstring& String);