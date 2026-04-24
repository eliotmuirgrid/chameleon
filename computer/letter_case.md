# Letter case (for paths and names)

## Concept

In this notebook, **case** in file and folder names means **letter case**: the distinction between **capital** and **small** forms of the same **letter** when those forms exist (for example **A** versus **a**). Many path names today use **Latin** letters that have such pairs. Other writing systems **do not** split the same way, so “case” questions **apply differently** there; this tree mostly discusses **Latin-style** paths as they show up in cross-platform software.

Path names are **text**. Whether `Readme.md` and `README.md` are the **same path** is a **comparison rule** the filesystem (or tool) chooses—not a matter of taste. **Do not** use words like **case-insensitive** until the reader can reach **what “case” names** here; use the pages below in **order** when you teach or link.

## Comparison rules (define these after “case,” before OS examples)

Use these as **canonical homes** for the adjectives; **link** them on **first precise use** in any concept page that talks about path spelling:

1. [Case-sensitive comparison](letter_case/case_sensitive_comparison.md) — differing letter case ⇒ **different** path under the rule.
2. [Case-insensitive comparison](letter_case/case_insensitive_comparison.md) — differing letter case can still mean the **same** path for **collision** / **same-file** decisions.
3. [Case-preserving storage](letter_case/case_preserving_storage.md) — stores the spelling you typed while still using a [case-insensitive](letter_case/case_insensitive_comparison.md) rule for **matching**.

Index with short blurbs: [Letter case (index)](letter_case/index.md).

## Where this shows up

[Filesystem case on major desktop OS families](git/git_core_ignorecase/filesystem_case_by_os.md) applies the rules above per **OS family**. [Git `core.ignorecase` and filesystems](git/git_core_ignorecase.md) is the **Git** layer on top. [Common filesystems (cross-platform)](storage/common_filesystems.md) names **formats**; each format page points back here for **vocabulary**.

## Related

[Simple English (80/20 language rule)](../communication/simple_english.md); [Recursive decomposition — practice checklist](../breakdown/recursive_decomposition_practice.md) (check **6**, **Pass E**).

**Same boundary shape:** [USB-C charger compatibility](../electricity/usb-c-power.md) negotiates **electrical profiles** across plug and device; [Adaptive communication](../communication/adaptive_communication.md) negotiates **human style** while keeping the message true. Here the “profiles” are [case-sensitive](letter_case/case_sensitive_comparison.md) vs [case-insensitive](letter_case/case_insensitive_comparison.md) path rules; Git’s layer is [Git `core.ignorecase` and filesystems](git/git_core_ignorecase.md).
