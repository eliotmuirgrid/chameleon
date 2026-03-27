#pragma once
//---------------------------------------------------------------------------
// Copyright (C) 2026 Eliot Muir.  All rights reserved.
//
// Description:
//
// CORwindows.h
//
// Since Microsoft is such a screwed up entity that it requires workarounds like
// disabling of warnings 4005 etc I think it makes sense to have one place we include
// windows.h and centralize it in COR.  My opinion hasn't changed.
//
// Author: Eliot Muir
//---------------------------------------------------------------------------

#ifdef _WIN32
   #define NOMINMAX // needed because Windows defines macros min and max by default and we need it to not do so
   #define WIN32_LEAN_AND_MEAN      // Exclude rarely-used stuff from Windows headers
   #pragma warning( disable : 4005 ) // Stupid http://stackoverflow.com/questions/23178739/what-is-causing-this-visual-studio-pro-2013-warning
   #include <windows.h>
   #pragma warning( default : 4005 ) // Stupid http://stackoverflow.com/questions/23178739/what-is-causing-this-visual-studio-pro-2013-warning
#endif
