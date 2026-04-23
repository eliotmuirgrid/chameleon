# Concept - Relative Links

## Concept

When creating links in this repository, use relative Markdown paths from the current file, not commit-hash URLs or UI-copied snapshot links.

Example: [Solubility mechanism](../../physics/solubility_mechanism.md)

This rule sits with the rest of the [concept standard](../../concept.md), works best alongside [inline links](inline_links.md) (link on the phrase you mean), and supports the [two-layer detail pattern](detail.md): relative paths keep hubs and detail folders navigable as the tree grows.

## Rules

1. Link using relative paths from the current file.
2. Do not use URLs containing commit hashes (for example, `/src/<hash>/...`).
3. Avoid absolute URLs unless explicitly required.
4. If an absolute repository URL is needed, use main branch references, never commit hashes.
5. Prefer links that remain valid as the repository evolves.

## Why

- Relative links support a stable, evolving knowledge graph.
- Commit-hash links point to frozen snapshots and break the living-document model.

## Mental model

- Relative links = living system.
- Commit links = dead snapshot.
- Always choose the living system.
