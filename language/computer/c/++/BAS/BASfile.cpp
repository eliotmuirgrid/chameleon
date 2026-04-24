//-------------------------------------------------------
// Copyright (C) 2026 Eliot Muir.  All rights reserved.
//
// BASfile
//-------------------------------------------------------

#include <BAS/BASfile.h>

#include <BAS/BASerror.h>
#include <BAS/BASstring.h>

#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>

#ifdef WIN32
#include <io.h>
#include <sys/stat.h>
#include <sys/types.h>
#define BASfile_impl_open _open
#define BASfile_impl_close _close
#define BASfile_impl_write _write
#else
#include <strings.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#define BASfile_impl_open open
#define BASfile_impl_close close
#define BASfile_impl_write write
#endif

static void BASfileSetErrnoMessage(BASstring* pError, const char* pPrefix) {
   if (!pError) {
      return;
   }
   pError->clear();
   pError->append(pPrefix);
   pError->append(BASerrorStringFromErrno(errno));
}

#ifndef WIN32
#define BASfile_strcasecmp strcasecmp
#else
#define BASfile_stricmp _stricmp
#endif

static bool BASfileEndsWithInsensitive(const BASstring& Path, const char* Suffix) {
   const int SuffixLength = (int)strlen(Suffix);
   if (Path.size() < SuffixLength) {
      return false;
   }
   const char* Start = Path.c_str() + Path.size() - SuffixLength;
#ifdef WIN32
   return BASfile_stricmp(Start, Suffix) == 0;
#else
   return BASfile_strcasecmp(Start, Suffix) == 0;
#endif
}

bool BASfileExists(const BASstring& Path) {
#ifdef WIN32
   struct _stati64 FileStat;
   return _stati64(Path.c_str(), &FileStat) == 0;
#else
   struct stat FileStat;
   return stat(Path.c_str(), &FileStat) == 0;
#endif
}

bool BASfileIsDirectory(const BASstring& Path) {
#ifdef WIN32
   struct _stati64 FileStat;
   if (_stati64(Path.c_str(), &FileStat) != 0) {
      return false;
   }
   return (FileStat.st_mode & _S_IFMT) == _S_IFDIR;
#else
   struct stat FileStat;
   if (stat(Path.c_str(), &FileStat) != 0) {
      return false;
   }
   return S_ISDIR(FileStat.st_mode);
#endif
}

bool BASfileIsExecutable(const BASstring& Path) {
#ifdef WIN32
   struct _stati64 FileStat;
   if (_stati64(Path.c_str(), &FileStat) != 0) {
      return false;
   }
   if ((FileStat.st_mode & _S_IFMT) != _S_IFREG) {
      return false;
   }
   return BASfileEndsWithInsensitive(Path, ".exe") || BASfileEndsWithInsensitive(Path, ".com")
       || BASfileEndsWithInsensitive(Path, ".bat") || BASfileEndsWithInsensitive(Path, ".cmd")
       || BASfileEndsWithInsensitive(Path, ".ps1");
#else
   struct stat FileStat;
   if (stat(Path.c_str(), &FileStat) != 0) {
      return false;
   }
   if (!S_ISREG(FileStat.st_mode)) {
      return false;
   }
   return access(Path.c_str(), X_OK) == 0;
#endif
}

bool BASfileIsReadable(const BASstring& Path) {
#ifdef WIN32
   return _access(Path.c_str(), 04) == 0;
#else
   return access(Path.c_str(), R_OK) == 0;
#endif
}

bool BASfileIsWritable(const BASstring& Path) {
#ifdef WIN32
   return _access(Path.c_str(), 02) == 0;
#else
   return access(Path.c_str(), W_OK) == 0;
#endif
}

bool BASfileDelete(const BASstring& Path, BASstring* pError) {
   if (pError) {
      pError->clear();
   }
   if (remove(Path.c_str()) != 0) {
      BASfileSetErrnoMessage(pError, "remove: ");
      return false;
   }
   return true;
}

