#pragma once
//---------------------------------------------------------------------------
// Copyright (C) 2026 Eliot Muir.  All rights reserved.
//
// Module: CORthreadLocal
//
// Description:
//
//   Thread local storage class.
//
// Author: Andrew Vajoczki
//---------------------------------------------------------------------------

#include <new>
#include <memory.h>
#include <stdint.h>

class CORthreadLocalBase{
public:
   typedef void (*CORthreadLocalBase_destroy_fn)(void*);
   CORthreadLocalBase(CORthreadLocalBase_destroy_fn = 0, int DeleteKeyOnExit = 1);
   ~CORthreadLocalBase();
   const void* getSpecific() const;
   void* getSpecific();
   void setSpecific(void* value);
private:
   void* m_ThreadKey;
   int m_DeleteKeyOnExit;
};

// An optimization to use the thread specific pointer itself
// as the integer in order to avoid an extra memory allocation
// to store the value.
//
class CORthreadLocalLong{
public:
   typedef intptr_t Type;
   CORthreadLocalLong(int DeleteKeyOnExit = 1);
   Type get() const           { return (Type)m_tls.getSpecific(); }
   operator Type() const      { return (Type)m_tls.getSpecific(); }
   void set(Type value)       { m_tls.setSpecific((void*)value); }
   void operator=(Type value) { m_tls.setSpecific((void*)value); }
private:
   CORthreadLocalLong(const CORthreadLocalLong&);
   CORthreadLocalLong& operator=(const CORthreadLocalLong&);
private:
   mutable CORthreadLocalBase m_tls;
};

template <typename Type>
class CORthreadLocal : public CORthreadLocalBase{
public:
   CORthreadLocal() : CORthreadLocalBase(&destroy) { }
   ~CORthreadLocal() { }

   // Does this thread local object exist?
   // Do not create one if it does not.
   bool exists() const{
      const Type* value = (const Type*)getSpecific();
      return value != 0;
   }

   Type* getPointer()             { return getPointerPrivate(); }
   const Type* getPointer() const { return getPointerPrivate(); }

   Type& get()                    { return *getPointerPrivate(); }
   const Type& get() const        { return *getPointerPrivate(); }
   operator Type&()               { return *getPointerPrivate(); }

   Type& operator=(const Type& value) { return *set(value); }

   Type* set(const Type& value){
      Type* p = getPointerPrivate();
      *p = value;
      return p;
   }

private:
   CORthreadLocal(const CORthreadLocal&); // disallow
   CORthreadLocal& operator=(const CORthreadLocal&); // disallow

   Type* getPointerPrivate(){
      Type* value = (Type*)getSpecific();
      if (value == 0){
         // memory must be zeroed and strictly aligned.
         char* mem = (char*)new double[(sizeof(Type) + sizeof(double) - 1) / sizeof(double)];
         memset(mem, 0, sizeof(Type));
         value = new (mem) Type;
         setSpecific(value);
      }
      return value;
   }

   static void destroy(void* value){
      // Because the Type used the placement new operator we must
      // invoke the destructor directly and then free it manually.
      ((Type*)value)->~Type();
      delete [] (double*)value;
   }
};

