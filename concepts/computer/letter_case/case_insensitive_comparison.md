# Case-insensitive comparison (paths)

Optional depth for [Letter case (for paths and names)](../letter_case.md).

---

## Concept

**Case-insensitive comparison** means: when the system decides whether two path names are the **same** target, **letter case does not count** for that decision. `Notes.txt` and `notes.txt` can refer to the **same** file. This page names the **rule** only; it does **not** say how the disk **remembers** spelling—that is [Case-preserving storage](case_preserving_storage.md).

## Prerequisites

Read [Letter case (for paths and names)](../letter_case.md) **before** relying on this term: **case-insensitive** only has a clear meaning once **case** itself is fixed.

## Where you see it

Typical **Windows** and **macOS** consumer defaults in [Filesystem case on major desktop OS families](../../git/git_core_ignorecase/filesystem_case_by_os.md). [NTFS](../../storage/common_filesystems/ntfs.md) and typical [APFS](../../storage/common_filesystems/apfs.md) examples in this repo use this rule for ordinary path **matching**.
