#pragma once
//-----------------------------------------------------------------------------
// Copyright (C) 2026 Eliot Muir.  All rights reserved.
//
// Module:      CORhashmap
//
// Description:
//
// Very much worth having a read through this critical data-structure - Eliot.
//
// Unordered templated key/value hash map collection class with unique keys.
//
// CORhashmap is patterned after the STL unordered_map class.
//
//    CORhashmap<CORstring,int> MyMap;
//
//    MyMap["foo"] = 40;
//    MyMap["bar"] += 55;
//    MyMap["bar"] = 123;
//    MyMap["baz"] += 11;
//    MyMap["foo"] -= 333;
//    MyMap["bar"] -= 200;
//    MyMap["baz"] += 99;
//
//    // output will be unordered
//    for (auto it=MyMap.begin(), auto E= MyMap.end(); it != E; ++it) {
//       CORcout << "key = " << it->first
//               << ", value = " << it->second << newline;
//    }
//    if (int Count = MyMap.count("foo")) {
//       CORcout << "element foo exists with count of " << Count << newline;
//    }
//    auto ci = MyMap.find("bar");
//    if (ci != MyMap.cend()) {
//       CORcout << "Found item with key = " << ci->first
//               << ", value = " << ci->second << newline;
//    }
//
// Output:
//
//    key = bar, value = -77
//    key = foo, value = -293
//    key = baz, value = 110
//    element foo exists with count of 1
//    Found item with key = bar, value = -77
//
// CORhashmap also supports legacy CORhashmapPlace iteration which is
// deprecated and discouraged for new code.
//
// See http://www.cplusplus.com/reference/unordered_map/unordered_map/
//
// A custom hash function can be supplied to the class.
// It is defaulted for common key types like CORstring and numbers.
//
// When a collection is constructed it is passed a hash function that
// returns a CORindex.
//
// CORindex HashProc(const KeyType& Key);
//
// The operator == is used to test that keys match.
//
// The objects stored in the template must support the copy contructor
// Type(const Type&)
//
// A copy is made of an item when it is inserted into the list. When
// an item is removed from the list it is destructed.
//
// Author: Ian Farquharson
//
// Author: Andrew Vajoczki - added STL style methods and iterators.
//-----------------------------------------------------------------------------

#include <COR/CORerror.h>
#include <COR/CORhash.h>
#include <COR/CORpair.h>

class CORhashmapBaseNode{
public:
   CORhashmapBaseNode* Next;
};

typedef CORhashmapBaseNode* CORhashmapPlace;

class CORvoidLookup{
private:
   CORhashmapPlace*   Buckets;
   const CORindex*   pCountOfBucket;
   CORindex          Size;
   void init(void);
   inline void grow(void);
public:
   CORvoidLookup(void) { init(); }
   virtual ~CORvoidLookup(void);
   CORindex size(void) const { return Size; }
   void clear(void);
   void remove(CORhashmapPlace Place);
   CORindex countOfBucket() const;
   CORindex countOfBucketItem(CORindex BucketIndex) const;
   CORhashmapPlace first(void) const;
   CORhashmapPlace last(void) const;
   CORhashmapPlace previous(CORhashmapPlace Place) const;
   CORhashmapPlace next(CORhashmapPlace Place) const;
protected:
   bool removeItem(CORindex Hash, const void* Key);
   CORhashmapPlace addItem(CORindex Hash, const void* Key, CORhashmapPlace Node);
   CORhashmapPlace findItem(CORindex Hash, const void* Key) const;
protected:
   virtual void destroyItem(CORhashmapPlace Place) = 0;
   virtual CORindex hashItem(CORhashmapPlace Place) const = 0;
   virtual bool equalKey(const void* Key, CORhashmapPlace Place) const = 0;
private:
   CORvoidLookup(const CORvoidLookup& Lookup);               // disable copy constructor
   CORvoidLookup& operator =(const CORvoidLookup& Lookup);   // disable assignment
#ifdef COR_ENABLE_INVARIANT_INTEGRITY_CHECK
   void invariant(void) const;
#else
   void invariant(void) const {}
#endif
};

template <class KeyType, class Type>
struct CORhashmapNode: public CORhashmapBaseNode{
   CORindex Hash;
   KeyType  Key;
   Type     Item;
   CORhashmapNode(CORindex iHash, const KeyType& iKey, const Type& iItem)
   : Hash(iHash), Key(iKey), Item(iItem) {}
};

