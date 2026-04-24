# Journaled filesystem

## Concept

A **journaled filesystem** is a filesystem design that uses **journaling**—a **log** of planned or partial changes—so that after a crash or sudden power loss the disk can be brought back to a **consistent** story without scanning the whole volume. The general human-and-systems idea is [Journaling](../../system/design/journaling.md); this page stays on **storage**.

## Why it matters

Without a journal, the machine might have **half-written** a rename or a new file block; on restart the tree could **lie** in ways users and tools do not expect. The journal makes **recovery** a defined job instead of guesswork.

## Examples in this repo

Several Linux-oriented identities in [Common filesystems (cross-platform)](common_filesystems.md) are commonly described as **journaled** in production talk—for example [XFS](../common_filesystems/xfs.md). Exact on-disk layouts differ by format; the **shared** idea is the **log before trust**.

## Related

[Abstraction](../../system/design/abstraction.md) hides disk mechanics until a leak forces you to care; journaling is one of the **hidden layers** that surfaces when power or bugs interrupt a write.
