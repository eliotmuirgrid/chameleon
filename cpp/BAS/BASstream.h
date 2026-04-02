#pragma once
//-------------------------------------------------------
// Copyright (C) 2026 Eliot Muir.  All rights reserved.
//
// BASstream
// 
// Stream inteface like iostream
//-------------------------------------------------------

class BASdestination;

class BASstream{
public:
   BASstream(BASdestination& Destination);  // does not take ownership
   BASstream(BASdestination* pDestination, bool IsOwner);
   ~BASstream();

   BASdestination* destination();

private:
   bool m_IsOwner;
   BASdestination* m_pDestination;
};

BASstream& operator<<(BASstream& Stream, const char* pString);
BASstream& operator<<(BASstream& Stream, int Number);
BASstream& operator<<(BASstream& Stream, bool Value);
BASstream& operator<<(BASstream& Stream, long Value);
BASstream& operator<<(BASstream& Stream, const void* pObject);
BASstream& operator<<(BASstream& Stream, char Character);
BASstream& operator<<(BASstream& Stream, unsigned int Number);
BASstream& operator<<(BASstream& Stream, unsigned long Number);
BASstream& operator<<(BASstream& Stream, double Number);




BASstream& operator<<(BASstream& Stream, BASstream&(*pFunc)(BASstream&));

BASstream& flush(BASstream& Stream);
BASstream& newline(BASstream& Stream);

extern BASstream BASout; 

