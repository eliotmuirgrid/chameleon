//-------------------------------------------------------
// Copyright (C) 2026 Eliot Muir.  All rights reserved.
//
// BASdestinationStandardOut
//-------------------------------------------------------

#include <BAS/BASdestinationStandardOut.h>

#include <unistd.h>

BASdestinationStandardOut::BASdestinationStandardOut() {
}

BASdestinationStandardOut::~BASdestinationStandardOut() {
}

void BASdestinationStandardOut::write(const char* pData, int Size){
   ::write(STDOUT_FILENO, pData, Size);
}

void BASdestinationStandardOut::flush(){
   fsync(STDOUT_FILENO);
}
