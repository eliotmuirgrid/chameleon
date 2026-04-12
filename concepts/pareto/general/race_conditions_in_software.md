# Race conditions in software

**Summary:** In **programs**, a **race condition** usually means **two or more threads** (or **async** tasks) **touch the same data** or **order-dependent logic** **without** a guaranteed **order** of execution. The **result** depends on **timing**—how the OS **schedules** work, **network** latency, **disk** speed, or **load**. That makes the bug **intermittent** and **hard to reproduce**, even when the **underlying mistake** is simple. For the same pattern outside code, see [Race condition](race_condition.md).

---

## What goes wrong

Modern software often does **many things at once**: **parallel** loops, **background** workers, **callbacks** from I/O, **shared** caches. If two paths **read and write** the same **memory** (or the same **logical** state) **without** rules about **who goes first**, you get **nondeterminism**: run the program **ten** times and you may see **different** outcomes.

The **bug** is not always “wrong on every run.” It may appear **only** when thread A **wins** the race **twice in a row**, or **only** under **production** load—so **developers** see **nothing** on a quiet laptop, while **users** hit crashes or corrupted data.

---

## Why reproduction is hard

- **Timing changes behavior** — A **debugger** or **extra logging** **slows** one path and **hides** the bug (**Heisenbug**): the problem **vanishes** when you try to **watch** it closely.
- **Environment differs** — **Faster** CPU, **fewer** cores, **different** OS scheduling, or **slower** networks change **which** interleavings occur **often enough** to fail.
- **Rare interleavings** — The **bad** order might need **two** events **microseconds** apart; it happens **once in a million** requests.

So **“cannot reproduce”** often means **“we have not yet controlled or stressed timing enough,”** not **“there is no bug.”**

---

## What engineering usually does (conceptually)

This note is not a **coding** manual; it names **directions**:

- **Synchronization** — **Locks**, **mutexes**, or **atomic** operations so only **one** writer (or a **defined** sequence) touches **critical** state.
- **Ownership** — **One** thread **owns** a structure; others **send messages** instead of **sharing** mutable memory.
- **Immutability** — **Fewer** shared **variables** that **change** means **fewer** races.
- **Testing under stress** — **Load** tests, **stress** tools, or **deliberate** random **delays** (“jitter”) to **surface** order-dependent failures **before** production.

The goal is to make **order** either **impossible to get wrong** or **explicit** in the design—not **accidentally** left to **luck** and **scheduler** mood.

---

## See also

- [Race condition](race_condition.md) — the **general** pattern (including **non-software** examples).
- [Bottleneck](bottleneck.md) — unrelated **mechanism**, but **load** on a system often **changes timing** and can **expose** races.
