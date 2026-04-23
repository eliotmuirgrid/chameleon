# Git `core.ignorecase` and filesystems

This page is a **concrete example** of a [leaky abstraction](../../system/design/leaky_abstraction.md): Git presents paths one way, but the **operating system’s filesystem** is the hidden layer—and it **does not match** across all machines.

For what **abstraction** means in general, see [Abstraction](../../system/design/abstraction.md). For day-to-day Git without the hosting layer, see [Git (in plain terms)](git.md). The abstract idea Git implements is [source control (the idea)](../../pareto/general/source_control.md); portability across tools and files is [open vs closed](../../pareto/general/open_versus_closed.md). Filenames also meet shell parsing in [spaces in file names and the command line](../filename_spaces_command_line.md).

---

**What leaks:** `core.ignorecase = true` tracks a mismatch between how **Git** thinks about path strings and how some **filesystems** treat **case**. On macOS and Windows, names are usually **case-insensitive**: `file.txt` and `File.txt` are the **same** file. Git adapts by **collapsing** case when that applies—less noise locally, but **ambiguity** about the canonical spelling.

On **Linux**, the same strings are **different** paths. Moving work between environments exposes the leak: case-only renames that behave oddly, “works here” surprises in CI or production, or painful merges when two branches differ only by casing yet look identical on a case-insensitive checkout.

**Takeaway:** `ignorecase` reflects an **OS constraint**, not a style preference. **Discipline** still matters: treat paths as **stable identifiers** and use a **consistent convention** (often all lowercase). When **case carries no meaning** in your tree, the leaky boundary hurts less and behavior stays **predictable** across environments.
