#pragma once
//---------------------------------------------------------------------------
// Copyright (C) 2026 Eliot Muir.  All rights reserved.
//
// Module:      CORlist
//
// Description:
//
// Eliot - very much worth having a read through this class.
//
// Templated double linked list class patterned after STL list.
//
// See http://www.cplusplus.com/reference/list/list/ for examples.
//
// The objects stored in the template must support the copy contructor
// Type(const Type&)
//
// A copy is made of an item when it is inserted into the list.
// When an item is removed from the list it is destructed.
//
// Iteration with CORlistPlace is deprecated for new code.
// Use iterator or const_iterator instead.
//
// Author: Ian Farquharson
//
// Author: Andrew Vajoczki - added STL style methods and iterator
//---------------------------------------------------------------------------
#include <COR/CORerror.h>

struct CORlistNode {
   CORlistNode*  Previous;
   CORlistNode*  Next;
};

typedef CORlistNode* CORlistPlace;

class CORvoidList{
private:
   CORindex      Size;
   CORlistPlace  Head;
   CORlistPlace  Tail;
public:
   CORvoidList();
   virtual ~CORvoidList() {}
   CORindex size() const {return Size;}
   void clear();
   void remove(CORlistPlace Place);
   void exchange(CORlistPlace Place1, CORlistPlace Place2);
   CORlistPlace first() const { return Head; }
   CORlistPlace last() const { return Tail; }
   CORlistPlace previous(CORlistPlace Place) const;
   CORlistPlace next(CORlistPlace Place) const;
protected:
   CORlistPlace insertItem(CORlistPlace Item, CORlistPlace Place);
   CORlistPlace addItem(CORlistPlace Item);
protected:
   virtual void destroyItem(CORlistPlace Place) = 0;
private:
#ifdef COR_ENABLE_INVARIANT_INTEGRITY_CHECK
   void invariant() const;
#else
   void invariant() const {}
#endif
   CORvoidList(const CORvoidList& list);               // disable copy constructor
   CORvoidList& operator=(const CORvoidList& list);   // disable assignment
};

template <class Type>
struct CORlistItemNode: public CORlistNode{
   Type Item;
   CORlistItemNode(const Type& TheItem): Item(TheItem) {}
   CORlistItemNode() : Item() {}
};

template <class Type>
class CORlist : public CORvoidList{
public:
   struct iterator {
      CORlist<Type>* list_;
      CORlistPlace place_;
      iterator()
      : list_(NULL)
      , place_(NULL) {
      }
      iterator(const iterator& that)
      : list_(that.list_)
      , place_(that.place_) {
      }
      iterator& operator=(const iterator& that) {
         list_ = that.list_;
         place_ = that.place_;
         return *this;
      }
      iterator& operator++() {
         CORASSERT(list_);
         CORPRECONDITION(place_);
         place_ = list_->next(place_);
         return *this;
      }
      iterator operator++(int) {
         iterator tmp(*this);
         ++*this;
         return tmp;
      }
      iterator& operator--() {
         CORASSERT(list_);
         CORPRECONDITION(place_);
         place_ = list_->previous(place_);
         return *this;
      }
      iterator operator--(int) {
         iterator tmp(*this);
         --*this;
         return tmp;
      }
      Type& operator*() {
         CORASSERT(list_);
         CORPRECONDITION(place_);
         return list_->operator[](place_);
      }
      Type* operator->() {
         CORASSERT(list_);
         CORPRECONDITION(place_);
         return &(list_->operator[](place_));
      }
      bool operator==(const iterator& that) const {
         return that.list_  == this->list_
             && that.place_ == this->place_;
      }
      bool operator!=(const iterator& that) const {
         return !operator==(that);
      }
      // only to be used by CORlist class itself
      iterator(CORlist<Type>* list, CORlistPlace place) : list_(list) , place_(place) { }
   };

