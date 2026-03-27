//---------------------------------------------------------------------------
// Copyright (C) 2026 Eliot Muir.  All rights reserved.
//
// Module:  CORstring
//---------------------------------------------------------------------------

#include <COR/CORwindows.h>
#include <COR/CORstring.h>
#include <COR/CORerror.h>
#include <COR/CORlog.h>
COR_LOG_MODULE;

#ifndef _WIN32
#include <ctype.h>
#endif

#include <string.h>
#include <stdio.h>

CORstring::~CORstring()
{
   if (!isInternalString()) {
      delete [] _u.heap;
   }
}

CORstring::CORstring()
{
   init();
}

CORstring::CORstring(const CORstring& that)
{
   init();
   if (that.isInternalString()) {
       // This is an internal string - perform a fast blind
       // data copy since there are no pointers to deal with.
       ::memcpy((char*)this, (char*)&that, sizeof(*this));
   } else {
       const char* s = that.getStringData();
       const int len = that._length;
       if (len > 0) {
           setCapacity(len + 1);   // TODO is this correct since capacity already adds 1?
           _length = len;
           char* data = getStringData();
           ::memcpy(data, s, len); // no risk of copy overlap
           data[len] = 0;
       }
   }
}

// Private constructor as it is often used incorrectly.
// Leave this with size_t arguments due to subtle backwards compatibiity quirks.
// Note that length can be COR_NPOS.
CORstring::CORstring(const CORstring& s, size_t orig, size_t length)
{
   init();
   if (s.size() == 0) {
      return;
   }
   if ((orig == 0) && (length == COR_NPOS || length >= s.size())) {
      *this = s;
   }
   else if (orig < s.size()) {
      // #22935 length can be COR_NPOS and expression can overflow a 32 bit size_t
      if ((length == COR_NPOS) || (((unsigned long long)orig + length) > s.size())) {
         length = s.size() - orig;
      }
      append(s.c_str() + orig, length);
   }
}

CORstring::CORstring(int InitialSize, char InitializationCharacter)
{
   init();
   setCapacity(InitialSize);
   char* Buffer = get_buffer();
   ::memset(Buffer, InitializationCharacter, InitialSize);
   Buffer[InitialSize] = 0;
   overrideLength(InitialSize);
}

CORstring::CORstring(const char* s)
{
   init();
   if (s && s[0]) {
       int len = ::strlen(s);
       setCapacity(len + 1);
       _length = len; // this assignment must follow setCapacity
       // This is faster than strcpy() when we know the length already.
       ::memcpy(getStringData(), s, len + 1); // +1 includes trailing nil
   }
}

CORstring::CORstring(const char* s, int len)
{
   init();
   if (s) {
       if (COR_is_COR_NPOS(len)) {
          // COR_NPOS nonsense is necessary for backwards compatibility with CORstring.
          len = ::strlen(s);
       }
       if (len > 0) {
          setCapacity(len + 1);
          _length = len;
          char* data = getStringData();
          ::memcpy(data, s, len); // These will not overlap.
          data[len] = 0;
       }
   }
}

CORstring::CORstring(const CORtextLiteral& stringLiteral)
{
   init();
   if (stringLiteral.m_Length > 0) {
      setCapacity(stringLiteral.m_Length + 1);
      _length = stringLiteral.m_Length;
      char* data = getStringData();
      ::memcpy(data, stringLiteral.m_String, stringLiteral.m_Length); // These will not overlap.
      data[stringLiteral.m_Length] = 0;
   }
}

CORstring& CORstring::operator=(const CORstring& that)
{
   // Note - we cannot do this:   { *this = that.c_str(); return *this; }
   // Must consider case of embedded nulls.
   if (this != &that) {
      const char* thatString = that.getStringData();
      const int   thatLength = that._length;
      _length = 0; // this line is necessary - avoids unnecessary data copying of old string
      setCapacity(thatLength);
      _length = thatLength;
      char* thisString = getStringData();
      ::memcpy(thisString, thatString, thatLength + 1); // +1 includes trailing nil
   }
   return *this;
}

CORstring& CORstring::operator=(const char* s)
{
   if (0 == s || 0 == s[0]) {
      // Assigning a null pointer or "" to a string
      // results in a zero-length string.
      // Note: capacity remains the same.
      clear();
   } else {
      const int len = ::strlen(s);
      _length = 0; // avoid unnecessary data copying of old string
      setCapacity(len + 1);
      _length = len;
      ::memmove(getStringData(), s, len + 1); // Might overlap. +1 for nil.
   }
   return *this;
}

