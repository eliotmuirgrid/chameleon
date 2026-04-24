# Special case: overloaded concepts

## Concept

A page is overloaded when it tries to explain too many different ideas at once.
That is a signal to split the page.

Create smaller pages, give each page one main job, then link them.
Use a short hub plus detail pages when helpful: [Concept - Detail Pages](detail.md).

This is not about removing complexity. It is about placing complexity in structure, so readers do not hold everything at once.

## Why

- Lower [cognitive load](../system/design/cognitive_load/README.md)
- Better [separation of concerns](../system/design/separation_of_concerns/concept.md)
- Cleaner reuse across pages

## Example

[Git `core.ignorecase` and filesystems](../computer/git/git_core_ignorecase.md) combines several threads (OS rules, Git behavior, and setting details). The split pattern is used there, with a filesystem-only page: [Filesystem case on major desktop OS families](../computer/git/git_core_ignorecase/filesystem_case_by_os.md).

For the repeat habit, see [Recursive concept decomposition](web.md).
