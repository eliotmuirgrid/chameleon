//-----------------------------------------------------------------------------
// Copyright (C) 2026 Eliot Muir.  All rights reserved.
//
// Module:  CORvar
//
// Author:  Andrew Vajoczki
//
// Description:
//
// A variant object that can hold a number, string, vector or map.
//-----------------------------------------------------------------------------

#include <COR/CORvar.h>
#include <COR/CORvarJson.h>
#include <COR/CORlog.h>
COR_LOG_MODULE;

#include <stdio.h>

#include <string.h>

static void CORvarAdjustRangeForByte2(const unsigned char LeadByte, unsigned int* pLower, unsigned int* pUpper) {

  /* Syntax of valid UTF-8 Byte Sequences found at https://tools.ietf.org/html/rfc3629#section-4
   * which is why this range shifting must be done.
   *
   * UTF8-octets = *( UTF8-char )
   * UTF8-char   = UTF8-1 / UTF8-2 / UTF8-3 / UTF8-4
   * UTF8-1      = %x00-7F
   * UTF8-2      = %xC2-DF UTF8-tail
   * UTF8-3      = %xE0 %xA0-BF UTF8-tail / %xE1-EC 2( UTF8-tail ) / %xED %x80-9F UTF8-tail / %xEE-EF 2( UTF8-tail )
   * UTF8-4      = %xF0 %x90-BF 2( UTF8-tail ) / %xF1-F3 3( UTF8-tail ) / %xF4 %x80-8F 2( UTF8-tail )
   * UTF8-tail   = %x80-BF
   */

   unsigned int& Lower = *pLower;
   unsigned int& Upper = *pUpper;
   if (LeadByte == 0xE0) {
      Lower = 0xA0;
   } else if (LeadByte == 0xF0) {
      Lower = 0x90;
   }

   if (LeadByte == 0xED) {
      Upper = 0x9F;
   } else if (LeadByte == 0xF4) {
      Upper = 0x8F;
   }
}

static signed int CORvarCheckNextChars(int HowMany, const unsigned char FirstByte, const char* Source, int SourceIndex, char* Buffer, unsigned int* pBufferCount) {
   COR_FUNCTION(CORvarCheckNextChars);
   unsigned int& BufferCount = *pBufferCount;
   unsigned char Two =   Source[SourceIndex + 1];
   unsigned char Three = Source[SourceIndex + 2];
   unsigned char Four =  Source[SourceIndex + 3];

   // These are the standard lower and upper possible values for non-leading bytes in UTF-8 characters.
   // In some cases, the range for the second byte is different.
   unsigned int Lower  = 0x80;
   unsigned int Upper =  0xBF;
   unsigned int Lower2 = Lower;
   unsigned int Upper2 = Upper;
   switch (HowMany) {
      case 1:
         COR_TRC("Two bytes");
         if (Lower <= Two && Two <= Upper) {
            Buffer[BufferCount++] = FirstByte;
            Buffer[BufferCount++] = Two;
            return 1;
         } else {
            Buffer[BufferCount++] = '.';
            return 0;
         }
         break;
      case 2:
         CORvarAdjustRangeForByte2(FirstByte, &Lower2, &Upper2);
         if ( (Lower2  <= Two && Two <= Upper2) &&
            (Lower <= Three && Three <= Upper) ) {
               Buffer[BufferCount++] = FirstByte;
               Buffer[BufferCount++] = Two;
               Buffer[BufferCount++] = Three;
               return 2;
         } else {
            Buffer[BufferCount++] = '.';
            return 0;
         }
         break;
      case 3:
         CORvarAdjustRangeForByte2(FirstByte, &Lower2, &Upper2);
         if ( (Lower2  <= Two && Two <= Upper2)  &&
            (Lower <= Three && Three <= Upper) &&
            (Lower <= Four  && Four  <= Upper) ) {
               Buffer[BufferCount++] = FirstByte;
               Buffer[BufferCount++] = Two;
               Buffer[BufferCount++] = Three;
               Buffer[BufferCount++] = Four;
               return 3;
         } else {
            Buffer[BufferCount++] = '.';
            return 0;
         }
         break;
      default:
         CORASSERT(false);
         return -1;
         break;
   }
}


