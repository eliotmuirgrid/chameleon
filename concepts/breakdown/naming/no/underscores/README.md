# No underscores in `concepts/` path names

## Concept

**Underscores** are **not** used in file or folder names under `concepts/`. In path naming they **borrow meaning** from **program identifiers** (`snake_case`, `__dunder__`, generated symbols), so a segment like `case_insensitive_comparison` reads as **code** or **API surface** as often as it reads as **plain language**. Readers **disagree** whether `_` is a **word join**, a **namespace**, or **noise** from tooling—and search, review, and mental parsing inherit that **ambiguity**. That fights the same goal as [No hyphens](../hyphens/README.md) and [No spaces in `concepts/` names](../spaces/README.md): a path segment should behave like a **stable name**, not a **mini expression**.

**What to do instead:** keep each segment to a **head noun** (or short agreed **identifier** without `_`, `-`, or space) and push extra words into **parent folders** or a **hub + detail** split; see [Singular](../../yes/singular/README.md) and [Concept - Detail Pages](../../../detail.md).

## Related

[Naming `no/` (hub)](../no.md); [No hyphens](../hyphens/README.md); [No spaces in `concepts/` names](../spaces/README.md); [No plural](../plural/README.md); [Singular](../../yes/singular/README.md); [Path and file naming (concepts tree)](../../../naming.md); [Concept - Relative Links](../../../relative_links.md).