   struct const_iterator {
      const CORlist<Type>* list_;
      CORlistPlace place_;
      const_iterator()
      : list_(NULL)
      , place_(NULL) {
      }
      const_iterator(const const_iterator& that)
      : list_(that.list_)
      , place_(that.place_) {
      }
      const_iterator(const iterator& that)
      : list_(that.list_)
      , place_(that.place_) {
      }
      const_iterator& operator=(const const_iterator& that) {
         list_ = that.list_;
         place_ = that.place_;
         return *this;
      }
      const_iterator& operator=(const iterator& that) {
         list_ = that.list_;
         place_ = that.place_;
         return *this;
      }
      const_iterator& operator++() {
         CORASSERT(list_);
         CORPRECONDITION(place_);
         place_ = list_->next(place_);
         return *this;
      }
      const_iterator operator++(int) {
         const_iterator tmp(*this);
         ++*this;
         return tmp;
      }
      const_iterator& operator--() {
         CORASSERT(list_);
         CORPRECONDITION(place_);
         place_ = list_->previous(place_);
         return *this;
      }
      const_iterator operator--(int) {
         const_iterator tmp(*this);
         --*this;
         return tmp;
      }
      const Type& operator*() const {
         CORASSERT(list_);
         CORPRECONDITION(place_);
         return list_->operator[](place_);
      }
      const Type* operator->() const {
         CORASSERT(list_);
         CORPRECONDITION(place_);
         return &(list_->operator[](place_));
      }
      bool operator==(const const_iterator& that) const {
         return that.list_  == this->list_
             && that.place_ == this->place_;
      }
      bool operator!=(const const_iterator& that) const {
         return !operator==(that);
      }
      // only to be used by CORlist class itself
      const_iterator(const CORlist<Type>* list, CORlistPlace place) : list_(list) , place_(place) { }
   };

   struct reverse_iterator {
      CORlist<Type>* list_;
      CORlistPlace place_;
      reverse_iterator()
      : list_(NULL)
      , place_(NULL) {
      }
      reverse_iterator(const reverse_iterator& that)
      : list_(that.list_)
      , place_(that.place_) {
      }
      reverse_iterator& operator=(const reverse_iterator& that) {
         list_ = that.list_;
         place_ = that.place_;
         return *this;
      }
      reverse_iterator& operator++() {
         CORASSERT(list_);
         CORPRECONDITION(place_);
         place_ = list_->previous(place_);
         return *this;
      }
      reverse_iterator operator++(int) {
         reverse_iterator tmp(*this);
         ++*this;
         return tmp;
      }
      reverse_iterator& operator--() {
         CORASSERT(list_);
         CORPRECONDITION(place_);
         place_ = list_->next(place_);
         return *this;
      }
      reverse_iterator operator--(int) {
         reverse_iterator tmp(*this);
         --*this;
         return tmp;
      }
      Type& operator*() {
         CORASSERT(list_);
         CORPRECONDITION(place_);
         return list_->operator[](place_);
      }
      Type* operator->() {
         CORASSERT(list_);
         CORPRECONDITION(place_);
         return &(list_->operator[](place_));
      }
      bool operator==(const reverse_iterator& that) const {
         return that.list_  == this->list_
             && that.place_ == this->place_;
      }
      bool operator!=(const reverse_iterator& that) const {
         return !operator==(that);
      }
      // only to be used by CORlist class itself
      reverse_iterator(CORlist<Type>* list, CORlistPlace place) : list_(list) , place_(place) { }
   };

