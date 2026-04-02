//---------------------------------------------------------------------------
// Copyright (C) 2026 Eliot Muir.  All rights reserved.
//
// Module: CORmap
//
// Description:
//
// Templated sorted tree-based map container
//
// Author: Ian Farquharson
//---------------------------------------------------------------------------
#include <COR/CORerror.h>
#include <COR/CORmap.h>

/***************************\
*                           *
* AVL Tree collection class *
*                           *
\***************************/

// CORavlTree: Copyright (C) 2026 Eliot Muir.  All rights reserved.

// Rotation Primitives

static void CORmapBalance1(CORavlTreePlace& p, bool& h)
{
   CORavlTreePlace p1;
   CORavlTreePlace p2;
   int      b1;     // -1..+1
   int      b2;     // -1..+1

   //  h == true ==> Left branch has become less high
   switch (p->Balance)
   {
   case (-1):
      p->Balance = 0;
      break;

   case (0) :
      p->Balance = 1;
      h = false;
      break;

   case (1) :
      // rebalance
      p1 = p->Right;
      b1 = p1->Balance;
      if (b1 >= 0)
      {
         /********************\
         *                    *
         * single RR rotation *
         *                    *
         *             pR     *
         *           /    \   *
         *         p          *
         *       /   \        *
         *           pRL      *
         *                    *
         \********************/
         p->Right = p1->Left;
         p1->Left = p;
         if (b1 == 0)
         {
            p->Balance = 1;
            p1->Balance = (-1);
            h = false;
         }
         else
         {
            p->Balance = 0;
            p1->Balance = 0;
         }
         p = p1;
         // now do the ups
         p->Up = p->Left->Up;
         p->Left->Up = p;
         if (p->Left->Right != NULL)
            p->Left->Right->Up = p->Left;
      }
      else
      {
         /************************\
         *                        *
         * Double RL Rotation     *
         *             pRL        *
         *          /       \     *
         *        p          pR   *
         *      /   \      /    \ *
         *         pRLL  p        *
         *                        *
         \************************/
         p2 = p1->Left;
         b2 = p2->Balance;
         p1->Left = p2->Right;
         p2->Right = p1;
         p->Right = p2->Left;
         p2->Left = p;
         if (b2 == 1)
            p->Balance = (-1);
         else
            p->Balance = 0;
         if (b2 == (-1))
            p1->Balance = 1;
         else
            p1->Balance = 0;
         p = p2;
         p2->Balance = 0;
         // now do the ups
         p->Up = p->Left->Up;
         p->Left->Up = p;
         if (p->Left->Right)
            p->Left->Right->Up = p->Left;
         p->Right->Up = p;
         if (p->Right->Left)
            p->Right->Left->Up = p->Right;
      }
   }
}

static void CORmapBalance2(CORavlTreePlace& p, bool& h)
{
   CORavlTreePlace p1;
   CORavlTreePlace p2;
   int      b1;     // -1..+1
   int      b2;     // -1..+1

   //  h == true ==> Right branch has become less high
   switch (p->Balance)
   {
   case 1 :
      p->Balance = 0;
      break;

   case 0 :
      p->Balance =(-1);
      h = false;
      break;

   case -1:
      p1 = p->Left;
      b1 = p1->Balance;
      if (b1 <= 0)
      {
         /*********************\
         *                     *
         *  single LL rotation *
         *             pL      *
         *           /    \    *
         *                 p   *
         *                /    *
         *              pLR    *
         *                     *
         \*********************/
         p->Left = p1->Right;
         p1->Right = p;
         if (b1 == 0)
         {
            p->Balance = (-1);
            p1->Balance = 1;
            h = false;
         }
         else
         {
            p->Balance = 0;
            p1->Balance = 0;
         }
         p = p1;
         // now do the ups
         p->Up = p->Right->Up;
         p->Right->Up = p;
         if (p->Right->Left)
            p->Right->Left->Up = p->Right;
      }
      else
      {
         /************************\
         *                        *
         *  Double LR Rotation    *
         *             pLR        *
         *          /       \     *
         *        pL          p   *
         *      /   \      /    \ *
         *         pLRL  pLRR     *
         *                        *
         \************************/
         p2 = p1->Right;
         b2 = p2->Balance;
         p1->Right= p2->Left;
         p2->Left = p1;
         p->Left = p2->Right;
         p2->Right = p;
         if (b2 == (-1))
            p->Balance = 1;
         else
            p->Balance = 0;
         if (b2 == 1)
            p1->Balance = (-1);
         else
            p1->Balance = 0;
         p = p2;
         p2->Balance = 0;
         // now do the ups
         p->Up = p->Right->Up;
         p->Left->Up = p;
         if (p->Left->Right)
            p->Left->Right->Up = p->Left;
         p->Right->Up = p;
         if (p->Right->Left)
            p->Right->Left->Up = p->Right;
      }
   }
}

