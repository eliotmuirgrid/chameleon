#pragma once
//-------------------------------------------------------
// Copyright (C) 2026 Eliot Muir.  All rights reserved.
//
// BAStypes
//
//   Computers store whole numbers in fixed-size chunks of bits. Bigger chunks can
//   hold larger values. Some types allow negative numbers; others (names starting
//   with BASuint) only allow zero and positive values, which is common for sizes
//   and counts that are never negative.
//
//   This header gives simple BAS names for those standard sizes: BASint8 and
//   BASuint8 are the smallest; BASint16/BASuint16 are larger; BASint32/BASuint32
//   are typical "everyday" sizes; BASint64/BASuint64 are for very large values
//   (for example big file sizes or positions).
//
//   "Portable" here means each name always refers to the same size on the machines
//   this project supports, so behavior does not change silently when you build on
//   different computers or compilers.
//
//   In short: friendly names for fixed-size integers so BAS code stays readable
//   and consistent. The typedefs below match the usual C stdint names (int8_t,
//   uint64_t, etc.).
//-------------------------------------------------------

#include <stdint.h>

typedef int8_t BASint8;
typedef uint8_t BASuint8;

typedef int16_t BASint16;
typedef uint16_t BASuint16;

typedef int32_t BASint32;
typedef uint32_t BASuint32;

typedef int64_t BASint64;
typedef uint64_t BASuint64;
