#pragma hdrstop
//-----------------------------------------------------------------------------
// Copyright (C) 2026 Eliot Muir.  All rights reserved.
//
// Module:  CORvar
//
// Author:  Andrew Vajoczki
//
// Description:
//   Very important class - worth giving a good read.
//
//   A variant object that can hold a bool, number, string, vector or map.
//
//   Can represent a JSON-like object.
//   Everything is stored by value.  No cycles are possible.
//-----------------------------------------------------------------------------

#include "CORmap.h"
#include <COR/CORarray.h>

extern "C" { struct lua_State; }; // predeclared for method that converts from a Lua table.

struct CORvarKeyCompare {
   static CORint32 compare(const CORstring& A, const CORstring& B);
};

void CORappendJsonString(CORstring* Out, const CORstring& In, bool WithQuotes, int encoding);
class CORvar{
public:
   typedef CORmap<CORstring,CORvar,CORvarKeyCompare> CORvarMap;
   typedef CORarray<CORvar>                         CORvarVec;

   // Type values must be between 0 - 15 inclusive to fit into 4 bits.
   enum Type {
      None      = 0, // None must be zero.
      Boolean   = 1,
      Integer   = 2,
      Double    = 3,
      String    = 4,
      MaxScalar = 4, // Scalar types must be less than or equal to this.
      Array     = 5,
      Map       = 6,
   };

   // Extra specialized types for binary serialization.
   // Values must not overlap with enum Type above
   // and must be between 0 - 15 inclusive.
   enum {
      VarIntPositive = 7,
      VarIntNegative = 8,
      BooleanTrue    = 9,
      BooleanFalse   = 10
   };

   // String escape sequence encoding
   enum {
      StrEncCpp = 0, // Encode ctrl chars and non-ascii as \xXX
      StrEncJs  = 1, // Encode ctrl chars. Replace invalid UTF-8 bytes with "."
      StrEncRaw = 2  // Don't encode any characters
   };

   ~CORvar();
   CORvar();
   CORvar(bool value);
   CORvar(int value);
   CORvar(long long value);
   CORvar(double value);
   CORvar(const CORstring& value);
   CORvar(const char* value);
   CORvar(const char* str, int len);

   // deep copy
   CORvar(const CORvar& that);

   // deep copy
   CORvar& operator=(const CORvar& that);

   // full tree scan for equality
   inline bool operator==(const CORvar& that) const { return fastCompare(*this,that) == 0; }

   // full tree scan for inequality
   inline bool operator!=(const CORvar& that) const { return fastCompare(*this,that) != 0; }

   // Parse json string into this instance.
   // Returns true for success, false for failure.
   // A CORvar::parse() returning false leaves the CORvar instance in a null state.
   // IX-1399 The above statement is currently a lie.  The current behaviour is to put a formatted error message into the CORvar
   // in the event of an error.  Eliot
   bool parse(const CORstring& json);
   bool parse(const char* json, int bytes);

   // Parse XML into this instance.
   // Returns true for success, false for failure.
   // A CORvar::parse() returning false leaves the CORvar instance in a null state.
   // Implementation of this method is in CXMLparse.cpp
   // If you call CORvar::parseXml() in your application then you must specify makefile
   // MODULES in this order: DOM XML expat
   // WARNING - so far the XML support in CORvar is for XML elements and attributes only.  CDATA
   // and #Text elements are ignored.
   bool parseXml(const CORstring& xml);
   bool parseXml(const char* xml, int bytes);

   // Return CORvar in XML - it uses the format that is parsed into from parseXml
   // Currently this method in implemented in the CXMLparse.cpp file.  Set indent
   // to a value greater than zero if you would like indentation.  
   CORstring xml(int indent=0);

   // WARNING - this function may throw exceptions.
   // This will convert the data found in a Lua table in the stack at
   // position i into this CORvar.  User data with __tostring defined is converted
   // If the __tostring is not defined an exception will be thrown.
   // Lua coroutines and functions are ignored.
   // Implementation of this method is in LUA/LUAvar.cpp.
   // You will need to link in LUA and friends to use this function.
   void fromLua(lua_State* L, int i = -1); 

   // Push the equivalent of this CORvar onto the top of the Lua stack.
   void toLua(lua_State* L) const;

   // Push the equivalent of this CORvar onto the top of the Lua stack,
   // knowing it's about to be serialized as JSON. This turns null CORvars
   // into magic "JSON nulls" in the resulting Lua table, which preserves all
   // keys, including those whose values are null.
   void toLuaNullsNotNils(lua_State* L) const;

   // Swap the contents of this CORvar instance with another.
   // Implemented with memory "sliding".
   // Be very careful not to create cycles in the same CORvar tree.
   void swap(CORvar* that);