template <class KeyType, class Type, class CompareType = CORhash<KeyType> >
class CORhashmap: public CORvoidLookup{
public:
   struct iterator {
      iterator() : map_(NULL), place_(NULL) { }
      iterator(const iterator& that) : map_(that.map_), place_(that.place_) { }
      iterator& operator=(const iterator& that) {
         map_ = that.map_;
         place_ = that.place_;
         return *this;
      }
      iterator& operator++() {
         CORPRECONDITION(place_);
         place_ = map_->next(place_);
         return *this;
      }
      iterator operator++(int) {
         iterator tmp(*this);
         ++*this;
         return tmp;
      }
      iterator& operator--() {
         CORPRECONDITION(place_);
         place_ = map_->previous(place_);
         return *this;
      }
      iterator operator--(int) {
         iterator tmp(*this);
         --*this;
         return tmp;
      }
      bool operator==(const iterator& that) const {
         return that.map_   == this->map_
             && that.place_ == this->place_;
      }
      bool operator!=(const iterator& that) const {
         return !operator==(that);
      }
      // non-standard method to support (*iter).first, (*iter).second syntax
      CORpair<const KeyType&,Type&> operator*() {
         return CORpair<const KeyType&,Type&>(this->key(), this->value());
      }
      // non-standard method to support iter->first, iter->second syntax
      CORpair<const KeyType&,Type&> operator->() {
         return CORpair<const KeyType&,Type&>(this->key(), this->value());
      }
      //
      // non-STL methods
      //
      operator CORhashmapPlace() const { return place_; } // for legacy find()
      const KeyType& key() const { return map_->key(place_); }
      Type& value() { return map_->operator[](place_); }
      //
      // not public interface - treat as private
      //
      iterator(CORhashmap<KeyType,Type,CompareType>* m, CORhashmapPlace p) : map_(m), place_(p) { }
      CORhashmap<KeyType,Type,CompareType>* map_;
      CORhashmapPlace place_;
   };

   struct const_iterator {
      const_iterator() : map_(NULL), place_(NULL) { }
      const_iterator(const const_iterator& that) : map_(that.map_), place_(that.place_) { }
      const_iterator(const iterator& that) : map_(that.map_), place_(that.place_) { }
      const_iterator& operator=(const const_iterator& that) {
         map_ = that.map_;
         place_ = that.place_;
         return *this;
      }
      const_iterator& operator=(const iterator& that) {
         map_ = that.map_;
         place_ = that.place_;
         return *this;
      }
      const_iterator& operator++() {
         CORPRECONDITION(place_);
         place_ = map_->next(place_);
         return *this;
      }
      const_iterator operator++(int) {
         const_iterator tmp(*this);
         ++*this;
         return tmp;
      }
      const_iterator& operator--() {
         CORPRECONDITION(place_);
         place_ = map_->previous(place_);
         return *this;
      }
      const_iterator operator--(int) {
         const_iterator tmp(*this);
         --*this;
         return tmp;
      }
      bool operator==(const const_iterator& that) const {
         return that.map_   == this->map_
             && that.place_ == this->place_;
      }
      bool operator!=(const const_iterator& that) const {
         return !operator==(that);
      }
      // non-standard method to support (*iter).first, (*iter).second syntax
      CORpair<const KeyType&,const Type&> operator*() const {
         return CORpair<const KeyType&,const Type&>(this->key(), this->value());
      }
      // non-standard method to support iter->first, iter->second syntax
      const CORpair<const KeyType&,const Type&> operator->() const {
         return CORpair<const KeyType&,const Type&>(this->key(), this->value());
      }
      //
      // non-STL methods
      //
      operator CORhashmapPlace() const { return place_; } // for legacy find()
      const KeyType& key() const { return map_->key(place_); }
      const Type& value() const { return map_->operator[](place_); }
      //
      // not public interface - treat as private
      //
      const_iterator(const CORhashmap<KeyType,Type,CompareType>* m, CORhashmapPlace p) : map_(m), place_(p) { }
      const CORhashmap<KeyType,Type,CompareType>* map_;
      CORhashmapPlace place_;
   };

   bool empty() const { return 0 == this->size(); }

   iterator       begin()        { return iterator(this, this->first()); }
   const_iterator begin()  const { return const_iterator(this, this->first()); }
   const_iterator cbegin() const { return const_iterator(this, this->first()); }

   iterator       end()          { return iterator(this, NULL); }
   const_iterator end()  const   { return const_iterator(this, NULL); }
   const_iterator cend() const   { return const_iterator(this, NULL); }

   // determine whether key exists
   int count(const KeyType& Key) const {
      return this->find(Key) == this->end() ? 0 : 1;
   }

   iterator erase(iterator position) {
      CORASSERT(this == position.map_); // iterator must match map instance
      if (position.place_) {
         CORhashmapPlace Next = this->next(position.place_);
         this->remove(position.place_);
         return iterator(this, Next);
      }
      // it is not an error to erase(end())
      return this->end();
   }

   iterator erase(const KeyType& key) {
      return this->erase(this->find(key));
   }

   //public typedefs for generic functions
   typedef KeyType         TKey;
   typedef Type            TValue;
   typedef CORhashmapPlace TPlace;

   typedef CORindex (*HashProc)(const KeyType& Key);

   CORhashmap(): Hash(CompareType::defaultHash) {}
   CORhashmap(HashProc TheHashProc): Hash(TheHashProc) {}

   virtual ~CORhashmap(void) { 
      try {
         clear(); 
      }
      catch (const CORerror& Error) {
         // There was an error logged here...
      }
   }

