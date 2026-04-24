# No spaces in `concepts/` file and folder names

## Concept

**Spaces** are **not** used in file or folder names under `concepts/`. A space is **ambiguous** in a path string: it is both **visible gap** in prose and **invisible splitter** in shells and scripts, so the same characters can mean **one path** to a human and **several arguments** to a tool. That double reading is **naming ambiguity**, not only a quoting bug. The same “path as identifier” goal rules out **hyphens** and **underscores** in segments for parallel reasons; see [No hyphens](../hyphens/README.md) and [No underscores](../underscores/README.md).

The usual **mechanism** (shells split on spaces; quoting fixes it) is in [Spaces in file names and the command line](../../../../computer/filename_spaces_command_line.md). This page is the **site-local** rule: no literal space in `concepts/` names.

Separator hubs: [Naming `no/` (hub)](../no.md); [Path and file naming (concepts tree)](../../../naming.md).

## Why this site avoids spaces

Each reason is its own short page:

1. [Command line and scripts](command_line_and_scripts.md) — one path becoming two tokens without quotes; scripts over `concepts/`.
2. [Copy, paste, and teaching](copy_paste_and_teaching.md) — plain-text paths in docs and chat; fewer paste mistakes.
3. [URLs and previews](urls_and_previews.md) — `%20`, readability, and generated links.
4. [Path as identifier](path_as_identifier.md) — alignment with Git, search, and the naming hub.

## What to use instead

Do **not** glue words with **spaces**, **hyphens**, or **underscores** inside one segment. Prefer a **single head token** per segment and add depth with **folders** or a **hub + detail** split; see [Singular](../../yes/singular/README.md), [No hyphens](../hyphens/README.md), and [No underscores](../underscores/README.md).

## Related

[Naming `no/` (hub)](../no.md); [Path and file naming (concepts tree)](../../../naming.md); [Spaces in file names and the command line](../../../../computer/filename_spaces_command_line.md); [Concept - Relative Links](../../../relative_links.md).
