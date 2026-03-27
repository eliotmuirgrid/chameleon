//---------------------------------------------------------------------------
// Copyright (C) 2026 Eliot Muir.  All rights reserved.
//
// Module: CORhash
//
// Description:
//
// Implementation
//
// Author: Nasron Cheong
//---------------------------------------------------------------------------
#include <COR/CORhash.h>
#include <COR/CORlog.h>
COR_LOG_MODULE;

#define COR_LOOKUP_HASH_HASH_VALUE_BITS 32

//CORstring specialization
template <>
CORindex CORhash<CORstring>::defaultHash(const CORstring& Key)
{
   //COR_FUNCTION(CORhash<CORstring>::defaultHash);
   CORuint32 Hash = 0;
   if (Key.size())
   {
      //TODO replace all one letter variables with meaningful names
      //TODO add some comments for block of code, eliminate magic values
      CORuint32 HashIncrement;
      CORuint32 ByteIncrement = sizeof(CORuint32);
      CORuint32 ByteIndex;
      CORuint32 c;
      CORuint32 DividingByte = Key.size() & 0xFFFC; // the largest multiple of 4 <= Key.size()
      const char* pStr = Key.c_str();

      //COR_VAR3(Hash,DividingByte, Key);
      // process 4 byte chunks of Key up to the DividingByte, hashing each into a 32 bit integer
      for (ByteIndex = 0; ByteIndex < DividingByte; ByteIndex += ByteIncrement)
      {
         HashIncrement = *(CORuint32*) (pStr + ByteIndex);
         Hash += HashIncrement;
         c = (int(HashIncrement >> 24) + (int(HashIncrement >> 16) & 0x00FF) + (int(HashIncrement >> 8) & 0x00FF) + (int(HashIncrement) & 0x00FF)) % (COR_LOOKUP_HASH_HASH_VALUE_BITS - 1) + 1;
         Hash = (Hash << (COR_LOOKUP_HASH_HASH_VALUE_BITS - c)) | (Hash >> c);
      }
      // process bytes remaining after DividingByte
      for (ByteIndex = DividingByte; ByteIndex < Key.size(); ByteIndex++)
      {
         Hash += pStr[ByteIndex];
         c = (pStr[ByteIndex] + ByteIndex) % (COR_LOOKUP_HASH_HASH_VALUE_BITS - 1) + 1;
         Hash = (Hash << (COR_LOOKUP_HASH_HASH_VALUE_BITS - c)) | (Hash >> c);
      }
   }
   COR_DBG("Key = " << Key << ", Hash = " << Hash);
   return Hash;   
}

//A Basic CRC hash we can use for other types
static const CORuint32 COR_LOOKUP_HASH_BYTE_WIDTH = 8; // Number of bits in a byte
static const CORuint32 COR_LOOKUP_HASH_WORD_WIDTH = sizeof (CORuint32) * COR_LOOKUP_HASH_BYTE_WIDTH;
static const CORuint32 COR_LOOKUP_HASH_CRC_HASH_SHIFT = 5;

static inline CORuint32 CORhashCRC(void* Key, CORuint32 Size)
{
   if(!Size)
   {
      return 0;
   }
   CORuint32 HashValue = 0;
   CORuint32 Index = 0;
   while (Index < (Size-1)) //note that 0 is always returned if Size = 1, so do not use for chars
   {
      CORuint32 leftShiftedValue = HashValue << COR_LOOKUP_HASH_CRC_HASH_SHIFT;
      CORuint32 rightShiftedValue = HashValue >> (COR_LOOKUP_HASH_WORD_WIDTH - COR_LOOKUP_HASH_CRC_HASH_SHIFT);
   
      // Put the shifted values together, and then XOR them with the
      // next key character
      HashValue = (leftShiftedValue | rightShiftedValue) ^ (((CORuint8*)Key)[Index+1]);
      Index++;
   }
   return HashValue;
}

static const CORuint32 SizeofCORuint64 = sizeof(CORuint64);
static const CORuint32 SizeofCORuint32 = sizeof(CORuint32);
static const CORuint32 SizeofCORuint16 = sizeof(CORuint16);
static const CORuint32 SizeofCORuint8 = sizeof(CORuint8);

//Integer specializations
template <>
CORindex CORhash<CORuint64>::defaultHash(const CORuint64& Key)
{
   return CORhashCRC((void*)&Key,SizeofCORuint64);
}

template <>
CORindex CORhash<CORint64>::defaultHash(const CORint64& Key)
{
   return CORhashCRC((void*)&Key,SizeofCORuint64);
}

template <>
CORindex CORhash<CORuint32>::defaultHash(const CORuint32& Key)
{
   return CORhashCRC((void*)&Key,SizeofCORuint32);
}

template <>
CORindex CORhash<CORint32>::defaultHash(const CORint32& Key)
{
   return CORhashCRC((void*)&Key,SizeofCORuint32);
}

template <>
CORindex CORhash<CORuint16>::defaultHash(const CORuint16& Key)
{
   return CORhashCRC((void*)&Key,SizeofCORuint16);
}

template <>
CORindex CORhash<CORint16>::defaultHash(const CORint16& Key)
{
   return CORhashCRC((void*)&Key,SizeofCORuint16);
}

//TODO, explain this better, get rid of magic value 3
//chars use the integer multiply algorithm
inline CORuint32 CORhashIntegerMultiply(CORuint32 Key)
{
   return Key * (Key + 3);
}

template <>
CORindex CORhash<CORuint8>::defaultHash(const CORuint8& Key)
{
   return CORhashIntegerMultiply(Key);
}

template <>
CORindex CORhash<CORint8>::defaultHash(const CORint8& Key)
{
   return CORhashIntegerMultiply(Key);
}
