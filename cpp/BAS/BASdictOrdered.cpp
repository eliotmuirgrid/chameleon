//-------------------------------------------------------
// Copyright (C) 2026 Eliot Muir.  All rights reserved.
//
// BASdictOrdered
//
// Implementation
//-------------------------------------------------------

#include <BAS/BAStrace.h>
BAS_TRACE_INIT;

#include <BAS/BASdictOrdered.h>

#include <BAS/BASstring.h>

static int BASavlChildHeight(BASavlNode* pNode){
   return pNode ? pNode->m_Height : 0;
}

static void BASavlRefreshHeight(BASavlNode* pNode){
   if (!pNode){
      return;
   }
   int lh = BASavlChildHeight(pNode->m_pLeft);
   int rh = BASavlChildHeight(pNode->m_pRight);
   pNode->m_Height = 1 + (lh > rh ? lh : rh);
}

BASavlNode::BASavlNode() : m_pLeft(NULL), m_pRight(NULL), m_Height(1){
   BAS_METHOD(BASavlNode);
}

BASavlNode::~BASavlNode(){
   BAS_METHOD(BASavlNode::~BASavlNode);
   delete m_pLeft;
   delete m_pRight;
}


BASavlTreeBase::BASavlTreeBase(BASavlCompare pCompareFunc, BASavlExtractKey pKey) : m_pRoot(NULL), m_pCompareFunc(pCompareFunc), m_pKeyFunc(pKey), m_Size(0){
   BAS_METHOD(BASavlTreeBase::BASavlTreeBase);
}

BASavlTreeBase::~BASavlTreeBase(){
   BAS_METHOD(BASavlTreeBase::~BASavlTreeBase);
   delete m_pRoot;
}

int BASavlDifference(BASavlNode* pNode){
   BAS_FUNCTION(BASavlDifference);
   return BASavlChildHeight(pNode->m_pLeft) - BASavlChildHeight(pNode->m_pRight);
}

static BASavlNode* BASavlRotateRR(BASavlNode* pParent) {
   BAS_FUNCTION(BASavlRotateRR);
   BASavlNode* t;
   t = pParent->m_pRight;
   pParent->m_pRight = t->m_pLeft;
   t->m_pLeft = pParent;
   BASavlRefreshHeight(pParent);
   BASavlRefreshHeight(t);
   return t;
}

static BASavlNode* BASavlRotateLL(BASavlNode* pParent) {
   BAS_FUNCTION(BASavlRotateLL);
   BASavlNode* t;
   t = pParent->m_pLeft;
   pParent->m_pLeft = t->m_pRight;
   t->m_pRight = pParent;
   BASavlRefreshHeight(pParent);
   BASavlRefreshHeight(t);
   return t;
}

static BASavlNode* BASavlRotateLR(BASavlNode* pParent) {
   BAS_FUNCTION(BASavlRotateLR);
   BASavlNode* t;
   t = pParent->m_pLeft;
   pParent->m_pLeft = BASavlRotateRR(t);
   return BASavlRotateLL(pParent);
}

static BASavlNode* BASavlRotateRL(BASavlNode* pParent) {
   BAS_FUNCTION(BASavlRotateRL);
   BASavlNode* t;
   t = pParent->m_pRight;
   pParent->m_pRight = BASavlRotateLL(t);
   return BASavlRotateRR(pParent);
}

BASavlNode* BASavlBalance(BASavlNode* pNode) {
   BAS_FUNCTION(BASavlBalance);
   int Balance = BASavlDifference(pNode);
   if (Balance > 1) {
      if (BASavlDifference(pNode->m_pLeft) > 0)
         pNode = BASavlRotateLL(pNode);
      else
         pNode = BASavlRotateLR(pNode);
   } else if (Balance < -1) {
      if (BASavlDifference(pNode->m_pRight) > 0)
         pNode = BASavlRotateRL(pNode);
      else
         pNode = BASavlRotateRR(pNode);
   }
   return pNode;
}

BASavlNode* BASinsert(BASavlNode* pNode, BASavlNode* pNewNode, BASavlCompare pCompFunc, BASavlExtractKey pKeyFunc, int* pSize){
   BAS_FUNCTION(BASinsert);
   BAS_VAR2(pNode, pNewNode);
   if (pNode == NULL){
      BAS_TRC("New node. Count goes up by one.");
      (*pSize)++;
      return pNewNode;
   }
   int Compare = (*pCompFunc)((*pKeyFunc)(pNode),(*pKeyFunc)(pNewNode));
   if (Compare == 0){
      BAS_TRC("Replace");
      pNode->copy(*pNewNode);
      delete pNewNode;
      return pNode;
   }
   if (Compare > 0){
      BAS_TRC("Insert to left");
      pNode->m_pLeft = BASinsert(pNode->m_pLeft, pNewNode, pCompFunc,pKeyFunc, pSize);
      BASavlRefreshHeight(pNode);
      return BASavlBalance(pNode);
   }
   BAS_TRC("Insert to right");
   pNode->m_pRight = BASinsert(pNode->m_pRight, pNewNode, pCompFunc,pKeyFunc, pSize);
   BASavlRefreshHeight(pNode);
   return BASavlBalance(pNode);
}


