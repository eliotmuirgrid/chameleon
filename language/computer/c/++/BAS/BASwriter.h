#pragma once
//-------------------------------------------------------
// Copyright (C) 2026 Eliot Muir.  All rights reserved.
//
// BASwriter
//
// Formats values and writes them to a BASdestination (chained << like iostream).
//-------------------------------------------------------

class BASdestination;

class BASwriter{
public:
   BASwriter(BASdestination& Destination);  // does not take ownership
   BASwriter(BASdestination* pDestination, bool IsOwner);
   ~BASwriter();

   BASdestination* destination();

private:
   bool m_IsOwner;
   BASdestination* m_pDestination;
};

BASwriter& operator<<(BASwriter& Writer, const char* pString);
BASwriter& operator<<(BASwriter& Writer, int Number);
BASwriter& operator<<(BASwriter& Writer, bool Value);
BASwriter& operator<<(BASwriter& Writer, long Value);
BASwriter& operator<<(BASwriter& Writer, const void* pObject);
BASwriter& operator<<(BASwriter& Writer, char Character);
BASwriter& operator<<(BASwriter& Writer, unsigned int Number);
BASwriter& operator<<(BASwriter& Writer, unsigned long Number);
BASwriter& operator<<(BASwriter& Writer, double Number);



BASwriter& operator<<(BASwriter& Writer, BASwriter&(*pFunc)(BASwriter&));

BASwriter& flush(BASwriter& Writer);
BASwriter& newline(BASwriter& Writer);

extern BASwriter BASout;
