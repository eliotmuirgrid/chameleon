# Separation of concerns *(the idea)*

**Core idea:** **Do not tangle solutions to different problems.** Give each concern its **own** place—name it, implement it, and change it **without** dragging the rest along.

That habit **simplifies** work: less to hold in your head at once, fewer accidental couplings.

---

## Why it works

When concerns are **mixed**, the system behaves like a **messy workshop**: things are **harder to find**, progress **slows**, and **mistakes** hide in the clutter—so errors are **more likely** and **harder to spot**. When concerns are **separated**, each part answers **one** kind of question, so it is easier to **write**, **read**, and make **reliable**.

That drift toward mess has the same shape as [**entropy**](../../../pareto/general/decluttering_and_retrieval.md#entropy-and-search-space) in physical space—more places to look, more **uncertainty**—even though the mechanics differ in code.

---

## Keep the concept separate from the examples

This page is **only** the abstract pattern—on purpose.

**Concrete examples** (code, diet tracking, contracts, …) belong on **their own pages** so that:

- You can **learn the idea first** with **almost no domain knowledge**.
- Examples can go **deep** or **change** (new stack, new log format) without **rewriting** the definition.
- Readers who already know one domain are not forced through **another** domain’s detail just to get the core idea.

That is itself **separation of concerns**: **definition** here, **illustrations** elsewhere—[code](code.md), [diet reports](diet_report.md).

---

## Quick test

Can you **change or verify one thing** (one rule, one bug, one clause, one person’s totals) **without** touching unrelated parts? If not, concerns may still be **tangled**.

---

## See also

- [Symmetry](../symmetry.md) — when two parts **should** match on purpose.
- [Immediate solutions](../immediate_solutions.md) — fix one slice without redesigning everything.
- [Small packet](../../../design/small_packet.md) — small units; separation is **which** unit owns **which** job.

*Hub (all entry points):* [Separation of concerns](../separation_of_concerns.md)
