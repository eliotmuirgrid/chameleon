//-------------------------------------------------------
// Copyright (C) 2026 Eliot Muir.  All rights reserved.
//
// BASsinkStandardOut
//-------------------------------------------------------

#include <BAS/BASsinkStandardOut.h>

#include <unistd.h>

BASsinkStandardOut::BASsinkStandardOut(){

}

BASsinkStandardOut::~BASsinkStandardOut(){

}

void BASsinkStandardOut::write(const char* pData, int Size){
   ::write(STDOUT_FILENO, pData, Size);
} 

void BASsinkStandardOut::flush(){
   fsync(STDOUT_FILENO);
}