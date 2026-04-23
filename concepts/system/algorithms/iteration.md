# Iteration

**Iteration** means improving a result through repeated passes.

Each pass follows the same small loop: do, check, adjust, repeat.

## Core parts

- **Current state** - what you have now.
- **Feedback signal** - what tells you if it got better or worse.
- **Adjustment rule** - what you change on the next pass.
- **Stop rule** - when to stop iterating.

## System view

Iteration is useful when one perfect pass is unlikely, but many small corrections can move the system toward [equilibrium](../design/equilibrium.md).

## Failure mode

Without a clear feedback signal or stop rule, iteration can become random churn.

## Simple example

Write a draft, review for clarity, revise one section, then review again.

Domain example: [Building a bathroom (iterative approach)](iteration/bathroom_build.md) - one change at a time, learning from each step.

## See also

- [Recursion](recursion.md)
- [Pipeline](../troubleshooting/pipeline.md)
- [Equilibrium](../design/equilibrium.md)
- [Cognitive load](../design/cognitive_load/README.md)
- [Concept - Detail Pages](../../concept/detail.md)
