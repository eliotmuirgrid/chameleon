# No spaces — command line and scripts

## Concept

Anyone cloning the repo may run **find**, **grep**, **git**, or small **shell** loops over paths. A **space** in a file or folder name turns one path into **two tokens** unless every use remembers **quotes** or **escapes**. The failure mode is often **silent** (wrong file) or **noisy** (“file not found”). The concepts tree is meant to be **safe to treat as data** in scripts without special cases for spaces.

That splitting behavior is the same idea as [Spaces in file names and the command line](../../../../computer/filename_spaces_command_line.md), applied here as a **naming choice** for `concepts/`.

## Related

[No spaces in `concepts/` names (hub)](README.md); [Naming `no/` (hub)](../no.md); [Path and file naming (concepts tree)](../../../naming.md); [Spaces in file names and the command line](../../../../computer/filename_spaces_command_line.md); [Concept - Relative Links](../../../relative_links.md).
