# Small packet

A **small packet** is a **little unit** of work, data, or responsibility sent or handled **one step at a time** instead of bundled into one large lump.

**Why it helps**

- **Earlier feedback.** Something useful can **arrive or finish sooner**, instead of waiting for a whole batch.
- **Easier recovery.** If something fails, you **re-send or re-do a small piece**, not the entire load.
- **Clearer limits.** Boundaries stay obvious: each piece has a **defined size and purpose**.

**What it costs**

- **Overhead.** Each packet may need **headers, checks, or handoffs**—many small ones can add up compared to one big transfer.
- **Coordination.** Someone has to define **order, numbering, and what “done” means** for the stream of pieces.

**Quick test:** Are you splitting because the problem is **naturally incremental**, or because the **design is unclear**? The first is a strength; the second can hide a need for a clearer whole.

Small packets often **flow through** a [pipeline](../troubleshooting/pipeline.md). When a **tiny fix now** unblocks the next step without waiting for the full design, that is [immediate solutions](immediate_solutions.md).