   struct const_reverse_iterator {
      const CORlist<Type>* list_;
      CORlistPlace place_;
      const_reverse_iterator()
      : list_(NULL)
      , place_(NULL) {
      }
      const_reverse_iterator(const const_reverse_iterator& that)
      : list_(that.list_)
      , place_(that.place_) {
      }
      const_reverse_iterator(const reverse_iterator& that)
      : list_(that.list_)
      , place_(that.place_) {
      }
      const_reverse_iterator& operator=(const const_reverse_iterator& that) {
         list_ = that.list_;
         place_ = that.place_;
         return *this;
      }
      const_reverse_iterator& operator=(const reverse_iterator& that) {
         list_ = that.list_;
         place_ = that.place_;
         return *this;
      }
      const_reverse_iterator& operator++() {
         CORASSERT(list_);
         CORPRECONDITION(place_);
         place_ = list_->previous(place_);
         return *this;
      }
      const_reverse_iterator operator++(int) {
         const_reverse_iterator tmp(*this);
         ++*this;
         return tmp;
      }
      const_reverse_iterator& operator--() {
         CORASSERT(list_);
         CORPRECONDITION(place_);
         place_ = list_->next(place_);
         return *this;
      }
      const_reverse_iterator operator--(int) {
         const_reverse_iterator tmp(*this);
         --*this;
         return tmp;
      }
      const Type& operator*() {
         CORASSERT(list_);
         CORPRECONDITION(place_);
         return list_->operator[](place_);
      }
      const Type* operator->() {
         CORASSERT(list_);
         CORPRECONDITION(place_);
         return &(list_->operator[](place_));
      }
      bool operator==(const const_reverse_iterator& that) const {
         return that.list_  == this->list_
             && that.place_ == this->place_;
      }
      bool operator!=(const const_reverse_iterator& that) const {
         return !operator==(that);
      }
      // only to be used by CORlist class itself
      const_reverse_iterator(const CORlist<Type>* list, CORlistPlace place) : list_(list) , place_(place) { }
   };

public:
   //public typedefs for generic functions
   typedef Type                                     TValue;
   typedef CORlistPlace                             TPlace;

   typedef Type        value_type;
   typedef Type&       reference;
   typedef const Type& const_reference;
   typedef Type*       pointer;
   typedef const Type* const_pointer;

   virtual ~CORlist() {
      this->clear(); 
   }
   Type& operator[](CORlistPlace Place) {
      CORPRECONDITION(Place != NULL);
      return ((CORlistItemNode<Type>*) Place)->Item;
   }
   const Type& operator[](CORlistPlace Place) const {
      CORPRECONDITION(Place != NULL);
      return ((CORlistItemNode<Type>*) Place)->Item;
   }
   CORlistPlace insert(const Type& Item, CORlistPlace Place) {
      return this->insertItem(new CORlistItemNode<Type>(Item), Place);
   }
   CORlistPlace add(const Type& Item) {
      return this->addItem(new CORlistItemNode<Type>(Item));
   }
   CORlistPlace add() {
      return this->addItem(new CORlistItemNode<Type>());
   }

   bool empty() const { return 0 == this->size(); }

   const Type& front() const { return operator[](this->first()); }
   Type&       front()       { return operator[](this->first()); }

   const Type& back() const { return operator[](this->last()); }
   Type&       back()       { return operator[](this->last()); }

   const_iterator begin() const { return const_iterator(this, this->first()); }
   iterator       begin()       { return iterator(this, this->first()); }

   const_iterator end() const { return const_iterator(this, NULL); }
   iterator       end()       { return iterator(this, NULL); }

   const_reverse_iterator rbegin() const { return const_reverse_iterator(this, this->last()); }
   reverse_iterator       rbegin()       { return reverse_iterator(this, this->last()); }

   const_reverse_iterator rend() const { return const_reverse_iterator(this, NULL); }
   reverse_iterator       rend()       { return reverse_iterator(this, NULL); }

   const_iterator cbegin() const { return const_iterator(this, this->first()); }
   const_iterator cend()   const { return const_iterator(this, NULL); }

   const_reverse_iterator crbegin() const { return const_reverse_iterator(this, this->last()); }
   const_reverse_iterator crend()   const { return const_reverse_iterator(this, NULL); }

   iterator insert(iterator position, const Type& value) {
      CORASSERT(this == position.list_);
      CORlistPlace NewPlace = this->insert(value, position.place_);
      return iterator(this, NewPlace);
   }

   void push_front(const Type& value) { this->insert(value, this->first()); }

   void push_back(const Type& value) { this->add(value); }

   Type& push_back() {
      this->add(Type());
      return this->back();
   }

   iterator erase(iterator position) {
      CORASSERT(this == position.list_);
      CORPRECONDITION(position.place_);
      CORlistPlace Next = this->next(position.place_);
      this->remove(position.place_);
      return iterator(this, Next);
   }

   void pop_front() { this->erase(begin()); }
   void pop_back()  { this->erase(iterator(this,this->last())); }

protected:
   virtual void destroyItem(CORlistPlace Place) { delete (CORlistItemNode<Type>*) Place; }
};