void CORstring::setCapacity(int newCapacity)
{
   newCapacity += 1; // add 1 to capacity for the nil terminator
   if (newCapacity > _capacity) {
       {
           int proposedCapacity = _capacity * 2;
           if (newCapacity < proposedCapacity) {
               newCapacity = proposedCapacity;
           }
       }
       char* newMemory = new char[newCapacity];
       if (_length > 0) {
           // perform reallocation and copying of data to new buffer
           ::memcpy(newMemory, getStringData(), _length);
       }
       if (getStringData() != _u.internal) { delete [] _u.heap; }
       _u.heap = newMemory;
       _u.heap[_length] = 0;
       _capacity = newCapacity;
   }
}

void CORstring::overrideLength(int len)
{
   if (len >= 0 && len < capacity()) {
      _length = len;
   }
}

void CORstring::clear()
{
   getStringData()[0] = 0;
   _length = 0;
}

void CORstring::zero()
{
   if (getStringData() != _u.internal) { delete [] _u.heap; }
   init();
}

//
// Discard n bytes from the beginning of the string buffer.
// Capacity remains the same. CORstring::size() is changed accordingly.
//
void CORstring::shift(int n) {
   CORASSERT(n >= 0);
   CORASSERT(n <= _length);
   char* p = getStringData();
   const int NewLength = _length - n;
   ::memmove(p, p+n, NewLength);
   _length = NewLength;
   p[_length] = 0;
}

//
// Shrink heap use to CapacityHint if possible without altering the string.
// Note: Do not use old CORstring::data() and CORstring::c_str() values after this call.
//
void CORstring::shrink(int CapacityHint) {
   if (CapacityHint < (_length + 1)) {
      // new capacity must not be too small
      CapacityHint = _length + 1;
   }
   if (CapacityHint < 32) {
      // Have a minimum capacity of 32 so we don't have to mess with internal string logic.
      CapacityHint = 32;
   }
   if (CapacityHint < _capacity) {
       CORASSERT(CapacityHint > sizeof(_u.internal));
       char* NewMemory = new char[CapacityHint];
       ::memcpy(NewMemory, getStringData(), _length); // never overlaps
       if (getStringData() != _u.internal) { delete [] _u.heap; }
       _u.heap = NewMemory;
       _u.heap[_length] = 0;
       _capacity = CapacityHint;
       CORASSERT(_capacity > _length);
   }
}

void CORstring::swap(CORstring* that) {
   // If we swap with ourselves, memcpy() might clobber us.  We could use
   // memmove() to be safe, but we may as well just do nothing.
   if (this != that) {
      // if sliding is good enough for LEGvector...
      char Temp[sizeof(CORstring)];
      memcpy(       Temp, (char*)that, sizeof(CORstring));
      memcpy((char*)that, (char*)this, sizeof(CORstring));
      memcpy((char*)this,        Temp, sizeof(CORstring));
   }
}

CORstring& CORstring::append(const char* s) {
   if (s && s[0]) {
       int len = ::strlen(s);
       return append(s, len);
   }
   return *this;
}

CORstring& CORstring::append(int count, char character)
{
   setCapacity(size()+count);
   char* buff = get_buffer();
   ::memset(&buff[size()], character, count);
   buff[size()+count] = 0;
   overrideLength(size()+count);
   return *this;
}

CORstring& CORstring::append(const CORstring& that)
{
   return append(that.c_str(), that.size());
}

// allow appending binary data with embedded null characters
CORstring& CORstring::append(const char* s, int len)
{
   if (COR_is_COR_NPOS(len)) {
       return append(s);
   }
   if (s && len > 0) {
       char* thisData = getStringData();
       if (s >= thisData && s < thisData+_length) {
          // the string to append is within this string
          // so we must make a new string to append to.
          return *this = CORstring(*this).append(s, len);
       }
       else {
          const int newLength = _length + len;
          setCapacity(newLength + 1);
          char* data = getStringData();
          ::memcpy(data + _length, s, len);
          data[newLength] = 0; // nil terminate the string
          _length = newLength;
       }
   }
   return *this;
}

void CORstring::set(const char* s, int len)
{
   clear();
   append(s, len);
}

void CORstring::splitAtIndex(CORstring& Out1, CORstring& Out2, int SplitIndex) const
{
   if (SplitIndex > size())
   {
      Out1 = *this;
      Out2 = "";
   }
   else
   {
      Out1 = substr(0,SplitIndex);
      Out2 = substr(SplitIndex);
   }
}

size_t CORstring::find(const char* Pattern) const
{
   return find(Pattern, 0);
}

size_t CORstring::find(const CORstring& Pattern) const
{
   return find(Pattern.c_str(), 0);
}

