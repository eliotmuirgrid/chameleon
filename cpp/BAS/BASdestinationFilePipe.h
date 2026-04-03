#pragma once
//-------------------------------------------------------
// Copyright (C) 2026 Eliot Muir.  All rights reserved.
//
// BASdestinationFilePipe
//
// BASwriter sends formatted output to a BASdestination. This destination forwards
// bytes to a POSIX file descriptor using write(2) and flush() using fsync(2) when
// applicable. The descriptor may refer to a regular file, pipe, FIFO, socket, or
// terminal (including standard streams).
//
// Lifetime: this object does not take ownership of the descriptor. The caller must
// keep the fd open and valid for the entire lifetime of this BASdestinationFilePipe
// (and for any BASwriter that writes to it). Closing the fd while a writer still
// uses it is undefined behavior.
//
// Usage with BASwriter (after #include <unistd.h> where you use STDOUT_FILENO etc.):
//
//   // Standard output; BASwriter owns the destination (deletes it when done).
//   BASwriter out(new BASdestinationFilePipe(STDOUT_FILENO), true);
//   out << "Hello" << newline;
//
//   // Standard error (same pattern).
//   BASwriter err(new BASdestinationFilePipe(STDERR_FILENO), true);
//   err << "problem" << newline;
//
//   // A file opened elsewhere (you own the fd; the destination does not close it).
//   // Prefer BASfileOpen / BASfileClose (see BASfile.h) for a portable int fd.
//   int fd = BASfileOpen("/tmp/log.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
//   if (fd >= 0) {
//      { BASwriter log(new BASdestinationFilePipe(fd), true);
//        log << "line" << newline << flush;
//      }  // writer deletes the BASdestinationFilePipe; fd stays open
//      BASfileClose(fd);
//   }
//
//   // Stack destination, writer does not own the destination object.
//   BASdestinationFilePipe pipe(STDOUT_FILENO);
//   BASwriter console(pipe);
//   console << 42 << newline;
//-------------------------------------------------------

#include <BAS/BASdestination.h>

class BASdestinationFilePipe : public BASdestination{
public:
   explicit BASdestinationFilePipe(int FileDescriptor) : m_FileDescriptor(FileDescriptor) {}
   virtual ~BASdestinationFilePipe() {}

   int fileDescriptor() const { return m_FileDescriptor; }

   virtual void write(const char* pData, int Size);
   virtual void flush();

private:
   int m_FileDescriptor;
};
