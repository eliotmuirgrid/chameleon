//-------------------------------------------------------
// Copyright (C) 2026 Eliot Muir.  All rights reserved.
//
// BASstream
// 
// Stream interface like iostream
//-------------------------------------------------------

#include <BAS/BASstream.h>
#include <BAS/BASdestination.h>
#include <BAS/BASdestinationStandardOut.h>

#include <string.h>
#include <stdio.h>

BASstream BASout(new BASdestinationStandardOut(), true);

BASstream::BASstream(BASdestination& Destination) : m_pDestination(&Destination), m_IsOwner(false) {
}

BASstream::BASstream(BASdestination* pDestination, bool IsOwner) : m_pDestination(pDestination), m_IsOwner(IsOwner) {
}

BASstream::~BASstream() {
   if (m_IsOwner) {
      delete m_pDestination;
   }
}

BASdestination* BASstream::destination() {
   return m_pDestination;
}

BASstream& operator<<(BASstream& Stream, const char* pString){
   Stream.destination()->write(pString, strlen(pString));
   return Stream;
}


BASstream& operator<<(BASstream& Stream, int Number){
   char Buffer[32];
   int Size = snprintf(Buffer, sizeof(Buffer), "%d", Number);
   Stream.destination()->write(Buffer, Size);
   return Stream;
}

BASstream& operator<<(BASstream& Stream, bool Value){
   if (Value){
      Stream.destination()->write("true", 4);
   } else {
      Stream.destination()->write("false", 5);
   }
   return Stream;
}

BASstream& operator<<(BASstream& Stream, long Number){
   char Buffer[32];
   int Size = snprintf(Buffer, sizeof(Buffer), "%ld", Number);
   Stream.destination()->write(Buffer, Size);
   return Stream;
}

BASstream& operator<<(BASstream& Stream, unsigned int Number){
   char Buffer[32];
   int Size = snprintf(Buffer, sizeof(Buffer), "%u", Number);
   Stream.destination()->write(Buffer, Size);
   return Stream;
}

BASstream& operator<<(BASstream& Stream, unsigned long Number){
   char Buffer[32];
   int Size = snprintf(Buffer, sizeof(Buffer), "%lu", Number);
   Stream.destination()->write(Buffer, Size);
   return Stream;
}

BASstream& operator<<(BASstream& Stream, double Number){
   char Buffer[32];
   int Size = snprintf(Buffer, sizeof(Buffer), "%f", Number);
   Stream.destination()->write(Buffer, Size);
   return Stream;
}


BASstream& operator<<(BASstream& Stream, const void* pPointer){
   char Buffer[32];
   int Size = snprintf(Buffer, sizeof(Buffer), "%p", pPointer);
   Stream.destination()->write(Buffer, Size);
   return Stream;
}

BASstream& operator<<(BASstream& Stream, char Character){
   Stream.destination()->write(&Character, 1);
   return Stream;
}

BASstream& newline(BASstream& Stream) {
   Stream.destination()->write("\n", 1);
   return Stream;
}

BASstream& flush(BASstream& Stream) {
   Stream.destination()->flush();
   return Stream;
}

BASstream& operator<<(BASstream& Stream, BASstream&(*pFunc)(BASstream&)){
   return (*pFunc)(Stream);
}


