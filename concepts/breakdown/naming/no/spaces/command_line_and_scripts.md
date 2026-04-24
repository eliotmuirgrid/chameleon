# No spaces — command line and scripts

## Concept

People who clone the repo run tools like `find`, `rg`, `git`, and shell loops on paths.
A space in a file or folder name splits one path into two parts unless every command uses quotes or escapes.
That often causes wrong results or "file not found" errors.

We want the `concepts/` tree to work in scripts without special handling for spaces.
This is the same issue explained in [Spaces in file names and the command line](../../../../computer/filename_spaces_command_line.md).

## Related

[No spaces in `concepts/` names (hub)](README.md); [Naming `no/` (hub)](../no.md); [Path and file naming (concepts tree)](../../../naming.md); [Spaces in file names and the command line](../../../../computer/filename_spaces_command_line.md); [Concept - Relative Links](../../../relative_links.md).
