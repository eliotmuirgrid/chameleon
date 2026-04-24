# Path and file naming (concepts tree)

## Concept

This notebook stores ideas as **Markdown files** in a **folder tree**. Names are not just labels: they are **strings** that **tools** (shells, Git, search, preview servers) parse and compare. A practical **naming convention** keeps paths **easy to type**, **stable in links**, and **predictable across machines**.

**Convention (preference, not a purity test):**

1. **No spaces**, **no hyphens**, **no underscores**, and **no plural** path-segment names under `concepts/`—each invites **naming ambiguity** (see [Naming `no/`](naming/no.md): [Spaces](naming/no/spaces/README.md), [No hyphens](naming/no/hyphens/README.md), [No underscores](naming/no/underscores/README.md), [No plural](naming/no/plural/README.md)). Prefer **one head token per segment** and **folders** or **hub + detail** for extra words; see [Singular](naming/yes/singular/README.md).
2. **Stable letter case** in names: pick a spelling and keep it. In practice, **lowercase** is a simple default. If you use capitals (for example a **proper noun** in a file name), treat that spelling as part of the identity and **do not rename casually**.
3. **Head term in the leaf basename** when you can: let the **file name** carry the **main noun** (or short identifier), and put **qualifiers** in **parent folders** or a **hub + detail** split rather than stuffing several words into one segment. Prefer **singular** path segments when one idea owns the path; see [Singular](naming/yes/singular/README.md) and [No plural](naming/no/plural/README.md).

Rule **3** is an **aspiration**. It fights you when the idea is naturally a **phrase** or **relation**; then **deeper folders** or the **two-layer pattern** on [Concept - Detail Pages](detail.md) is better than gluing words with `_`, `-`, or spaces.

## Why spaces hurt

Short version: spaces force **quoting** in shells, complicate **copy/paste**, and show up as **`%20`** in **URLs**—and they **blur** whether a string is **one path** or **several tokens**. **Hyphens**, **underscores**, and **plural** segments add other **ambiguities**; see [Naming `no/`](naming/no.md). The underlying shell behavior is in [Spaces in file names and the command line](../computer/filename_spaces_command_line.md).

## Why case discipline matters

Path matching is **not universal**: the same spelling with different **capitalization** can be **one path** or **two paths** depending on [case-sensitive comparison](../computer/letter_case/case_sensitive_comparison.md) vs [case-insensitive comparison](../computer/letter_case/case_insensitive_comparison.md), and storage can still be [case-preserving](../computer/letter_case/case_preserving_storage.md). A casual rename of `readme.md` to `README.md` can be a **no-op** or a **break-every-link** event depending on OS and tool.

For how **desktop families** compare case, see [Filesystem case on major desktop OS families](../computer/git/git_core_ignorecase/filesystem_case_by_os.md). For **Git’s** layer on top, see [Git `core.ignorecase` and filesystems](../computer/git/git_core_ignorecase.md). The hub [Letter case (for paths and names)](../computer/letter_case.md) is the vocabulary home before you use adjectives like **case-insensitive** in prose.

**Naming takeaway:** treat path strings as **identifiers**, not free-form prose. **Lowercase** and **singular**, **one token per segment** where you can avoids spaces, hyphen and underscore **overloading**, and plural **cardinality** confusion; when you must preserve **branding** or **proper nouns**, document the spelling and link to the letter-case pages when you teach path behavior.

## How this ties to structure

- **Hub + folder:** keep the **short** name on `<topic>.md` and move long tails into `<topic>/`, per [Concept - Detail Pages](detail.md). That achieves much of what “put extra words in folders” wants **without** arbitrary depth.
- **Glossaries:** prefer **one identity per file** (and a hub) rather than one **kitchen sink** file; see the [practice checklist](recursive_decomposition_practice.md) and [Special case: overloaded concepts](overloaded_concept.md).
- **Links:** after you rename or split, update **relative** links; rules in [Concept - Relative Links](relative_links.md).

## Related

[Concept standard](../concept.md); [Naming `no/`](naming/no.md); [Naming `yes/`](naming/yes.md); [Letter case (for paths and names)](../computer/letter_case.md); [Spaces in file names and the command line](../computer/filename_spaces_command_line.md).
