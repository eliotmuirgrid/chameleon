#pragma once
//-------------------------------------------------------
// Copyright (C) 2026 Eliot Muir.  All rights reserved.
//
// BASfile — reading and writing files (simple explanations)
//
// WHAT THIS IS
//   This file declares functions for working with files on disk in a way that works on
//   Mac, Linux, and Windows. You pass file paths as BASstring and get back either whole
//   file contents or a small integer the operating system uses to mean “this open file.”
//
// KEY IDEA: A “FILE DESCRIPTOR” (fd)
//   When your program opens a file, the system gives back a small integer (0, 1, 2, …).
//   Think of it as a ticket number: while that number is valid, it refers to that one open
//   file. When you are done, you must close it (or use BASfileAutoClose so it closes for
//   you). Invalid operations use -1 as the “no ticket” value.
//
// ---------------------------------------------------------------------------
// EASIEST PATH — WHOLE FILE AT ONCE (what most people want)
// ---------------------------------------------------------------------------
//   Read everything from a path into a string:
//     BASstring Content;
//     BASstring Error;
//     if (!BASfileRead(Path, &Content, &Error)) {
//        // failed: Error holds a short explanation (if you passed &Error)
//        return;
//     }
//     // Content now holds the bytes of the file.
//
//   Write a string to a path (replaces the whole file if it already exists):
//     BASstring Error;
//     if (!BASfileWrite(Path, Content, BASfileCreateMode_DefaultDataFile, &Error)) {
//        // failed
//        return;
//     }
//
//   These return true/false. Some parameters are named pError: they are optional places
//   for an error message. Pass the address of a BASstring (for example &Error) if you want
//   the function to fill in text when something goes wrong (and clear it when things work).
//   If you do not want any error text, pass nullptr — in C++, nullptr means “this pointer
//   does not point at anything,” i.e. skip the optional message.
//
// ---------------------------------------------------------------------------
// MORE CONTROL — OPEN, READ/WRITE PIECES, SEEK, CLOSE
// ---------------------------------------------------------------------------
//   1) Open: BASfileOpenRead (read-only) or BASfileOpenWrite (can create the file).
//   2) Optional: BASfilePosition / BASfilePositionSet / BASfileSize on the fd.
//   3) Read or write chunks with BASfileRead(fd, …) / BASfileWrite(fd, …).
//   4) Close with BASfileClose, or wrap the fd in BASfileAutoClose so close happens
//      automatically when the wrapper goes out of scope.
//
// ---------------------------------------------------------------------------
// ERRORS — TWO DIFFERENT STYLES (important)
// ---------------------------------------------------------------------------
//   A) Whole-file BASfileRead(Path, …) / BASfileWrite(Path, …) and path helpers that take
//      BASstring* pError: they return false on failure and, when you passed a real pointer
//      (not nullptr), put a human-readable message in *pError. BASfileClose can also fill
//      pError on failure when you pass a pointer there.
//
//   B) Low-level functions that take only an fd number (BASfilePosition, BASfilePositionSet,
//      BASfileSize, and the BASfileRead/BASfileWrite that take Buffer + Size) do NOT take
//      pError. Instead they return a special number and set the global “errno” variable
//      (an integer error code) when something went wrong:
//        - BASfilePosition, BASfilePositionSet, BASfileSize: result is -1 on failure;
//          otherwise the position or size (never negative on success).
//        - BASfileRead / BASfileWrite (fd): returns how many bytes were read or written;
//          0 means end-of-file for read; -1 means an error.
//      Right after a failure, you can turn errno into text with BASerrorStringFromErrno
//      (from BASerror.h) before calling other functions that might overwrite errno.
//
// ---------------------------------------------------------------------------
// CREATE MODE — ONLY WHEN CREATING A NEW FILE WHILE WRITING
// ---------------------------------------------------------------------------
//   When you open for writing and the file does not exist yet, the system creates it.
//   CreateMode says who is allowed to read or write that new file (like file permissions
//   in plain language). Reading an existing file does not use CreateMode and does not
//   change permissions on disk.
//
//   Prefer the BASfileCreateMode_* names below so one program can compile on every OS.
//
//   On Apple and Linux, new files get “permissions”: who may read, write, or run the file
//   (you, your group, everyone else). Those rules are often written as octal digits—base 8,
//   the digits 0–7—grouped in threes, for example 0644 meaning “owner can read/write, others
//   can read.” You do not need to memorize the digits; the preset names encode common choices.
//
//   Windows (through the C runtime’s _open) does not offer the same fine-grained Unix model.
//   It mainly exposes simple read/write permission flags. So two presets that mean different
//   octal patterns on Apple/Linux may collapse to the same numeric flag on Windows. That is
//   normal: you still pick a preset for clarity in your source code; the exact effect is
//   richest on Apple/Linux and coarser on Windows.
//
// ---------------------------------------------------------------------------
// CHECKING A PATH WITHOUT OPENING IT
// ---------------------------------------------------------------------------
//   BASfileExists, BASfileIsDirectory, BASfileIsExecutable, BASfileIsReadable,
//   BASfileIsWritable return true/false. BASfileDelete removes a file (or empty item);
//   pass an error string pointer if you want a message on failure (or nullptr to skip).
//
//-------------------------------------------------------

#include <BAS/BAStypes.h>
#include <stddef.h>

class BASstring;

// ----- Pick one of these when you pass CreateMode (new file permissions when writing) -----
#if defined(_WIN32) || defined(WIN32)
#define BASfileCreateMode_Private (0x0100 | 0x0080)
#define BASfileCreateMode_DefaultDataFile (0x0100 | 0x0080)
#define BASfileCreateMode_Executable (0x0100 | 0x0080 | 0x0040)
#else
#define BASfileCreateMode_Private 0600
#define BASfileCreateMode_DefaultDataFile 0644
#define BASfileCreateMode_Executable 0755
#endif

// ----- Whole file by path (start here if you just need load or save) -----
bool BASfileRead(const BASstring& Path, BASstring* pContent, BASstring* pError = nullptr);
bool BASfileWrite(const BASstring& Path, const BASstring& Content, int CreateMode, BASstring* pError = nullptr);

// ----- Questions about a path on disk (yes/no; no fd) -----
bool BASfileExists(const BASstring& Path);
bool BASfileIsDirectory(const BASstring& Path);
bool BASfileIsExecutable(const BASstring& Path);
bool BASfileIsReadable(const BASstring& Path);
bool BASfileIsWritable(const BASstring& Path);
bool BASfileDelete(const BASstring& Path, BASstring* pError = nullptr);

// ----- Open a file and get an fd (integer “ticket”) -----
int BASfileOpenRead(const BASstring& Path, BASstring* pErrorMessage);
int BASfileOpenWrite(const BASstring& Path, int CreateMode = BASfileCreateMode_DefaultDataFile, BASstring* pErrorMessage = nullptr);

// ----- Use the fd: where am I, how big is it, read/write a block (see errno on failure) -----
BASint64 BASfilePosition(int FileDescriptor);
BASint64 BASfilePositionSet(int FileDescriptor, BASint64 AbsoluteOffset);
BASint64 BASfileRead(int FileDescriptor, void* Buffer, size_t Size);
BASint64 BASfileWrite(int FileDescriptor, const void* Buffer, size_t Size);
BASint64 BASfileSize(int FileDescriptor);

// ----- Done with the fd (optional error text on failure) -----
int BASfileClose(int FileDescriptor, BASstring* pError = nullptr);

// ----- Wraps one fd: closes it for you when this object is destroyed (move-only; no copy) -----
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
