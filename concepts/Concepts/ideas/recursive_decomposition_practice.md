# Recursive decomposition — practice checklist

Optional depth for [Recursive concept decomposition (break up into a web)](breakup_concepts_into_web.md). This file holds the **template** and **step-by-step checks** so the short hub page can stay one idea.

---

## Hub page shape (before or instead of bloat)

When a topic is still **one page** but already **thick**, a clear **hub** often needs:

- **Title** — clear, noun-based name.
- **One sentence** — what this page is *for* (its identity).
- **Core tension** — why the topic is hard (for example two systems that disagree, or a [leaky abstraction](../../system/design/leaky_abstraction.md)).
- **Threads** — two or three **separate tracks** (for example tool logic vs OS rules vs team convention), each able to move to its own file later.
- **Links out** — every **black-box** term that is **central** but **not** the main job of this page should become an inline link to a **small** page or a **promise** to add one.
- **Takeaway** — one line the reader can carry away.

That shape lines up with the [concept standard](../../concept.md), [Simple English (80/20 language rule)](../../communication/simple_english.md), and [small packets](../../system/design/small_packet.md) of meaning.

---

## Recursive checks (do these in order)

1. **Spot overload** — If one paragraph **must** explain two different systems (for example **Git** and **kernel path rules**) to make sense, **stop**. Move the second system to its own page and link back. The signal matches [Special case: overloaded concepts](overloaded_concept.md).

