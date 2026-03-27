#pragma once
//-----------------------------------------------------------------------------
// Copyright (C) 2026 Eliot Muir.  All rights reserved.
//
// Module:  CORstring
// 
// Description
//
// CORstring is the core string class.  This code evolved from earlier work by the author
// prior to any incorporated entity; copyright in this file is as stated above.
//
// Author: Eliot Muir
//-----------------------------------------------------------------------------

#include <COR/CORcore.h>

//=============================================================================
// The COR_T "literal string" optimization to avoid calling strlen().
//
// Examples:
//
//   CORstring MyString = COR_T("abc");
//   CORostream MyStringStream(MyString);
//   MyStringStream << COR_T("def")
//   MyString = COR_T("ghi");
//   MyString += COR_T("xyz");

#define COR_T(X_) CORtextLiteral((X_),(sizeof(X_)-1))

// NEVER use CORtextLiteral directly outside of the COR library - use COR_T() instead.
struct CORtextLiteral {
   inline CORtextLiteral(const char* StringLiteral, unsigned Length) : m_String(StringLiteral), m_Length(Length) {}
   // Do not add any methods or a destructor to this struct so it will be inlined.
   const char* m_String;
   unsigned    m_Length;
};

//=============================================================================

class CORstring {
public:
   enum StripType { Leading = 1, Trailing = 2, Both = Leading|Trailing };

   CORstring();
   CORstring(const CORstring& that);
   CORstring(const char* s);
   CORstring(const char* s, int length);
   CORstring(int InitialSize, char InitializationChar);

   // Optimization for C string literals to avoid a strlen() call when constructing a CORstring.
   // For example: 
   //   CORstring str("foo");        // not optimized - calls strlen internally.
   //   CORstring str(COR_T("foo")); // optimized.
   CORstring(const CORtextLiteral& stringLiteral);

   // Windows wide strings
   CORstring(const wchar_t* WideCharacterString);
   CORstring& operator=(const wchar_t* pValue);

   ~CORstring();

   int size() const { return _length; }       // Get length of string without trailing nil byte.

   int capacity() const { return _capacity; } // Get capacity. capacity() always greater than size().
   void setCapacity(int capacity);            // Hint to set new capacity. Capacity set may be larger.

   const bool is_null(void) const { return _length == 0; }

   const char* c_str() const;
   const char* data() const;

   // ExampleString = COR_T("xyz");
   inline CORstring& operator=(const CORtextLiteral& stringLiteral) {
      set(stringLiteral.m_String, stringLiteral.m_Length); return *this;
   }
   // ExampleString += COR_T("xyz");
   inline CORstring& operator+=(const CORtextLiteral& stringLiteral) {
      append(stringLiteral.m_String, stringLiteral.m_Length); return *this;
   }

   // string assignment - overwrite original.
   CORstring& operator=(const CORstring& that);
   CORstring& operator=(const char* s);
   void set(const char*, int len);  // set a string with length

   // append operators
   inline CORstring& operator+=(const char* s)      { return append(s); }    // append string
   inline CORstring& operator+=(const CORstring& s) { return append(s); }    // append CORstring
   inline CORstring& operator+=(char b)             { return append(1, b); } // append byte

   // char array access methods
   char& operator[](int pos);
   char operator[](int pos) const;

   void clear();  // Resets string to "", retaining its capacity.
   void zero();   // Resets string to "", reduces its capacity.

   // Discard 'n' bytes from the beginning of the string buffer.
   // Capacity remains the same. CORstring::size() is reduced by 'n'.
   // 'n' must be less than or equal to size(), but not negative.
   void shift(int n);

   // Shrink heap use to CapacityHint if possible without altering the string.
   // Note: actual capacity() after this call will not necessarily match CapacityHint.
   // Note: Do not use old CORstring::data() and CORstring::c_str() values after this call.
   void shrink(int CapacityHint = 0);

   // swap strings and capacities
   void swap(CORstring* pString);

   // Return substring from `begin' position to the end of the string.
   CORstring substr(int begin) const;

   // Return substring from `begin' position max of `length' characters.
   // NOTE: length can be `COR_NPOS', in which case return substr(begin).
   // For future code, do not rely on this "length could be COR_NPOS" trick.
   CORstring substr(int begin, int length) const;

   CORstring& toUpperCase();  // Modifies string: converts CORstring to uppercase via stdlib toupper().
   CORstring& toLowerCase();  // Modifies string: converts CORstring to lowercase via stdlib tolower().

