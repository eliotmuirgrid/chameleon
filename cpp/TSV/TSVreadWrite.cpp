// Copyright (C) 2026 Eliot Muir. All rights reserved.
//
// Module: TSVreadWrite
//
// Implementation
//-------------------------------------------------------

#include <TSV/TSVreadWrite.h>

#include <BAS/BASerror.h>
#include <BAS/BASstringUtil.h>

static void TSVstripTrailingCr(BASstring* pLine) {
   BAS_ASSERT(pLine);
   int N = pLine->size();
   if (N > 0 && (*pLine)[N - 1] == '\r') {
      pLine->setSize(N - 1);
   }
}

static void TSVtrimTrailingEmptyLines(BASarray<BASstring>* pLines) {
   BAS_ASSERT(pLines);
   while (pLines->size() > 1 && pLines->back().empty()) {
      pLines->pop();
   }
}

bool TSVparse(const BASstring& Content, TSVtable* pTable, BASstring* pError) {
   (void)pError;
   BAS_ASSERT(pTable);
   pTable->clear();
   if (Content.size() == 0) {
      return true;
   }

   BASarray<BASstring> Lines;
   BASstringSplit(Content, '\n', &Lines);
   TSVtrimTrailingEmptyLines(&Lines);

   const int LineCount = Lines.size();
   for (int LineIndex = 0; LineIndex < LineCount; ++LineIndex) {
      BASstring Line = Lines[LineIndex];
      TSVstripTrailingCr(&Line);

      TSVrow Row;
      BASstringSplit(Line, '\t', &Row);
      pTable->push(Row);
   }
   return true;
}

bool TSVformat(const TSVtable& Table, BASstring* pContent, BASstring* pError) {
   (void)pError;
   BAS_ASSERT(pContent);
   pContent->clear();

   const int RowCount = Table.size();
   for (int RowIndex = 0; RowIndex < RowCount; ++RowIndex) {
      const TSVrow& Row = Table[RowIndex];
      const int FieldCount = Row.size();
      for (int FieldIndex = 0; FieldIndex < FieldCount; ++FieldIndex) {
         if (FieldIndex > 0) {
            *pContent += '\t';
         }
         *pContent += Row[FieldIndex];
      }
      *pContent += '\n';
   }
   return true;
}
