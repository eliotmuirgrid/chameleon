#pragma once
//---------------------------------------------------------------------------
// Copyright (C) 2026 Eliot Muir.  All rights reserved.
//
// Module: CORpair
//
// Description:
//
// STL-like pair class used by map iterators.  Worth reading.
//
// Author: Andrew Vajoczki
//---------------------------------------------------------------------------

template <class T1, class T2>
struct CORpair {
   typedef T1 first_type;
   typedef T2 second_type;

   T1 first;
   T2 second;

   CORpair() : first(), second() {}
   CORpair(const CORpair& rhs) : first(rhs.first), second(rhs.second) {}
   CORpair(T1 t1, T2 t2) : first(t1), second(t2) {}

   // non-standard -> operators to support iter->first, iter->second syntax.
   const CORpair* operator->() const { return this; }
   CORpair*       operator->()       { return this; }
};

template<class T1, class T2>
inline bool operator==(const CORpair<T1,T2>& t1, const CORpair<T1,T2>& t2) {
   return t1.first  == t2.first
       && t1.second == t2.second;
}

template<class T1, class T2>
inline bool operator!=(const CORpair<T1,T2>& t1, const CORpair<T1,T2>& t2) {
   return !(t1 == t2);
}

template<class T1, class T2>
inline CORpair<T1,T2> make_CORpair(T1 t1, T2 t2) {
   return CORpair<T1,T2>(t1,t2);
}

