#pragma once
//---------------------------------------------------------------------------
// Copyright (C) 2026 Eliot Muir.  All rights reserved.
//
// Module: CORcore.h 
//
// Author: Eliot Muir
//
// Description:
//
// Defines the fundamental types, platform abstractions, compiler
// normalizations, and DLL interface macros used throughout the codebase.
// This file establishes a consistent, portable base layer across all
// supported platforms.
//
// A lot of code that participates in the COR ecosystem may need to include this
// header as its lowest-level dependency.
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Forward declarations
//---------------------------------------------------------------------------

class CORostream;


//---------------------------------------------------------------------------
// Standard headers (C-style, global namespace)
//---------------------------------------------------------------------------

#include <stddef.h>
#include <string.h>


//---------------------------------------------------------------------------
// Platform compatibility
//---------------------------------------------------------------------------

#if defined(_WIN32)
#   define strdup      _strdup
#   define strcasecmp  _stricmp
#   define access      _access
#endif


//---------------------------------------------------------------------------
// Compiler configuration
//---------------------------------------------------------------------------

#ifdef _WIN32

// Disable Microsoft's "unsafe CRT" warnings.
#   pragma warning(disable: 4996)

// Treat incomplete-type destructor issues as errors.
#   pragma warning(error: 4150)

// Disable unreferenced local variable warnings.
#   pragma warning(disable: 4101)

#endif


//---------------------------------------------------------------------------
// Platform markers
//---------------------------------------------------------------------------

#ifdef _WIN64
#   ifndef COR_64
#      define COR_64
#   endif
#endif


//---------------------------------------------------------------------------
// Fundamental COR types
//---------------------------------------------------------------------------

#define CORint8   char
#define CORuint8  unsigned CORint8

#define CORint16  short
#define CORuint16 unsigned CORint16

#define CORint32  int
#define CORuint32 unsigned CORint32

#ifndef _WIN32
#   define CORint64 long long
#else
#   define CORint64 __int64
#endif

#define CORuint64 unsigned CORint64

#define CORfloat32 float
#define CORfloat64 double

#define CORindex   size_t

//---------------------------------------------------------------------------
// Sentinel values
//---------------------------------------------------------------------------

// Value representing "not found" for index-based operations.
// Defined as the maximum value of CORindex.
constexpr CORindex COR_NPOS = static_cast<CORindex>(-1);


//---------------------------------------------------------------------------
// DLL export/import support
//---------------------------------------------------------------------------
//
// Files built as part of DLL should define COR_DLL_EXPORTS.
// Code consuming the DLL should define COR_DLL_IMPORTS.
// Otherwise these macros expand to nothing.
//

#ifdef COR_DLL_EXPORTS
#   define COR_DLL __declspec(dllexport)
#   define COR_DLL_FUNC(X) COR_DLL X
#else
#   ifdef COR_DLL_IMPORTS
#      define COR_DLL __declspec(dllimport)
#      define COR_DLL_FUNC(X) COR_DLL X
#   else
#      define COR_DLL
#      define COR_DLL_FUNC(X) X
#   endif
#endif


//---------------------------------------------------------------------------
// Calling convention macros
//---------------------------------------------------------------------------

#ifdef _WIN32
#   define COR_STD_CALL __stdcall
#   define COR_C_DECL   __cdecl
#else
#   define COR_STD_CALL
#   define COR_C_DECL
#endif


//---------------------------------------------------------------------------
// Integer helpers
//---------------------------------------------------------------------------

constexpr CORuint16 COR_HI32(CORuint32 value){
   return (CORuint16)((value >> 16) & 0xFFFF);
}

constexpr CORuint16 COR_LO32(CORuint32 value){
   return (CORuint16)(value & 0xFFFF);
}

constexpr CORuint32 COR_MAKE32(CORuint16 low, CORuint16 high){
   return (CORuint32)low | ((CORuint32)high << 16);
}


//---------------------------------------------------------------------------
// Numeric limits
//---------------------------------------------------------------------------


#define COR_UINT_64_MAX ((CORuint64)(~(CORuint64)0))
#define COR_UINT_32_MAX ((CORuint32)(~(CORuint32)0))
#define COR_UINT_16_MAX ((CORuint16)(~(CORuint16)0))
#define COR_UINT_8_MAX  ((CORuint8)(~(CORuint8)0))

#define COR_INT_64_MAX  ((CORint64)(COR_UINT_64_MAX >> 1))
#define COR_INT_32_MAX  ((CORint32)(COR_UINT_32_MAX >> 1))
#define COR_INT_16_MAX  ((CORint16)(COR_UINT_16_MAX >> 1))
#define COR_INT_8_MAX   ((CORint8)(COR_UINT_8_MAX >> 1))

#define COR_INT_64_MIN  ((CORint64)(~COR_INT_64_MAX))
#define COR_INT_32_MIN  ((CORint32)(~COR_INT_32_MAX))
#define COR_INT_16_MIN  ((CORint16)(~COR_INT_16_MAX))
#define COR_INT_8_MIN   ((CORint8)(~COR_INT_8_MAX))

#define COR_FLOAT_64_MAX ((CORfloat64)1.7976931348623157e+308)


//---------------------------------------------------------------------------
// Small utility functions
//---------------------------------------------------------------------------

template <class T>
constexpr const T& COR_MIN(const T& a, const T& b) {
   return (b < a) ? b : a;
}

template <class T>
constexpr const T& COR_MAX(const T& a, const T& b) {
   return (a < b) ? b : a;
}

template <class T>
constexpr T COR_ABS(T value) {
   return (value < 0) ? -value : value;
}