   CORvar::Type type() const { return type_; }

   // These methods do not throw.
   bool isNone()       const { return type_ == None; }
   bool isNull()       const { return type_ == None; }
   bool isBoolean()    const { return type_ == Boolean; }
   bool isBool()       const { return type_ == Boolean; }
   bool isInteger()    const { return type_ == Integer; }
   bool isInt()        const { return type_ == Integer; }
   bool isDouble()     const { return type_ == Double; }
   bool isString()     const { return type_ == String; }
   bool isArray()      const { return type_ == Array; }
   bool isMap()        const { return type_ == Map; }
   bool isNumeric()    const { return type_ == Integer || type_ == Double || type_ == Boolean; }
   bool isScalar()     const { return type_ <= MaxScalar; }
   bool isCollection() const { return !isScalar(); }
   bool isLeaf()       const { return isScalar(); }

   // Return value assuming this element is a scalar value. Does not throw.
   bool      asBool()    const;
   long long asInt()     const;
   double    asDouble()  const;
   CORstring asString()  const;  // Use to convert scalars to a string
   CORstring asEscapedString(int encoding=StrEncJs) const;

   // Returns a const string reference ONLY if this is a String type,
   // otherwise return a reference to an empty string.
   // Note: this method does no conversions from other types.
   const CORstring& str() const;

   // Return value assuming this element is a scalar value. Does not throw.
   operator bool()      const { return asBool();   }
   operator int()       const { return asInt();    } // potential for truncation
   operator long long() const { return asInt();    }
   operator double()    const { return asDouble(); }
   operator CORstring() const { return asString(); }

   // Return child element assuming this element is a map. Does not throw.
   bool      getBool   (const CORstring& key) const;
   long long getInt    (const CORstring& key) const;
   double    getDouble (const CORstring& key) const;
   CORstring getString (const CORstring& key) const;

   // Return child element assuming this element is an array. Does not throw.
   bool      getBool   (int idx) const;
   long long getInt    (int idx) const;
   double    getDouble (int idx) const;
   CORstring getString (int idx) const;

   // Return escaped string WITHOUT surrounding quotes in JSON style.
   static CORstring escape(const CORstring&, int encoding=StrEncCpp);

   // Output CORvar as JSON. Set nesting to true if you want indenting.
   CORstring json(int nesting=0, int encoding=StrEncJs) const;

   // Output CORvar to a binary payload stored in a CORstring.
   void toBinary(CORstring* BinaryOut) const;

   enum ParseState {
      kSUCCESS        = 0,
      kNEED_MORE_DATA = 1,
      kFAILURE        = 2
   };

   // Convert a binary buffer to a CORvar.
   // Returns kSUCCESS for a successful parse and *pBytesConsumed will hold 
   // the number of bytes used by the parse.
   // Returns kFAILURE for an outright parse failure - the caller
   // must take actions to drop the connection or whatever they need to do.
   // Returns kNEED_MORE_DATA if the frame is not complete.
   // Note: this method will NOT BUFFER data for incomplete frames - the
   // caller must manage that.
   // Note: *pBytesConsumed will be set to 0 for both kNEED_MORE_DATA and kFAILURE.
   CORvar::ParseState parseBinary(const void* Data, int Length, int* pBytesConsumed);

   void set(bool value);
   void set(int value);
   void set(long long value);
   void set(double value);
   void set(const CORstring& value);
   void set(const char* value);
   void set(const char* str, int len);

   // Swap the contents of pString with this CORvar.
   // If the original CORvar is not of type String no attempt is made to
   // convert it - the non-string contents of the CORvar will be lost.
   void swap(CORstring* pString);

   // Append a string to this CORvar.
   // First convert instance to String if not already that type.
   // If instance is an Array or a Map, then use an empty string prior to append.
   void append(const CORstring& value);
   void append(const char* value);
   void append(const char* str, int len);

   // Convert instance to specified type.
   // If the present type is the same as the new type, this is a no op.
   // Otherwise if the specified type is different than the present type and
   // if it was a Map or scalar type previously, all data will be lost.
   // This call is necessary to represent an empty Array or Map in JSON.
   CORvar& setType(Type type);

   // Convert instance to the Array type.
   // This call is necessary to represent an empty Array.
   // If it was a Map or scalar type previously, all data will be lost.
   CORvar& setArrayType() { return setType(CORvar::Array); }

   // Convert instance to the Map type.
   // This call is necessary to represent an empty Map.
   // If it was a scalar type previously, then its data will be lost.
   // If it was an Array type previously, it will be converted to a Map.
   CORvar& setMapType() { return setType(CORvar::Map); }

   // clears and sets the instance to the None state
   CORvar& reset() { return setType(CORvar::None); }