   CORstring& append(int AppendCharRepeatCount, char AppendChar);       // binary safe
   CORstring& append(const CORstring& AppendString);                    // binary safe
   CORstring& append(const char* AppendString, int AppendStringLength); // binary safe
   CORstring& append(const char* AppendString);

   // true if the CORstring is only whitespace (spaces, tabs, carriage returns, or newlines), false otherwise
   bool isWhitespace() const;

   // Splits the CORstring using the token provided as the delimiter and returns the values in the provided strings. 
   // rpslit uses the last occurance of the token in the string  as the split point.
   // If no token is found rpslit returns the input as the second argument and returns false.
   // eg if the string is "path/file1/file2", with token "/" then
   // Out1 = path/file1, Out2 = file2
   bool rsplit(CORstring& Out1, CORstring& Out2, const char* Token) const;
  
   // Splits the CORstring using the token provided as the delimiter and returns the values in the provided strings. 
   // split uses the first occurrence of the token in the string as the split point.
   // If no token is found split returns the input as the first argument and returns false.
   // eg if the string is "path/file1/file2", with token "/" then
   // Out1 = path,  Out2 = file1/file2
   bool split(CORstring& Out1, CORstring& Out2, const char* Token) const;

   // Splits the CORstring at the specified index, and returns the values in the provided strings. 
   // The character at index SplitIndex is the first character of Out2.
   // If SplitIndex is greater than the length of the CORstring object, splitAtIndex returns the
   // input as the first argument, and the second argument is empty.
   //   eg. if the string is "Physician, heal thyself." and Split Index is 11, then 
   // Out1 = "Physician, ",  Out2 = "heal thyself."
   void splitAtIndex(CORstring& Out1, CORstring& Out2, int SplitIndex) const;

   // Returns a pointer to the actual char buffer used by the CORstring
   const char* get_buffer() const;
   char*       get_buffer();

   // Sets the string to be of length Length and filled with the specified FillChar character.
   // Returns the CORstring instance after assignment.
   CORstring& assign(int Length, char FillChar);

   // Does a forward search of the CORstring for the specified character starting at the specified Position.
   // If the character is found then the position (starting index) of the character in the CORstring is returned.
   // If the character is not found COR_NPOS is returned.
   // DEPRECATED: See bool find(int* FoundPosition, const char Character, size_t Position = 0) const
   size_t find(const char Character, size_t Position = 0) const;

   bool find(int* FoundPosition, const char Character, size_t Position = 0) const;

   // Does a forward search of the CORstring for the specified Pattern.
   // If the Pattern is found then the position (starting index) of the Pattern in the CORstring is returned.
   // If the Pattern is not found COR_NPOS is returned.
   // DEPRECATED: See bool find(int* FoundPosition, const char* Pattern) const
   // DEPRECATED: See bool find(int* FoundPosition, const CORstring& Pattern) const
   size_t find(const char*      Pattern) const;
   size_t find(const CORstring& Pattern) const;

   bool find(int* FoundPosition, const char*      Pattern) const;
   bool find(int* FoundPosition, const CORstring& Pattern) const;

   // Does a forward search of the CORstring for the specified Pattern string.
   // If the Pattern string is found then the position (starting index) of the Pattern in the CORstring is returned.
   // If the Pattern string is not found COR_NPOS is returned.
   // DEPRECATED: See bool find(int* FoundPosition, const char* Pattern, size_t Position) const
   // DEPRECATED: See bool find(int* FoundPosition, const CORstring& Pattern, size_t Position) const
   size_t find(const char*      Pattern, size_t Position) const;
   size_t find(const CORstring& Pattern, size_t Position) const;

   bool find(int* FoundPosition, const CORstring& Pattern, size_t Position) const;
   bool find(int* FoundPosition, const char*      Pattern, size_t Position) const;

   // Does a reverse search of the CORstring for the specified pattern.
   // If the pattern is found the position (starting index) of the Pattern in the CORstring is returned.
   // If the Pattern is not found COR_NPOS is returned.
   // DEPRECATED: See bool rfind(int* FoundPosition, const CORstring& Pattern) const
   size_t rfind(const CORstring& Pattern) const;

   bool rfind(int* FoundPosition, const CORstring& Pattern) const;