size_t CORstring::find(const char* Pattern, size_t StartIndex) const
{
   if (Pattern == 0 || Pattern[0] == 0) {
      return COR_NPOS;
   }

   const char* pStart = c_str();
   const char* pStringStart = pStart;
   const char* pFound = NULL;

   pStart += StartIndex;

   if (!(pFound = strstr(pStart, Pattern))) {
      return COR_NPOS;
   } else {
      return pFound-pStringStart;
   }
}

size_t CORstring::find(const CORstring& Pattern, size_t StartIndex) const
{
   return CORstring::find(Pattern.c_str(), StartIndex);
}

size_t CORstring::rfind(const CORstring& Pattern, size_t StartIndex) const {
   if (Pattern.is_null()) { return COR_NPOS; }
   size_t PatternLength = Pattern.size();
   int Position = StartIndex;

   if ((size_t)Position >= size()) {
      Position = size() - 1;
   }

   const char* current = get_buffer();
   const char* cstring = current + Position;

   while (Position >= 0) {
      if (strlen(cstring) >= PatternLength) { // TODO: optimize after writing unit tests.
         for (size_t i = 0; i < PatternLength; i++) {
            if (cstring[i] != Pattern[i]) {
               break;
            } else if (i == PatternLength - 1) {
               return Position;
            }
         }
      }
      Position--;
      cstring = current + Position;
   }
   return COR_NPOS;          // Not found.
}

size_t CORstring::rfind(const CORstring& Pattern) const
{
   return rfind(Pattern, size());
}

CORstring CORstring::strip(CORstring::StripType Type, char StripCharacter) const
{
   if (size() == 0) {
      return CORstring();  // null string
   }
   int StartIndex = 0;        // index of first character.
   int EndIndex = size() - 1; // index of last character. #9922: must be signed
   const char* Direct = c_str();

   // check for start and special case of resulting empty string
   if (Type & Leading) {
      for(; StartIndex <= EndIndex; StartIndex++) {
         if (Direct[StartIndex] != StripCharacter) {
            goto nonNull;
         }
      }
      return CORstring(); // Null string
   }

nonNull:
   if (Type & Trailing) {
      for(; EndIndex >= StartIndex; EndIndex--) {
         // #9922: EndIndex would be -1 here if EndIndex was unsigned CORindex
         if ( Direct[EndIndex] != StripCharacter ) {
            break;
         }
      }
   }
   int CharacterCount = EndIndex - StartIndex + 1;
   if (CharacterCount < 0) {
      CharacterCount = 0;
   }
   return CORstring(c_str() + StartIndex, CharacterCount);
}

bool CORstring::split(CORstring& Out1, CORstring& Out2, const char* Token) const {
   const char* pToken = c_str();
   const int TokenSize = strlen(Token);
   pToken = strstr(pToken,Token);
   if (!pToken) {
      Out1 = *this;
      Out2 = "";
      return false;
   } else {
      const int FoundIndex = pToken-c_str();
      Out1 = substr(0,FoundIndex);
      Out2 = substr(FoundIndex+TokenSize);
      return true;
   }
}

size_t CORstring::write(const void* inBuff, unsigned length)
{
   append((const char*)inBuff, length);
   return length;
}

bool CORstring::rsplit(CORstring& Out1, CORstring& Out2, const char* Token) const {
   const char* pToken = c_str();
   const char* pPreviousToken = 0;
   int TokenSize = strlen(Token);
   while (Token && Token[0] && (pToken = strstr(pToken,Token))) {
      pPreviousToken = pToken;
      if ((pToken+TokenSize) <= (c_str()+size()))
      {
         pToken += TokenSize;
      }
      else
      {
         Out1 = "";
         Out2 = *this;
         return false;
      }
   }
   if (!pPreviousToken)
   {
      Out1 = "";
      Out2 = *this;
      return false;
   }
   else
   {
      const int FoundIndex = pPreviousToken-c_str();
      Out1 = substr(0, FoundIndex);
      Out2 = substr(FoundIndex+TokenSize);
      return true;
   }
}

bool CORstring::isWhitespace() const
{
   const char* pData = c_str();
   int CharIndex = size();
   while (CharIndex > 0)
   {
      CharIndex--;
      // if the character isn't a space, newline, carridge return or tab then it isn't white space.
      if (pData[CharIndex]  != ' ' &&
          pData[CharIndex] != '\n' &&
          pData[CharIndex] != '\r' &&
          pData[CharIndex] != '\t')
      {
         // we jump out since one non white space character means we haven't got whitespace.
         return false;
      }
   }
   return true;
}

size_t CORstring::find(const char Character, size_t StartIndex) const
{
   return find_index(Character, StartIndex);
}

