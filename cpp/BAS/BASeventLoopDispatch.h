#pragma once
//-------------------------------------------------------
// Copyright (C) 2026 Eliot Muir. All rights reserved.
//
// BASeventLoopDispatch — platform-specific wakeup + timed wait for BASeventLoop.
// Linux: epoll + eventfd. macOS: kqueue + pipe. Windows: unsupported (create returns null).
// All OS-specific code lives in BASeventLoopDispatch.cpp.
//-------------------------------------------------------

class BASstring;

class BASeventLoopDispatch {
public:
   static BASeventLoopDispatch* create(BASstring* pError);
   ~BASeventLoopDispatch();

   BASeventLoopDispatch(const BASeventLoopDispatch&) = delete;
   BASeventLoopDispatch& operator=(const BASeventLoopDispatch&) = delete;

   void signal();
   void drain();
   int wait(int timeout_ms);

private:
   struct Impl;
   explicit BASeventLoopDispatch(Impl* pImpl);

   Impl* m_pImpl;
};
