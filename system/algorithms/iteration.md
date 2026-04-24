# Iteration

**Iteration** means improving a result through repeated passes.

Each pass follows the same small loop: do, check, adjust, repeat.

## Core parts

- **Current state** - what you have now.
- **Feedback signal** - what tells you if it got better or worse.
- **Adjustment rule** - what you change on the next pass.
- **Stop rule** - when to stop iterating.

## System view

Iteration is useful when one perfect pass is unlikely, but many small corrections can move the system toward [equilibrium](../design/equilibrium.md). It pairs with ordered multi-step flows in the [pipeline](../troubleshooting/pipeline.md) idea, with [recursion](recursion.md) when the loop has self-similar shape, and with attention to [cognitive load](../design/cognitive_load/index.md) so each pass stays reviewable. Growing topics can follow the [Concept - Detail Pages](../../breakdown/detail.md) pattern with a short hub and a matching detail folder.

## Failure mode

Without a clear feedback signal or stop rule, iteration can become random churn.

## Simple example

Write a draft, review for clarity, revise one section, then review again. A physical build that uses the same rhythm is [building a bathroom (iterative approach)](iteration/bathroom_build.md).
