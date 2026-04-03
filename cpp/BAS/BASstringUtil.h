#pragma once
//-------------------------------------------------------
// Copyright (C) 2026 Eliot Muir.  All rights reserved.
//
// BASstringUtil
//
// Free functions that operate on BASstring (split, search, etc.). Keeps BASstring.h
// focused on the string object; put algorithms here.
//
// BASstringSplit: cuts Source into pieces wherever Delimiter appears. The delimiter
// itself is not included in any piece. Consecutive delimiters produce empty pieces.
// If Source is empty, the result is a single empty string (one element). If there
// is no delimiter in Source, the result is one element equal to Source.
//
// pLines must be non-null (BAS_ASSERT in the implementation); it is cleared first,
// then filled with the pieces.
//-------------------------------------------------------

#include <BAS/BASarray.h>
#include <BAS/BASstring.h>

void BASstringSplit(const BASstring& Source, char Delimiter, BASarray<BASstring>* pLines);