   CORhashmap(const CORhashmap& Orig) : Hash(Orig.Hash) {
      *this = Orig;
   }

   CORhashmap& operator=(const CORhashmap&);

   Type& operator[](CORhashmapPlace Place) {
      CORPRECONDITION(Place != NULL);
      return ((CORhashmapNode<KeyType, Type>*) Place)->Item;
   }

   const Type& operator[](CORhashmapPlace Place) const {
      CORPRECONDITION(Place != NULL);
      return ((CORhashmapNode<KeyType, Type>*) Place)->Item;
   }
   
   KeyType& key(CORhashmapPlace Place) {
      CORPRECONDITION(Place != NULL);
      return ((CORhashmapNode<KeyType, Type>*) Place)->Key;
   }

   const KeyType& key(CORhashmapPlace Place) const {
      CORPRECONDITION(Place != NULL);
      return ((CORhashmapNode<KeyType, Type>*) Place)->Key;
   }

   Type& operator[](const KeyType& Key);
   const Type& operator[](const KeyType& Key) const;

   bool removeKey(const KeyType& Key) { return removeItem(Hash(Key), &Key); }

   CORhashmapPlace add(const KeyType& Key, const Type& Item);

   void emplace(const KeyType& Key, const Type& Item) {
      this->add(Key, Item);
   }

   // legacy CORhashmapPlace find(const KeyType& Key) const replaced with iterator versions.
   // iterator classes have an operator CORhashmapPlace() method for backwards compatibility.
   const_iterator find(const KeyType& Key) const {
      return const_iterator(this, findItem(Hash(Key),&Key));
   }
   iterator find(const KeyType& Key) {
      return iterator(this, findItem(Hash(Key),&Key));
   }

   template<class TClass>
   void iterate(void (TClass::*pMethodVoid)(const KeyType&,Type&),TClass* pInstance, CORhashmapPlace From = NULL, CORhashmapPlace To = NULL){
      if (!From) {
         From = this->first();
      }
      while (From != NULL) {
         (pInstance->*pMethodVoid)(this->key(From),this->operator[](From));
         if (To && To == From) {
            break;
         }
         From = this->next(From);
      }
   }

   template<class TClass>
   CORhashmapPlace iterate(CORhashmapPlace (TClass::*pMethodVoid)(const KeyType&,Type&,CORhashmapPlace CurrentPlace),TClass* pInstance, CORhashmapPlace From=NULL, CORhashmapPlace To=NULL){
      if (!From) {
         From = this->first();
      }
      while (From != NULL) {
         CORhashmapPlace Found = (pInstance->*pMethodVoid)(this->key(From),this->operator[](From),From);
         if (Found) {
            return Found;
         }
         if (To && To == From) {
            break;
         }
         From = this->next(From);
      }
      return NULL;
   }

protected:
   virtual void destroyItem(CORhashmapPlace Place) {
      delete (CORhashmapNode<KeyType, Type>*) Place;
   }
   virtual CORindex hashItem(CORhashmapPlace Place) const {
      return ((CORhashmapNode<KeyType, Type>*) Place)->Hash;
   }
   virtual bool equalKey(const void* Key, CORhashmapPlace Place) const {
      return CompareType::equalKey(*(KeyType*) Key,((CORhashmapNode<KeyType, Type>*) Place)->Key);
   }
private:
   HashProc Hash;
};

template <class K, class V, class Cmp>
CORhashmap<K,V,Cmp>& CORhashmap<K,V,Cmp>::operator=(const CORhashmap<K,V,Cmp>& That) {
   CORhashmapPlace Place;
   this->clear();
   for(Place = That.first(); Place; Place = That.next(Place)) {
      this->add(That.key(Place), That[Place]);
   }
   return *this;
}

template <class KeyType, class Type, class CompareType>
Type& CORhashmap<KeyType, Type, CompareType>::operator[](const KeyType& Key) {
   const CORindex HashValue = Hash(Key);
   CORhashmapPlace Place = this->findItem(HashValue,&Key);
   if (Place == NULL) {
      Place = this->addItem(HashValue, &Key, new CORhashmapNode<KeyType, Type>(HashValue, Key, Type()));
   }
   return ((CORhashmapNode<KeyType, Type>*) Place)->Item;
}

template <class KeyType, class Type, class CompareType>
const Type& CORhashmap<KeyType, Type, CompareType>::operator[](const KeyType& Key) const {
   CORhashmapPlace Place = this->find(Key);
   CORPRECONDITION(Place != NULL);
   return ((CORhashmapNode<KeyType, Type>*) Place)->Item;
}

template <class KeyType, class Type, class CompareType>
CORhashmapPlace CORhashmap<KeyType, Type, CompareType>::add(const KeyType& Key, const Type& Item) {
   CORindex HashValue = Hash(Key);
   return this->addItem(HashValue, &Key, new CORhashmapNode<KeyType, Type>(HashValue, Key, Item));
}