//
// Emit JSON strings with or without surrounding double quotes.
// Exceedingly non-standard - emits special characters as \xHH, *WHICH IS NOT JSON*.
// Encoding: StrEncCpp - encodes ctrl chars and non-ascii as \xXX
// Encoding: StrEncJs  - encodes ctrl chars. Replaces invalid UTF-8 bytes with "."
//   THIS IS THE ONLY encoding that produces valid JSON.
//
// Encoding: StrEncRaw - does not encode anything. Will pass data through. Careful with that one.
//
void CORappendJsonString(CORstring* Out, const CORstring& In, bool WithQuotes, int encoding) {
   COR_FUNCTION(CORappendJsonString);
   const int BufferSize = 256;
   char      Buffer[BufferSize];    // Minimize expensive calls to CORstring::append.
   const int BufferHighWater = sizeof(Buffer) - 7; // Pad by 2 extra just to be safe.
   unsigned int       BufferCount = 0;
   if (encoding==CORvar::StrEncRaw) {
      if (WithQuotes) { Out->append("\""); }
      Out->append(In);
      if (WithQuotes) { Out->append("\""); }
   } else {
      if (WithQuotes) { Buffer[BufferCount++] = '\"'; }
      const char* p = In.c_str();
      const int   N = In.size();
      for (int i = 0; i < N; ++i) {
         COR_VAR(i);
         const unsigned char Ch = p[i];
         switch (Ch) {
            case '\\': Buffer[BufferCount++] = '\\'; Buffer[BufferCount++] = Ch ; break;
            case '\"': Buffer[BufferCount++] = '\\'; Buffer[BufferCount++] = Ch ; break;
            case '\n': Buffer[BufferCount++] = '\\'; Buffer[BufferCount++] = 'n'; break;
            case '\r': Buffer[BufferCount++] = '\\'; Buffer[BufferCount++] = 'r'; break;
            case '\t': Buffer[BufferCount++] = '\\'; Buffer[BufferCount++] = 't'; break;
            case '\f': Buffer[BufferCount++] = '\\'; Buffer[BufferCount++] = 'f'; break;
            case '\b': Buffer[BufferCount++] = '\\'; Buffer[BufferCount++] = 'b'; break;

            // \v is not allowed in JSON, so if this serialization is going near a browser,
            // this escaping will get caught by the general handler for control characters.
            case '\v': if(encoding != CORvar::StrEncJs) {
                            Buffer[BufferCount++] = '\\'; Buffer[BufferCount++] = 'v'; break;
                       }
            default  : if (0x20 <= Ch && Ch < 0x7F) {
                          // Printable ASCII
                          Buffer[BufferCount++] = Ch; // Emit as-is
                       } else if (encoding == CORvar::StrEncJs) {

                          // ASCII control characters are not allowed in JSON.
                          if (Ch < 0x20 || Ch == 0x7F) {
                             COR_TRC("Escaping control char.");
                             BufferCount += ::snprintf(Buffer + BufferCount, BufferSize - BufferCount, "\\u%04X", Ch);

                          } else if (Ch == 0xC0 || Ch == 0xC1 || Ch >= 0xF5) {
                             COR_TRC("Removing illegal byte.");
                             Buffer[BufferCount++] = '.';

                          } else if (0x80 <= Ch  && Ch <= 0xBF) {
                             COR_TRC("Looks like a standalone second or later byte of UTF-8 sequence. Removing.");
                             Buffer[BufferCount++] = '.';

                          // Multi-byte UTF-8
                          } else if (0xC2 <= Ch && Ch <= 0xDF) {
                             unsigned int NumNum = (unsigned int)Ch;
                             COR_TRC(Ch  << " (int value is: " << NumNum << ")" << " looks like the first byte of a two-byte sequence");
                             i += CORvarCheckNextChars(1, Ch, p, i, Buffer, &BufferCount);

                          } else if (0xE0 <= Ch && Ch <= 0xEF) {
                             unsigned int NumNum = (unsigned int)Ch;
                             COR_TRC(Ch  << " (int value is: " << NumNum << ")" << " looks like the first byte of a three-byte sequence");
                             i += CORvarCheckNextChars(2, Ch, p, i, Buffer, &BufferCount);

                          } else {
                             unsigned int NumNum = (unsigned int)Ch;
                             COR_TRC(Ch  << " (int value is: " << NumNum << ")" << " looks like the first byte of a four-byte sequence");
                             i += CORvarCheckNextChars(3, Ch, p, i, Buffer, &BufferCount);
                          }

                       } else { // Emit as \xXXX
                          BufferCount += ::snprintf(Buffer + BufferCount, BufferSize - BufferCount, "\\x%02X", Ch);
                       }
         }
         if (BufferCount >= BufferHighWater) {
            Out->append(Buffer, BufferCount);
            BufferCount = 0;
         }
      }
      if (WithQuotes) { Buffer[BufferCount++] = '\"'; }
      if (BufferCount>0) { Out->append(Buffer, BufferCount); }
   }
}

