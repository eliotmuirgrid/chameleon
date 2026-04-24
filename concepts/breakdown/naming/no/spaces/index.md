# No spaces in `concepts/` names

## Concept

Do not use ASCII spaces in file or folder names under `concepts/`.
A space looks like prose but acts like a separator in many tools.
That mismatch causes mistakes.

Shell details: [Spaces in file names and the command line](../../../../computer/filename_spaces_command_line.md).

## Why

- Commands and scripts split on spaces
- Copy/paste gets fragile
- URLs become harder to read (`%20`)

## What to do instead

Use one clear token per segment and add folder depth if you need extra words.
Also see [No hyphens](../hyphens/README.md) and [No underscores](../underscores/README.md).

## Related

[Naming `no/`](../no.md); [Singular](../../yes/singular/README.md); [Path and file naming](../../../naming.md).
