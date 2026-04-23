# Journaling (general pattern)

## Concept

**Journaling** here means: **write down what you plan to do** (or what you did step by step) **before** the final state is trusted as **done**, so you can **recover**, **replay**, or **audit** when reality interrupts. The same shape appears in **software**, **paper processes**, and **personal habits**—not only on disks.

## Why

If the only record is the **finished** result, a crash or half-finished step **leaves no map** back to a clean state. A **journal** is the extra trail that makes **repair** and **learning** cheaper. That lowers panic and guesswork for both **people** and **programs**—the same pressure [cognitive load](cognitive_load/README.md) describes when a system hides its history.

## Transfer (beyond filesystems)

- **Filesystems** — A [journaled filesystem](../../computer/storage/journaled_filesystem.md) writes metadata (and sometimes data) through a **log** so the tree on disk can be brought back to a **consistent** story after power loss.
- **Databases** — Many engines use **write-ahead logs**: intent hits durable storage before pages are considered committed.
- **Human workflows** — Lab notebooks, **ship’s logs**, checklists with initials and times: the journal is the **durable** story of intent and order, not only the end artifact.

## Related

[Entropy](entropy.md) names drift when no maintenance runs; journals are one **tool** against losing the thread. [Separation of concerns](separation_of_concerns/concept.md) helps: the **journal** is one concern; the **live state** is another.