int BASfileOpenRead(const BASstring& Path, BASstring* pErrorMessage) {
   if (pErrorMessage) {
      pErrorMessage->clear();
   }
#ifdef WIN32
   int FileDescriptor = BASfile_impl_open(Path.c_str(), _O_RDONLY | _O_BINARY, 0);
#else
   int FileDescriptor = BASfile_impl_open(Path.c_str(), O_RDONLY, 0);
#endif
   if (FileDescriptor < 0) {
      BASfileSetErrnoMessage(pErrorMessage, "open: ");
   }
   return FileDescriptor;
}

int BASfileOpenWrite(const BASstring& Path, int CreateMode, BASstring* pErrorMessage) {
   if (pErrorMessage) {
      pErrorMessage->clear();
   }
#ifdef WIN32
   int FileDescriptor = BASfile_impl_open(Path.c_str(), _O_WRONLY | _O_CREAT | _O_BINARY, CreateMode);
#else
   int FileDescriptor = BASfile_impl_open(Path.c_str(), O_WRONLY | O_CREAT, CreateMode);
#endif
   if (FileDescriptor < 0) {
      BASfileSetErrnoMessage(pErrorMessage, "open: ");
   }
   return FileDescriptor;
}

int BASfileClose(int FileDescriptor, BASstring* pError) {
   int Result = BASfile_impl_close(FileDescriptor);
   if (Result != 0) {
      BASfileSetErrnoMessage(pError, "close: ");
   }
   return Result;
}

BASint64 BASfilePosition(int FileDescriptor) {
#ifndef WIN32
   off_t Position = lseek(FileDescriptor, 0, SEEK_CUR);
   if (Position == (off_t)-1) {
      return -1;
   }
   return (BASint64)Position;
#else
   __int64 Position = _lseeki64(FileDescriptor, 0, SEEK_CUR);
   if (Position == -1) {
      return -1;
   }
   return (BASint64)Position;
#endif
}

BASint64 BASfilePositionSet(int FileDescriptor, BASint64 AbsoluteOffset) {
#ifndef WIN32
   off_t Position = lseek(FileDescriptor, (off_t)AbsoluteOffset, SEEK_SET);
   if (Position == (off_t)-1) {
      return -1;
   }
   return (BASint64)Position;
#else
   __int64 Position = _lseeki64(FileDescriptor, (__int64)AbsoluteOffset, SEEK_SET);
   if (Position == -1) {
      return -1;
   }
   return (BASint64)Position;
#endif
}

BASint64 BASfileRead(int FileDescriptor, void* Buffer, size_t Size) {
#ifndef WIN32
   ssize_t ReadCount = read(FileDescriptor, Buffer, Size);
   if (ReadCount < 0) {
      return -1;
   }
   return (BASint64)ReadCount;
#else
   size_t ChunkSize = Size;
   if (ChunkSize > (size_t)0x7FFFFFFF) {
      ChunkSize = (size_t)0x7FFFFFFF;
   }
   int ReadCount = _read(FileDescriptor, Buffer, (unsigned int)ChunkSize);
   if (ReadCount < 0) {
      return -1;
   }
   return (BASint64)ReadCount;
#endif
}

BASint64 BASfileWrite(int FileDescriptor, const void* Buffer, size_t Size) {
#ifndef WIN32
   ssize_t Written = BASfile_impl_write(FileDescriptor, Buffer, Size);
   if (Written < 0) {
      return -1;
   }
   return (BASint64)Written;
#else
   size_t ChunkSize = Size;
   if (ChunkSize > (size_t)0x7FFFFFFF) {
      ChunkSize = (size_t)0x7FFFFFFF;
   }
   int Written = BASfile_impl_write(FileDescriptor, Buffer, (unsigned int)ChunkSize);
   if (Written < 0) {
      return -1;
   }
   return (BASint64)Written;
#endif
}

