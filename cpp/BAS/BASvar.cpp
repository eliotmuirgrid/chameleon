//-------------------------------------------------------
// Copyright (C) 2026 Eliot Muir.  All rights reserved.
//
// BASvar
// 
// Implementation
//-------------------------------------------------------
#include <BAS/BASvar.h>
#include <BAS/BASvector.h>
#include <BAS/BASavlTree.h>
#include <BAS/BASsinkString.h>

#include <BAS/BAStrace.h>
BAS_TRACE_INIT;

BASvar::BASvar(){
   BAS_METHOD(BASvar::BASvar-none);
   m_Type = None;
}

BASvar::BASvar(int Value){
   BAS_METHOD(BASvar::BASvar-int);
   m_Data.Int = Value;
   m_Type = Integer;
}

BASvar::BASvar(double Value){
   BAS_METHOD(BASvar::BASvar-double);
   m_Data.Double = Value;
   m_Type = Double;
}

BASvar::BASvar(const BASstring& Value){
   BAS_METHOD(BASvar::BASvar-String);
   m_Data.pString = new BASstring(Value);
   m_Type = BASvar::String;
}

static void CleanVar(BASvar::Variant* pVariant, BASvar::Type* pType){
   BAS_FUNCTION(CleanVar);
   BAS_VAR(*pType);
   switch(*pType){
   case BASvar::String:
      delete pVariant->pString;
      break;
   case BASvar::None:
   case BASvar::Integer: 
   case BASvar::Double:
      break;
   case BASvar::Vector:{
         delete pVariant->pVec;
         pVariant->pVec = NULL;
      }
      break;
   case BASvar::Table:{
         delete pVariant->pTable;
         pVariant->pTable = NULL;
      }
      break;
   }
   *pType = BASvar::None;
}

BASvar::~BASvar(){
   BAS_METHOD(BASvar::~BASvar);
   CleanVar(&m_Data, &m_Type);
}

BASvar& BASvar::operator[](int i){
   BAS_METHOD(BASvar::operator[]-int);
   switch(m_Type){
   case BASvar::String:{
         delete m_Data.pString; 
         m_Data.pVec = NULL;
         m_Type = BASvar::Vector; 
      }
      break;
   case BASvar::Table:{
         delete m_Data.pTable;
         m_Data.pVec = NULL;
         m_Type = BASvar::Vector; 
      }
      break;
   case BASvar::Double:
   case BASvar::Integer:
   case BASvar::None:{
         m_Data.pVec = NULL;
         m_Type = BASvar::Vector;  // fall through
      }
      break;
   case BASvar::Vector:
      break;
      // do nothing;
   };

   if (NULL == m_Data.pVec){
      m_Data.pVec = new BASvector<BASvar>();
   }
   if (m_Data.pVec->size() <= i){
      m_Data.pVec->resize(i+1);
   }
   return (*m_Data.pVec)[i];
}

BASvar& BASvar::operator[](const BASstring& Key){
   BAS_METHOD(BASvar::operator[]-string);
   switch(m_Type){
   case BASvar::String:{
         delete m_Data.pString; // fall through
         m_Type = BASvar::Table;
         m_Data.pTable = NULL;
      }
      break;
   case BASvar::Vector:{
         delete m_Data.pVec;  // TODO - could convert to a table?
         m_Type = BASvar::Table;
         m_Data.pTable = NULL;
      }
      break;
   case BASvar::Double:
   case BASvar::Integer:
   case BASvar::None:
      m_Data.pTable = NULL;
      m_Type = BASvar::Table;
   case BASvar::Table:
      break; // do nothing
   }
   if (NULL == m_Data.pTable){
      m_Data.pTable = new BASavlTree<BASstring,BASvar>();
   }
   return (*m_Data.pTable)[Key];
}

BASvar& BASvar::operator=(int Value){
   BAS_METHOD(BASvar::operator=int);
   CleanVar(&m_Data, &m_Type);
   m_Data.Int = Value;
   m_Type = BASvar::Integer;
   return *this;
}

BASvar& BASvar::operator=(double Value){
   BAS_METHOD(BASvar::operator=int);
   CleanVar(&m_Data, &m_Type);
   m_Data.Double = Value;
   m_Type = BASvar::Double;
   return *this;
}

BASvar& BASvar::operator=(const BASstring& Value){
   BAS_METHOD(BASvar::operator=int);
   CleanVar(&m_Data, &m_Type);
   m_Data.pString = new BASstring(Value);
   m_Type = BASvar::String;
   return *this;
}

void BASescapeJsonString(BASstream& Stream, const BASstring& String){
   BAS_FUNCTION(BASescapeJsonString);
   const char* i = String.data();
   const char* pEnd = i + String.size();
   for (;i != pEnd; ++i){
      switch(*i){
      case '\"':
         Stream << "\\\"";
         break;
      default:
         Stream << *i;
      }
   }
}

void BASjson(BASstream& Stream, const BASvar& Var, int Indent){
   switch(Var.type()){
   case BASvar::None:
      Stream.sink()->write("null", 4);
   case BASvar::Double:
      Stream << Var.asDouble();
      break;
   case BASvar::Integer:
      Stream << Var.asInt();
      break;
   case BASvar::String:
      Stream << "\"";
      BASescapeJsonString(Stream, Var.asString());
      Stream << "\"";
      break;
   case BASvar::Vector:{
         Stream << "[";
         bool IsFirst = true;
         auto End = Var.asVector().cend();
         for (auto i= Var.asVector().cbegin(); i != End; ++i){
            if (!IsFirst){
               Stream << ",";
            } else {
               IsFirst = false;
            }
            BASjson(Stream, *i, Indent);
         }
         Stream << "]";
      }
      break;
   case BASvar::Table:{
         Stream << "{";
         bool IsFirst = true;
         auto End = Var.asTable().cend();
         for (auto i= Var.asTable().cbegin(); i != End; ++i){
            if (!IsFirst){
               Stream << ",";
            } else {
               IsFirst = false;
            }
            Stream << "\"";
            BASescapeJsonString(Stream, i.key());
            Stream <<  "\":";
            BASjson(Stream, i.value(), Indent);
         }
         Stream << "}";
      }
      break;
   }
}

BASstring BASvar::json(int Indent) const{
   BAS_METHOD(BASvar::json);
   BASsinkString Sink;
   BASstream Json(Sink);
   BASjson(Json, *this, Indent);
   
   return Sink.string();
}