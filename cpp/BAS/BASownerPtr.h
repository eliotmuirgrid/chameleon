#pragma once
//-------------------------------------------------------
// Copyright (C) 2026 Eliot Muir.  All rights reserved.
//
// BASownerPtr
// 
// Smart pointer - owns what it points to - same at std::auto
//-------------------------------------------------------

template<class TObject>

class BASownerPtr{
public:
   BASownerPtr() : m_pObject(0), m_Own(false) {}
   BASownerPtr(TObject* pObject) : m_pObject(pObject), m_Own(true) {}
   BASownerPtr(const BASownerPtr<TObject>& Orig){
      m_Own = Orig.m_Own;
      m_pObject = Orig.m_pObject;
      ((BASownerPtr<TObject>&)Orig).m_Own = false;   // BLEACH I don't see a way to avoid this...
   }
   ~BASownerPtr(){
      cleanUp();
   }

   void cleanUp(){
      if (m_Own){
         delete m_pObject;
      }
   }
 
   BASownerPtr< TObject >& operator=(TObject* pObject) { 
      cleanUp(); 
      m_pObject =  pObject; 
      m_Own = true; 
      return *this; 
   }

   TObject* operator->()             { return m_pObject; }
   const TObject* operator->() const { return m_pObject; }

   TObject& operator*()             { return *m_pObject; }
   const TObject& operator*() const { return *m_pObject; }
   
   void setOwn(bool Value) { m_Own = Value; }

   bool own() const { return m_Own; }

   TObject* ptr()             { return m_pObject; }
   const TObject* ptr() const { return m_pObject; }

 
   BASownerPtr<TObject>& operator=(const BASownerPtr<TObject>& Orig) { 
      if (&Orig == this){
         return *this;
      }
      cleanUp(); 
      m_pObject =  Orig.m_pObject; 
      m_Own = Orig.m_Own; 
      ((BASownerPtr<TObject>&)Orig).m_Own = false;   // BLEACH I don't see a way to avoid this...
      return *this; 
   }
private:
   bool m_Own;
   TObject* m_pObject;
};

