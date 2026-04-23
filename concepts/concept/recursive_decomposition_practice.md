# Recursive decomposition — practice checklist

Optional depth for [Recursive concept decomposition (break up into a web)](breakup_concepts_into_web.md). This file holds the **template** and **step-by-step checks** so the short hub page can stay one idea.

---

## Hub page shape (before or instead of bloat)

When a topic is still **one page** but already **thick**, a clear **hub** often needs:

- **Title** — clear, noun-based name.
- **One sentence** — what this page is *for* (its identity).
- **Core tension** — why the topic is hard (for example two systems that disagree, or a [leaky abstraction](../system/design/leaky_abstraction.md)).
- **Threads** — two or three **separate tracks** (for example tool logic vs OS rules vs team convention), each able to move to its own file later.
- **Links out** — every **black-box** term that is **central** but **not** the main job of this page should become an inline link to a **small** page or a **promise** to add one.
- **Takeaway** — one line the reader can carry away.

That shape lines up with the [concept standard](../concept.md), [Simple English (80/20 language rule)](../communication/simple_english.md), and [small packets](../system/design/small_packet.md) of meaning.

---

## Recursive checks (do these in order)

1. **Spot overload** — If one paragraph **must** explain two different systems (for example **Git** and **kernel path rules**) to make sense, **stop**. Move the second system to its own page and link back. The signal matches [Special case: overloaded concepts](overloaded_concept.md).

2. **Spot prerequisites** — Terms that act like **black boxes** (for example a normalization rule, a disk structure name) and **carry** the argument belong on their **own** page if they are not the topic under hand. On the hub, **link** them; do not **define** them at length in passing.

3. **Parentage** — Every page you **split out** should link **up** to the hub (or parent) that motivated it, so the [web](breakup_concepts_into_web.md) stays navigable both ways.

4. **Boundary** — Keep [tool internal model and environment](internal_model_and_environment.md) in view: **inside the tool** vs **outside constraints** should not share one sentence unless the sentence is *about* that boundary.

---

## When to stop splitting

You stop when extra pages would only repeat **primitives** you can name in one line (**string**, **bit**, **true/false**, **byte**) or when another layer would be **noise**. The [concept standard](../concept.md) quality gate still applies: least information needed to stay **correct**, with depth in **linked** pages per [Concept - Detail Pages](detail.md).