void BASavlTreeBase::insert(BASavlNode* pNewNode){
   BAS_METHOD(BASavlTreeBase::insert);
   m_pRoot = BASinsert(m_pRoot, pNewNode, m_pCompareFunc, m_pKeyFunc, &m_Size);
}

BASavlNode* BASfind(BASavlNode* pNode, const void* pKey, BASavlCompare pCompFunc, BASavlExtractKey pKeyFunc){
   BAS_FUNCTION(BASfind);
   if (pNode == NULL){
      return NULL;
   }
   int Compare = (*pCompFunc)((*pKeyFunc)(pNode), pKey);
   BAS_VAR(Compare);
   if (Compare == 0){
      return pNode;
   }
   if (Compare > 0){
      return BASfind(pNode->m_pLeft, pKey, pCompFunc, pKeyFunc);
   } else {
      return BASfind(pNode->m_pRight, pKey, pCompFunc, pKeyFunc);
   }
}

BASavlNode* BASavlTreeBase::find(const void* pKey) const{
   BAS_METHOD(BASavlTreeBase::find);
   return BASfind((BASavlNode*)m_pRoot, pKey, m_pCompareFunc, m_pKeyFunc);
}

int BASsCompare(const BASstring& Rhs, const BASstring& Lhs){
   return Rhs.compare(Lhs);
}


BASstream& operator<<(BASstream& Stream, const BASavlNode& Node){
   //Stream << Node.m_Key;
   if (!Node.m_pRight && !Node.m_pLeft){
      return Stream; // empty node
   }
   Stream << "-->[";
   if (Node.m_pLeft){
      Stream << *(Node.m_pLeft);
   }
   Stream << ",";
   if (Node.m_pRight){
      Stream << *(Node.m_pRight);
   }
   Stream << "]";
   return Stream;
}

BASavlIterator::BASavlIterator(BASavlNode* pRoot) : m_StackPos(1){
   BAS_METHOD(BASavlIterator::BASavlIterator);
   m_Stack[0] = NULL;
   m_Stack[1] = pRoot;
}

void BASavlIterator::first(){
   BAS_METHOD(BASavlIterator::first);
   downLeft();
}

bool BASavlIterator::next(){
   BAS_METHOD(BASavlIterator::next);
   if (root()->m_pRight != NULL){
      goRight();
      return downLeft();
   }
   return upRight();
}

void BASavlIterator::goLeft(){
   BAS_METHOD(BASavlIterator::goLeft);
   BAS_ASSERT(m_StackPos + 1 < kBASavlIteratorStackDepth);
   BAS_ASSERT(root() != NULL);
   BAS_ASSERT(root()->m_pLeft != NULL);
   m_StackPos++;
   m_Stack[m_StackPos] = parent()->m_pLeft;
}

bool BASavlIterator::downRight(){
   BAS_METHOD(BASavlIterator::downRight);
   while (root() != NULL && root()->m_pRight != NULL){
      BAS_ASSERT(m_StackPos + 1 < kBASavlIteratorStackDepth);
      m_StackPos++;
      m_Stack[m_StackPos] = parent()->m_pRight;
   }
   return root() != NULL;
}

bool BASavlIterator::upLeft(){
   BAS_METHOD(BASavlIterator::upLeft);
   while (m_StackPos > 1 && parent()->m_pLeft == root()){
      pop();
   }
   pop();
   return root() != NULL;
}

bool BASavlIterator::prev(){
   BAS_METHOD(BASavlIterator::prev);
   if (m_StackPos == 0){
      m_StackPos = 1;
      if (m_Stack[1] == NULL){
         return false;
      }
      return downRight();
   }
   BAS_ASSERT(root() != NULL);
   if (root()->m_pLeft != NULL){
      goLeft();
      return downRight();
   }
   return upLeft();
}

void BASavlIterator::goRight(){
   BAS_METHOD(BASavlIterator::goRight);
   BAS_ASSERT(m_StackPos + 1 < kBASavlIteratorStackDepth);
   m_StackPos++;
   m_Stack[m_StackPos] = parent()->m_pRight;
}

bool BASavlIterator::downLeft(){
   BAS_METHOD(BASavlIterator::downLeft);
   while (root()->m_pLeft != NULL){
      BAS_ASSERT(m_StackPos + 1 < kBASavlIteratorStackDepth);
      m_StackPos++;
      m_Stack[m_StackPos] = parent()->m_pLeft;
   }
   return true;
}

bool BASavlIterator::upRight(){
   BAS_METHOD(BASavlIterator::upRight);
   BAS_VAR(parent());
   while (m_StackPos > 1 && parent()->m_pRight == root()){
      BAS_VAR2(parent()->m_pRight, root());
      pop();
   }
   pop();
   BAS_VAR(root());
   return root() != NULL;
}

void BASavlIterator::pop(){
   BAS_METHOD(BASavlIterator::pop);
   m_StackPos--;
}