static bool CORmapDel(CORavlTreePlace& r, CORavlTreePlace& q, bool& h)
{
   if (r->Right)
   {
      // now going Right until we can't
      bool res = CORmapDel(r->Right, q, h);
      if (q->Left == r)
      {
         if (h)
            CORmapBalance2(q->Left, h);
      }
      else if (h)
         CORmapBalance2(r, h);
      return res;
   }
   else
   {
      // copy the data from node r to q 'position'
      CORavlTreePlace qq    = q;
      CORavlTreePlace rr    = r;
      CORavlTreePlace qup   = q->Up;
      CORavlTreePlace qprev = q->Left;
      CORavlTreePlace qnext = q->Right;
      int          qBal  = q->Balance;
      CORavlTreePlace rup   = r->Up;
      CORavlTreePlace rprev = r->Left;
      q = rr;
      q->Balance = qBal;
      q->Up   = qup;
      if (q->Up){
         if (q->Up->Left == qq){
            q->Up->Left = q;
         } else {
            q->Up->Right = q;
         }
      }
      if (qnext != rr)
      {
         q->Right = qnext;
         if (q->Right)
            q->Right->Up = q;
      }
      if (qprev != rr)
      {
         q->Left = qprev;
         if (q->Left)
            q->Left->Up = q;
      }
      if (rup->Right == rr){
         if (rprev)
         {
            rup->Right = rprev;
            rprev->Up = rup;
         }
         else{
            rup->Right = NULL;
         }  
      }
      r = rprev;

      h = true;
      return true;
   }
}

// CORavlTreeNode

CORavlTreeNode::CORavlTreeNode(void):
   Up(NULL),
   Left(NULL),
   Right(NULL),
   Balance(0)
{
}

// CORavlTreeBase

CORavlTreeBase::CORavlTreeBase(void):
   RootNode(NULL),
   NodeCount(0)
{
}

void CORavlTreeBase::clear(void)
{
   if (RootNode != NULL)
   {
      CORavlTreePlace curr = RootNode;
      CORavlTreePlace parent;
      while (true)
      {
         while (true)  // find a leaf
         {
            if (curr->Left != NULL)
            {
               curr = curr->Left;
               continue;
            }
            if (curr->Right != NULL)
            {
               curr = curr->Right;
               continue;
            }
            break;    // now at a leaf since both Left and Right pointers are NULL
         }

         if ((parent = curr->Up) == NULL)
         {
            destroyItem(curr);  // only the root of the tree is Left, delete it and break out of loop
            break;
         }
         else
         {
            if (parent->Left == curr) // Set the appropriate pointer to NULL, The parent may become a leaf
               parent->Left = NULL;
            else
               parent->Right = NULL;
            destroyItem(curr);
            curr = parent;
         }
      }
   }
   RootNode = NULL;
   NodeCount = 0;
}

