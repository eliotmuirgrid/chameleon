# Filesystem case on major desktop OS families

Optional depth for [Git `core.ignorecase` and filesystems](../git_core_ignorecase.md). This page holds **only** how common **local filesystems** treat [letter case](../../letter_case.md) in file and folder names. Git’s reaction to those rules stays on the hub page. **Proper names** below link to **one file per identity** under [Common filesystems (cross-platform)](../../storage/common_filesystems.md).

---

## Prerequisites (read before the OS sections)

1. [Letter case (for paths and names)](../../letter_case.md) — what **case** names in this notebook.  
2. Then the comparison rules: [case-sensitive](../../letter_case/case_sensitive_comparison.md), [case-insensitive](../../letter_case/case_insensitive_comparison.md), [case-preserving](../../letter_case/case_preserving_storage.md).

The sections below describe **typical defaults** per **OS family** using that vocabulary.

---

## Windows (typical desktop install)

On the usual [**NTFS**](../../storage/common_filesystems/ntfs.md) setup for Windows desktops, the filesystem is [case-preserving](../../letter_case/case_preserving_storage.md) and [case-insensitive](../../letter_case/case_insensitive_comparison.md): `Notes.txt` and `notes.txt` refer to the **same** file. Some installs and APIs differ; the point for portable work is the **default** most collaborators see.

---

## macOS (typical single-volume install)

Most Macs use [**APFS**](../../storage/common_filesystems/apfs.md) or older [**HFS+**](../../storage/common_filesystems/hfs_plus.md) volumes formatted [case-insensitive](../../letter_case/case_insensitive_comparison.md), [case-preserving](../../letter_case/case_preserving_storage.md): again, `Readme.md` and `README.md` collide as **one** path. You **can** create [case-sensitive](../../letter_case/case_sensitive_comparison.md) APFS volumes; treat that as a deliberate exception when reasoning about “what most Mac users have.”

---

## Linux (typical native filesystem)

Common layouts on [**ext4**](../../storage/common_filesystems/ext4.md), [**XFS**](../../storage/common_filesystems/xfs.md), [**Btrfs**](../../storage/common_filesystems/btrfs.md), and similar treat names as [case-sensitive](../../letter_case/case_sensitive_comparison.md): `File.txt` and `file.txt` are **two different** paths. That is the environment many **servers** and **CI** runners use.

---

## Why this matters outside Git

Any tool that must **sync**, **copy**, or **version** trees across machines inherits a **boundary**: the **same string** of path components can mean **one file** on one OS and **two files** on another. Git sits on that boundary; the hub page names how Git adapts.

For the same **compatibility / profile** idea in other domains, see [USB-C charger compatibility](../../../electricity/usb-c-power.md) (electrical **profiles**) and [Adaptive communication](../../../communication/adaptive_communication.md) (human **style**), both linked from the [Letter case (for paths and names)](../../letter_case.md) hub as parallel readings.