size_t CORstring::find_index(const char Character, size_t StartIndex) const
{
   if (StartIndex >= size())
   {
       return COR_NPOS;
   }

   const char* pStart = c_str();
   const char* pStringStart = pStart;
   const char* pFound = NULL;

   pStart += StartIndex;

   if (!(pFound = strchr(pStart, Character)))
   {
      return COR_NPOS;
   }
   else
   {
      return pFound-pStringStart;
   }
}

size_t CORstring::find_index(const char* Pattern, size_t StartIndex) const
{
   const char* pStart = c_str();
   const char* pStringStart = pStart;
   const char* pFound = NULL;

   pStart += StartIndex;

   if (!(pFound = strstr(pStart, Pattern)))
   {
      return COR_NPOS;
   }
   else
   {
      return pFound-pStringStart;
   }
}

CORstring& CORstring::insert(int Position, const char* Source)
{
   if (Position >= 0 && Position <= size() && Source) {
      CORstring TemporaryString(*this, 0, Position);
      TemporaryString.append(Source);
      TemporaryString.append(c_str() + Position);
      *this = TemporaryString;
   }
   return *this;
}

CORstring& CORstring::replace(size_t StartIndex, size_t CountOfCharacters, const CORstring& Replacement, size_t ReplacementStartIndex, size_t ReplacementCountOfCharacters)
{
   if (StartIndex <= size())
   {
      // get the first section
      CORstring TemporaryString(*this, 0, StartIndex);

      // get the replace section
      if (ReplacementStartIndex < Replacement.size())
      {
         TemporaryString.append(Replacement.c_str() + ReplacementStartIndex, ReplacementCountOfCharacters);
      }

      // if anything left over then add that
      if ((CountOfCharacters != COR_NPOS) &&
          (CountOfCharacters < (size() - StartIndex)))
      {
         TemporaryString.append(c_str() + StartIndex + CountOfCharacters);
      }

      *this = TemporaryString;
   }
   return *this;
}

CORstring& CORstring::remove(size_t StartIndex, size_t CountOfCharacters)
{
   if (StartIndex <= size())
   {
      // first section
      CORstring TemporaryString(*this, 0, StartIndex);

      // remainder
      if ((CountOfCharacters != COR_NPOS) &&
          (CountOfCharacters < (size() - StartIndex)))
      {
         TemporaryString.append(c_str() + StartIndex + CountOfCharacters);
      }

      *this = TemporaryString;
   }
   return *this;
}

CORstring CORstring::substr(int StartIndex, int CountOfCharacters) const
{
   return CORstring(*this, StartIndex, (size_t)(unsigned)CountOfCharacters);
}

CORstring CORstring::substr(int StartIndex) const
{
   return CORstring(*this, StartIndex, COR_NPOS);
}

void CORstring::stripAll(char StripCharacter)
{
   char* s = get_buffer();
   int r = 0; // stripped index
   for (size_t i=0; i < _length && s[i]; ++i) {
      if (s[i] != StripCharacter) {
         s[r++] = s[i];
      }
   }
   s[r] = 0;
   _length = r;
}

CORstring& CORstring::assign(int Length, char FillChar)
{
   if (Length > 0) {
      setCapacity(Length);
      char* Buffer = get_buffer();
      ::memset(Buffer, FillChar, Length);
      Buffer[Length] = 0;
      overrideLength(Length);
   }
   else {
      zero();
   }
   return *this;
}

CORstring& CORstring::toLowerCase()
{
   const int End = size();
   if (End == 0) {
      return *this;  // empty string
   }
   char* pBuffer = get_buffer();
   for (int i = 0; i < End; i++) {
      pBuffer[i] = tolower(pBuffer[i]);
   }
   return *this;
}

CORstring& CORstring::toUpperCase()
{
   const int End = size();
   if (End == 0) {
      return *this;  // empty string
   }
   char* pBuffer = get_buffer();
   for (int i = 0; i < End; i++) {
      pBuffer[i] = toupper(pBuffer[i]);
   }
   return *this;
}

