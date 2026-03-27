//---------------------------------------------------------------------------
// Copyright (C) 2026 Eliot Muir.  All rights reserved.
//
// Module: TESTlastFailed
//
// Author: Eliot Muir
//
//
// Description:
//
// Implementation
//---------------------------------------------------------------------------
#include "TESTlastFailed.h"
#include "TESTrun.h"

#include <FIL/FILutils.h>

#include <COR/CORhashmap.h>
#include <COR/CORlist.h>
#include <COR/CORsplit.h>
#include <COR/CORarray.h>
#include <COR/CORlog.h>
COR_LOG_MODULE;

void TESTsaveFailedTests(const TESTsummary& Summary){
   COR_FUNCTION(TESTsaveFailedTests);
   CORstring Output;
   for (CORmap<CORstring, CORstring>::const_iterator i = Summary.m_FailedBuilds.cbegin(); i != Summary.m_FailedBuilds.cend(); i++){
      if (i->second != "succeeded"){
         Output += i->first + "\n";
      }
   }
   if (!Output.is_null()){
      FILwriteFile("lastfailed.tmp", Output);
      CORcout << "Wrote failed tests into lastfailed.tmp - to rerun failed tests use --lastfailed flag." << newline;
   } else {
      if (FILfileExists("lastfailed.tmp")){
         FILremoveWithThrow("lastfailed.tmp");
      }
   }
}


void TESTfilterFailedTests(CORmap<CORstring, CORauto<CORclosure0> >* pTests){
   COR_FUNCTION(TESTfilterFailedTests);
   if (!FILfileExists("lastfailed.tmp")){
      CORcout << "No failed tests to run." << newline;
      pTests->clear();
      return;
   }
   CORstring Content;
   FILreadFile("lastfailed.tmp", &Content);
   CORarray<CORstring> List;
   CORsplit(&List, Content, "\n");
   CORhashmap<CORstring, CORstring> Map;
   for (int i=0; i < List.size(); i++){
      Map.add(List[i].strip(CORstring::Both, ' '), "");
   }
   CORlist<CORstring> RemoveList;
   for (auto i = pTests->cbegin(); i != pTests->cend(); i++){
      if (!Map.find(i->first)){
          RemoveList.push_back(i->first);
          COR_TRC("Remove " << i->first);
      }
   } 
   for (CORlist<CORstring>::const_iterator j = RemoveList.cbegin(); j != RemoveList.cend(); j++){
      pTests->removeKey(*j);
   }
}