struct CORavlTreeBaseContext           // used for zapping a node
{
   CORavlTreePlace   stack[32];    // path to the target node
   int            stack_count;  // number of items in path
   int            stack_place;  // where we are Up to
   CORavlTreePlace   target_node;  // target node
};

void CORavlTreeBase::remove(CORavlTreePlace Place)
{
   CORPRECONDITION(Place != NULL);
   bool Higher = false;
   CORavlTreeBaseContext Context;
   memset(&Context, 0, sizeof(Context));
   for (CORavlTreePlace p = Place; p != RootNode; p = p->Up)
   {
      Context.stack[Context.stack_count] = p;
      Context.stack_count++;
   }
   Context.stack_place = Context.stack_count;
   Context.target_node = Place;
   if (zapIt(Context, RootNode, Higher))
      NodeCount--;
   invariant();
}

CORavlTreePlace CORavlTreeBase::first(void) const
{
   return downLeft(RootNode);
}

CORavlTreePlace CORavlTreeBase::last(void) const
{
   return downRight(RootNode);
}

CORavlTreePlace CORavlTreeBase::previous(CORavlTreePlace Place) const
{
   if (Place == NULL)
      return last();
   if (Place->Left != NULL)
      return downRight(Place->Left);
   return upLeft(Place);
}

CORavlTreePlace CORavlTreeBase::next(CORavlTreePlace Place) const
{
   if (Place == NULL)
      return first();
   if (Place->Right != NULL)
      return downLeft(Place->Right);
   return upRight(Place);
}

bool CORavlTreeBase::removeItem(const void* Key)
{
   bool Higher = false;
   if (zapIt(Key, RootNode, Higher))
   {
      NodeCount--;
      invariant();
      return true;
   }
   return false;
}

CORavlTreePlace CORavlTreeBase::addItem(const void* Key, CORavlTreePlace Item)
{
   bool new_level = false;
   CORavlTreePlace Place = insertIt(Key, Item, RootNode, NULL, new_level, false);
   if (Place == NULL)
   {
      destroyItem(Item);
      return NULL;
   }
   NodeCount++;
   invariant();
   return Place;
}

CORavlTreePlace CORavlTreeBase::addUniqueItem(const void* Key, CORavlTreePlace Item)
{
   bool new_level = false;
   CORavlTreePlace Place = insertIt(Key, Item, RootNode, NULL, new_level, true);
   if (Place == NULL)
   {
      destroyItem(Item);
      return NULL;
   }
   NodeCount++;
   invariant();
   return Place;
}

CORavlTreePlace CORavlTreeBase::findFirstItem(const void* Key) const
{
   CORavlTreePlace Place = findBelowItem(Key);
   if (Place) Place = next(Place);
   else Place = first();
   if (Place && compareKey(Key,Place) == 0) return Place;
   return 0;
}

CORavlTreePlace CORavlTreeBase::findItem(const void* Key) const
{
   CORavlTreePlace curr = RootNode;
   while (curr != NULL)
   {
      int comparism = compareKey(Key, curr);
      if (comparism < 0)
         curr = curr->Left;
      else if (comparism > 0)
         curr = curr->Right;
      else
         break; // found it
   }
   return curr;
}

CORavlTreePlace CORavlTreeBase::findNearestItem(const void* Key) const
{
   CORavlTreePlace curr = RootNode;
   while (curr != NULL)
   {
      int comparism = compareKey(Key, curr);
      if (comparism < 0)
         if (curr->Left != NULL)
            curr = curr->Left;
         else
            break; // found nearest
      else if (comparism > 0)
         if (curr->Right != NULL)
            curr = curr->Right;
         else
         {
            CORavlTreePlace p = next(curr);
            if (p != NULL)
               curr = p;
            break; // found nearest
         }
      else
         break; // found it
   }
   return curr;
}

