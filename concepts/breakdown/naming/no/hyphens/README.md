# No hyphens in `concepts/` path names

## Concept

**Hyphens** are **not** used in file or folder names under `concepts/`. The character is **ambiguous** in naming: it already means **subtraction**, **ranges**, **flags**, and **other punctuation** in shells, math, URLs, and prose. In a path segment it is easy to read as “something technical happened here” instead of “this is a **word boundary** inside one identifier,” so people **disagree** about whether `foo-bar` is one name or a **relation** between `foo` and `bar`. Tools and humans then resolve names **inconsistently**, which is the opposite of a stable **path as identifier** story (see [No spaces in `concepts/` names — path as identifier](../spaces/path_as_identifier.md)).

Do **not** replace hyphens with **underscores** or **spaces** inside a segment either; see [No underscores](../underscores/README.md) and [No spaces in `concepts/` names](../spaces/README.md). Prefer **one head token per segment** and **folder depth** or a **hub + detail** split; see [Singular](../../yes/singular/README.md).

## Related

[Naming `no/` (hub)](../no.md); [No underscores](../underscores/README.md); [No spaces in `concepts/` names](../spaces/README.md); [No plural](../plural/README.md); [Singular](../../yes/singular/README.md); [Path and file naming (concepts tree)](../../../naming.md); [Concept - Relative Links](../../../relative_links.md).
