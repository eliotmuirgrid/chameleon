# Immediate solutions (what you have now)

When **building or running systems**, it often pays to **solve the urgent problem quickly** with **whatever is already available**—tools, time, people, budget, code you can reuse—instead of waiting for the perfect design.

**Why bother:** Blockages cost more than imperfect fixes. A **working patch** keeps delivery, support, or life moving; you learn what the system really needs before you invest heavily.

**The tradeoff:** Fast, local fixes can **pile up** (harder to reason about, duplicated patterns, or hidden assumptions). Treat many of them as **provisional**: good enough to **ship or survive now**, with a **path** to consolidate later when the shape of the problem is clear.

**Quick test:** If this fix **failed tomorrow**, would you still know **why** it was there and **what** would replace it? If not, leave a **short note** (comment, ticket, doc) when you can.

**When not to shortcut:** **Safety**, **security**, **compliance**, or **data you cannot lose**—those deserve the **right** tool, not only the **nearby** one.

## See also

- [Symmetry](symmetry.md) — when two parts of a system should **match on purpose** for the long haul; pairs well with “fix now, align later.”
