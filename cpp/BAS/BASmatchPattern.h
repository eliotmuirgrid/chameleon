#pragma once
//-------------------------------------------------------
// Copyright (C) 2026 Eliot Muir.  All rights reserved.
//
// BASmatchPattern
//
// Pattern matching for strings (glob-style segments with optional + / - token lists).
//-------------------------------------------------------

bool BASmatchPattern(const char* pTarget, const char* pPattern);