CORint32 CORvarKeyCompare::compare(const CORstring& A, const CORstring& B) {
   int r = A.icompare(B);
   if (r) {
      return r;
   }
   return A.compare(B);
}

CORvar::~CORvar() {
   destroy_();
}

CORvar::CORvar() {
   type_ = None;
}

CORvar::CORvar(bool value) {
   set_(value);
}

CORvar::CORvar(int value) {
   set_(value);
}

CORvar::CORvar(long long value) {
   set_(value);
}

CORvar::CORvar(double value) {
   set_(value);
}

CORvar::CORvar(const CORstring& value) {
   set_(value);
}

CORvar::CORvar(const char* value) {
   set_(value);
}

CORvar::CORvar(const char* str, int len) {
   set_(str, len);
}

// deep copy
CORvar::CORvar(const CORvar& that) {
   copy_(that);
}

void CORvar::set(bool value) {
   destroy_();
   set_(value);
}

void CORvar::set(int value) {
   destroy_();
   set_(value);
}

void CORvar::set(long long value) {
   destroy_();
   set_(value);
}

void CORvar::set(double value) {
   destroy_();
   set_(value);
}

void CORvar::set(const CORstring& value) {
   destroy_();
   set_(value);
}

void CORvar::set(const char* value) {
   destroy_();
   set_(value);
}

void CORvar::set(const char* str, int len) {
   destroy_();
   set_(str, len);
}

void CORvar::swap(CORstring* pString)
{
   CORstring* this_colstring = (CORstring*)u_.colstring_;
   if (type_ != String) {
      destroy_();
      type_ = String;
      new (this_colstring) CORstring();
   }
   this_colstring->swap(pString);
}

void CORvar::append(const CORstring& value) {
   append(value.c_str(), value.size());
}

void CORvar::append(const char* value) {
   append(value, ::strlen(value));
}

void CORvar::append(const char* str, int len) {
   if (!isString()) {
      if (isBool() || isInt() || isDouble()) {
         // convert number to string
         set(asString());
      } else {
         setType(CORvar::String);
      }
   }
   //CORASSERT(isString());
   CORstring* s = (CORstring*)u_.colstring_;
   s->append(str, len);
}

CORvar& CORvar::operator=(bool value) {
   set(value);
   return *this;
}

CORvar& CORvar::operator=(int value) {
   set(value);
   return *this;
}

CORvar& CORvar::operator=(long long value) {
   set(value);
   return *this;
}

CORvar& CORvar::operator=(double value) {
   set(value);
   return *this;
}

CORvar& CORvar::operator=(const CORstring& value) {
   set(value);
   return *this;
}

CORvar& CORvar::operator=(const char* value) {
   set(value);
   return *this;
}

CORvar& CORvar::operator=(const CORvar& that)
{
   if (this != &that) {
      switch (type_) {
      case Array:
      case Map:
         // must use a temp value for arrays and maps just
         // in case we are copying a child element into this
         {
            CORvar tmp(that);
            destroy_();
            swap(&tmp);
         }
         break;
      case String:
         destroy_();
         // no break - fall through
      default:
         copy_(that);
         break;
      }
   }
   return *this;
}

bool CORvar::asBool() const
{
   switch (type_) {
   case Integer:
   case Boolean:
      return u_.int_ != 0;
   case Double:
      return u_.double_ != 0;
   case String:
      {
         const CORstring& s = *(CORstring*)u_.colstring_;
         if (s.icompare("true")  == 0){ return true;  }
         if (s.icompare("false") == 0){ return false; }
         return ::atoi(s.c_str()) != 0;
      }
      break;
   case Array:
   case Map:
   default:
      break;
   }
   return 0;
}

long long CORvar::asInt() const
{
   switch (type_) {
   case Integer:
   case Boolean:
      return u_.int_;
   case Double:
      return int(u_.double_);
   case String:
      {
         const CORstring& s = *(CORstring*)u_.colstring_;
         return ::atoll(s.c_str());
      }
      break;
   case Array:
   case Map:
   default:
      break;
   }
   return 0;
}

