# Concept - Detail Pages

## Concept

Use a two-layer structure:

- A main concept page for the core idea (`<concept>.md`).
- A matching folder for optional depth (`<concept>/`).

This keeps the core easy to read while still allowing depth. It matches [separation of concerns](../system/design/separation_of_concerns.md): definition on the hub page, illustrations and long transfers on linked pages.

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

When there are several detail pages, add `abc/README.md` as a small index that links back to `abc.md` and lists each detail file. Examples in this repo: [Equilibrium detail pages](../system/design/equilibrium/README.md), [Slatboard detail pages](../home/slatboard/README.md), [Open vs closed detail pages](../pareto/general/open_versus_closed/README.md).

Domain-specific algorithm examples can live under a parent folder that matches the main algorithm page (for example [Iteration](../system/algorithms/iteration.md) with [Bathroom build](../system/algorithms/iteration/bathroom_build.md)).

## Quick test

Ask:

1. Can someone understand the core idea from `abc.md` alone?
2. Are deeper explanations moved to `abc/` pages?
3. Can a reader jump to detail without scanning unrelated text?

## Anti-pattern

Do not stack long analogies, domain transfers, and implementation detail on the main hub when they could live in `abc/<topic>.md` with one short bridge paragraph on `abc.md`.

## See also

- [Concept standard](../concept.md)
- [Cognitive load](../system/design/cognitive_load/README.md)
- [Simple English (80/20 language rule)](../communication/simple_english.md)
- [Separation of concerns](../system/design/separation_of_concerns.md)
- [Small packet](../system/design/small_packet.md)