2. **Spot prerequisites** — Terms that act like **black boxes** (for example a normalization rule, a disk structure name) and **carry** the argument belong on their **own** page if they are not the topic under hand. On the hub, **link** them; do not **define** them at length in passing. When many **named identities** (formats, vendors, APIs) already sit in **one glossary file**, run [Glossary packet split](#glossary-packet-split) below instead of growing that file.

3. **Parentage** — Every page you **split out** should link **up** to the hub (or parent) that motivated it, so the [web](breakup_concepts_into_web.md) stays navigable both ways.

4. **Boundary** — Keep [tool internal model and environment](internal_model_and_environment.md) in view: **inside the tool** vs **outside constraints** should not share one sentence unless the sentence is *about* that boundary.

5. **Promote nested supporting concepts** — On **identity** or **leaf** pages, watch for **mechanism words** or **significant modifiers** (for example **journaled**, **normalized**, **consensus**) that name a **whole idea**, not just flavor text. If the idea **reuses** across domains or needs a **fair** explanation for trust, **do not** grow the leaf into a tutorial. Add pages in an **abstraction ladder**: **general pattern** (wide [transfer test](../../concept.md)) → optional **domain bridge** → **identity** leaf. Example: [Journaling](../../system/design/journaling.md) (general) → [Journaled filesystem](../../computer/storage/journaled_filesystem.md) (storage) → [XFS](../../computer/storage/common_filesystems/xfs.md) (one format). Each step links **up** and **down** so humans and assistants can **climb** or **stop** early.

6. **Lexical prerequisite order (define base before derived)** — If term **D** only makes sense after term **B** (for example **case-insensitive** after **letter case**), **do not** introduce **D** in a **precise** way before the reader has a path to **B**. Link the **base** on **first** substantive use in each file (or earlier). Keep a **canonical hub** for **B** and **small** pages for each **derived** adjective so the whole repo shares one **vocabulary ladder**. Example hub: [Letter case (for paths and names)](../../computer/letter_case.md) with [case-sensitive](../../computer/letter_case/case_sensitive_comparison.md), [case-insensitive](../../computer/letter_case/case_insensitive_comparison.md), and [case-preserving](../../computer/letter_case/case_preserving_storage.md) comparisons.

---

## When to stop splitting

You stop when extra pages would only repeat **primitives** you can name in one line (**string**, **bit**, **true/false**, **byte**) or when another layer would be **noise**. The [concept standard](../../concept.md) quality gate still applies: least information needed to stay **correct**, with depth in **linked** pages per [Concept - Detail Pages](detail.md). If a **leaf** still hides a **reusable mechanism** behind one adjective, you have **not** finished—run **Promote nested supporting concepts** (check **5**) instead of stopping early.

---

## Glossary packet split

Some pages are not quite a free-form [kitchen sink page](kitchen_sink_page.md), but they **stack** many **parallel** definitions—**NTFS**, **ext4**, six acronyms in a row—because “they are all filesystems.” That is still **one scroll** and still pushes links toward **heading anchors** inside a long file. Same problem class: **many named identities** in one file instead of **one home per name**.

**Better pattern (generalized):**

1. **Hub** — Short `Topic.md` with **one sentence** identity for the **family** (“common filesystems for cross-platform readers”) and **no** long definitions in the body.
2. **Folder** — `Topic/` matching the hub name (same pattern as [Concept - Detail Pages](detail.md)).
3. **One file per named identity** — `Topic/ntfs.md`, `Topic/apfs.md`, … each small, each linking **up** to the hub and sideways where useful. When an identity **depends** on a **shared mechanism** (see check **5**), link **out** to a **general** or **domain** page instead of **inlining** the mechanism on every leaf.
4. **Index** — `Topic/README.md` listing links (optional but helpful when there are several children).
5. **Redirect stub** — If an old **kitchen-sink filename** is linked from outside the repo, replace its body with “moved to hub” prose instead of breaking paths silently.

**Worked example:** [Common filesystems (cross-platform)](../../computer/storage/common_filesystems.md) with identities under [`common_filesystems/`](../../computer/storage/common_filesystems/README.md); callers link to **files** (for example from [Filesystem case on major desktop OS families](../../computer/git/git_core_ignorecase/filesystem_case_by_os.md)). **Lexical ladder:** path adjectives presuppose [Letter case (for paths and names)](../../computer/letter_case.md) plus the three comparison pages under [`letter_case/`](../../computer/letter_case/README.md)—see check **6** and **Pass E**.

**Why:** [Files are more stable than headings](kitchen_sink_page.md#linking)—anchors drift when headings get renamed; a path to `ext4.md` stays honest.

---

## Iterative passes (not one-shot)

Decomposition works best as a **short loop**, not a single heroic split.

1. **Pass A — Structure** — Apply **checks 1–4** above: overload, prerequisites, parentage, boundary. Split **threads** onto the right pages. If you already know a **leaf** will lean on a **reusable mechanism**, plan check **5** in the same pass so you do not ship **dead adjectives**. If the topic uses **derived** vocabulary tied to a **shared base** (path **case** words, …), plan check **6** and **Pass E** so you do not ship **floating adjectives**. Prefer a **small index** plus **separate identity pages** over one long mixed file—a [kitchen sink page](kitchen_sink_page.md). If the file is instead a **glossary of parallel names** (same kind of thing, many headings), use [Glossary packet split](#glossary-packet-split): hub, folder, **one file per name**, optional redirect for the old path.

2. **Pass B — Term audit** — Reread the draft **only** for **opaque tokens**: **acronyms**, **product or format names**, **APIs**, anything a **high-school reader** would have to guess. For each token, choose **one**:
   - **Inline gloss** — one clause in **plain English** on **first** use, if the idea is **local** to this page; or
   - **Link** — to an existing concept page or glossary packet; or
   - **New small page** — if the name will **reuse** across the repo. Prefer **one file per identity** after a [glossary packet split](#glossary-packet-split) (example: [ext4](../../computer/storage/common_filesystems/ext4.md) from [Common filesystems (cross-platform)](../../computer/storage/common_filesystems.md), linked from [Filesystem case on major desktop OS families](../../computer/git/git_core_ignorecase/filesystem_case_by_os.md)).

3. **Pass C — Re-run the gate** — After links land, read again: did any paragraph **smuggle** a second system back in? Did a link **replace** needed context with a **dead name**? Repeat **B** until the page reads clean or you consciously **defer** work (note *where* the next pass should start).

4. **Pass D — Abstraction ladder** — On pages that are already **split** (especially **identity** leaves), scan for **adjectives or labels** that imply a **mechanism** readers must trust. If removing the word would make the sentence **empty** or **misleading**, apply check **5**: add or link **general → domain → identity** so advanced readers and assistants can **climb** one step at a time instead of **absorbing** the whole stack on one screen.

5. **Pass E — Lexical prerequisites** — Scan for **derived** vocabulary (**case-insensitive**, **normalized**, …) that **presupposes** a **base** term (**letter case**, **Unicode**, …). If the base is not already linked **on first precise use** in this file, add a link to the **canonical hub** (check **6**). Example: any new paragraph about path **collision** should point at [Letter case (for paths and names)](../../computer/letter_case.md) before it leans on [case-insensitive comparison](../../computer/letter_case/case_insensitive_comparison.md).

**Why iterative:** Pass A fixes **shape**; Pass B fixes **vocabulary debt** you could not see until the shape existed; Pass D fixes **hidden mechanism debt** on leaves; Pass E fixes **definition order** across the web. Trying to do all of it in one pass is how **journaled** stays a decoration with no home—or how **case-insensitive** floats without **case**.

---

## “Automatic” expansion — what is realistic

Markdown does **not** expand terms by itself. What you can add **around** the repo:

| Approach | What you get | Cost |
|----------|----------------|------|
| **This checklist** in Pass B | Humans and assistants **know** to run a second pass | Cheap; relies on discipline |
| **Cursor rule or Agent Skill** | After editing `concepts/`, “run term audit: list acronyms/proper nouns without links; stub or link” | One-time setup; behavior follows the rule |
| **Curated wordlist + script** | CI fails if `NTFS` appears without link to `common_filesystems/ntfs.md` (or chosen canonical path) | Brittle (false positives, misses synonyms) |
| **LLM in CI** | Theoretically full expansion | Slow, flaky, expensive for a notes repo |

**Practical default:** encode **Pass B** in a **project rule** or **skill** so assistants **always** iterate; when a glossary grows, **split** it per [Glossary packet split](#glossary-packet-split) (see [Common filesystems (cross-platform)](../../computer/storage/common_filesystems.md)). **True** automation without a maintainer list tends to be **noise**; **semi-automatic** (rule + stable file targets + links) matches how this tree already grows.
