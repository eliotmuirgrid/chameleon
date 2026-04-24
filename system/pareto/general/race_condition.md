# Race condition

**Summary:** A **race condition** happens when **two or more processes** are **in flight at the same time** and the **outcome** depends on **which one finishes first** (or in what **order** events land). In **software**, it is a classic bug pattern; in **business** and **procurement**, the same shape appears when you **parallelize** slow external systems—each with its own [bottleneck](bottleneck.md)—and your **decision** depends on **timing** you do not fully control.

---

## The idea

If **only one** thing could happen, there is no “race.” When **several** things can happen **overlapping in time**, **order** and **speed** matter: the **result** can change depending on **who responds first**, **what arrives when**, or **what you do** before all inputs are in.

Managing that well means **naming** the uncertainty: **assumptions**, **deadlines**, **fallbacks**, and **rules** so you are not accidentally **committed** to two incompatible paths.

---

## Example: two vendors, two bottlenecks, one problem

You have the **same** technical or procurement **problem** and you ask **two vendors** for **quotes**. Each vendor has its own **ordering or follow-up process**, and each process has a [bottleneck](bottleneck.md)—slow replies, quotes that sit behind an installer, **internal handoffs**, or thin weekend coverage.

You are now in a **race** you did not design:

- **Neither** quote may arrive quickly; both pipelines are **loaded**.
- **Whichever** quote or clarification **lands first** may change what you **do next**—even if you later **prefer** the other offer when it finally arrives.
- **Comparing** “fairly” may require **both** responses; if one path is **much slower**, you face **pressure** to commit before the second input exists—a **timing-dependent** decision.

That is a **race condition** in the wild: **outcome** depends on **how two slow systems** (each with its own **constraint**) **interleave** with your **deadlines** and **patience**. See [theory of constraints](theory_of_constraints.md) for why each vendor’s **throughput** is capped by its **weakest step**; your project sits **above** both, waiting on **two** independent clocks.

---

## Named vendors: Audiophile and Eddies

For **what each business is** in this notebook, see the vendor concepts **[Audiophile](../../entity/company/audiophile.md)** and **[Eddies](../../entity/company/eddies.md)** ([Company (concepts)](../../entity/company/index.md)).

**Audiophile** is one real case where **order follow-up** is the bottleneck—worked through in [Example: order follow-up as a bottleneck (Audiophile)](example_bottleneck_order_followup_audiophile.md). **Eddies** is **another** vendor: **not** a direct competitor, but **another** plausible solution path for the **same** underlying problem. It **also** shows an **ordering bottleneck**—delayed replies, **tentative** slots, and confirmation still pending before anything is **firm**.

Illustrative email (ordering / scheduling thread):

> Dear Eliot,
>
> I hope my email finds you well. Our apologies in delay in reverting to you with our next available appointment.
> We have tentatively scheduled your onsite appointment for this Friday, 10th April around 3pm.
> Kindly advise if this time suits at your earliest convenience.
>
> Until then, have a pleasant rest of your day.
> Kind regards,
>
> Kisha

When **Eddies** and **Audiophile** (and any **other** paths) are **in parallel**, you are not only racing **two** quotes—you are juggling **several** **slow pipelines**, each with its own **handoffs**. **Which** date, **which** vendor, and **which** plan **sticks** can still depend on **timing**—the same **race-condition** shape, just with **more** moving parts.

---

## What helps

- **Explicit rules** — e.g. “we will not commit until both quotes are in,” or “we will decide by date X regardless,” so timing does not **implicitly** decide.
- **Single owner** for tracking **each** open vendor or scheduling thread, so **handoffs** inside *your* side do not add **another** race.
- **Honest** expectations when **external** [bottlenecks](bottleneck.md) are **known**—parallel requests buy **optionality**, not **speed**, unless at least one path is **actually** fast.

The same timing shape in code is [race conditions in software](race_conditions_in_software.md). [Theory of constraints](theory_of_constraints.md) names the wider improvement loop. **Vendors** in this notebook: [Audiophile](../../entity/company/audiophile.md), [Eddies](../../entity/company/eddies.md) ([Company (concepts)](../../entity/company/index.md)). **Follow-up bottleneck** story: [Example: order follow-up as a bottleneck (Audiophile)](example_bottleneck_order_followup_audiophile.md).