   // This method does not likely do what you think it does.
   // It does a reverse search of the CORstring for the specified pattern starting from the specified Position. 
   // Position represents the *highest* index into this CORstring that a byte comparison against the Pattern
   // will begin and Position will decrement towards 0 until a matching string is found or the beginning of
   // this CORstring is reached.
   // For example: CORstring("0123456789").rfind("3456",4) will return 3 even though the matched Pattern
   // string length goes above/beyond Position.
   // If the Pattern is found the position (starting index) of the Pattern in the CORstring is returned.
   // If the Pattern is not found COR_NPOS is returned.
   // DEPRECATED: See bool rfind(int* FoundPosition, const CORstring& Pattern, size_t Position) const
   size_t rfind(const CORstring& Pattern, size_t Position) const;

   bool rfind(int* FoundPosition, const CORstring& Pattern, size_t Position) const;

   // Does a reverse search from the specified Position and returns the the position (index) of the first
   // occurrence of ANY of the specified Characters. If no match is found COR_NPOS is returned.
   // DEPRECATED: see bool find_last_of(int* FoundPosition, const CORstring& Characters, size_t Position) const
   size_t find_last_of(const CORstring& Characters, size_t Position = COR_NPOS) const;

   bool find_last_of(int* FoundPosition, const CORstring& Characters, size_t Position = COR_NPOS) const;
   
   // Removes all occurrences of the specified character from the CORstring
   void stripAll(char c = ' ');

   // Returns a new CORstring with consecutive occurrences of the specified character removed removed
   // from the beginning, end, or both ends (depending  on the StripType) of the original CORstring.
   CORstring strip(StripType s = Trailing, char c = ' ') const;
   
   // Returns the result of stdlib strcmp of this CORstring and the specified CORstring
   inline int compare(const CORstring& s) const { return ::strcmp(c_str(), s.c_str()); }

   // Returns the result of stdlib strcmp of this CORstring and the specified C-string
   inline int compare(const char* s) const { return ::strcmp(getStringData(), s); }

   // All comparison operators ultimately call this static method. Calls stdlib strcmp.
   static inline int compare(const char* a, const char* b) { return ::strcmp(a, b); }
   
   // case sensitive equals
   bool equals(const CORstring& s) const;
   bool equals(const char*      s) const;

   // case insensitive equals
   bool equalsIgnoreCase(const CORstring& s) const;
   bool equalsIgnoreCase(const char*      s) const;

   // Case insensitive string compare similar to stricmp/strcasecmp.
   // Returns 0 for equal, negative if this is less than s, positive if this is greater than s.
   int icompare(const CORstring& s) const;
   int icompare(const char*      s) const;

   // Case insensitive string compare similar to stricmp/strcasecmp.
   static int icompare(const char* s1, const char* s2);

   // Removes the specified NumberOfCharacters from the string starting at the specified StartIndex. 
   // A reference to the modified string is also returned.
   CORstring& remove(size_t StartIndex, size_t NumberOfCharacters = COR_NPOS);

   // Replaces all occurrences of the specified substring in the CORstring with the specified ReplacementString.
   // Case sensitive. Returns number of Substrings replaced.
   size_t replace(const CORstring& Substring, const CORstring& ReplacementString);

   // Replaces all occurrences of FromChar with ToChar.
   // This version of replace() that is much faster for char replacement.
   // Works correctly with binary data with embedded nil characters up to size().
   void replace(char FromChar, char ToChar);
   
   // Replaces the specified NumberOfCharacters starting at StartIndex with ReplacementString.
   // Optionally you may specify to use a substring of the ReplacementString.
   CORstring& replace(size_t StartIndex, size_t NumberOfCharacters, const CORstring& ReplacementString, size_t ReplacementStartIndex = 0, size_t ReplacementNumberOfCharacters = COR_NPOS);
   
   // Prepends the CORstring s to this CORstring
   CORstring& prepend(const CORstring &s) { return insert(0, s.c_str()); }
   
   // Prepends the c-string s to this CORstring
   CORstring& prepend(const char* s) { return insert(0, s); }
   
   // Inserts the CORstring s in to this CORstring at Position
   CORstring& insert(int Position, const CORstring& s) { return insert(Position, s.c_str()); }
   
   // Inserts the c-string s in to this CORstring at Position
   CORstring& insert(int Position, const char* s);

   // Append binary or string data to CORstring. Returns SizeOfBuffer.
   // This was the CORsink interface implementation until we took CORsink out of CORstring.
   size_t write(const void* Buffer, CORuint32 SizeOfBuffer);

