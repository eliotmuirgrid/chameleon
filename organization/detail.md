# Concept - Detail Pages

## Concept

Use two layers:

- Core page: `<concept>.md`
- Optional depth: `<concept>/`

Keep the main page short. Put longer examples and edge cases in the folder pages. This follows [separation of concerns](../system/design/separation/of/concerns.md), lowers [cognitive load](../system/design/cognitive_load/index.md), and matches the [concept standard](../rule.md).

## Why

- Readers get the core idea fast.
- Depth is still available when needed.
- One page keeps one job.

## Pattern

For `abc`:

- `abc.md`
- `abc/`
- `abc/<topic>.md`

If there are many detail files, add `abc/README.md` as an index.

## Quick test

1. Can someone learn the core from `abc.md` alone?
2. Is deeper content moved to `abc/` pages?
3. Can readers jump straight to the detail they need?

## Anti-pattern

Do not keep adding tangents to the hub page. Split and link instead. See [Special case: overloaded concepts](overloaded_concept.md) and [Kitchen sink page](kitchen_sink_page.md).
