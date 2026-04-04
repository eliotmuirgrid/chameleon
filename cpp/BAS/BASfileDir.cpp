//-------------------------------------------------------
// Copyright (C) 2026 Eliot Muir.  All rights reserved.
//
// BASfileDir
//
// Implementation
//-------------------------------------------------------

#include <BAS/BASfile.h>
#include <BAS/BASfileDir.h>

#include <BAS/BASerror.h>
#include <BAS/BASstring.h>

#include <errno.h>
#include <cstring>

#ifdef WIN32
#include <direct.h>
#include <io.h>
#else
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#endif

static void BASfileDirSetErrnoMessage(BASstring* pError, const char* pPrefix) {
   if (!pError) {
      return;
   }
   pError->clear();
   pError->append(pPrefix);
   pError->append(BASerrorStringFromErrno(errno));
}

static bool BASfileDirEndsWithSeparator(const BASstring& Path) {
   const int ByteCount = Path.size();
   if (ByteCount == 0) {
      return false;
   }
   const char Ch = Path[ByteCount - 1];
   return Ch == '/' || Ch == '\\';
}

static char BASfileDirNativeSeparator() {
#ifdef WIN32
   return '\\';
#else
   return '/';
#endif
}

BASstring BASfileDirJoin(const BASstring& Directory, const BASstring& FileName) {
   if (Directory.empty()) {
      return FileName;
   }
   if (FileName.empty()) {
      return Directory;
   }
   BASstring Result = Directory;
   if (!BASfileDirEndsWithSeparator(Result)) {
      Result += BASfileDirNativeSeparator();
   }
   Result += FileName;
   return Result;
}

BASstring BASfileDirFileName(const BASstring& Path) {
   int End = Path.size();
   while (End > 0) {
      const char Ch = Path[End - 1];
      if (Ch != '/' && Ch != '\\') {
         break;
      }
      End--;
   }
   if (End == 0) {
      return BASstring();
   }
   int LastSeparator = -1;
   for (int i = End - 1; i >= 0; i--) {
      const char Ch = Path[i];
      if (Ch == '/' || Ch == '\\') {
         LastSeparator = i;
         break;
      }
   }
   if (LastSeparator < 0) {
      return BASstring(Path.c_str(), End);
   }
   return BASstring(Path.c_str() + LastSeparator + 1, End - LastSeparator - 1);
}

BASstring BASfileDirParent(const BASstring& Path) {
   int End = Path.size();
   while (End > 0) {
      const char Ch = Path[End - 1];
      if (Ch != '/' && Ch != '\\') {
         break;
      }
      End--;
   }
   if (End == 0) {
      return BASstring(".");
   }
   int LastSeparator = -1;
   for (int i = End - 1; i >= 0; i--) {
      const char Ch = Path[i];
      if (Ch == '/' || Ch == '\\') {
         LastSeparator = i;
         break;
      }
   }
   if (LastSeparator < 0) {
      return BASstring(".");
   }
   if (LastSeparator == 0) {
      return BASstring(Path.c_str(), 1);
   }
   return BASstring(Path.c_str(), LastSeparator + 1);
}

static bool BASfileDirMkdirOne(const BASstring& Path, int CreateMode, BASstring* pError) {
#ifdef WIN32
   (void)CreateMode;
   const int Result = _mkdir(Path.c_str());
#else
   const int Result = mkdir(Path.c_str(), (mode_t)CreateMode);
#endif
   if (Result == 0) {
      return true;
   }
   if (errno == EEXIST && BASfileIsDirectory(Path)) {
      return true;
   }
   BASfileDirSetErrnoMessage(pError, "mkdir: ");
   return false;
}

bool BASfileDirCreate(const BASstring& Path, int CreateMode, BASstring* pError) {
   if (pError) {
      pError->clear();
   }
   if (Path.empty()) {
      if (pError) {
         pError->append("mkdir: empty path");
      }
      return false;
   }
   if (BASfileIsDirectory(Path)) {
      return true;
   }
   BASstring Parent = BASfileDirParent(Path);
   if (!Parent.empty() && Parent != Path && !BASfileIsDirectory(Parent)) {
      if (!BASfileDirCreate(Parent, CreateMode, pError)) {
         return false;
      }
   }
   return BASfileDirMkdirOne(Path, CreateMode, pError);
}