double CORvar::asDouble() const
{
   switch (type_) {
   case Double:
      return u_.double_;
   case Integer:
   case Boolean:
      return u_.int_;
   case String:
      {
         const CORstring& s = *(CORstring*)u_.colstring_;
         return ::atof(s.c_str());
      }
   case Array:
   case Map:
   default:
      break;
   }
   return 0;
}

CORstring CORvar::asString() const
{
   char buf[256];
   switch (type_) {
   case String:
      return *(CORstring*)u_.colstring_;
      break;
   case Integer:
      ::snprintf(buf, 256, "%lld", u_.int_);
      return buf;
   case Boolean:
      return u_.int_ ? "true" : "false";
   case Double:
      {
         const int n = int(u_.double_);
         if (n == u_.double_) {
            ::snprintf(buf, 256, "%d", n);
         } else {
            ::snprintf(buf, 256, "%g", u_.double_);
         }
         return buf;
      }
      break;
   case Array:
   case Map:
   default:
      break;
   }
   return CORstring();
}

CORstring CORvar::asEscapedString(int encoding) const {
   CORstring out;
   CORappendJsonString(&out, asString(), false, encoding);
   return out;
}

static const CORstring s_EmptyString;

const CORstring& CORvar::str() const
{
   if (String == type_) {
      return *(CORstring*)u_.colstring_;
   }
   return s_EmptyString;
}

bool CORvar::getBool(const CORstring& key) const
{
   if (const CORvar* child = get(key)) {
      return child->asBool();
   }
   return false;
}

long long CORvar::getInt(const CORstring& key) const
{
   if (const CORvar* child = get(key)) {
      return child->asInt();
   }
   return 0;
}

double CORvar::getDouble(const CORstring& key) const
{
   if (const CORvar* child = get(key)) {
      return child->asDouble();
   }
   return 0;
}

CORstring CORvar::getString(const CORstring& key) const
{
   if (const CORvar* child = get(key)) {
      return child->asString();
   }
   return CORstring();
}

bool CORvar::getBool(int idx) const
{
   if (const CORvar* child = get(idx)) {
      return child->asBool();
   }
   return false;
}

long long CORvar::getInt(int idx) const
{
   if (const CORvar* child = get(idx)) {
      return child->asInt();
   }
   return 0;
}

double CORvar::getDouble(int idx) const
{
   if (const CORvar* child = get(idx)) {
      return child->asDouble();
   }
   return 0;
}

CORstring CORvar::getString(int idx) const
{
   if (const CORvar* child = get(idx)) {
      return child->asString();
   }
   return CORstring();
}

static void CORvarIndent(CORstring* out, int N)
{
   const int INDENT = 4;
   const int max = 1000;
   static int s_Initialized;
   static char buf[INDENT*max+1];
   if (0 == s_Initialized) {
      memset(buf, ' ', sizeof(buf));
      buf[sizeof(buf)-1] = 0;
      s_Initialized = 1;
   }
   *out += '\n';
   if (N > max) {
      N = max;
   }
   N *= INDENT;
   out->append(buf, N);
}

CORstring CORvar::escape(const CORstring& in, int encoding)
{
   CORstring out;
   CORappendJsonString(&out, in, false, encoding);
   return out;
}

CORstring CORvar::json(int N, int encoding) const
{
   CORstring s;
   char buf[256];
   switch (type_) {
   case None:
      s = "null";
      break;
   case String:
      CORappendJsonString(&s, *(CORstring*)u_.colstring_, true, encoding);
      break;
   case Integer:
      {
         const int len = ::snprintf(buf, 256, "%lld", u_.int_);
         s.set(buf, len);
      }
      break;
   case Boolean:
      s = u_.int_ ? "true" : "false";
      break;
   case Double:
      {
         int len = 0;
         const int n = int(u_.double_);
         if (n == u_.double_) {
            len = ::snprintf(buf, 256, "%d", n);
         } else {
            len = ::snprintf(buf, 256, "%g", u_.double_);
         }
         s.set(buf, len);
      }
      break;
   case Array:
      {
         if (u_.vec_ && u_.vec_->size() > 0) {
            bool isFirst = true;
            s += '[';
            if (N) { CORvarIndent(&s,N); }
            for (CORvarVec::iterator it = u_.vec_->begin(); it != u_.vec_->end(); ++it) {
               if (!isFirst) {
                  s += ',';
                  if (N) { CORvarIndent(&s,N); }
               }
               isFirst = false;
               s.append(it->json(N>0 ? N+1 : 0, encoding));
            }
            if (N) { CORvarIndent(&s,N-1); }
            s += ']';
         } else {
            // empty vector
            s += "[]";
         }
      }
      break;
   case Map:
      {
         if (u_.map_ && u_.map_->size() > 0) {
            bool isFirst = true;
            s += '{';
            if (N) { CORvarIndent(&s,N); }
            for (CORvarMap::iterator it = u_.map_->begin(); it != u_.map_->end(); ++it) {
               if (!isFirst) {
                  s += ',';
                  if (N) { CORvarIndent(&s,N); }
               }
               isFirst = false;
               CORappendJsonString(&s, it->first, true, encoding);
               s += ':';
               if (N) s += ' ';
               s.append(it->second.json(N>0 ? N+1 : 0, encoding));
            }
            if (N) { CORvarIndent(&s,N-1); }
            s += '}';
         } else {
            // empty map
            s += "{}";
         }
      }
      break;
   default:
      break;
   }
   return s;
}

