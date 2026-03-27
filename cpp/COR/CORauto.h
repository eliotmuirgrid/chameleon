#pragma once
//---------------------------------------------------------------------------
// Copyright (C) 2026 Eliot Muir.  All rights reserved.
//
// Module: CORauto
//
// Description:
//
// Smart Owner Pointer Class.
//
// {
//    CORauto<Foo> pFoo = new Foo();
//
//    // when pFoo goes out of scope it will delete the Foo() object
//    // since it owns it.
// } <--- Foo deleted here.
//
// Note that it can be dangerous to use this in a collection class.
// For example, CORarray< CORauto<X> >.
// It will technically work, unless you do the following:
//
// CORarray< CORauto<X> > V;
// V.push_back(new X);
// CORauto<X> pX = V[0]; // bad bad bad!  Now when pX goes out of scope,
//                       // V[0] will have a bad pointer.
// const X* pX = V[0].get(); // this is better, if you absolutely must
//                           // use CORarray< CORauto<X> >.
//
// See http://stackoverflow.com/questions/111478/why-is-it-wrong-to-use-stdauto-ptr-with-standard-containers.
//
// Eliot - I recommend reading this carefully and understanding how ownership of
// that which is pointed to gets tranfered from one CORauto to another with the assignment
// operator.
//
// Author: Ryan Dewsbury
//---------------------------------------------------------------------------

#include <COR/CORerror.h>

template<class TemplateClass>
class CORauto {
public:
   CORauto() : pObject(NULL), IsOwner(false) {}
   
   CORauto(TemplateClass* ipObject, bool iIsOwner = true)
    : pObject(ipObject), IsOwner(iIsOwner) {}
   
   // use this to assign what CORauto points to
   // NOTE: If you'd like to make CORauto point
   // to something it doesn't own, call setIsOwner(false);
   // after calling this function.
   CORauto<TemplateClass>& operator=(TemplateClass* ipObject) { 
      cleanUpPointer();
      pObject = ipObject; 
      IsOwner = true; 
      return *this; 
   }
   
   CORauto(const CORauto<TemplateClass>& Pointer)
   : pObject(Pointer.pObject),IsOwner(Pointer.IsOwner){ 
      ((CORauto<TemplateClass>&) Pointer).IsOwner = false; 
   }
   
   CORauto<TemplateClass>& operator=(const CORauto<TemplateClass>& Pointer) {
      if (&Pointer != this) {
         cleanUpPointer();
         pObject = Pointer.pObject;
         IsOwner = Pointer.IsOwner;
         ((CORauto< TemplateClass >&)Pointer).IsOwner = false;
      }
      return *this;
   }

   ~CORauto() { 
      try {
         cleanUpPointer();  
      } catch (const CORerror& Error) {
         //COR_LOG(Error);
      }
   }

   //access operators
   TemplateClass& operator *()             { return *pObject; }
   const TemplateClass& operator *() const { return *pObject; } 
   operator TemplateClass&()               { return *pObject; } 
   operator const TemplateClass&() const   { return *pObject; }  
   
   operator TemplateClass*()               { return pObject; } 
   operator const TemplateClass*() const   { return pObject; }  
   
   TemplateClass* operator->() { 
      CORASSERT(pObject); // #10840 it seems a crash is more useful
      return pObject; 
   }
   
   const TemplateClass* operator->() const { 
      CORASSERT(pObject); // #10840 it seems a crash is more useful
      return pObject; 
   }

   const TemplateClass* get() const { return pObject; }
   TemplateClass*  get()            { return pObject; }
   bool isOwner() const             { return IsOwner; }
   void setIsOwner(bool BeOwner)    { IsOwner = BeOwner; }

   TemplateClass* release() {
      if (IsOwner) {
         TemplateClass* p = pObject;
         IsOwner = false;
         pObject = 0;
         return p;
      }
      return 0;
   }

private:
   void cleanUpPointer()
   { 
      if( IsOwner ) {
         delete pObject; 
         pObject=0;
      }
   }

   bool IsOwner;
   TemplateClass* pObject;
};