size_t CORstring::replace(const CORstring& Substring, const CORstring& ReplacementString)
{
   // Pass one:
   //    This method will loop through this string and count the number of
   //    instances of the substring, and thus the number of replacements
   //    in order.
   //
   // The difference between the two strings will be calculated an a buffer of
   // size equal to the original + difference will be created.  This is the
   // the one and only [re]size that takes place.
   //
   // Pass two:
   //    The method will now loop through the buffer and copy character by
   //    character from the original buffer.  In the case that a pattern match
   //    is found, the replace pattern is copied instead, and the the matched
   //    pattern will be skipped from the original string.

   size_t SizeOfSubstring   = Substring.size();
   size_t SizeOfReplacement = ReplacementString.size();
   size_t SizeOfThis        = size();
   size_t CountOfReplacement = 0;

   // Pass one:
   size_t ThisIndex = 0;
   size_t Findex = 0;

   while (Findex != COR_NPOS) {
      Findex = find(Substring, ThisIndex);
      ThisIndex = Findex + SizeOfSubstring;
      CountOfReplacement++;
   }

   CountOfReplacement--;

   // Intermediate calculations.
   size_t SizeOfNewString = SizeOfThis + CountOfReplacement * (SizeOfReplacement - SizeOfSubstring);
   CORstring NewString(SizeOfNewString, '\0');

   // Pass two:
   const char* ThisBuffer = this->get_buffer();
   const char* ReplaceBuffer = ReplacementString.c_str();
   char* NewBuffer = NewString.get_buffer();

   size_t NewIndex = 0;
   ThisIndex = 0;
   for(size_t ReplacingIterator = 0; ReplacingIterator < CountOfReplacement; ReplacingIterator++) {
      Findex = find(Substring, ThisIndex);

      while (ThisIndex < Findex) {
         *(NewBuffer + NewIndex) = *(ThisBuffer + ThisIndex);
         NewIndex++;
         ThisIndex++;
      }

      size_t ReplaceIndex = 0;
      while (ReplaceIndex < SizeOfReplacement) {
         *(NewBuffer + NewIndex) = *(ReplaceBuffer + ReplaceIndex);
         NewIndex++;
         ReplaceIndex++;
      }
      ThisIndex = ThisIndex + SizeOfSubstring;
   }
   while (NewIndex < SizeOfNewString) {
      *(NewBuffer + NewIndex) = *(ThisBuffer + ThisIndex);
      NewIndex++;
      ThisIndex++;
   }

   *this = NewString;
   return CountOfReplacement;
}

void CORstring::setSize(int NewSize)
{
   // don't use this method unless you know what you are doing...
   CORASSERT(NewSize < _capacity);
   get_buffer()[NewSize] = '\0';
   overrideLength(NewSize);
}

char& CORstring::operator[](int CharIndex)
{
   CORASSERT(CharIndex >= 0 && CharIndex < size());
   // using C style cast for compatibility with older compilers
   return (char&)((c_str())[CharIndex]);
}

char CORstring::operator[](int pos) const
{
   CORASSERT(pos >= 0 && pos < _length);
   return c_str()[pos];
}

// Some Handy Conversion Routines
CORstring CORintToString(int Value) {
   char Result[32]; // Room for a 64-bit int.
#ifdef _WIN32
   return _ltoa((long)Value, Result, 10);
#else
   snprintf(Result, 32, "%d", Value);
   return Result;
#endif
}

CORstring CORint32ToString(CORint32 Value)
{
   char Result[32];
#ifdef _WIN32
   return _ltoa((long)Value, Result, 10);
#else
   snprintf(Result, 32, "%ld", (long)Value);
   return Result;
#endif
}

CORstring CORuint32ToString(CORuint32 Value)
{
   char Result[32];
#ifdef _WIN32
   return _ultoa((unsigned long)Value, Result, 10);
#else
   snprintf(Result, 32, "%lu", (unsigned long)Value);
   return Result;
#endif
}

CORstring CORint64ToString(CORint64 Value)
{
   char Result[32];
#ifdef _WIN32
   return _i64toa(Value, Result, 10);
#else
   snprintf(Result, 32, "%lld", (long long)Value);
   return Result;
#endif
}

CORstring CORuint64ToString(CORuint64 Value)
{
   char Result[32];
#ifdef _WIN32
   return _ui64toa(Value, Result, 10);
#else
   snprintf(Result, 32, "%llu", (unsigned long long)Value);
   return Result;
#endif
}

CORstring CORstripWhiteSpace(const CORstring& String, bool StripLeading, bool StripTrailing) {
   const char* pString = String.c_str();
   int Size = String.size();
   if (StripLeading) {
      while (Size && isspace(*pString)) {
         Size--;
         pString++;
      }
   }
   if (StripTrailing) {
      while (Size && isspace(pString[Size-1])) {
         Size--;
      }
   }
   return CORstring(pString, Size);
}

static const CORstring COR_ALL_THE_ASCII_WHITESPACE = " \a\b\f\n\r\t\v";

CORstring CORremoveAllWhiteSpace(const CORstring& String) {
   COR_FUNCTION(CORremoveAllWhiteSpace);
   const int MaxSize = String.size();
   CORstring NewString;
   NewString.setCapacity(String.size());
   int NewLength = 0;
   char* Buffer = NewString.get_buffer();
   for (int i = 0; i < MaxSize; i++) {
      if (COR_ALL_THE_ASCII_WHITESPACE.find(String[i]) == COR_NPOS) {
         Buffer[NewLength++] = String[i];
      }
   }
   NewString.setSize(NewLength);
   return NewString;
}

