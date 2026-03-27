#pragma hdrstop
//-----------------------------------------------------------------------------
// Copyright (C) 2026 Eliot Muir.  All rights reserved.
//
// Module:      CORmap
//
// Description:
//
// It's worth having a read through this file.
//
// Templated key/value map collection class with non-unique keys.
// Elements are sorted by key. A custom compare function can be supplied.
//
// CORmap is patterned after its STL equivalent.
// If CORmap is populated with unique keys it emulates an STL map class.
// If CORmap is populated with non-unique keys, it is similar to STL multimap.
//
//    CORmap<CORstring,int> MyMap;
//
//    // map style with unique keys
//    MyMap["foo"] = 123;
//    MyMap["bar"] = 88;
//    MyMap["baz"] = -400;
//
//    // multimap style with non-unique keys
//    MyMap.emplace("orange", 84);
//    MyMap.emplace("green", 99);
//    MyMap.emplace("green", 111);
//
//    CORmap<CORstring,int>::iterator it = MyMap.begin(), E = MyMap.end();
//    // output will be ordered by key
//    for (; it != E; ++it) {
//       CORcout << "key = " << it->first
//               << ", value = " << it->second << newline;
//    }
//    if (int Count = MyMap.count("green")) {
//       CORcout << "element green exists with count of " << Count << newline;
//    }
//    CORmap<CORstring,int>::const_iterator ci = MyMap.find("bar");
//    if (ci != MyMap.cend()) {
//       CORcout << "Found item with key = " << ci->first
//               << ", value = " << ci->second << newline;
//    }
//
// Output:
//
//    key = bar, value = 88
//    key = baz, value = -400
//    key = foo, value = 123
//    key = green, value = 99
//    key = green, value = 111
//    key = orange, value = 84
//    element green exists with count of 2
//    Found item with key = bar, value = 88
//
// CORmap also supports legacy CORmapPlace iteration which is deprecated
// and discouraged for new code.
//
// See http://www.cplusplus.com/reference/map/ for more info.
//
// The implementation of this class uses an embedded AVL tree (CORavlTree).
//
// Author: Ian Farquharson
//
// Author: Andrew Vajoczki - added STL style methods and iterators.
//-----------------------------------------------------------------------------

#include <COR/CORerror.h>
#include <COR/CORpair.h>

/***************************\
*                           *
* AVL Tree collection class *
*                           *
\***************************/

struct CORavlTreeNode
{
   CORavlTreeNode*   Up;         // 3-cornered node
   CORavlTreeNode*   Left;
   CORavlTreeNode*   Right;
   int            Balance;    // required for the tree re-balancing

   CORavlTreeNode();
};

typedef CORavlTreeNode*  CORavlTreePlace;

struct CORavlTreeBaseContext;    // used for zapping a node

class CORavlTreeBase{
private:
   CORavlTreePlace  RootNode;    // top of the tree
   CORindex      NodeCount;   // number of nodes in the tree
public:
   CORavlTreeBase();
   virtual ~CORavlTreeBase() {}

   CORindex size() const { return NodeCount; }
   bool empty() const { return 0 == this->size(); }

   void clear();
   void remove(CORavlTreePlace Place);

   CORavlTreePlace first() const;
   CORavlTreePlace last() const;
   CORavlTreePlace previous(CORavlTreePlace Place) const;
   CORavlTreePlace next(CORavlTreePlace Place) const;
protected:
   bool removeItem(const void* Key);
   CORavlTreePlace addItem(const void* Key, CORavlTreePlace Item);
   CORavlTreePlace addUniqueItem(const void* Key, CORavlTreePlace Item);
   CORavlTreePlace findFirstItem(const void* Key) const;
   CORavlTreePlace findItem(const void* Key) const;
   CORavlTreePlace findNearestItem(const void* Key) const;
   CORavlTreePlace findBelowItem(const void* Key) const;
   CORavlTreePlace findAboveItem(const void* Key) const;
protected:
   virtual void destroyItem(CORavlTreePlace Place) = 0;
   virtual int compareKey(const void* Key, CORavlTreePlace Place) const = 0;
private:
   CORavlTreePlace downLeft(CORavlTreePlace Place) const;
   CORavlTreePlace downRight(CORavlTreePlace Place) const;
   CORavlTreePlace upLeft(CORavlTreePlace Place) const;
   CORavlTreePlace upRight(CORavlTreePlace Place) const;
   CORavlTreePlace insertIt(const void* Key, CORavlTreePlace Item, CORavlTreePlace& CurrNode, CORavlTreePlace NodeAbove, bool& Higher, bool Unique);
   bool zapIt(CORavlTreeBaseContext& Context, CORavlTreePlace& CurrNode, bool& Higher);
   bool zapIt(const void* Key, CORavlTreePlace& CurrNode, bool& Higher);
#ifdef COR_ENABLE_INVARIANT_INTEGRITY_CHECK
   void testLinkage(CORavlTreePlace Place) const;
   void invariant() const;
#else
   void invariant() const {}
#endif
   CORavlTreeBase(const CORavlTreeBase& Tree);               // disable copy constructor
   CORavlTreeBase& operator =(const CORavlTreeBase& Tree);   // disable assignment
};

