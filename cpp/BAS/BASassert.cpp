//-------------------------------------------------------
// Copyright (C) 2026 Eliot Muir.  All rights reserved.
//
// BASassert
//
// Implementation
//-------------------------------------------------------
#include <BAS/BASassert.h>

#include <stdio.h>
#include <stdlib.h>

void BASabortWithMessage(const BASstring& Message) {
   fprintf(stderr, "Fatal Error. Abort with message: %s\n", Message.c_str());
   abort();
}
