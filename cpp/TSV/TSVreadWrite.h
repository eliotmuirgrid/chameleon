#pragma once
// Copyright (C) 2026 Eliot Muir. All rights reserved.
//
// Module: TSVreadWrite
//
// Tab-separated values (TSV): parse and format tables in memory. Field separator is tab
// (U+0009); row separator is newline (LF, optionally CRLF on input). Load/save paths use
// BASfileRead / BASfileWrite with TSVparse / TSVformat (RISC-style composition).

#include <BAS/BASarray.h>
#include <BAS/BASstring.h>

// One row: ordered fields (columns), indexed from zero.
typedef BASarray<BASstring> TSVrow;

// Full file content: ordered rows; each row is an array of field strings.
typedef BASarray<TSVrow> TSVtable;

// Parse TSV from memory. On failure, returns false and may set *pError.
bool TSVparse(const BASstring& Content, TSVtable* pTable, BASstring* pError = nullptr);

// Serialize a table to TSV text (LF between rows, tab between fields). On failure, returns false.
bool TSVformat(const TSVtable& Table, BASstring* pContent, BASstring* pError = nullptr);