   CORvar& operator=(bool value);
   CORvar& operator=(int value);
   CORvar& operator=(long long value);
   CORvar& operator=(double value);
   CORvar& operator=(const CORstring& value);
   CORvar& operator=(const char* value);

   // Does a child element exist with matching index or key?
   // Always returns false if this is a scalar.
   bool exists(int idx) const              { return !!get(idx); }
   bool exists(const CORstring& key) const { return !!get(key); }

   // If this var is Map, erase the element matching `key'.
   // If not a Map type - do nothing.
   void erase(const CORstring& key);

   // If this var is Array, erase the element matching `index'.
   // If not a Array type - do nothing.
   void remove(int idx);

   // Lookup functions to retrieve a child CORvar pointer by index or key.
   // Returns NULL if this CORvar is a scalar or if idx/key is not found.
   // These get() methods never create an element.
   const CORvar* get(int idx) const;
   CORvar*       get(int idx);
   const CORvar* get(const CORstring& key) const;
   CORvar*       get(const CORstring& key);

   // Find and/or create an element with matching index or key.
   // Note: if called on a scalar CORvar then the scalar value WILL BE LOST
   //       and an array or map created with this key.
   CORvar& operator[](int idx);
   CORvar& operator[](const CORstring& key);
   CORvar& operator[](const char* key) { return operator[](CORstring(key)); }

   // These const attribute lookup operators never throw.
   // They return a reference to const CORvar of type CORvar::None if key or idx not found.
   const CORvar& operator[](int idx) const;
   const CORvar& operator[](const CORstring& key) const;
   const CORvar& operator[](const char* key) const { return operator[](CORstring(key)); }

   // Push an element to the back of the array.
   // Throw an exception if this is anything other than None or Array.
   CORvar& push_back(const CORvar& value);
   CORvar& push_back() { return push_back(CORvar()); }

   // Pop an element from the back of the array.
   // Throw an exception if this is not an Array or if array is empty.
   void pop_back();

   // Returns the array.
   // Throw an exception if not a array.
   const CORvarVec& array() const;
   CORvarVec& array();

   // Returns the map.
   // Throw an exception if not a map.
   const CORvarMap& map() const;
   CORvarMap& map();

   // Returns the Array size, or the number of elements in the Map.
   // This may be surprising if an Array is promoted to a Map.
   // Returns 0 for scalar types.
   int size() const;

   // Resize CORvar array. No effect if this instance is not an Array.
   void resize(int NewArraySize);

   CORvar::ParseState parseBinary(class CORvarBinBuf* bin);

   // Does a lazy comparision of two CORvars (ignoring IPArule and CORspan)
   // of following and retuns as soon as tie between the two CORvars is broken:
   //    type_ enum
   //    for atomic types (None,Boolean,Integer,Double) : full comparision
   //    for String: uses fastBinaryStringCompare - ordering is NOT lexical.
   //          "Z" is less than "ABC" due to shorter String length.
   //          Same binary string length ties settled by memcmp().
   //    for Array and Map: size comparision (# of entries)
   //    for Arrays of same size: element by element comparision
   //    for Maps of same size: for each entry key is compared using
   //          fastBinaryStringCompare followed by comparision of the
   //          elements recursively using fastCompare.
   //
   static int fastCompare(const CORvar& A, const CORvar& B);

   inline static int fastCompareByPtr(const CORvar* A, const CORvar* B) {
      return fastCompare(*A, *B);
   }

private:
   CORvar(const void* not_implemented_to_catch_illegal_pointer_arguments);
   CORvar& operator=(const void* not_implemented_to_catch_illegal_pointer_arguments);
   void set(const void* not_implemented_to_catch_illegal_pointer_arguments);

   inline void set_(bool value) {
      type_ = Boolean;
      u_.int_ = value;
   }
   inline void set_(int value) {
      type_ = Integer;
      u_.int_ = value;
   }
   inline void set_(long long value) {
      type_ = Integer;
      u_.int_ = value;
   }
   inline void set_(double value) {
      type_ = Double;
      u_.double_ = value;
   }
   void set_(const CORstring& value);
   void set_(const char* value);
   void set_(const char* str, int len);
   void copy_(const CORvar& that);
   void convertToMap_();
   void destroy_();

   union Payload {
      long long  int_;
      double     double_;
      char       colstring_[sizeof(CORstring)];
      CORvarVec* vec_;
      CORvarMap* map_;
   };

   // Optimal data member order for Win32, Mac32, Linux32 => 40 bytes.
   // Win64 and Linux64 => 56 bytes 
   Payload        u_;
   Type           type_;
};

CORostream& operator<<(CORostream& Stream, const CORvar& Var);


