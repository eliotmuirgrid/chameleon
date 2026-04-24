# No directory index files

Do not use `index.md` to list files in a directory.

Use this algorithm:

1. Identify a directory where `index.md` is only a local file list.
2. For each non-local concept link that the index points to, create one local concept page.
3. In each new local page, make sure there is a link to its non-local target concept page.
4. Update links that point to the old `index.md` so they point to the right local concept page.
5. Delete the file `index.md`.

Specific example: `communication/assistant/ai/fast/index.md`

- Current local pages: `clarity.md` and `refine.md`.
- Current non-local links in the index: `../../../text/pace.md` and `../../weaken/index.md`.
- Required local replacements before deleting the index:
  - Create/update a local page for pace (for example `pace.md`) that links to `../../../text/pace.md`.
  - Create/update a local page for weaken (for example `weaken.md`) that links to `../../weaken/index.md`.
- Then update inbound links from `.../fast/index.md` to the appropriate local page (`clarity.md`, `refine.md`, `pace.md`, or `weaken.md`) and delete `fast/index.md`.