void CORvar::set_(const CORstring& s)
{
   type_ = String;
   CORstring* this_colstring = (CORstring*)u_.colstring_;
   new (this_colstring) CORstring(s);
}

void CORvar::set_(const char* s)
{
   type_ = String;
   CORstring* this_colstring = (CORstring*)u_.colstring_;
   new (this_colstring) CORstring(s);
}

void CORvar::set_(const char* s, int n)
{
   type_ = String;
   CORstring* this_colstring = (CORstring*)u_.colstring_;
   new (this_colstring) CORstring(s,n);
}

void CORvar::swap(CORvar* that)
{
   char tmp[sizeof(CORvar)];
   memcpy((void*)tmp,  this, sizeof(CORvar));
   memcpy((void*)this, that, sizeof(CORvar));
   memcpy((void*)that, tmp,  sizeof(CORvar));
}

void CORvar::copy_(const CORvar& that)
{
   switch (that.type_) {
   case Integer:
   case Boolean:
      u_.int_ = that.u_.int_;
      break;
   case Double:
      u_.double_ = that.u_.double_;
      break;
   case String:
      {
         CORstring* that_colstring = (CORstring*)that.u_.colstring_;
         CORstring* this_colstring = (CORstring*)u_.colstring_;
         new (this_colstring) CORstring(*that_colstring);
      }
      break;
   case Array:
      u_.vec_ = 0;
      if (that.u_.vec_) {
         u_.vec_ = new CORvarVec(*that.u_.vec_);
      }
      break;
   case Map:
      u_.map_ = new CORvarMap(*that.u_.map_);
      break;
   default:
      break;
   }
   type_ = that.type_;
}

void CORvar::destroy_()
{
   switch (type_) {
   case String:
      {
         CORstring* colstring = (CORstring*)u_.colstring_;
         colstring->~CORstring();
      }
      break;
   case Array:
      delete u_.vec_;
      break;
   case Map:
      delete u_.map_;
      break;
   default:
      break;
   }
   type_ = None;
   u_.double_ = 0;
   //rule_ = 0;
   //span_.reset();
}

CORvar& CORvar::operator[](int i)
{
   switch (type_) {
   case None:
   case Integer:
   case Boolean:
   case Double:
   case String:
      // destroy the scalar value and make this object an array
      destroy_();
      u_.vec_ = 0;
      type_ = Array;
      // no break - fall through
   case Array:
      // Only use a vector representation if 0 <= i <= 1000
      // OR index i is less or equal twice the previous vector size.
      if (i >= 0) {
         // Later have to make a spase array class
         if (i <= 1000 || (u_.vec_ && i <= u_.vec_->size() * 2)) {
            // we're dealing with an array element.
            if (0 == u_.vec_) {
               // create vector if null.
               u_.vec_ = new CORvarVec();
               u_.vec_->setCapacity(8);
            }
            if (u_.vec_->size() < i+1) {
               // fill array with empty CORvars if required
               // in case it is accessed in a sparse manner.
               u_.vec_->resize(i+1);
            }
            // return the array element
            return (*u_.vec_)[i];
         }
      }
      // index is out of range for a vector - convert the vector to a map
      convertToMap_();
      break;
   case Map:
      break;
   }
   // if we got this far, we must be dealing with a map
   CORASSERT(type_==Map);
   CORASSERT(u_.map_);
   return (*u_.map_)[CORintToString(i)];
}

