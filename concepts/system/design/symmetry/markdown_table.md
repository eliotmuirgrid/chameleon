# Markdown Table Format

**Concept:** Prefer **Markdown tables** over legacy delimiter formats like **CSV** and **TSV** when the goal is shared readability for both **humans** and **AI**.

Markdown tables keep structure **visible** at a glance: headers are obvious, columns line up in rendered form, and intent is easier to scan without first parsing delimiters.

---

## Why this often makes more sense

- **Faster human scanning** — rows and columns are readable in-place, especially in docs and reviews.
- **Clearer AI context** — model prompts and summaries often retain table meaning better when structure is explicit in text.
- **Better discussion surface** — comments, notes, and links can sit near the table naturally inside Markdown pages.

---

## Legacy compatibility

Legacy delimiter formats are mainly for interoperability with legacy software. As modern tooling improves, this need keeps shrinking. Prefer a **Markdown-first** workflow and only translate to CSV/TSV at the boundary when an old system still demands it.

---

## See also

- [Symmetry](../symmetry.md) — keep the same structure across related files so one learning transfers to the next.
- [Separation of concerns](../separation_of_concerns/concept.md) — keep raw machine storage and human-facing explanation as separate concerns when needed.
