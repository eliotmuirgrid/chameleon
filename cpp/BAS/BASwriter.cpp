//-------------------------------------------------------
// Copyright (C) 2026 Eliot Muir.  All rights reserved.
//
// BASwriter
//
// Implementation
//-------------------------------------------------------

#include <BAS/BASwriter.h>
#include <BAS/BASdestination.h>
#include <BAS/BASdestinationFilePipe.h>

#include <stdio.h>
#include <string.h>
#include <unistd.h>

BASwriter BASout(new BASdestinationFilePipe(STDOUT_FILENO), true);

BASwriter::BASwriter(BASdestination& Destination) : m_pDestination(&Destination), m_IsOwner(false) {
}

BASwriter::BASwriter(BASdestination* pDestination, bool IsOwner) : m_pDestination(pDestination), m_IsOwner(IsOwner) {
}

BASwriter::~BASwriter() {
   if (m_IsOwner) {
      delete m_pDestination;
   }
}

BASdestination* BASwriter::destination() {
   return m_pDestination;
}

BASwriter& operator<<(BASwriter& Writer, const char* pString){
   Writer.destination()->write(pString, strlen(pString));
   return Writer;
}


BASwriter& operator<<(BASwriter& Writer, int Number){
   char Buffer[32];
   int Length = snprintf(Buffer, sizeof(Buffer), "%d", Number);
   Writer.destination()->write(Buffer, Length);
   return Writer;
}

BASwriter& operator<<(BASwriter& Writer, bool Value){
   if (Value){
      Writer.destination()->write("true", 4);
   } else {
      Writer.destination()->write("false", 5);
   }
   return Writer;
}

BASwriter& operator<<(BASwriter& Writer, long Number){
   char Buffer[32];
   int Length = snprintf(Buffer, sizeof(Buffer), "%ld", Number);
   Writer.destination()->write(Buffer, Length);
   return Writer;
}

BASwriter& operator<<(BASwriter& Writer, unsigned int Number){
   char Buffer[32];
   int Length = snprintf(Buffer, sizeof(Buffer), "%u", Number);
   Writer.destination()->write(Buffer, Length);
   return Writer;
}

BASwriter& operator<<(BASwriter& Writer, unsigned long Number){
   char Buffer[32];
   int Length = snprintf(Buffer, sizeof(Buffer), "%lu", Number);
   Writer.destination()->write(Buffer, Length);
   return Writer;
}

BASwriter& operator<<(BASwriter& Writer, double Number){
   char Buffer[32];
   int Length = snprintf(Buffer, sizeof(Buffer), "%f", Number);
   Writer.destination()->write(Buffer, Length);
   return Writer;
}


BASwriter& operator<<(BASwriter& Writer, const void* pPointer){
   char Buffer[32];
   int Length = snprintf(Buffer, sizeof(Buffer), "%p", pPointer);
   Writer.destination()->write(Buffer, Length);
   return Writer;
}

BASwriter& operator<<(BASwriter& Writer, char Character){
   Writer.destination()->write(&Character, 1);
   return Writer;
}

BASwriter& newline(BASwriter& Writer) {
   Writer.destination()->write("\n", 1);
   return Writer;
}

BASwriter& flush(BASwriter& Writer) {
   Writer.destination()->flush();
   return Writer;
}

BASwriter& operator<<(BASwriter& Writer, BASwriter&(*pFunc)(BASwriter&)){
   return (*pFunc)(Writer);
}

