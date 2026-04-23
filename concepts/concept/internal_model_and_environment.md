# Tool internal model and environment

## Concept

Many tools carry an **internal model**: how they **name**, **store**, or **compare** things inside their own logic. The **environment** (operating system, filesystem, shell, network, another program) follows **its own** rules. **Recursive concept decomposition** asks you to keep those two stories **separate** on the page so readers—and assistants—do not merge them by accident.

## Why

When the two layers are **folded into one paragraph**, people argue about “what Git wants” when the real clash is “what the disk does,” or the reverse. Naming the split lowers [cognitive load](../system/design/cognitive_load/README.md) and matches [separation of concerns](../system/design/separation_of_concerns/concept.md). Where the surface **lies**, you get a [leaky abstraction](../system/design/leaky_abstraction.md).

## Example in this repo

[Git `core.ignorecase` and filesystems](../computer/git/git_core_ignorecase.md) tells **Git’s portable path story** and points filesystem-only detail to [Filesystem case on major desktop OS families](../computer/git/git_core_ignorecase/filesystem_case_by_os.md). The hub page also says **who should read which thread** so the internal model and the environment do not compete in one block of text.
