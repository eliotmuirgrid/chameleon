#pragma once
//-------------------------------------------------------
// Copyright (C) 2026 Eliot Muir.  All rights reserved.
//
// BASfile
//
// Cross-platform helpers for POSIX-style integer file descriptors (small integers
// that stand for an open file). On POSIX these are open(2)/close(2). On Windows
// they are the CRT _open/_close family (also int), not a raw HANDLE.
//
// Most callers: BASfileRead(Path, ...) / BASfileWrite(Path, ...) for whole-file I/O. For
// manual control, use BASfileOpenRead / BASfileOpenWrite, then BASfileRead(fd, ...) /
// BASfileWrite(fd, ...) / BASfilePosition / BASfileSize, then BASfileClose or BASfileAutoClose.
// Writable convenience opens use O_CREAT (create if missing) and do not truncate; delete
// the file first if you need an empty file. Whole-file BASfileWrite(Path, ...) uses O_TRUNC
// and the given CreateMode when creating.
//
// CreateMode (writes only): permission bits used when O_CREAT creates a new file. Reading
// does not take a mode and does not change on-disk permissions.
//
// Portable: use the BASfileCreateMode_* macros below—same names on every platform. On POSIX
// they expand to octal modes for open(2). On Windows they expand to CRT _open pmode values
// (same effect as _S_IREAD | _S_IWRITE | …). The CRT model is coarse: it does not reproduce Unix group/other
// bits, so BASfileCreateMode_Private and BASfileCreateMode_DefaultDataFile map to the same
// Windows value; the distinction applies on POSIX.
//
// POSIX-only (advanced): you may pass any valid open(2) mode (e.g. 0600, 0644, 0755) when
// building for non-Windows; do not rely on that for portable builds.
//
// Return values (errors):
//   BASfileOpenRead / BASfileOpenWrite: fd >= 0 on success, or -1 on failure.
//   BASfileClose: 0 on success, -1 on error (if pError non-null, set on failure only).
//   BASfilePosition, BASfilePositionSet, BASfileSize: BASint64 result, or -1 on error.
//   BASfileRead (fd): byte count read (>= 0), 0 at end of file, or -1 on error.
//-------------------------------------------------------

#include <BAS/BAStypes.h>
#include <stddef.h>

class BASstring;

// CreateMode presets (no extra #includes): same intent on every OS. Non-Windows: octal for
// open(2). Windows: numeric pmode equivalent to MSVC _S_IREAD|_S_IWRITE|_S_IEXEC (0x0100,
// 0x0080, 0x0040) so we do not #include <sys/stat.h> here.
#if defined(_WIN32) || defined(WIN32)
#define BASfileCreateMode_Private (0x0100 | 0x0080)
#define BASfileCreateMode_DefaultDataFile (0x0100 | 0x0080)
#define BASfileCreateMode_Executable (0x0100 | 0x0080 | 0x0040)
#else
#define BASfileCreateMode_Private 0600
#define BASfileCreateMode_DefaultDataFile 0644
#define BASfileCreateMode_Executable 0755
#endif

// Whole-file path helpers (most callers start here). BASfileWrite(Path, ...) replaces the
// file (O_TRUNC). CreateMode matches BASfileOpenWrite. Line splitting or joining is left to
// callers. On failure, returns false; if pError is non-null, it is replaced with a short
// message (often including BASerrorStringFromErrno). On success, pError is cleared when non-null.
bool BASfileRead(const BASstring& Path, BASstring* pContent, BASstring* pError = nullptr);
bool BASfileWrite(const BASstring& Path, const BASstring& Content, int CreateMode, BASstring* pError = nullptr);

bool BASfileExists(const BASstring& Path);
bool BASfileIsDirectory(const BASstring& Path);
bool BASfileIsExecutable(const BASstring& Path);
bool BASfileIsReadable(const BASstring& Path);
bool BASfileIsWritable(const BASstring& Path);
bool BASfileDelete(const BASstring& Path, BASstring* pError = nullptr);

// Simple opens: read-only vs writable (O_CREAT). CreateMode applies when a new file is
// created on write; see file banner. Returns -1 on failure, or a non-negative fd on success.
int BASfileOpenRead(const BASstring& Path, BASstring* pErrorMessage);
int BASfileOpenWrite(const BASstring& Path, int CreateMode = BASfileCreateMode_DefaultDataFile, BASstring* pErrorMessage = nullptr);


int BASfileClose(int FileDescriptor, BASstring* pError = nullptr);

// Owns a non-negative file descriptor and closes it in the destructor. Move-only; use
// release() to hand the fd to something else without closing, or reset() to replace it.
class BASfileAutoClose {
public:
   BASfileAutoClose() : m_FileDescriptor(-1) {}
   explicit BASfileAutoClose(int FileDescriptor) : m_FileDescriptor(FileDescriptor) {}
   ~BASfileAutoClose() { closeIfOpen(); }

   BASfileAutoClose(const BASfileAutoClose&) = delete;
   BASfileAutoClose& operator=(const BASfileAutoClose&) = delete;

   BASfileAutoClose(BASfileAutoClose&& Other) : m_FileDescriptor(Other.m_FileDescriptor) {
      Other.m_FileDescriptor = -1;
   }
   BASfileAutoClose& operator=(BASfileAutoClose&& Other) {
      if (this != &Other) {
         closeIfOpen();
         m_FileDescriptor = Other.m_FileDescriptor;
         Other.m_FileDescriptor = -1;
      }
      return *this;
   }

   int descriptor() const { return m_FileDescriptor; }
   bool isOpen() const { return m_FileDescriptor >= 0; }
   int release() {
      int FileDescriptor = m_FileDescriptor;
      m_FileDescriptor = -1;
      return FileDescriptor;
   }
   void reset(int FileDescriptor = -1) {
      closeIfOpen();
      m_FileDescriptor = FileDescriptor;
   }

private:
   void closeIfOpen() {
      if (m_FileDescriptor >= 0) {
         BASfileClose(m_FileDescriptor, nullptr);
         m_FileDescriptor = -1;
      }
   }
   int m_FileDescriptor;
};

BASint64 BASfilePosition(int FileDescriptor);
BASint64 BASfilePositionSet(int FileDescriptor, BASint64 AbsoluteOffset);
BASint64 BASfileRead(int FileDescriptor, void* Buffer, size_t Size);
BASint64 BASfileWrite(int FileDescriptor, const void* Buffer, size_t Size);
BASint64 BASfileSize(int FileDescriptor);