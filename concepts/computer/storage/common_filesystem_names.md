# Common filesystem names (quick reference)

One-line **identity** pages for **proper names** that show up when you talk about **paths**, **case**, and **disks**. This file is a **glossary packet**: enough to read [Filesystem case on major desktop OS families](../git/git_core_ignorecase/filesystem_case_by_os.md) without treating **NTFS** or **ext4** as empty words. It is **not** a tuning or admin guide.

---

## NTFS

**NTFS** (*New Technology File System*) is the usual **default filesystem** on **Windows** drives today. It **stores** long filenames and metadata; for **most** desktop setups it behaves **case-insensitive** and **case-preserving** for normal programs (the detail that matters for **cross-platform paths** lives on the case page above).

---

## APFS

**APFS** (*Apple File System*) is Apple’s **modern** filesystem on **Mac** internal drives, replacing much day-to-day use of **HFS+**. Volumes are often formatted **case-insensitive, case-preserving**; **case-sensitive** APFS exists for people who choose it.

---

## HFS+

**HFS+** (also called **Mac OS Extended**) is an **older Apple** filesystem still seen on **external** drives and older Macs. Like typical **APFS** for consumers, it is commonly **case-insensitive** and **case-preserving**.

---

## ext4

**ext4** is a common **native Linux** filesystem (fourth generation “extended” fs). It is **case-sensitive** for path names: `A` and `a` are **different** last path components.

---

## XFS

**XFS** is a **journaled** filesystem common on **Linux** servers and some desktops. For **path case** behavior in normal use, treat it like **ext4**: **case-sensitive** names.

---

## Btrfs

**Btrfs** (*B-tree file system*) is an **advanced Linux** filesystem (snapshots, checksums, pooling). For **ordinary path naming** and **case**, it behaves **case-sensitively** like **ext4** in typical layouts.