CORstring CORreplaceAllWhiteSpace(const CORstring& String, const char Replacement) {
   COR_FUNCTION(CORreplaceAllWhiteSpace);
   const int MaxSize = String.size();
   int NewLength = 0;
   CORstring NewString;
   NewString.setCapacity(String.size());
   bool OnASpace = false;
   char* Buffer = NewString.get_buffer();
   for (int i = 0; i < MaxSize; i++) {
      if (COR_ALL_THE_ASCII_WHITESPACE.find(String[i]) != COR_NPOS) {
         if (! OnASpace) {
            Buffer[NewLength++] = Replacement;
            OnASpace = true;
         }
      } else{
         Buffer[NewLength++] = String[i];
         OnASpace = false;
      }
   }
   NewString.setSize(NewLength);
   return NewString;
}

int CORreplaceAllWhiteSpaceCount(CORstring& String, const char Replacement) {
   COR_FUNCTION(CORreplaceAllWhiteSpace);
   int ReplacementCount = 0;
   const int MaxSize = String.size();
   int NewLength = 0;
   CORstring NewString;
   NewString.setCapacity(String.size());
   bool OnASpace = false;
   char* Buffer = NewString.get_buffer();
   for (int i = 0; i < MaxSize; i++) {
      if (COR_ALL_THE_ASCII_WHITESPACE.find(String[i]) != COR_NPOS) {
         if (!OnASpace) {
            Buffer[NewLength++] = Replacement;
            OnASpace = true;
            ReplacementCount++;
         }
      } else{
         Buffer[NewLength++] = String[i];
         OnASpace = false;
      }
   }
   NewString.setSize(NewLength);
   String = NewString;
   return ReplacementCount;
}

CORstring CORstripChars(const CORstring& String, const CORstring& CharsToKill) {
   COR_FUNCTION(CORstripChars);
   COR_VAR2(String, CharsToKill);
   CORstring Clean;
   int Max = String.size();
   Clean.setCapacity(Max);
   for (int i = 0; i < Max; i++) {
      if (CharsToKill.find(String[i]) == COR_NPOS) {
         Clean.append(1, String[i]);
      }
   }
   COR_VAR(Clean);
   return Clean;
}

CORstring CORtoAscii(const CORstring& String, char Marker) {
   COR_FUNCTION(CORtoAscii);
   CORstring Ascii;
   CORstring Pattern(1, Marker);
   if (Marker == '%') {
      // We are about to snprintf, so we need to escape a percent sign
      Pattern.append(1, Marker);
   }
   Pattern.append("%02X");
   int Max = String.size();
   for (int i = 0; i < Max; i++) {
      unsigned char Ch = String[i];
      COR_VAR2(i, CORstring(1, Ch));
      if (0x20 <= Ch && Ch < 0x7F) {
         Ascii.append(1, Ch);
      } else {
         CORstring Tank;
         Tank.assign(3, '\0');
         ::snprintf(Tank.get_buffer(), Tank.capacity(), Pattern.c_str(), Ch);
         Ascii.append(Tank);
      }
   }
   COR_VAR(String);
   COR_VAR(Ascii);
   return Ascii;
}

CORstring CORlowerCase(const CORstring& String) {
   CORstring Result(String);
   Result.toLowerCase();
   return Result;
};

CORstring CORupperCase(const CORstring& String) {
   CORstring Result(String);
   Result.toUpperCase();
   return Result;
};

void CORstring::replace(char FromChar, char ToChar)
{
   char* pBuffer = get_buffer();
   const int End = size();
   for (int i = 0; i < End; i++) {
      if (pBuffer[i] == FromChar) {
         pBuffer[i] = ToChar;
      }
   }
}

CORstring::CORstring(const wchar_t* WideCharacterString){
   init();
   if( WideCharacterString == 0 ){ //null string
      return;
   }
   size_t MultiByteLength = wcstombs( 0, WideCharacterString, 0 );
   bool UsingUTF8 = false;

   // if our length is -1 then wcstombs has returned an error
   // try using UTF-8 on windows
#ifdef _WIN32
   if (MultiByteLength == -1){
      MultiByteLength = WideCharToMultiByte(CP_UTF8, 0, WideCharacterString, -1, 0, 0, 0, 0);
      UsingUTF8 = true;
   }
#endif

   MultiByteLength += 2; //null char length
   setCapacity(MultiByteLength + 1);
   if (!UsingUTF8)
   {
      //XXX - VERIFY - untested
      int newCount = wcstombs( get_buffer(), WideCharacterString, MultiByteLength );
      CORASSERT(newCount < capacity());
      overrideLength(newCount); //XXX VERIFY
   }
#ifdef _WIN32
   else
   {
      WideCharToMultiByte(CP_UTF8, 0, WideCharacterString, -1, get_buffer(), MultiByteLength, 0, 0);
   }
#endif
}