BASint64 BASfileSize(int FileDescriptor) {
#ifndef WIN32
   struct stat FileStat;
   if (fstat(FileDescriptor, &FileStat) != 0) {
      return -1;
   }
   return (BASint64)FileStat.st_size;
#else
   struct _stati64 FileStat;
   if (_fstati64(FileDescriptor, &FileStat) != 0) {
      return -1;
   }
   return (BASint64)FileStat.st_size;
#endif
}

bool BASfileRead(const BASstring& Path, BASstring* pContent, BASstring* pError) {
   BAS_ASSERT(pContent);
   if (pError) {
      pError->clear();
   }
   pContent->clear();
#ifdef WIN32
   int FileDescriptor = BASfile_impl_open(Path.c_str(), _O_RDONLY | _O_BINARY, 0);
#else
   int FileDescriptor = BASfile_impl_open(Path.c_str(), O_RDONLY, 0);
#endif
   if (FileDescriptor < 0) {
      BASfileSetErrnoMessage(pError, "open: ");
      return false;
   }
   BASint64 ByteLength = BASfileSize(FileDescriptor);
   if (ByteLength < 0) {
      BASfileSetErrnoMessage(pError, "size: ");
      BASfileClose(FileDescriptor, nullptr);
      return false;
   }
   if (ByteLength > (BASint64)INT_MAX) {
      if (pError) {
         pError->clear();
         pError->append("read: file too large");
      }
      BASfileClose(FileDescriptor, nullptr);
      return false;
   }
   int TotalBytes = (int)ByteLength;
   if (TotalBytes > 0) {
      pContent->setCapacity(TotalBytes);
      pContent->setSize(TotalBytes);
      char* Dest = pContent->data();
      BASint64 Offset = 0;
      while (Offset < ByteLength) {
         BASint64 Chunk = BASfileRead(FileDescriptor, Dest + Offset, (size_t)(ByteLength - Offset));
         if (Chunk < 0) {
            BASfileSetErrnoMessage(pError, "read: ");
            pContent->clear();
            BASfileClose(FileDescriptor, nullptr);
            return false;
         }
         if (Chunk == 0) {
            if (pError) {
               pError->clear();
               pError->append("read: unexpected end of file");
            }
            pContent->clear();
            BASfileClose(FileDescriptor, nullptr);
            return false;
         }
         Offset += Chunk;
      }
   }
   if (BASfileClose(FileDescriptor, pError) != 0) {
      pContent->clear();
      return false;
   }
   return true;
}

bool BASfileWrite(const BASstring& Path, const BASstring& Content, int CreateMode, BASstring* pError) {
   if (pError) {
      pError->clear();
   }
#ifdef WIN32
   int FileDescriptor = BASfile_impl_open(Path.c_str(), _O_WRONLY | _O_CREAT | _O_TRUNC | _O_BINARY, CreateMode);
#else
   int FileDescriptor = BASfile_impl_open(Path.c_str(), O_WRONLY | O_CREAT | O_TRUNC, CreateMode);
#endif
   if (FileDescriptor < 0) {
      BASfileSetErrnoMessage(pError, "open: ");
      return false;
   }
   const char* Data = Content.data();
   int Remaining = Content.size();
   while (Remaining > 0) {
      BASint64 Chunk = BASfileWrite(FileDescriptor, Data, (size_t)Remaining);
      if (Chunk < 0) {
         BASfileSetErrnoMessage(pError, "write: ");
         BASfileClose(FileDescriptor, nullptr);
         return false;
      }
      if (Chunk == 0) {
         if (pError) {
            pError->clear();
            pError->append("write: wrote 0 bytes");
         }
         BASfileClose(FileDescriptor, nullptr);
         return false;
      }
      Data += (int)Chunk;
      Remaining -= (int)Chunk;
   }
   if (BASfileClose(FileDescriptor, pError) != 0) {
      return false;
   }
   return true;
}
