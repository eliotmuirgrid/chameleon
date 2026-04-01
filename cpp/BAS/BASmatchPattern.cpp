//-------------------------------------------------------
// Copyright (C) 2026 Eliot Muir.  All rights reserved.
//
// BASmatchPattern
//
// Implementation
//-------------------------------------------------------

#include <BAS/BASmatchPattern.h>
#include <BAS/BAStrace.h>
//#include <BAS/BASstring.h>
//BAS_TRACE_INIT;

#include <string.h>

static bool BASmatchUntilChar(const char** ppTarget, char Char){
  // BAS_FUNCTION(BASmatchUntilChar);
  // BAS_VAR2(*ppTarget, Char);
   while (*(*ppTarget) != Char){
      (*ppTarget)++;
   }
   bool Result = *(*ppTarget) == Char;

  // BAS_VAR2(Result, *ppTarget);
   return Result;
}

static bool matchSegment(const char* pTarget, const char* pPattern){
   //BAS_FUNCTION(matchSegment);
   // BAS_VAR2(pTarget, pPattern);
   const char* i= pPattern;
   const char* j= pTarget;
   while (*i != 0){
    //  BAS_VAR(*i);
      if (*i == '*'){
         i++;
         if (*i == 0){
      //      BAS_TRC("Expression matches");
            return true;
         }
         if (!BASmatchUntilChar(&j, *i)){
            return false;
         }
      } else {
         if (*i != *j){
        //    BAS_TRC("Expression does not match.");
            return false;
         }
      }
      ++j;
      ++i;
   }
//   BAS_TRC("Expression matches.");
   return true;
}

bool BASmatchPattern(const char* pTarget, const char* pPattern){
  // BAS_FUNCTION(BASmatchPattern);
   bool Match = false;
   //BAS_VAR(pPattern);
   char* Buffer = new char[strlen(pPattern)+1];
   strcpy(Buffer, pPattern);
	const char* delim = " ";
	char* pToken = strtok(Buffer, delim);
	while(pToken != NULL){
    //  BAS_VAR(pToken);
      if (*pToken == '+'){
         pToken++;
         if (matchSegment(pTarget, pToken)){
      //      BAS_TRC("Positive Match");
            Match = true;
         }
      } else if (*pToken == '-'){
         pToken++;
         if (matchSegment(pTarget, pToken)){
      //      BAS_TRC("Negative match removed");
            Match = false;
         }
      } else {
         if (matchSegment(pTarget, pToken)){
      //      BAS_TRC("Positive match");
            Match = true;
         }
      }
		pToken = strtok(NULL, delim);
	}
   delete []Buffer;
//   BAS_VAR(Match);
   return Match;
}