   // Sets the size of the CORstring and null terminates it.
   // Will throw an exception if NewSize is greater than or equal to the string capacity.
   // This is intended for use with operating system API calls which write directly to buffers.
   // Not for normal use - Eliot
   void setSize(int NewSize);

private:
   CORstring(const CORstring& s, size_t orig, size_t length);

   // first line in every CORstring ctor
   inline void init() {
       _length = 0;
       _capacity = sizeof(_u.internal);
       _u.internal[0] = 0;
   }

   inline bool isInternalString() const     { return _capacity <= sizeof(_u.internal); }

   inline char*       getStringData()       { return _capacity <= sizeof(_u.internal) ? _u.internal : _u.heap; }
   inline const char* getStringData() const { return _capacity <= sizeof(_u.internal) ? _u.internal : _u.heap; }

   size_t find_index(const char*, size_t start) const;
   size_t find_index(const char, size_t start) const;
   size_t rfind_index(const char*, size_t start) const;

   // Force a new length into string. NO capacity check. For internal use only.
   void overrideLength(int len);

private:
   union U {
       char* heap;         // is string data if _capacity > sizeof(internal)
       char  internal[16]; // is string data if _capacity <= sizeof(internal)
   };

   int _length;   // Length without trailing nil.
   int _capacity; // Storage available to string without reallocation.
   U   _u;        // String data - local or heap allocation depends on _capacity.
};

CORstring operator+(const char*      a, const CORstring& b);
CORstring operator+(const CORstring& a, const char*      b);
CORstring operator+(char             a, const CORstring& b);
CORstring operator+(const CORstring& a, char             b);
CORstring operator+(const CORstring& a, const CORstring& b);

// Comparison operators.
// Note: these comparisons are NOT binary compatible - will stop at first nil byte.
bool operator==(const CORstring& a, const CORstring& b);
bool operator==(const char*      a, const CORstring& b);
bool operator==(const CORstring& a, const char*      b);
bool operator!=(const CORstring& a, const CORstring& b);
bool operator!=(const char*      a, const CORstring& b);
bool operator!=(const CORstring& a, const char*      b);
bool operator<( const CORstring& a, const CORstring& b);
bool operator<( const char*      a, const CORstring& b);
bool operator<( const CORstring& a, const char*      b);
bool operator>( const CORstring& a, const CORstring& b);
bool operator>( const char*      a, const CORstring& b);
bool operator>( const CORstring& a, const char*      b);
bool operator>=(const CORstring& a, const CORstring& b);
bool operator>=(const char*      a, const CORstring& b);
bool operator>=(const CORstring& a, const char*      b);
bool operator<=(const CORstring& a, const CORstring& b);
bool operator<=(const char*      a, const CORstring& b);
bool operator<=(const CORstring& a, const char*      b);

// case conversion without altering original CORstring
CORstring CORlowerCase(const CORstring& String);
CORstring CORupperCase(const CORstring& String);

// convert signed and unsigned integers to strings
CORstring CORintToString(int);
CORstring CORint32ToString(int);
CORstring CORuint32ToString(CORuint32);
CORstring CORint64ToString(CORint64);
CORstring CORuint64ToString(CORuint64);

CORstring CORstripWhiteSpace(const CORstring& String, bool StripLeading = true, bool StripTrailing = true);
CORstring CORremoveAllWhiteSpace(const CORstring& String);
CORstring CORreplaceAllWhiteSpace(const CORstring& String, const char Replacement);
int CORreplaceAllWhiteSpaceCount(CORstring& String, const char Replacement);
CORstring CORstripChars(const CORstring& String, const CORstring& CharsToKill);
CORstring CORtoAscii(const CORstring& String, char Marker = 'x');

inline bool CORisspace(int c) { return c == 32 || (c >= 9 && c <= 13); } // see #22552
inline bool CORisdigit(int c) { return c >= 48 && c <= 57; }

bool CORstringHasPrefix(const CORstring& String, const CORstring& Prefix);
CORstring CORstringCutPrefix(const CORstring& String, const CORstring& Prefix);

inline static bool COR_is_COR_NPOS(     int pos) { return COR_NPOS == (size_t)(unsigned)pos; }
inline static bool COR_is_COR_NPOS(unsigned pos) { return COR_NPOS == (size_t)(unsigned)pos; }

bool CORstringContains(const CORstring& StringToSearch, const CORstring& Pattern);
bool CORstringContains(const char* String, const char* Pattern);

