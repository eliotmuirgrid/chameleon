#pragma once
//-------------------------------------------------------
// Copyright (C) 2026 Eliot Muir.  All rights reserved.
//
// BASfile
//
// Cross-platform helpers for POSIX-style integer file descriptors.
// On POSIX this is open(2)/close(2). On Windows it is the CRT _open/_close
// family (also int), not a raw HANDLE.
//
// Return convention: BASfileOpen returns a non-negative fd on success, or -1 on
// failure (same as open/_open). BASfileClose returns 0 on success, -1 on error
// (same as close/_close). Use OpenFlags and Mode the same way you would for
// open(2) on your platform (e.g. O_RDONLY | O_CREAT and 0644); include your
// platform <fcntl.h> when building call sites.
//
// Windows: add _O_BINARY in OpenFlags when you need binary mode.
//-------------------------------------------------------

int BASfileOpen(const char* Path, int OpenFlags, int Mode);
int BASfileClose(int FileDescriptor);