CORvar& CORvar::operator[](const CORstring& key)
{
   convertToMap_();
   return (*u_.map_)[key];
}

void CORvar::convertToMap_()
{
   switch (type_) {
   case Map:
      break;
   case Array:
      {
         CORvarVec* pVec = u_.vec_;
         CORvarMap* pMap = new CORvarMap();
         if (pVec) {
            const int vec_size = pVec->size();
            for (int i = 0; i < vec_size; ++i) {
               const CORvar& var = (*pVec)[i];
               if (var.type() != CORvar::None) {
                  // map keys are the array indexes converted to strings
                  (*pMap)[CORintToString(i)] = var;
               }
            }
            delete pVec;
         }
         u_.map_ = pMap;
         type_ = Map;
      }
      break;
   case String:
      destroy_();
      // no break - fall through
   case Integer:
   case Boolean:
   case Double:
   case None:
      u_.map_ = new CORvarMap();
      type_ = Map;
      break;
   }
   CORASSERT(type_==Map);
}

CORvar* CORvar::get(int i)
{
   //COR_METHOD(CORvar::get(int));
   switch (type_) {
   case Array:
      if (u_.vec_ && i >= 0 && i < u_.vec_->size()) {
         return &(*u_.vec_)[i];
      }
      // no break - fall through
   case Map:
      return get(CORintToString(i));
   default:
      break;
   }
   return NULL;
}

const CORvar* CORvar::get(int i) const
{
   //COR_METHOD(CORvar::get(int) const);
   return const_cast<CORvar*>(this)->get(i);
}

CORvar* CORvar::get(const CORstring& key)
{
   //COR_METHOD(CORvar::get(const CORstring&));
   if (type_ == CORvar::Map && u_.map_) {
      CORvarMap::iterator it = u_.map_->find(key);
      if (it != u_.map_->end()) {
         return &it->second;
      }
   }
   return NULL;
}

const CORvar* CORvar::get(const CORstring& key) const
{
   //COR_METHOD(CORvar::get(const CORstring&) const);
   return const_cast<CORvar*>(this)->get(key);
}

void CORvar::erase(const CORstring& key)
{
   if (type_ == Map && u_.map_) {
      u_.map_->erase(key);
   }
}

void CORvar::remove(int idx)
{
   if (type_ == Array && u_.vec_){
      u_.vec_->remove(idx);
   }
}

static const CORvar s_NullVar;

const CORvar& CORvar::operator[](int i) const
{
   if (const CORvar* pVar = get(i)) {
      // Found the element matching index i.
      return *pVar;
   }
   // Index i not found - return a global static null CORvar.
   CORASSERT(s_NullVar.isNull()); // Make sure no one alters this instance.
   return s_NullVar;
}

const CORvar& CORvar::operator[](const CORstring& key) const
{
   if (const CORvar* pVar = get(key)) {
      // Found the element matching key.
      return *pVar;
   }
   // Key not found - return a global static null CORvar.
   CORASSERT(s_NullVar.isNull()); // Make sure no one alters this instance.
   return s_NullVar;
}

void CORvar::resize(int NewArraySize)
{
   if (type_ == Array) {
      if (0 == u_.vec_) {
         u_.vec_ = new CORvar::CORvarVec();
      }
      u_.vec_->resize(NewArraySize);
   }
}

int CORvar::size() const
{
   switch (type_) {
   case Array:
      if (u_.vec_) {
         return u_.vec_->size();
      }
      return 0;
   case Map:
      return u_.map_->size();
   default:
      break;
   }
   return 0; // scalar elements have no children
}

const CORvar::CORvarVec& CORvar::array() const
{
   //CORASSERT(type_ == Array && u_.vec_);
   CORPRECONDITION(type_ == Array && u_.vec_);
   return *u_.vec_;
}

CORvar::CORvarVec& CORvar::array()
{
   CORPRECONDITION(type_ == Array && u_.vec_);
   return *u_.vec_;
}

const CORvar::CORvarMap& CORvar::map() const
{
   CORPRECONDITION(type_ == Map);
   return *u_.map_;
}

CORvar::CORvarMap& CORvar::map()
{
   CORPRECONDITION(type_ == Map);
   return *u_.map_;
}

CORvar& CORvar::push_back(const CORvar& value)
{
   if (type_ == None) {
      type_ = Array;
      u_.vec_ = 0;
   }
   CORPRECONDITION(type_ == Array);
   if (u_.vec_ == 0) {
      u_.vec_ = new CORvar::CORvarVec();
   }
   return u_.vec_->push_back(value);
}

