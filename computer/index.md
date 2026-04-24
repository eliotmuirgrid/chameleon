# Computer (concepts)

Short notes on **how computers present work to you**—same style as the rest of [`docs/concepts/`](../): one main idea per page, linked for reuse. Many pages end with a **short check** so you can confirm you got the idea.

---

## Apple computers (read this if any of this is new)

**Apple** (the company) sells laptops and desktop computers. Their **personal computers** are sold under the brand name **Mac** (short for *Macintosh*). Saying “a Mac” is like saying “a Dell” or “an HP”—it only means **which company made the machine**, not a special skill on your part.

The **operating system**—the software that draws the desktop, windows, and menu bar on a Mac—is called **macOS** (say it “mac **O** **S**”). It is **not** Windows and it is **not** what phones use. Guides below that say **macOS** assume you are sitting at **Apple’s computer software** on **Apple hardware**.

If you use a **Windows PC** or another system, the keys and menus will differ; these pages are written for **Mac / macOS** only where noted.

---

## Pages

- [The command line](command_line.md) — what the command line is, in plain language (no commands required).
- [Open apps with search (Spotlight) on a Mac](open_apps_with_spotlight_mac.md) — keyboard or magnifying glass, then type a name and **Enter**.
- [Using the terminal](using_the_terminal.md) — on **macOS** only: open Terminal, then three commands (`pwd`, `ls`, `cd`).
- [Spaces in file names and the command line](filename_spaces_command_line.md) — why spaces split arguments and how to avoid pain (naming, quotes).
- [Install WhatsApp on an Apple computer](install_whatsapp_on_mac.md) — App Store or official download, then link to your phone.
- [Screenshot part of the screen](region_screenshot_mac.md) — **Shift + ⌘ + 4**, drag a box; optional **Shift + ⌘ + 5** for more choices.

## Paths and letter case

- [Letter case (for paths and names)](letter_case.md) — what **case** means for names, then [case-sensitive](letter_case/case_sensitive_comparison.md) / [case-insensitive](letter_case/case_insensitive_comparison.md) / [case-preserving](letter_case/case_preserving_storage.md) comparison rules before OS or Git detail.

## Storage (names and formats)

- [Common filesystems (cross-platform)](storage/common_filesystems.md) — hub for **NTFS**, **APFS**, **HFS+**, **ext4**, **XFS**, **Btrfs**; one **identity file** each under [`storage/common_filesystems/`](storage/common_filesystems/index.md). Old path: [Common filesystem names (redirect)](storage/common_filesystem_names.md).
- [Journaled filesystem](storage/journaled_filesystem.md) — how a **log-before-trust** design fits filesystems; general pattern in [Journaling](../system/design/journaling.md).

## Git

- [Git (concepts)](git/index.md) — Git itself, `core.ignorecase`, and GitHub/Bitbucket vs local Git. Git implements [source control (the idea)](../pareto/general/source_control.md); the index above is the usual entry point.
