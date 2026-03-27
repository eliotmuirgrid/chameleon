#pragma hdrstop
// ---------------------------------------------------------------------------
// Copyright (C) 2026 Eliot Muir.  All rights reserved.
//
// Module: CORvarJson
//
// Description:
//
// This is a new parser for JSON.
//
// Author: Eliot Muir 
// ---------------------------------------------------------------------------

class CORstring;
class CORvar;

bool CORparseJson(const char* pData, CORvar* pOutput);
bool CORparseJson(const CORstring& Data, CORvar* pOutput);