void CORvar::pop_back()
{
   CORPRECONDITION(type_ == Array && u_.vec_ != NULL && u_.vec_->size() > 0);
   u_.vec_->pop_back();
}

CORvar& CORvar::setType(CORvar::Type type)
{
   COR_METHOD(CORvar::setType);
   COR_VAR(type);

   if (type_ != type) {
      if (type == Map) {
         convertToMap_();
      }
      else {
         destroy_();
         type_ = type;
         if (type == Array) {
            u_.vec_ = new CORvar::CORvarVec();
         }
      }
   }
   CORASSERT(type == type_);
   return *this;
}

// Note: String payload can be binary.
// Ordering is not lexical. "Z" is less than "ABC" due to shorter length.
static inline int CORvarFastBinaryStringCompare(const CORstring& A, const CORstring& B) {
   const int sizeA = A.size();
   const int sizeB = B.size();
   if (sizeA == sizeB) {
      return ::memcmp(A.get_buffer(), B.get_buffer(), sizeA);
   }
   return sizeA - sizeB;
}

int CORvar::fastCompare(const CORvar& A, const CORvar& B) {
   if (&A == &B) { return 0; }
   if (A.type_ != B.type_) { return int(A.type_) - int(B.type_); }
   switch(A.type_) {
   case None:
      return 0;
   case String: {
         const CORstring* pA = (CORstring*)A.u_.colstring_;
         const CORstring* pB = (CORstring*)B.u_.colstring_;
         return CORvarFastBinaryStringCompare(*pA, *pB);
      }
   case Boolean:
   case Integer:
      return A.u_.int_ - B.u_.int_;
   case Double:
      return (A.u_.double_ < B.u_.double_)? -1 : (A.u_.double_ > B.u_.double_);
   case Array: {
         const int as = A.size(), bs = B.size();
         if (as != bs) { return as - bs; }
         CORvarVec::const_iterator itrA=A.array().begin(), itrB=B.array().begin(), endA=A.array().end();
         for (; itrA!=endA ; ++itrA, ++itrB) {
            int ret = fastCompare(*itrA, *itrB);
            if(ret) { return ret; }
         }
      }
      return 0;
   case Map: {
         const int as = A.size(), bs = B.size();
         if (as != bs) { return as - bs; }
         CORvarMap::const_iterator itrA=A.map().begin(), itrB=B.map().begin(), endA=A.map().end();
         for (; itrA!=endA ; ++itrA, ++itrB) {
            // Assume that Map keys are binary
            int ret = CORvarFastBinaryStringCompare(itrA->first, itrB->first);
            if (ret) { return ret; }
            ret = fastCompare(itrA->second, itrB->second);
            if (ret) { return ret; }
         }
      }
      return 0;
   }
   return 0;
}

CORostream& operator<<(CORostream& Stream, const CORvar& Var){
   Stream << Var.json(0,CORvar::StrEncCpp);
   return Stream;
}

#if defined(_WIN32) || defined(__APPLE__) || defined(__linux__)
   enum { s_IsLitteEndianMachine = 1 };
#else
   enum { s_IsLitteEndianMachine = 0 };
#endif

static inline void CORvarAppendByte(CORstring* s, unsigned char v) {
   *s += (char)v;
}

static void CORvarAppendVarInt(CORstring* s, CORint64 v)
{
   char Buffer[16];
   if (v <= 0x7f) {
      CORvarAppendByte(s, (unsigned char)(unsigned)v);
   } else {
      unsigned CORint64 u = v;
      int i = 0;
      while (u) {
         Buffer[i++] = (((unsigned)u) & 0x7f) | 0x80;
         u >>= 7;
      }
      CORASSERT(i>0);
      Buffer[i-1] &= 0x7f;
      s->append(Buffer, i);
   }
}

static void CORvarAppendDoubleLE(CORstring* s, double v)
{
   char* p = (char*)&v;
   char buf[8];
   if (s_IsLitteEndianMachine) {
      buf[0] = p[0];
      buf[1] = p[1];
      buf[2] = p[2];
      buf[3] = p[3];
      buf[4] = p[4];
      buf[5] = p[5];
      buf[6] = p[6];
      buf[7] = p[7];
   } else {
      buf[0] = p[7];
      buf[1] = p[6];
      buf[2] = p[5];
      buf[3] = p[4];
      buf[4] = p[3];
      buf[5] = p[2];
      buf[6] = p[1];
      buf[7] = p[0];
   }
   s->append(buf, 8);
}

