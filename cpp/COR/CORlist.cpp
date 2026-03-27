//---------------------------------------------------------------------------
// Copyright (C) 2026 Eliot Muir.  All rights reserved.
//
// Module: CORlist
//
// Description:
//
// Templated double linked list class
//
// Author: Ian Farquharson
//
//---------------------------------------------------------------------------
#include "CORerror.h"
#include "CORlist.h"

CORvoidList::CORvoidList(): Size(0), Head(NULL), Tail(NULL){}


void CORvoidList::clear(){
   CORlistPlace Place = Head;
   while (Place != NULL){
      CORlistPlace Current = Place;
      Place = Place->Next;
      destroyItem(Current);
   }
   Size = 0;
   Head = NULL;
   Tail = NULL;
   invariant();
}

void CORvoidList::remove(CORlistPlace Place){
   CORPRECONDITION(Place != NULL);
   if (Place == NULL){
      return; // TODO not needed if precondition is used
   }

   if (Place->Previous == NULL){
      Head = Place->Next;
   } else {
      Place->Previous->Next = Place->Next;
   }

   if (Place->Next == NULL) {
      Tail = Place->Previous;
   } else{
      Place->Next->Previous = Place->Previous;
   }

   destroyItem(Place);
   Size--;
   invariant();
}

void CORvoidList::exchange(CORlistPlace Place1, CORlistPlace Place2){
   CORPRECONDITION(Place1 != NULL && Place2 != NULL);
   if (Place1 == NULL || Place2 == NULL){
      return; // TODO not needed if precondition is used
   }

   if (Place1 != Place2){
      CORlistPlace Previous = Place1->Previous;
      CORlistPlace Next = Place1->Next;
      Place1->Previous = Place2->Previous;
      Place1->Next = Place2->Next;
      Place2->Previous = Previous;
      Place2->Next = Next;

      if (Place1->Previous != NULL){
         if (Place1->Previous == Place1){
            Place1->Previous = Place2;
         } else {
            Place1->Previous->Next = Place1;
         }
      }

      if (Place1->Next != NULL){
         if (Place1->Next == Place1){
            Place1->Next = Place2;
         } else {
            Place1->Next->Previous = Place1;
         }
      }

      if (Place2->Previous != NULL) {
         if (Place2->Previous == Place2) {
            Place2->Previous = Place1;
         } else {
            Place2->Previous->Next = Place2;
         }
      }

      if (Place2->Next != NULL) {
         if (Place2->Next == Place2){
            Place2->Next = Place1;
         } else {
            Place2->Next->Previous = Place2;
         }
      }

      if (Head == Place1){
         Head = Place2;
      } else if (Head == Place2){
         Head = Place1;
      }

      if (Tail == Place1){
         Tail = Place2;
      } else if (Tail == Place2) {
         Tail = Place1;
      }
      invariant();
   }
}

CORlistPlace CORvoidList::previous(CORlistPlace Place) const{
   return Place == NULL ? Tail : Place->Previous;
}

CORlistPlace CORvoidList::next(CORlistPlace Place) const{
   return Place == NULL ? Head : Place->Next;
}

CORlistPlace CORvoidList::insertItem(CORlistPlace Item, CORlistPlace Place){
   CORPRECONDITION(Item != NULL);
   if (Item == NULL) {
      COR_ERROR_STREAM("Out of memory", 0);
   }
   if (Place == NULL){
      return addItem(Item);
   }
   Item->Previous = Place->Previous;
   Item->Next = Place;
   if (Item->Previous == NULL){
      Head = Item;
   } else {
      Item->Previous->Next = Item;
   }
   Place->Previous = Item;
   Size++;
   invariant();
   return Item;
}

CORlistPlace CORvoidList::addItem(CORlistPlace Item){
   CORPRECONDITION(Item != NULL);
   if (Item == NULL) {
      COR_ERROR_STREAM("Out of memory", 0);
   }
   Item->Previous = Tail;
   Item->Next = NULL;
   if (Tail == NULL){
      Head = Item;
   } else {
      Tail->Next = Item;
   }
   Tail = Item;
   Size++;
   invariant();
   return Item;
}

#ifdef COR_ENABLE_INVARIANT_INTEGRITY_CHECK
void CORvoidList::invariant() const{
   if (Size == 0) {
      CORASSERT(Head == NULL && Tail == NULL);
   } else {
      CORASSERT(Head != NULL && Tail != NULL);
      CORASSERT(Head->Previous == NULL && Tail->Next == NULL);
   }
   CORlistPlace Place = Head;
   for (CORindex i = 0; i < Size; i++){
      CORASSERT(Place != NULL);
      if (Place->Next == NULL) {
         CORASSERT(Place == Tail);
      } else {
         CORASSERT(Place->Next->Previous == Place);
      }
      Place = Place->Next;
   }
   CORASSERT(Place == NULL);
}
#endif