struct BASfileDirIteratorImpl {
   BASstring DirectoryPath;
   BASstring EntryName;
   bool EntryIsDirectory;
   bool AtEnd;
#ifdef WIN32
   intptr_t FindHandle;
#else
   DIR* Dir;
#endif
};

static void BASfileDirIteratorClose(BASfileDirIteratorImpl* pImpl) {
   if (!pImpl) {
      return;
   }
#ifdef WIN32
   if (pImpl->FindHandle != static_cast<intptr_t>(-1)) {
      _findclose(pImpl->FindHandle);
      pImpl->FindHandle = static_cast<intptr_t>(-1);
   }
#else
   if (pImpl->Dir) {
      closedir(pImpl->Dir);
      pImpl->Dir = nullptr;
   }
#endif
}

static void BASfileDirIteratorSetIsDirectoryFromEntry(BASfileDirIteratorImpl* pImpl) {
   const BASstring FullPath = BASfileDirJoin(pImpl->DirectoryPath, pImpl->EntryName);
   pImpl->EntryIsDirectory = BASfileIsDirectory(FullPath);
}

#ifndef WIN32
static void BASfileDirIteratorAdvancePosix(BASfileDirIteratorImpl* pImpl) {
   if (!pImpl->Dir) {
      pImpl->AtEnd = true;
      pImpl->EntryName.clear();
      return;
   }
   for (;;) {
      struct dirent* pEntry = readdir(pImpl->Dir);
      if (!pEntry) {
         pImpl->AtEnd = true;
         pImpl->EntryName.clear();
         return;
      }
      if (strcmp(pEntry->d_name, ".") == 0 || strcmp(pEntry->d_name, "..") == 0) {
         continue;
      }
      pImpl->EntryName = pEntry->d_name;
      pImpl->AtEnd = false;
#ifdef DT_DIR
      if (pEntry->d_type == DT_DIR) {
         pImpl->EntryIsDirectory = true;
      } else
# ifdef DT_REG
      if (pEntry->d_type == DT_REG) {
         pImpl->EntryIsDirectory = false;
      } else
# endif
      {
         BASfileDirIteratorSetIsDirectoryFromEntry(pImpl);
      }
#else
      BASfileDirIteratorSetIsDirectoryFromEntry(pImpl);
#endif
      return;
   }
}

static bool BASfileDirIteratorOpenPosix(BASfileDirIteratorImpl* pImpl) {
   BASfileDirIteratorClose(pImpl);
   pImpl->Dir = opendir(pImpl->DirectoryPath.c_str());
   if (!pImpl->Dir) {
      pImpl->AtEnd = true;
      pImpl->EntryName.clear();
      return false;
   }
   return true;
}
#else
static void BASfileDirIteratorAdvanceWindows(BASfileDirIteratorImpl* pImpl) {
   if (pImpl->FindHandle == static_cast<intptr_t>(-1)) {
      pImpl->AtEnd = true;
      pImpl->EntryName.clear();
      return;
   }
   for (;;) {
      struct _finddata_t FileData;
      const int NextResult = _findnext(pImpl->FindHandle, &FileData);
      if (NextResult != 0) {
         BASfileDirIteratorClose(pImpl);
         pImpl->AtEnd = true;
         pImpl->EntryName.clear();
         return;
      }
      if (strcmp(FileData.name, ".") == 0 || strcmp(FileData.name, "..") == 0) {
         continue;
      }
      pImpl->EntryName = FileData.name;
      pImpl->AtEnd = false;
      pImpl->EntryIsDirectory = (FileData.attrib & _A_SUBDIR) != 0;
      return;
   }
}

