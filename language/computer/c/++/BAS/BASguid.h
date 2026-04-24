#pragma once
//-------------------------------------------------------
// Copyright (C) 2026 Eliot Muir. All rights reserved.
//
// BASguid — human-readable random identifiers from OS-quality entropy.
//
// BASguid(Size) returns a BASstring of exactly `Size` characters when possible:
//   Size <= 0 or Size > 4096 — empty string.
//   Size == 36 — RFC 4122 UUID version 4 (lowercase hex with hyphens).
//   Size == 32 — same 16 bytes as a v4 UUID, formatted as 32 lowercase hex digits (no hyphens).
//   otherwise — `Size` lowercase hex digits from random bytes (no UUID structure).
//
// Concurrent calls do not share mutable state (thread-safe).
//-------------------------------------------------------

#include <BAS/BASstring.h>

BASstring BASguid(int Size);
