#pragma once
//-------------------------------------------------------
// Copyright (C) 2026 Eliot Muir.  All rights reserved.
//
// BASvar
// 
// A variant class which maps very closely to a JSON object.
// It's a generic container which is valuable for storing data.
//-------------------------------------------------------

#include <BAS/BASstring.h>

class BASvar;

template<class BASvar> class BASvector;
template<class BASstring, class BASvar> class BASdictOrdered;

class BASstream;

class BASvar{
public:
   BASvar();
   BASvar(int Value);
   BASvar(double Value);
   BASvar(const BASstring& Value);
   
   ~BASvar();

   enum Type{
      None = 0, 
      Integer,
      Double,
      String,
      Vector,
      Table
   };

   Type type() const { return m_Type; }

   BASvar& operator[](int i);
   BASvar& operator[](const BASstring& Key);

   double           asDouble() const { return m_Data.Double; }
   int              asInt()    const { return m_Data.Int;    }
   const BASstring& asString() const { return *m_Data.pString; }
   const BASdictOrdered<BASstring, BASvar>& asTable() const { return *m_Data.pTable; }
   const BASvector<BASvar>& asVector() const { return *m_Data.pVec; }


   union Variant{
      int       Int;   // should I use a long?
      double    Double;
      BASstring* pString;
      BASvector<BASvar>* pVec;
      BASdictOrdered<BASstring, BASvar>* pTable;
   };

   BASvar& operator=(int Value);
   BASvar& operator=(double Value);
   BASvar& operator=(const BASstring& Value);

   BASstring json(int Indent=0) const;

private:
 
   Variant m_Data;
   Type m_Type;
};

BASstream& operator<<(BASstream& Stream, const BASvar& Var);

