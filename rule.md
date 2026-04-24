# Concept standard

This is the single source of truth for writing concept pages in this repository.

## Rules

1. **General case first** - define the concept so it works across domains before any domain example.
2. **Simple English first** - use high-school English and the 80/20 language rule. See also: [Simple English guidelines](communication/simple_english.md).
3. **Define terms once** - if a specialist term is required, define it in one short line.
4. **One concept per page** - do not mix concept, implementation, and deep examples on the same page.
5. **Core before derived** - state the principle before tools, methods, or workflows derived from it.
6. **Use two layers for depth** - keep core explanation in `<concept>.md` and move optional depth into `<concept>/` pages; see [Concept - Detail Pages](breakdown/detail.md).
7. **Transfer test** - include a quick check that the concept still makes sense in another domain.
8. **Link out for depth** - keep the page light; weave related pages into the body with [inline links](breakdown/inline_links.md) instead of stacking a separate link list unless the page is a pure index.

## Required page shape

1. **Concept** - one short definition.
2. **Related links** - prefer inline links in the prose; a short tail list is only for pure indexes.

## Detail page pattern

Use the detail-page pattern documented here: [Concept - Detail Pages](breakdown/detail.md).

## Quality gate before publish

- Can a bright high-school reader understand it?
- Is this the least information needed to be correct?
- Is deep detail moved to linked pages?
- For growing topics, does optional depth live under `<concept>/` per [Concept - Detail Pages](breakdown/detail.md)?
- If the page keeps branching into many unrelated threads, is it time to split per [Special case: overloaded concepts](breakdown/overloaded_concept.md)?
- Does the page stay focused on one concept?
- Are you avoiding a [kitchen sink page](breakdown/kitchen_sink_page.md) where many identities share one file instead of a small index plus separate homes?
- If one file is a **glossary of parallel names** (formats, vendors, APIs), is it time for a [glossary packet split](breakdown/recursive_decomposition_practice.md#glossary-packet-split) into a hub plus **one file per identity**?
- On **identity** pages, do **mechanism words** (for example **journaled**) link through an [abstraction ladder](breakdown/recursive_decomposition_practice.md#iterative-passes-not-one-shot) (**general → domain → leaf**) per check **5** on the [practice checklist](breakdown/recursive_decomposition_practice.md)?
- For path **case** language (**case-sensitive**, **case-insensitive**, …), is [Letter case (for paths and names)](computer/letter/case.md) linked before **derived** terms, per check **6** and **Pass E** on the [practice checklist](breakdown/recursive_decomposition_practice.md)?

These rules apply [separation of concerns](system/design/separation/of/concerns.md) to concept writing itself. Supporting writer notes: [Concept - Detail Pages](breakdown/detail.md), [Special case: overloaded concepts](breakdown/overloaded_concept.md), [Kitchen sink page](breakdown/kitchen_sink_page.md), [Recursive concept decomposition](breakdown/web.md) with [practice checklist](breakdown/recursive_decomposition_practice.md), [Path and file naming](breakdown/naming.md), [Letter case (for paths and names)](computer/letter/case.md) (example **lexical ladder** for path vocabulary), [Journaling](system/design/journal.md) / [Journaled filesystem](computer/storage/journaled/filesystem.md) (example **abstraction ladder**), [Concept - Inline Links](breakdown/inline_links.md), [Concept - Relative Links](breakdown/relative_links.md).