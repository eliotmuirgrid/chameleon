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

---

## Iterative passes (not one-shot)

Decomposition works best as a **short loop**, not a single heroic split.

1. **Pass A — Structure** — Apply the four **recursive checks** above: overload, prerequisites, parentage, boundary. Split **threads** onto the right pages.

2. **Pass B — Term audit** — Reread the draft **only** for **opaque tokens**: **acronyms**, **product or format names**, **APIs**, anything a **high-school reader** would have to guess. For each token, choose **one**:
   - **Inline gloss** — one clause in **plain English** on **first** use, if the idea is **local** to this page; or
   - **Link** — to an existing concept page or glossary packet; or
   - **New small page** — if the name will **reuse** across the repo (example: [Common filesystem names (quick reference)](../computer/storage/common_filesystem_names.md) feeding [Filesystem case on major desktop OS families](../computer/git/git_core_ignorecase/filesystem_case_by_os.md)).

3. **Pass C — Re-run the gate** — After links land, read again: did any paragraph **smuggle** a second system back in? Did a link **replace** needed context with a **dead name**? Repeat **B** until the page reads clean or you consciously **defer** work (note *where* the next pass should start).

**Why iterative:** Pass A fixes **shape**; Pass B fixes **vocabulary debt** you could not see until the shape existed. Trying to do both in one pass is how **NTFS** and **ext4** stay undefined.

---

## “Automatic” expansion — what is realistic

Markdown does **not** expand terms by itself. What you can add **around** the repo:

| Approach | What you get | Cost |
|----------|----------------|------|
| **This checklist** in Pass B | Humans and assistants **know** to run a second pass | Cheap; relies on discipline |
| **Cursor rule or Agent Skill** | After editing `concepts/`, “run term audit: list acronyms/proper nouns without links; stub or link” | One-time setup; behavior follows the rule |
| **Curated wordlist + script** | CI fails if `NTFS` appears without link to `common_filesystem_names.md` | Brittle (false positives, misses synonyms) |
| **LLM in CI** | Theoretically full expansion | Slow, flaky, expensive for a notes repo |

**Practical default:** encode **Pass B** in a **project rule** or **skill** so assistants **always** iterate; keep **human-curated** glossary pages (like common filesystem names) for families of terms that repeat. **True** automation without a maintainer list tends to be **noise**; **semi-automatic** (rule + glossary + links) matches how this tree already grows.