template <class KeyType, class Type>
struct CORavlTreeItemNode: public CORavlTreeNode
{
   KeyType  Key;
   Type     Item;
   CORavlTreeItemNode(const KeyType& TheKey, const Type& TheItem): Key(TheKey), Item(TheItem) {}
};

template <class KeyType, class Type>
class CORavlTree: public CORavlTreeBase {
public:
   typedef CORint32 (*CompareProc)(const KeyType& Key1, const KeyType& Key2);
   CORavlTree(CompareProc TheCompareProc)
   : Compare(TheCompareProc) {
   }
   virtual ~CORavlTree() {
      clear(); 
   }
   Type& operator [](CORavlTreePlace Place) {
      CORPRECONDITION(Place != NULL);
      return((CORavlTreeItemNode<KeyType, Type>*) Place)->Item;
   }
   const Type& operator [](CORavlTreePlace Place) const {
      CORPRECONDITION(Place != NULL);
      return((CORavlTreeItemNode<KeyType, Type>*) Place)->Item;
   }
   const KeyType& key(CORavlTreePlace Place) const {
      CORPRECONDITION(Place != NULL);
      return((CORavlTreeItemNode<KeyType, Type>*) Place)->Key;
   }
   bool removeKey(const KeyType& Key) {
      return this->removeItem(&Key);
   }
   CORavlTreePlace add(const KeyType& Key, const Type& Item) {
      return this->addItem(&Key, new CORavlTreeItemNode<KeyType, Type>(Key, Item));
   }
   CORavlTreePlace addUnique(const KeyType& Key, const Type& Item) {
      return this->addUniqueItem(&Key, new CORavlTreeItemNode<KeyType, Type>(Key, Item));
   }
   //returns the first place matching the key, or null if the key isn't mapped
   CORavlTreePlace findFirst(const KeyType& Key) const {
      return this->findFirstItem(&Key);
   }
   CORavlTreePlace findNearest(const KeyType& Key) const {
      return this->findNearestItem(&Key);
   }
   CORavlTreePlace findBelow(const KeyType& Key) const {
      return this->findBelowItem(&Key);
   }
   CORavlTreePlace findAbove(const KeyType& Key) const {
      return this->findAboveItem(&Key);
   }
protected:
   virtual void destroyItem(CORavlTreePlace Place) {
      delete (CORavlTreeItemNode<KeyType, Type>*) Place;
   }
   virtual int compareKey(const void* Key, CORavlTreePlace Place) const {
      return Compare(*(KeyType*) Key, ((CORavlTreeItemNode<KeyType, Type>*) Place)->Key);
   }
private:
   CompareProc Compare;
};

typedef CORavlTreePlace CORmapPlace;

// This template provides an easier way to construct sorted lists without writing 
// compare functions.
// 
// This compare function is used as the default depends on the < operator of the Type.
//
// To specify a completely different compare function, use the one that doesn't use > and < operators
// simply pass in the third parameter for CORmap as a new class.
// Note that this means that an external compare class must contain the static function of the prototype
//
// static int compare(const Type& A, const Type& B);
//
// neither the external compare class nor the compare function itself needs to be templated.
template <class Type>
class CORmapCompare {
public:
   //generic implementation - only use operator<()
   static int compare(const Type& A, const Type& B) {
      if (B < A) {
         return 1;
      } else if (A < B) {
         return -1;
      }
      return 0;
   }
};

//CORstring specialization
template <>
class CORmapCompare<CORstring>{
public:
   static int compare( const CORstring& A, const CORstring& B ){
     return A.compare(B);
   }
};

// Case-insensitive CORstring specialization.
class CORmapCaseInsensitiveCompare{
public:
   static int compare( const CORstring& A, const CORstring& B ){
     return A.icompare(B);
   }
};

