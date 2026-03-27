//---------------------------------------------------------------------------
// Copyright (C) 2026 Eliot Muir.  All rights reserved.
//
// Module: TESTfilter
//
// Author: Eliot Muir
//
//
// Description:
//
// Implementation
//---------------------------------------------------------------------------
#include "TESTfilter.h"

#include <COR/CORutils.h>  // for CORglobMatch function
#include <COR/CORlist.h>
#include <COR/CORlog.h>
COR_LOG_MODULE;

void TESTfilterTests(const CORstring& Glob, CORmap<CORstring, CORauto<CORclosure0> >* pTests){
   COR_FUNCTION(TESTfilterTests);
   COR_VAR(Glob);
   CORlist<CORstring> RemoveList;
   for (auto i = pTests->cbegin(); i != pTests->cend(); i++){
      if (!CORglobMatch(Glob.c_str(), i->first.c_str()
      )){
          RemoveList.push_back(i->first);
          COR_TRC("Remove " << i->first);
      }
   } 
   for (CORlist<CORstring>::const_iterator j = RemoveList.cbegin(); j != RemoveList.cend(); j++){
      pTests->removeKey(*j);
   }
}
