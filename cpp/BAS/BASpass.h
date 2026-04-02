#pragma once
//-------------------------------------------------------
// Copyright (C) 2026 Eliot Muir. All rights reserved.
//
// BASpass & BASpassHold
//
// THE TOILET KEY ANALOGY:
// Imagine a restaurant with a single-occupancy toilet.
//
// 1. The BASpass is the toilet key kept behind the counter.
//    Only one person can hold it at a time. If the key is
//    already taken, everyone else has to wait.
//
// 2. The BASpassHold is your temporary hold on that key.
//    When you create a BASpassHold, it waits until the key
//    is free and then takes it for you.
//
//    While the BASpassHold exists, you have exclusive access.
//    When the BASpassHold goes away, it automatically returns
//    the key so the next person can use it.
//
// IMPLEMENTATION NOTE:
// This uses the RAII (Resource Acquisition Is Initialization) pattern:
// BASpass wraps the OS primitive that enforces one holder at a time;
// BASpassHold acquires the pass in its constructor and returns it in
// the destructor so the pass is always released on every exit path.
//-------------------------------------------------------

class BASpass {
public:
   BASpass();
   ~BASpass();

   // Wait until the pass is free, then take it.
   void takePass();

   // Return the pass so others can use it.
   void returnPass();

private:
   BASpass(const BASpass&) = delete;
   BASpass& operator=(const BASpass&) = delete;

   // Opaque storage sized for the OS "one holder at a time" primitive (POSIX / Windows).
   char m_Handle[64];
};

class BASpassHold {
public:
   // Constructor: Automatically takes the pass.
   BASpassHold(BASpass& Pass) : m_pPass(&Pass) { m_pPass->takePass(); }

   // Destructor: Automatically returns the pass.
   ~BASpassHold() { m_pPass->returnPass(); }

   // Prevent copying to ensure only one "hold" manages the pass at a time.
   BASpassHold(const BASpassHold&) = delete;
   BASpassHold& operator=(const BASpassHold&) = delete;

private:
   BASpass* m_pPass;
};