template <class KeyType, class Type, class CompareType = CORmapCompare<KeyType> >
class CORmap : public CORavlTree<KeyType, Type>{
public:
   //public typedefs for generic functions
   typedef KeyType      TKey;
   typedef Type         TValue;
   typedef CORmapPlace  TPlace;

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
         CORASSERT(that.map_ == this->map_);
         return this->place_ == that.place_;
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
      operator CORavlTreePlace() const { return place_; } // for legacy find()
      const KeyType& key() const { return map_->key(place_); }
      Type& value() { return map_->operator[](place_); }
      //
      // not public interface - treat as private
      //
      iterator(CORmap<KeyType,Type,CompareType>* m, CORavlTreePlace p) : map_(m), place_(p) { }
      CORmap<KeyType,Type,CompareType>* map_;
      CORavlTreePlace place_;
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
         CORASSERT(that.map_== this->map_);
         return that.place_ == this->place_;
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
      operator CORavlTreePlace() const { return place_; } // for legacy find()
      const KeyType& key() const { return map_->key(place_); }
      const Type& value() const { return map_->operator[](place_); }
      //
      // not public interface - treat as private
      //
      const_iterator(const CORmap<KeyType,Type,CompareType>* m, CORavlTreePlace p) : map_(m), place_(p) { }
      const CORmap<KeyType,Type,CompareType>* map_;
      CORavlTreePlace place_;
   };

   iterator       begin()        { return       iterator(this, CORavlTreeBase::first()); }
   const_iterator begin()  const { return const_iterator(this, CORavlTreeBase::first()); }
   const_iterator cbegin() const { return const_iterator(this, CORavlTreeBase::first()); }

   iterator       end()          { return       iterator(this, NULL); }
   const_iterator end()  const   { return const_iterator(this, NULL); }
   const_iterator cend() const   { return const_iterator(this, NULL); }

   // legacy CORavlTreePlace find(const KeyType& Key) const replaced with iterator versions.
   // iterator classes have an operator CORavlTreePlace() method for backwards compatibility.
   //
   const_iterator find(const KeyType& Key) const {
      return const_iterator(this, this->findItem(&Key));
   }
   iterator find(const KeyType& Key) {
      return iterator(this, this->findItem(&Key));
   }

   iterator lower_bound(const KeyType& Key) {
      // As per the standard, find the lowest map element whose key is equal to
      // OR GREATER than the target Key.  Return end() if no such key is found.
      iterator it = iterator(this, this->findBelowItem(&Key));
      if (this->size() && this->end() == it) {
         // Special case if Key is less than the first element's key.
         return this->begin();
      }
      while (it != this->end() && CompareType::compare(it->first,Key) < 0) {
         ++it;
      }
      return it;
   }
   const_iterator lower_bound(const KeyType& Key) const {
      return const_cast<CORmap*>(this)->lower_bound(Key);
   }

   iterator upper_bound(const KeyType& Key) {
      // As per the standard, find the first element whose key is AFTER Key.
      // Return end() if no keys are found after Key.
      return iterator(this, this->findAboveItem(&Key));
   }
   const_iterator upper_bound(const KeyType& Key) const {
      return const_cast<CORmap*>(this)->upper_bound(Key);
   }

   CORpair<iterator,iterator> equal_range(const KeyType& Key) {
      return CORpair<iterator,iterator>(this->lower_bound(Key), this->upper_bound(Key));
   }
   CORpair<const_iterator,const_iterator> equal_range(const KeyType& Key) const {
      return CORpair<const_iterator,const_iterator>(this->lower_bound(Key), this->upper_bound(Key));
   }

   int count(const KeyType& Key) const {
      int n = 0;
      const_iterator it = this->lower_bound(Key);
      for (; it != this->end() && CompareType::compare(it->first,Key)==0; ++it) {
         ++n;
      }
      return n;
   }

   void emplace(const KeyType& Key, const Type& Item) {
      this->add(Key, Item);
   }

   iterator erase(iterator position) {
      CORASSERT(this == position.map_); // iterator must match map instance
      if (position.place_) {
         CORavlTreePlace Next = this->next(position.place_);
         this->remove(position.place_);
         return iterator(this, Next);
      }
      // it is not an error to erase(end())
      return this->end();
   }

   iterator erase(const KeyType& key) {
      return this->erase(this->find(key));
   }

   CORmap(): CORavlTree<KeyType, Type>( CompareType::compare ) {}
   CORmap(typename CORavlTree<KeyType, Type>::CompareProc TheCompareProc): CORavlTree<KeyType, Type>(TheCompareProc) {}
   CORmap(const CORmap& that) : CORavlTree<KeyType,Type>(CompareType::compare) {
      CORavlTree<KeyType,Type>& me = *this;
      for (auto i = that.cbegin(); i!= that.cend(); i++){
         me.add(i->first, i->second);
      }
   }
   CORmap& operator=(const CORmap& that) {
      if (this != &that) {
         CORavlTree<KeyType,Type>& me = *this;
         me.clear();
         for (auto i = that.cbegin(); i!= that.cend(); i++){
            me.add(i->first, i->second);
         }
      }
      return *this;
   }
   Type& operator[](const KeyType& key) {
      CORavlTree<KeyType,Type>& me = *this;
      TPlace place = this->find(key);
      if (place==NULL)
         place = this->addUnique(key, TValue());
      return me.operator[](place);
   }
   const Type& operator[](const KeyType& key) const {
      const CORavlTree<KeyType,Type>& me = *this;
      TPlace place = this->find(key);
      CORPRECONDITION(place != NULL);
      return me.operator[](place);
   }
   const Type& operator[](CORavlTreePlace place) const {
      const CORavlTree<KeyType,Type>& me = *this;
      return me[place];
   }
   Type& operator[](CORavlTreePlace place) {
      CORavlTree<KeyType,Type>& me = *this;
      return me[place];
   }
};

CORostream& operator<<(CORostream& Stream, const CORmap<CORstring, CORstring>& Map);