CORavlTreePlace CORavlTreeBase::findBelowItem(const void* Key) const
{
   CORavlTreePlace curr = RootNode;
   while (curr != NULL)
   {
      int comparism = compareKey(Key, curr);
      if (comparism <= 0)
         if (curr->Left != NULL)
            curr = curr->Left;
         else
         {
            curr = previous(curr);
            break; // found below
         }
      else
         if (curr->Right != NULL)
         curr = curr->Right;
      else
         break; // found below
   }
   return curr;
}

CORavlTreePlace CORavlTreeBase::findAboveItem(const void* Key) const
{
   CORavlTreePlace curr = RootNode;
   while (curr != NULL)
   {
      int comparism = compareKey(Key, curr);
      if (comparism >= 0)
         if (curr->Right != NULL)
            curr = curr->Right;
         else
         {
            curr = next(curr);
            break; // found above
         }
      else
         if (curr->Left != NULL)
         curr = curr->Left;
      else
         break; // found above
   }
   return curr;
}

CORavlTreePlace CORavlTreeBase::downLeft(CORavlTreePlace Place) const
{
   if (Place != NULL)
      while (Place->Left != NULL)
         Place = Place->Left;
   return Place;
}

CORavlTreePlace CORavlTreeBase::downRight(CORavlTreePlace Place) const
{
   if (Place != NULL)
      while (Place->Right != NULL)
         Place = Place->Right;
   return Place;
}

CORavlTreePlace CORavlTreeBase::upLeft(CORavlTreePlace Place) const
{
   if (Place != NULL)
      while (Place->Up != NULL && Place->Up->Left == Place)
         Place = Place->Up;
   Place = Place->Up;
   return Place;
}

CORavlTreePlace CORavlTreeBase::upRight(CORavlTreePlace Place) const
{
   if (Place != NULL)
      while (Place->Up != NULL && Place->Up->Right == Place)
         Place = Place->Up;
   Place = Place->Up;
   return Place;
}

