# Separation of concerns — example: software

Back to: [Concept](concept.md)

---

In code, **separation of concerns** usually means **splitting modules by job**: authentication is not payment processing; persistence is not UI layout. Each layer or package answers **one** kind of question, exposes a **clear boundary**, and hides its internals. That way you can **fix billing** without accidentally breaking **login**, and **tests** can target one concern at a time.

The same structural move appears in a tight **legal contract**: obligations, risks, and remedies in **separate** clauses—not one paragraph that does everything.

---

## Reusable tools

Code that **isolates one concern** tends to read like a **small tool**: it does **one job** clearly, so the same function or module can be **called from many places** and **reused** for different features. A formatter, a validator, or a tiny pure function is **not** tied to one screen or one story—so you write it **once** and **compose** it elsewhere. **Large**, tangled routines are the opposite: they are hard to lift out and **reuse**, because everything is glued to a single context.

That overlap with **small, composable units** is why [Small packet](../../../design/small_packet.md) pairs well with this idea.

---

## Cross-reference

- [Diet reports](diet_report.md) — same *pattern*, different domain (shared meals vs individual targets).
