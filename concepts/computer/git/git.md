# Git (in plain terms)

**Summary:** **Git** is a **widely used program** that **implements** [source control](../../pareto/general/source_control.md)—it **remembers versions** of your files so you can **see what changed**, **go back in time**, and **work with others** without constantly overwriting each other’s work. It is **not** the same as the **abstract idea** of source control (see [source control](../../pareto/general/source_control.md)); other tools (Mercurial, Subversion, and others) implement that idea differently. Git is **general-purpose**: you can point it at **any** folder (code, writing, research, design, personal projects, and more).

---

## A history of changes, not one saved-over file

Imagine you are writing a document. Instead of saving over the **same file** again and again, Git keeps a **history** of versions.

You can:

- **Go back** to an earlier version  
- **See exactly what changed** between versions  
- **Recover** something you deleted by mistake  

---

## Working together

Git also helps **teams**. Several people can edit the **same project**, and Git keeps the work **organized** so changes are **merged** in an orderly way instead of blindly replacing each other’s files.

---

## General-purpose: not just for programmers

Think of Git as **infrastructure for change**, not a “coding-only” gadget. It is **not tied to one profession or file type**: it can track **writing**, **notes**, **designs**, **spreadsheets**, **ideas**—whatever lives in files.

You point it at a **folder** (any files and subfolders you choose). There is nothing special required about the **content**; the same tool serves many different kinds of work. That is what **general-purpose** means: **one system**, **many uses**.

---

## One-line picture

> Git is a **general-purpose**, very **smart “save history”** for **almost anything** you create—as long as it lives in files.

**GitHub** and **Bitbucket** are **websites** that use Git—they are **not** required to use Git on your own machine. How those layers fit together is in [GitHub, Bitbucket, and Git](github_bitbucket_and_git.md).

---

## See also

- [Source control (the idea)](../../pareto/general/source_control.md) — the **general concept**; Git is **one** implementation.  
- [GitHub, Bitbucket, and Git](github_bitbucket_and_git.md) — hosting sites **on top** of Git; what you **own** vs what the **site** adds.
- [`core.ignorecase` and case-sensitive vs case-insensitive filesystems](git_core_ignorecase.md) — why Mac/Windows and Linux disagree, and why stable filename conventions matter.
