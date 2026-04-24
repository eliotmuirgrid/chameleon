## Sparsely populated directories

A directory structure is sparsely populated when path depth grows faster than useful grouping.

Common signals:

- Many single-child directory chains.
- Folders that contain only one file and one subfolder.
- Names that add path length but little meaning.

Why this matters:

- It increases [cognitive load](../../../system/design/cognitive_load/load.md).
- It makes retrieval and navigation slower.
- It can hide weak [separation of concerns](../../../system/design/separation/of/concerns.md) by splitting one concern across too many levels.

When this pattern appears, prefer [flattening directories](../../flatten.md) and avoid compensating with [directory meta list files](../../no/list/meta.md).