CORavlTreePlace CORavlTreeBase::insertIt(const void* Key,
                                   CORavlTreePlace Item,
                                   CORavlTreePlace& CurrNode,    // tree top/ where found
                                   CORavlTreePlace NodeAbove,    // for Up
                                   bool& Higher,   // true if new level added
                                   bool Unique)
{
   CORavlTreePlace p1;
   CORavlTreePlace p2;
   int comparism;
   CORavlTreePlace result;

   Higher = false;

   if (CurrNode == NULL)        // check if we are empty - in which case insert
   {
      CurrNode = Item;
      CurrNode->Left = NULL;
      CurrNode->Right = NULL;
      CurrNode->Up = NodeAbove;   // from recursion
      CurrNode->Balance = 0;       // no need to Balance this node
      Higher = true;
      return CurrNode;           // back Up recursion
   }

   // otherwise we still want to look down

   comparism = compareKey(Key, CurrNode);
   if (comparism < 0)
   {
      result = insertIt(Key, Item, CurrNode->Left, CurrNode, Higher, Unique); // recurse
      if (Higher)
      {
         if (CurrNode->Balance == 1)
         {
            CurrNode->Balance = 0; Higher = false;
         }
         else if (CurrNode->Balance == 0)
            CurrNode->Balance = -1;   // pass Up
         else  // rebalance this section of the tree
         {
            p1 = CurrNode->Left;
            if (p1->Balance == -1)
            {
               // single LL rotation
               CurrNode->Left = p1->Right;
               p1->Right = CurrNode;
               CurrNode->Balance = 0;
               CurrNode = p1;
               CurrNode->Up = CurrNode->Right->Up;  // put back the ups
               CurrNode->Right->Up = CurrNode;
               if (CurrNode->Right->Left)
                  CurrNode->Right->Left->Up = CurrNode->Right;
            }
            else
            {
               // double LR rotation
               p2 = p1->Right;
               p1->Right = p2->Left;
               p2->Left = p1;
               CurrNode->Left = p2->Right;
               p2->Right = CurrNode;
               if (p2->Balance == -1)
                  CurrNode->Balance = 1;
               else
                  CurrNode->Balance = 0;
               if (p2->Balance == 1)
                  p1->Balance = -1;
               else
                  p1->Balance = 0;
               CurrNode = p2;
               CurrNode->Up = CurrNode->Right->Up;     // now return ups
               CurrNode->Right->Up = CurrNode;
               if (CurrNode->Right->Left)
                  CurrNode->Right->Left->Up = CurrNode->Right;
               CurrNode->Left->Up = CurrNode;
               if (CurrNode->Left->Right)
                  CurrNode->Left->Right->Up = CurrNode->Left;
            }
            CurrNode->Balance = 0;
            Higher = false;
         }
      } // Higher
   }
   else if (comparism > 0 || !Unique)
   {
      result = insertIt(Key, Item, CurrNode->Right, CurrNode, Higher, Unique);
      if (Higher)
      {                 // put in Higher - prev Branch High
         if (CurrNode->Balance < 0)
         {
            CurrNode->Balance = 0;
            Higher = false;
         }
         else if (CurrNode->Balance == 0)
            CurrNode->Balance = 1;   // rebalance further Up tree
         else
         {
            p1 = CurrNode->Right;             // rebalance now
            if (p1->Balance == 1)            // single RR rotation
            {
               CurrNode->Right = p1->Left;
               p1->Left = CurrNode;
               CurrNode->Balance = 0;
               CurrNode = p1;
               CurrNode->Up = CurrNode->Left->Up;       // restore the ups
               CurrNode->Left->Up = CurrNode;
               if (CurrNode->Left->Right)         // startup cond
                  CurrNode->Left->Right->Up = CurrNode->Left;
            }
            else
            {                         // double RL Rotation
               p2 = p1->Left;
               p1->Left = p2->Right;
               p2->Right = p1;
               CurrNode->Right = p2->Left;
               p2->Left = CurrNode;
               if (p2->Balance == +1)
                  CurrNode->Balance = -1;
               else
                  CurrNode->Balance = 0;
               if (p2->Balance == -1)
                  p1->Balance = 1;
               else
                  p1->Balance = 0;
               CurrNode = p2;
               CurrNode->Up = CurrNode->Left->Up;
               CurrNode->Left->Up = CurrNode;
               if (CurrNode->Left->Right != NULL)
                  CurrNode->Left->Right->Up = CurrNode->Left;
               CurrNode->Right->Up = CurrNode;
               if (CurrNode->Right->Left != NULL)
                  CurrNode->Right->Left->Up = CurrNode->Right;
            }
            CurrNode->Balance = 0;
            Higher = false;
         }
      } // Higher
   }
   else // comparism == 0
   {
      return NULL;
   }
   return result;
}

bool CORavlTreeBase::zapIt(CORavlTreeBaseContext& Context, // path down tree to target node
                        CORavlTreePlace& CurrNode,  // tree top/ where found
                        bool& Higher)  // true if new level added
{
   CORavlTreePlace kill_node;
   CORavlTreePlace p = NULL;
   bool result = false;

   if (CurrNode == NULL)
   {
      Higher = false;
      return result;
   }

   Context.stack_place--;
   if (Context.stack_place < 0)
   {
      CORPRECONDITION(CurrNode == Context.target_node);
      p = CurrNode;  // THIS CODE IS REPEATED IN BOTH kILLiT FUNCTIONS
      if (!p->Right)  // nothing on Right - just attach properly
      {
         if (p->Left)
            p->Left->Up = CurrNode->Up;
         CurrNode = p->Left;
         Higher = true;
         result = true;
         kill_node = p;
      }
      else if (!p->Left)  // alternatively nothing on prev - just attach
      {
         if (p->Right)
            p->Right->Up = CurrNode->Up;
         CurrNode = p->Right;
         Higher = true;
         result = true;
         kill_node = p;
      }
      else  // nothing either side - ok this is a pain - recurse !!
      {
         kill_node = p;
         result = CORmapDel(p->Left, p, Higher); // copy of killed node. Can result ever be false?!?
         CurrNode = p;
         if (Higher)
            CORmapBalance1(CurrNode, Higher);
      }
      destroyItem(kill_node);
   }
   else if (CurrNode->Left == Context.stack[Context.stack_place])
   {
      result = zapIt(Context, CurrNode->Left, Higher);
      if (Higher)
         CORmapBalance1(CurrNode, Higher);
   }
   else if (CurrNode->Right == Context.stack[Context.stack_place])
   {
      result = zapIt(Context, CurrNode->Right, Higher);
      if (Higher)
         CORmapBalance2(CurrNode, Higher);
   }
   else
   {
      ; // DiagFail();
   }
   return result;
}

