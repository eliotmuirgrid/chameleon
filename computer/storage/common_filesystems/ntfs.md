# NTFS

Optional identity for [Common filesystems (cross-platform)](../common_filesystems.md). [Letter case (for paths and names)](../../letter_case.md) first; then [Filesystem case on major desktop OS families](../../git/git_core_ignorecase/filesystem_case_by_os.md).

---

## Concept

**NTFS** (*New Technology File System*) is the usual **default filesystem** on **Windows** drives today. It **stores** long filenames and metadata.

## Case (typical desktop)

For **most** desktop setups, NTFS behaves [case-insensitive](../../letter_case/case_insensitive_comparison.md) and [case-preserving](../../letter_case/case_preserving_storage.md) for normal programs. That is the detail that matters for **cross-platform paths** when collaborators use **Windows** defaults.
