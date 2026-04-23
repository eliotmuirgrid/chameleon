# Git `core.ignorecase` and filesystems

## Concept

**One sentence:** Git stores and exchanges history in a **portable** way, but every checkout lands on a **real filesystem**—and the three big **desktop families** do **not** agree whether **letter case** in a path is **significant**. `core.ignorecase` is Git’s way of **recording which world** your working tree lives in so it does not fight the disk.

This page is intentionally **fat**: it ties together **Git policy**, **OS filesystem rules**, and a **leaky abstraction** story. That is an **overload signal** in the sense of [Special case: overloaded concepts](../../concept/overloaded_concept.md). The filesystem-only thread already lives in a [detail page](git_core_ignorecase/filesystem_case_by_os.md); if Git’s **index**, **merge**, and **rename** edges keep growing here, split them the same way per [Concept - Detail Pages](../../concept/detail.md).

---

## If you are extending this page (including assistants)

Keep **three threads** separate in your head and in the file tree:

1. **Filesystem thread** — How **Windows**, **macOS**, and **Linux** (typical defaults) treat **case** in paths. **Do not** fold Git config trivia into that explanation; use [Filesystem case on major desktop OS families](git_core_ignorecase/filesystem_case_by_os.md).

2. **Git’s portable model** — Git’s **object database** and **history** use path strings in a **consistent** way across clones; **checkout** and **working tree** operations must **map** those strings onto whatever rules the **local** filesystem uses.

3. **This knob** — `core.ignorecase` tells Git whether the **current** working tree filesystem is **case-insensitive** for collision purposes, so Git can align **index vs disk** behavior and avoid silent corruption. It is **not** a style switch; it reflects **environment**.

When a draft keeps mixing those threads in one paragraph, **stop** and add or link a **small packet** page instead of lengthening this hub.

---

## What Git has to reconcile

Git must stay **useful on all major platforms**: the same commit must **mean** the same logical tree everywhere, yet **check out** cleanly on a **case-insensitive** laptop and on a **case-sensitive** server. The tension is not “Git prefers uppercase”; the tension is **identity of paths** under different **OS defaults**. For the **three-family** filesystem picture without Git, read [Filesystem case on major desktop OS families](git_core_ignorecase/filesystem_case_by_os.md).

---

## Leaky abstraction (what surprises people)

This topic is also a **concrete example** of a [leaky abstraction](../../system/design/leaky_abstraction.md): Git presents paths one way in **discussion and diffs**, but the **operating system’s filesystem** is the hidden layer—and it **does not match** across machines.

**What leaks when `core.ignorecase` is true:** Git tracks the mismatch between how **Git** must think about path strings for **portability** and how some **filesystems** treat **case**. On typical **Windows** and **macOS** disks, names are **case-insensitive**: `file.txt` and `File.txt` are the **same** file. Git adapts by **collapsing** case when that applies—less noise locally, but **ambiguity** about the canonical spelling.

On typical **Linux**, the same strings are **different** paths. Moving work between environments exposes the leak: case-only renames that behave oddly, “works here” surprises in CI or production, or painful merges when two branches differ only by casing yet look identical on a case-insensitive checkout.

For what **abstraction** means in general, see [Abstraction](../../system/design/abstraction.md). For day-to-day Git without the hosting layer, see [Git (in plain terms)](git.md). The abstract idea Git implements is [source control (the idea)](../../pareto/general/source_control.md); portability across tools and files is [open vs closed](../../pareto/general/open_versus_closed.md). Filenames also meet shell parsing in [spaces in file names and the command line](../filename_spaces_command_line.md).

---

## Takeaway

`ignorecase` reflects an **OS constraint**, not a style preference. **Discipline** still matters: treat paths as **stable identifiers** and use a **consistent convention** (often all lowercase). When **case carries no meaning** in your tree, the leaky boundary hurts less and behavior stays **predictable** across environments.