bool CORavlTreeBase::zapIt(const void* Key,  // search for a Key
                        CORavlTreePlace& CurrNode,  // tree top/ where found
                        bool& Higher)  // true if new level added
{
   CORavlTreePlace kill_node;
   CORavlTreePlace p = NULL;
   int comparism;
   bool result = false;

   if (CurrNode == NULL)
   {
      Higher = false;
      return result;
   }

   comparism = compareKey(Key, CurrNode);
   if (comparism < 0)
   {
      result = zapIt(Key, CurrNode->Left, Higher);
      if (Higher)
         CORmapBalance1(CurrNode, Higher);
   }
   else if (comparism > 0)
   {
      result = zapIt(Key, CurrNode->Right, Higher);
      if (Higher)
         CORmapBalance2(CurrNode, Higher);
   }
   else
   {
      p = CurrNode;  // THIS CODE IS REPEATED IN BOTH kILLiT FUNCTIONS
      if (!p->Right)  // nothing on Right - just attach properly
      {
         if (p->Left)
            p->Left->Up = CurrNode->Up;
         CurrNode = p->Left;
         Higher = true;
         result = true;
         kill_node = p;
      }
      else if (!p->Left)  // alternatively nothing on prev - just attach
      {
         if (p->Right)
            p->Right->Up = CurrNode->Up;
         CurrNode = p->Right;
         Higher = true;
         result = true;
         kill_node = p;
      }
      else  // nothing either side - ok this is a pain - recurse !!
      {
         kill_node = p;
         result = CORmapDel(p->Left, p, Higher); // copy of killed node. Can result ever be false?!?
         CurrNode = p;
         if (Higher)
            CORmapBalance1(CurrNode, Higher);
      }
      destroyItem(kill_node);
   }
   return result;
}

CORostream& operator<<(CORostream& Stream, const CORmap<CORstring, CORstring>& Map) {
   Stream << "MAP size=" << Map.size() << newline;
   for(auto i = Map.cbegin(); i != Map.cend(); i++) { 
      Stream << "\t" << i->first << "=" << i->second << newline; 
   }
   return Stream;
}

#ifdef COR_ENABLE_INVARIANT_INTEGRITY_CHECK

void CORavlTreeBase::testLinkage(CORavlTreePlace Place) const
{
   if (Place == NULL)
      return;
   CORASSERT(Place->Left == NULL || Place->Left->Up == Place);
   CORASSERT(Place->Right == NULL || Place->Right->Up == Place);
   testLinkage(Place->Left);
   testLinkage(Place->Right);
}

void CORavlTreeBase::invariant(void) const
{
   testLinkage(RootNode);
   if (RootNode == NULL)
   {
      CORASSERT(NodeCount == 0);
   }
   else
   {
      CORindex count = 0;
      for (CORavlTreePlace curr = first(); curr != NULL; curr = next(curr))
      {
         CORASSERT(curr->Balance >= -1 && curr->Balance <= 1);
         count++;
      }
      CORASSERT(count == NodeCount);
   }
}

#endif
