//-------------------------------------------------------
// Copyright (C) 2026 Eliot Muir.  All rights reserved.
//
// BASfile
//-------------------------------------------------------

#include <BAS/BASfile.h>

#include <fcntl.h>
#ifdef WIN32
#include <io.h>
#define BASfile_impl_open _open
#define BASfile_impl_close _close
#else
#include <unistd.h>
#define BASfile_impl_open open
#define BASfile_impl_close close
#endif

int BASfileOpen(const char* Path, int OpenFlags, int Mode) {
   return BASfile_impl_open(Path, OpenFlags, Mode);
}

int BASfileClose(int FileDescriptor) {
   return BASfile_impl_close(FileDescriptor);
}