void CORvar::toBinary(CORstring* Out) const
{
   switch (type_) {
   case None:
      CORvarAppendByte(Out, (unsigned char)None);
      break;
   case String: {
         const CORstring& str = *(CORstring*)u_.colstring_;
         const int strSize = str.size();
         if (strSize <= 14) {
            // Lengths of 0 - 14 can be stored in the hi bits of the Type byte.
            CORvarAppendByte(Out, (unsigned char)String | (strSize << 4));
         } else {
            // A string length of 15 in the hi bits means "read the
            // string length from the varint that follows the Type byte."
            CORvarAppendByte(Out, (unsigned char)String | 0xf0);
            CORvarAppendVarInt(Out, str.size());  // string length
         }
         Out->append(str);                  // string without nil
      }
      break;
   case Integer: {
         unsigned char Type;
         long long AbsoluteValue;
         if (u_.int_ >= 0) {
            Type          = VarIntPositive;
            AbsoluteValue = u_.int_;
         } else {
            Type          = VarIntNegative;
            AbsoluteValue = -u_.int_;
         } //? below
         if (AbsoluteValue <= 14) {
            // Absolute Values of 0 - 14 can be stored in the hi bits of
            // the Type byte.
            CORvarAppendByte(Out, Type | ((unsigned)AbsoluteValue << 4));
         } else {
            // a value of 15 in the hi bits means "read the absolute value from
            // the varint that follows the Type byte."
            CORvarAppendByte(Out, Type | 0xf0);
            CORvarAppendVarInt(Out, AbsoluteValue);
         }
      }
      break;
   case Boolean:
      if (u_.int_) {
         CORvarAppendByte(Out, (unsigned char)BooleanTrue);
      } else {
         CORvarAppendByte(Out, (unsigned char)BooleanFalse);
      }
      break;
   case Double:
      CORvarAppendByte(Out, (unsigned char)Double);
      CORvarAppendDoubleLE(Out, u_.double_);
      break;
   case Array:
      if (u_.vec_ && u_.vec_->size() > 0) {
         // non-zero number of array elements
         const unsigned NumElements = u_.vec_->size();
         if (NumElements <= 14) {
            // sizes 14 or smaller stored in hi bits of type byte
            CORvarAppendByte(Out, (unsigned char)Array | (NumElements << 4));
         } else {
            // type byte hi bits set to 15 meaning varint length following.
            CORvarAppendByte(Out, (unsigned char)Array | 0xf0);
            CORvarAppendVarInt(Out, NumElements); // varint number of elements
         }
         // append each element
         for (CORvarVec::iterator it = u_.vec_->begin(); it != u_.vec_->end(); ++it) {
            it->toBinary(Out);
         }
      } else {
         // This is an empty vector.
         // Hi bits of type byte are set to 0 indicating no elements following.
         CORvarAppendByte(Out, (unsigned char)Array);
      }
      break;
   case Map:
      if (u_.map_ && u_.map_->size() > 0) {
         // non-zero number of map pairs
         const unsigned NumPairs = u_.map_->size();
         if (NumPairs <= 14) {
            // sizes 14 or smaller stored in hi bits of type byte
            CORvarAppendByte(Out, (unsigned char)Map | (NumPairs << 4));
         } else {
            // type byte hi bits set to 15 meaning varint length following.
            CORvarAppendByte(Out, (unsigned char)Map | 0xf0);
            CORvarAppendVarInt(Out, NumPairs); // varint number of key/value pairs
         }
         // append each key/value pair
         for (CORvarMap::iterator it = u_.map_->begin(); it != u_.map_->end(); ++it) {
            CORvarAppendVarInt(Out, it->first.size()); // key length
            Out->append(it->first);              // key string without nil
            it->second.toBinary(Out);            // value
         }
      } else {
         // This is an empty map.
         // Hi bits of type byte are set to 0 indicating no pairs following.
         CORvarAppendByte(Out, (unsigned char)Map);
      }
      break;
   default:
      break;
   }
}

bool CORvar::parse(const CORstring& Data){
   COR_METHOD(CORvar::parse-CORstring);
   return CORparseJson(Data, this);
}

bool CORvar::parse(const char* pData, int Length){
   COR_METHOD(CORvar::parse);
   return CORparseJson(pData, this);
}
