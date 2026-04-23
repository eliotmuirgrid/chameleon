# Concept - Detail Pages

## Concept

Use a two-layer structure:

- A main concept page for the core idea.
- A matching folder for optional detail pages.

This keeps the core easy to read while still allowing depth.

## Why

- Lowers [cognitive load](../system/design/cognitive_load/README.md).
- Keeps one concept page focused on one concept.
- Lets readers choose depth based on need.

## Pattern

For a concept like `abc`:

- Main page: `abc.md`
- Detail folder: `abc/`
- Detail pages inside: `abc/<topic>.md`

Keep `abc.md` short and link out to detail pages only when needed.

## Quick test

Ask:

1. Can someone understand the core idea from `abc.md` alone?
2. Are deeper explanations moved to `abc/` pages?
3. Can a reader jump to detail without scanning unrelated text?

## See also

- [Concept standard](../concept.md)
- [Cognitive load](../system/design/cognitive_load/README.md)
- [Simple English (80/20 language rule)](../communication/simple_english.md)
- [Separation of concerns](../system/design/separation_of_concerns.md)
- [Small packet](../system/design/small_packet.md)