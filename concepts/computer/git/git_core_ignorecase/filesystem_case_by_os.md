# Filesystem case on major desktop OS families

Optional depth for [Git `core.ignorecase` and filesystems](../git_core_ignorecase.md). This page holds **only** how common **local filesystems** treat **letter case** in file and folder names. Git’s reaction to those rules stays on the hub page.

---

## Windows (typical desktop install)

On the usual **NTFS** setup for Windows desktops, the filesystem is **case-preserving** and **case-insensitive**: `Notes.txt` and `notes.txt` refer to the **same** file. Some installs and APIs differ; the point for portable work is the **default** most collaborators see.

---

## macOS (typical single-volume install)

Most Macs use **APFS** or older **HFS+** volumes formatted **case-insensitive, case-preserving**: again, `Readme.md` and `README.md` collide as **one** path. You **can** create **case-sensitive** APFS volumes; treat that as a deliberate exception when reasoning about “what most Mac users have.”

---

## Linux (typical native filesystem)

Common layouts on **ext4**, **XFS**, **Btrfs**, and similar treat names as **case-sensitive**: `File.txt` and `file.txt` are **two different** paths. That is the environment many **servers** and **CI** runners use.

---

## Why this matters outside Git

Any tool that must **sync**, **copy**, or **version** trees across machines inherits a **boundary**: the **same string** of path components can mean **one file** on one OS and **two files** on another. Git sits on that boundary; the hub page names how Git adapts.
