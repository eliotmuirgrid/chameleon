#pragma once
//-------------------------------------------------------
// Copyright (C) 2026 Eliot Muir.  All rights reserved.
//
// BASfileDir — folder paths and file names (simple explanations)
//
// WHAT THIS IS
//   Helpers for putting path pieces together, taking a path apart (folder vs file name),
//   and creating folders on disk. Separators are both "/" and "\" when reading paths;
//   BASfileDirJoin uses the normal separator for the OS you compile on.
//
// CREATE MODE (mkdir only)
//   Same idea as BASfile.h: when creating a new folder, CreateMode sets permissions on
//   Apple/Linux. Use the BASfileCreateMode_* names from BASfile.h. Windows ignores the
//   detailed Unix-style bits; passing BASfileCreateMode_DefaultDataFile is fine.
//
// CREATING FOLDERS
//   BASfileDirCreate makes the whole path, like “mkdir -p” on the terminal: it creates
//   every missing intermediate subdirectory, then the last one. If a segment already
//   exists as a folder, it is left alone. If the path is already a folder, it succeeds
//   without extra work.
//
// ERRORS
//   BASfileDirCreate takes an optional pError (see BASfile.h): nullptr means you do not
//   want a message; otherwise *pError is set on failure.
//
// DIRECTORY LISTING
//   BASfileDirListing holds a folder path and exposes begin()/end()/cbegin()/cend() like
//   other BAS collections. BASfileDirIterator is the cursor: default construction is the
//   end sentinel; non-default starts at the first entry. Use positionAtBegin() to rewind.
//   Loop with for (auto It = L.begin(); It != L.end(); ++It), or compare to a default-
//   constructed end iterator. Entries "." and ".." are skipped. If the path cannot be
//   opened, begin() compares equal to end(). Copying iterators is disabled; moving is allowed.
//
//-------------------------------------------------------

#include <BAS/BASstring.h>

struct BASfileDirIteratorImpl;

class BASfileDirIterator {
public:
   BASfileDirIterator();
   explicit BASfileDirIterator(const BASstring& DirectoryPath);
   ~BASfileDirIterator();

   BASfileDirIterator(BASfileDirIterator&& Rhs) noexcept;
   BASfileDirIterator& operator=(BASfileDirIterator&& Rhs) noexcept;

   BASfileDirIterator(const BASfileDirIterator&) = delete;
   BASfileDirIterator& operator=(const BASfileDirIterator&) = delete;

   void positionAtBegin();
   void positionAtEnd();
   void operator++();
   bool operator!=(const BASfileDirIterator& Rhs) const;

   const BASstring& entryName() const;
   bool entryIsDirectory() const;

private:
   BASfileDirIteratorImpl* m_pImpl;
};

class BASfileDirListing {
public:
   explicit BASfileDirListing(const BASstring& DirectoryPath) : m_DirectoryPath(DirectoryPath) {}

   BASfileDirIterator begin() const { return BASfileDirIterator(m_DirectoryPath); }
   BASfileDirIterator end() const { return BASfileDirIterator(); }
   BASfileDirIterator cbegin() const { return begin(); }
   BASfileDirIterator cend() const { return end(); }

private:
   BASstring m_DirectoryPath;
};

BASstring BASfileDirJoin(const BASstring& Directory, const BASstring& FileName);
BASstring BASfileDirFileName(const BASstring& Path);
BASstring BASfileDirParent(const BASstring& Path);

bool BASfileDirCreate(const BASstring& Path, int CreateMode, BASstring* pError = nullptr);
