# Recursion

**Recursion** means solving a problem by solving a smaller version of the same problem.

You repeat that pattern until you hit a clear stop point.

## Core parts

- **Base case** - the stop rule; no more recursion.
- **Recursive step** - the rule that reduces the problem size.
- **Progress measure** - how you know each step gets closer to the base case.

## System view

Recursion works when each step:

1. makes the problem smaller,
2. keeps the same problem shape,
3. and eventually reaches the base case.

## Failure mode

If there is no valid base case (or no real progress), recursion does not stop.

## Simple example

To count down from 3:

- count(3) -> count(2) -> count(1) -> count(0) stop.

A sibling pattern that also halves a problem space is [binary search](binary/search.md). Recursion is easier to read with [Simple English (80/20 language rule)](../../communication/simple_english.md) and lower [cognitive load](../design/cognitive_load/load.md); if the stack of calls grows without discipline, you drift toward [entropy](../design/entropy.md). Clear [separation of concerns](../design/separation/of/concerns.md) keeps the base case and recursive step in view.