//TODO need to test this method
CORstring& CORstring::operator=(const wchar_t* WideCharacterString){
   if (WideCharacterString != NULL){
      size_t MultiByteLength = wcstombs( 0, WideCharacterString, 0 );
      if (MultiByteLength == -1){
         COR_ERROR_STREAM("Unable to convert wide char string to multibyte string, locale may be incorrect.", 0);
      }
      assign(MultiByteLength, 0);
      MultiByteLength = wcstombs( get_buffer(), WideCharacterString, MultiByteLength );
      if (MultiByteLength == -1){
         COR_ERROR_STREAM("Unable to convert wide char string to multibyte string, locale may be incorrect.", 0);
      }
   } else {
      clear();
   }
   return *this;
}

bool CORstringHasPrefix(const CORstring& String, const CORstring& Prefix)
{
   return String.size() >= Prefix.size() && String.substr(0, Prefix.size()) == Prefix;
}

CORstring CORstringCutPrefix(const CORstring& String, const CORstring& Prefix)
{
   CORPRECONDITION(String.size() >= Prefix.size() && String.substr(0, Prefix.size()) == Prefix);
   return String.substr(Prefix.size());
}

size_t CORstring::find_last_of(const CORstring& s, size_t _pos) const
{
   size_t len = size();
   size_t pos(_pos);
   if( pos == 0 || len == 0 )
      return COR_NPOS;
   if( pos > len )
      pos = len;
   else
      pos++;
   const char *target = s.c_str();
   const char *text = c_str();
   while (--pos > 0 )
   {
      if (strchr(target, text[pos]) != 0 )
         return pos;
   }
   return COR_NPOS;
}

bool CORstring::find(int* FoundPosition, const char Character, size_t Position) const {
   size_t rc = find(Character, Position);
   *FoundPosition = (unsigned)rc;
   return rc != COR_NPOS;
}

bool CORstring::find(int* FoundPosition, const char* Pattern) const {
   size_t rc = find(Pattern);
   *FoundPosition = (unsigned)rc;
   return rc != COR_NPOS;
}

bool CORstring::find(int* FoundPosition, const CORstring& Pattern) const {
   size_t rc = find(Pattern);
   *FoundPosition = (unsigned)rc;
   return rc != COR_NPOS;
}

bool CORstring::find(int* FoundPosition, const CORstring& Pattern, size_t Position) const {
   size_t rc = find(Pattern, Position);
   *FoundPosition = (unsigned)rc;
   return rc != COR_NPOS;
}

bool CORstring::find(int* FoundPosition, const char* Pattern, size_t Position) const {
   size_t rc = find(Pattern, Position);
   *FoundPosition = (unsigned)rc;
   return rc != COR_NPOS;
}

bool CORstring::rfind(int* FoundPosition, const CORstring& Pattern) const {
   size_t rc = rfind(Pattern);
   *FoundPosition = (unsigned)rc;
   return rc != COR_NPOS;
}

bool CORstring::rfind(int* FoundPosition, const CORstring& Pattern, size_t Position) const {
   size_t rc = rfind(Pattern, Position);
   *FoundPosition = (unsigned)rc;
   return rc != COR_NPOS;
}

bool CORstring::find_last_of(int* FoundPosition, const CORstring& Characters, size_t Position) const {
   size_t rc = find_last_of(Characters, Position);
   *FoundPosition = (unsigned)rc;
   return rc != COR_NPOS;
}

// Case insensitive string compare similar to stricmp/strcasecmp.
int CORstring::icompare(const char* s1, const char* s2)
{
   const unsigned char* us1 = (const unsigned char*)s1;
   const unsigned char* us2 = (const unsigned char*)s2;
   int i1, i2; // must be int
   for (; (i1 = toupper(*us1)) == (i2 = toupper(*us2)); ++us1, ++us2) {
      if (i1 == 0) {
         return 0;
      }
   }
   return i1 - i2;
}

int CORstring::icompare(const CORstring& s) const { return icompare(c_str(), s.c_str()); }
int CORstring::icompare(const char*      s) const { return icompare(getStringData(), s); }

bool CORstring::equalsIgnoreCase(const CORstring& s) const { return 0 == icompare(s.c_str()); }
bool CORstring::equalsIgnoreCase(const char*      s) const { return 0 == icompare(s); }

bool CORstring::equals(const CORstring& s) const { return 0 == compare(s.c_str()); }
bool CORstring::equals(const char*      s) const { return 0 == compare(s); }