static bool BASfileDirIteratorOpenWindows(BASfileDirIteratorImpl* pImpl) {
   BASfileDirIteratorClose(pImpl);
   const BASstring Pattern = BASfileDirJoin(pImpl->DirectoryPath, BASstring("*"));
   struct _finddata_t FileData;
   const intptr_t Handle = _findfirst(Pattern.c_str(), &FileData);
   if (Handle == static_cast<intptr_t>(-1)) {
      pImpl->FindHandle = static_cast<intptr_t>(-1);
      pImpl->AtEnd = true;
      pImpl->EntryName.clear();
      return false;
   }
   pImpl->FindHandle = Handle;
   for (;;) {
      if (strcmp(FileData.name, ".") == 0 || strcmp(FileData.name, "..") == 0) {
         if (_findnext(pImpl->FindHandle, &FileData) != 0) {
            BASfileDirIteratorClose(pImpl);
            pImpl->AtEnd = true;
            pImpl->EntryName.clear();
            return true;
         }
         continue;
      }
      pImpl->EntryName = FileData.name;
      pImpl->AtEnd = false;
      pImpl->EntryIsDirectory = (FileData.attrib & _A_SUBDIR) != 0;
      return true;
   }
}
#endif

BASfileDirIterator::BASfileDirIterator() : m_pImpl(nullptr) {
}

BASfileDirIterator::BASfileDirIterator(const BASstring& DirectoryPath) : m_pImpl(new BASfileDirIteratorImpl) {
   m_pImpl->DirectoryPath = DirectoryPath;
   m_pImpl->EntryIsDirectory = false;
   m_pImpl->AtEnd = true;
#ifdef WIN32
   m_pImpl->FindHandle = static_cast<intptr_t>(-1);
   BASfileDirIteratorOpenWindows(m_pImpl);
#else
   m_pImpl->Dir = nullptr;
   if (BASfileDirIteratorOpenPosix(m_pImpl)) {
      BASfileDirIteratorAdvancePosix(m_pImpl);
   }
#endif
}

BASfileDirIterator::~BASfileDirIterator() {
   if (m_pImpl) {
      BASfileDirIteratorClose(m_pImpl);
      delete m_pImpl;
      m_pImpl = nullptr;
   }
}

BASfileDirIterator::BASfileDirIterator(BASfileDirIterator&& Rhs) noexcept : m_pImpl(Rhs.m_pImpl) {
   Rhs.m_pImpl = nullptr;
}

BASfileDirIterator& BASfileDirIterator::operator=(BASfileDirIterator&& Rhs) noexcept {
   if (this != &Rhs) {
      if (m_pImpl) {
         BASfileDirIteratorClose(m_pImpl);
         delete m_pImpl;
      }
      m_pImpl = Rhs.m_pImpl;
      Rhs.m_pImpl = nullptr;
   }
   return *this;
}

void BASfileDirIterator::positionAtBegin() {
   if (!m_pImpl) {
      return;
   }
#ifdef WIN32
   BASfileDirIteratorOpenWindows(m_pImpl);
#else
   if (BASfileDirIteratorOpenPosix(m_pImpl)) {
      BASfileDirIteratorAdvancePosix(m_pImpl);
   }
#endif
}

void BASfileDirIterator::positionAtEnd() {
   if (!m_pImpl) {
      return;
   }
   BASfileDirIteratorClose(m_pImpl);
   m_pImpl->AtEnd = true;
   m_pImpl->EntryName.clear();
}

void BASfileDirIterator::operator++() {
   if (!m_pImpl || m_pImpl->AtEnd) {
      return;
   }
#ifdef WIN32
   BASfileDirIteratorAdvanceWindows(m_pImpl);
#else
   BASfileDirIteratorAdvancePosix(m_pImpl);
#endif
}

bool BASfileDirIterator::operator!=(const BASfileDirIterator& Rhs) const {
   const bool LhsAtEnd = !m_pImpl || m_pImpl->AtEnd;
   const bool RhsAtEnd = !Rhs.m_pImpl || Rhs.m_pImpl->AtEnd;
   if (LhsAtEnd != RhsAtEnd) {
      return true;
   }
   if (LhsAtEnd) {
      return false;
   }
   return m_pImpl->DirectoryPath != Rhs.m_pImpl->DirectoryPath ||
          m_pImpl->EntryName != Rhs.m_pImpl->EntryName;
}

const BASstring& BASfileDirIterator::entryName() const {
   static const BASstring Empty;
   if (!m_pImpl || m_pImpl->AtEnd) {
      return Empty;
   }
   return m_pImpl->EntryName;
}

bool BASfileDirIterator::entryIsDirectory() const {
   if (!m_pImpl || m_pImpl->AtEnd) {
      return false;
   }
   return m_pImpl->EntryIsDirectory;
}
