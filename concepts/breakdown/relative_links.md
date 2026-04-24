# Concept - Relative Links

## Concept

Use relative Markdown links from the current file.
Do not use commit-hash URLs or copied snapshot links.

Example: [Solubility mechanism](../physics/solubility_mechanism.md)

This works with the [concept standard](../concept.md), [inline links](inline_links.md), and [Concept - Detail Pages](detail.md).

## Rules

1. Use relative paths from the current file.
2. Do not use commit-hash URLs.
3. Avoid absolute URLs unless required.
4. If you must use an absolute repo URL, use main branch links.
5. Prefer links that keep working as the repo changes.

## Why

- Relative links support a living docs system.
- Commit links point to frozen snapshots.

## Mental model

- Relative links = living system
- Commit links = frozen snapshot