CORstring operator+(const char*      a, const CORstring& b) { return CORstring(a).append(b);   }
CORstring operator+(const CORstring& a, const char*      b) { return CORstring(a).append(b);   }
CORstring operator+(char             a, const CORstring& b) { return CORstring(1,a).append(b); }
CORstring operator+(const CORstring& a, char             b) { return CORstring(a).append(1,b); }
CORstring operator+(const CORstring& a, const CORstring& b) { return CORstring(a).append(b);   }

bool operator==(const CORstring& a, const CORstring& b) { return CORstring::compare(a.c_str(), b.c_str()) == 0; }
bool operator==(const char*      a, const CORstring& b) { return CORstring::compare(a,         b.c_str()) == 0; }
bool operator==(const CORstring& a, const char*      b) { return CORstring::compare(a.c_str(), b)         == 0; }

bool operator!=(const CORstring& a, const CORstring& b) { return CORstring::compare(a.c_str(), b.c_str()) != 0; }
bool operator!=(const char*      a, const CORstring& b) { return CORstring::compare(a,         b.c_str()) != 0; }
bool operator!=(const CORstring& a, const char*      b) { return CORstring::compare(a.c_str(), b)         != 0; }

bool operator<( const CORstring& a, const CORstring& b) { return CORstring::compare(a.c_str(), b.c_str()) < 0; }
bool operator<( const char*      a, const CORstring& b) { return CORstring::compare(a,         b.c_str()) < 0; }
bool operator<( const CORstring& a, const char*      b) { return CORstring::compare(a.c_str(), b)         < 0; }

bool operator>( const CORstring& a, const CORstring& b) { return CORstring::compare(a.c_str(), b.c_str()) > 0; }
bool operator>( const char*      a, const CORstring& b) { return CORstring::compare(a,         b.c_str()) > 0; }
bool operator>( const CORstring& a, const char*      b) { return CORstring::compare(a.c_str(), b)         > 0; }

bool operator>=(const CORstring& a, const CORstring& b) { return CORstring::compare(a.c_str(), b.c_str()) >= 0; }
bool operator>=(const char*      a, const CORstring& b) { return CORstring::compare(a,         b.c_str()) >= 0; }
bool operator>=(const CORstring& a, const char*      b) { return CORstring::compare(a.c_str(), b)         >= 0; }

bool operator<=(const CORstring& a, const CORstring& b) { return CORstring::compare(a.c_str(), b.c_str()) <= 0; }
bool operator<=(const char*      a, const CORstring& b) { return CORstring::compare(a,         b.c_str()) <= 0; }
bool operator<=(const CORstring& a, const char*      b) { return CORstring::compare(a.c_str(), b)         <= 0; }

const char* CORstring::c_str() const      { return getStringData(); }
const char* CORstring::data() const       { return getStringData(); }
const char* CORstring::get_buffer() const { return getStringData(); }
char*       CORstring::get_buffer()       { return getStringData(); }

static void CORcomputeLPSArray(const char* pPattern, size_t M, int* pLPS) {
   COR_FUNCTION(computeLPSArray);
   int len = 0;
   pLPS[0] = 0;
   int i = 1;
   while (i < M) {
      if (pPattern[i] == pPattern[len]) {
         len++;
         pLPS[i] = len;
         i++;
      } else {
         if (len != 0) { len = pLPS[len - 1]; }
         else {
            pLPS[i] = 0;
            i++;
         }
      }
   }
}

static bool CORkmpSearch(const char* pString, const char* pPattern) {
   COR_FUNCTION(CORkmpSearch);
   size_t M = strlen(pPattern);
   size_t N = strlen(pString);
   int* pLPS = new int[M];
   CORcomputeLPSArray(pPattern, M, pLPS);
   int i = 0;
   int j = 0;
   while (i < N) {
      if (pPattern[j] == pString[i]) {
         j++;
         i++;
      }
      if (j == M) {
         delete[] pLPS; 
         return true; 
      }
      else if (i < N && pPattern[j] != pString[i]) {
         if (j != 0) { j = pLPS[j - 1]; }
         else { i = i + 1; }
      }
   }
   delete[] pLPS;
   return false;
}

bool CORstringContains(const CORstring& StringToSearch, const CORstring& Pattern) {
   COR_FUNCTION(CORstringContains);
   if (StringToSearch.is_null()) return false;
   const char* pSearchText = StringToSearch.c_str();
   const char* pPattern    = Pattern.c_str();
   return CORkmpSearch(pSearchText, pPattern);
}

bool CORstringContains(const char* String, const char* Pattern) {
   COR_FUNCTION(CORstringContains);
   return CORkmpSearch(String, Pattern);
}
