//-------------------------------------------------------
// Copyright (C) 2026 Eliot Muir.  All rights reserved.
//
// BASdestinationFilePipe
//-------------------------------------------------------

#include <BAS/BASdestinationFilePipe.h>

#include <unistd.h>

void BASdestinationFilePipe::write(const char* pData, int Size){
   ::write(m_FileDescriptor, pData, Size);
}

void BASdestinationFilePipe::flush(){
   fsync(m_FileDescriptor);
}
