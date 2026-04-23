# Concept standard

This is the single source of truth for writing concept pages in this repository.

## Rules

1. **General case first** - define the concept so it works across domains before any domain example.
2. **Simple English first** - use high-school English and the 80/20 language rule. See also: [Simple English guidelines](communication/simple_english.md).
3. **Define terms once** - if a specialist term is required, define it in one short line.
4. **One concept per page** - do not mix concept, implementation, and deep examples on the same page.
5. **Core before derived** - state the principle before tools, methods, or workflows derived from it.
6. **Use two layers for depth** - keep core explanation in `<concept>.md` and move optional depth into `<concept>/` pages; see [Concept - Detail Pages](concept/detail.md).
7. **Transfer test** - include a quick check that the concept still makes sense in another domain.
8. **Link out for depth** - keep the page light; use "See also" links for detail pages.

## Required page shape

1. **Concept** - one short definition.
2. **See also** - links to why, method, examples, and related concepts.

## Detail page pattern

Use the detail-page pattern documented here: [Concept - Detail Pages](concept/detail.md).

## Quality gate before publish

- Can a bright high-school reader understand it?
- Is this the least information needed to be correct?
- Is deep detail moved to linked pages?
- For growing topics, does optional depth live under `<concept>/` per [Concept - Detail Pages](concept/detail.md)?
- Does the page stay focused on one concept?

These rules apply [separation of concerns](system/design/separation_of_concerns.md) to concept writing itself.

## See also

- [Concept - Detail Pages](concept/detail.md) - hub page plus `<concept>/` depth; index README when there are many detail files.
- [Concept - Inline Links](concept/inline_links.md)
- [Concept - Relative Links](concept/relative_links.md)