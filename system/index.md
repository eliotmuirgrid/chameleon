# System (concepts)

Short notes on **how systems are shaped**—architecture, design ideas, and tradeoffs—in the same style as the rest of [`concepts/`](../): one main idea per page, linked for reuse.

Topics that accumulate examples or long transfers should use the [two-layer detail pattern](../breakdown/detail.md) (hub `topic.md` plus optional `topic/` pages).

## Design

- [Symmetry](design/symmetry.md) — two sides built the same way so one lesson covers both; when to match on purpose and when not to.
- [Immediate solutions](design/immediate/solutions.md) — fix urgent problems fast with **resources at hand**; when that helps and when to be careful.
- [Separation of concerns](design/separation_of_concerns/concept.md) — split **different jobs** so each can be named and adjusted without tangling the rest; [hub with links to examples](design/separation/of/concerns.md).
- [Cognitive load](design/cognitive_load/index.md) — how much thinking effort a system demands at one time.
- [Entropy](design/entropy.md) — drift toward disorder unless active maintenance pushes back.
- [Equilibrium](design/equilibrium.md) — steady balance where opposing flows (in/out, create/fix, drift/maintenance) are roughly equal.
- [Proportional allocation](design/proportional/allocation.md) — split a total across parts by **share of size** (e.g. calories per serving from batch weight).
- [Abstraction](design/abstraction.md) — hide detail behind a simpler surface so you can reason with less at once.
- [Leaky abstraction](design/leaky/abstraction.md) — when hidden reality breaks through and you must deal with it anyway.
- [Journaling](design/journal.md) — record intent or steps **before** final commit so recovery and audit stay possible; applies beyond disks (databases, workflows).

## Algorithms

- [Algorithms (index)](algorithms/index.md) — repeatable step-by-step problem-solving methods.
- [Recursion](algorithms/recursion.md) — solve by reducing to smaller same-shape subproblems until a stop rule.
- [Binary search](algorithms/binary/search.md) — search sorted data by halving the remaining range each step.
- [Iteration](algorithms/iteration.md) — improve outcomes by repeating a loop of action, feedback, and adjustment.

## Troubleshooting

- [Troubleshooting (index)](troubleshooting/index.md) — finding failures in running systems.
- [Pipeline](troubleshooting/pipeline.md) — **ordered steps** (each feeds the next); plain-language idea, useful when something breaks along the way. Example: [power / won’t turn on](troubleshooting/pipeline/power.md).

## Organization

- [Organization (index)](organization/index.md) — structure information and responsibilities so systems remain understandable and maintainable.
