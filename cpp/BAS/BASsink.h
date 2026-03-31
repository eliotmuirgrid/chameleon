#pragma once
//-------------------------------------------------------
// Copyright (C) 2026 Eliot Muir.  All rights reserved.
//
// BASsink
// 
// Sink virtual interface.
//-------------------------------------------------------

class BASsink{
public:
    BASsink(){}
    virtual ~BASsink() {}

    virtual void write(const char* pData, int Size)=0; 
    virtual void flush()=0;
};

