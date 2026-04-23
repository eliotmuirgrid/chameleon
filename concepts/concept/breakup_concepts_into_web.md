# Recursive concept decomposition (break up into a web)

## Concept

**Recursive concept decomposition** means: when a topic **grows** past one clean job, you **split** it into **smaller** pages, **link** them, and **repeat** until each page matches **one main idea**. You are not deleting complexity; you are **moving** it into **structure** so a human—or an assistant—can follow **one thread at a time**.

This repo already encodes the same pressure in the [concept standard](../concept.md), [Special case: overloaded concepts](overloaded_concept.md), and [Concept - Detail Pages](detail.md). This page names the **habit** for people who edit here and for **automated assistants**: treat overload as a **signal**, then **refactor** the notes the way you would refactor code.

---

## Why

Big topics **pull in** prerequisites, second tools, and edge cases. If all of that stays in **one file**, readers pay [cognitive load](../system/design/cognitive_load/README.md) for threads they may not need, and summaries **blur**. [Simple English (80/20 language rule)](../communication/simple_english.md) is easier to hold when each page has **one job**. [Separation of concerns](../system/design/separation_of_concerns/concept.md) applies to **writing** as much as to systems: **separate**, then **link**.

---

## What to do in practice

Use the **template and ordered checks** on [Recursive decomposition — practice checklist](recursive_decomposition_practice.md): hub shape, four recursive rules, **iterative passes** (structure first, then **term audit**), and when to **stop** splitting.

Keep **tool logic** and **environment rules** in **different** pages when both matter; the distinction is [Tool internal model and environment](internal_model_and_environment.md).

---

## Worked example (do not copy the threads into this page)

**Filesystem letter case** across **Windows**, **macOS**, and **Linux** is **not** defined here—that was an old “start here” exercise and it **duplicated** work that already lives under Git. For the **three OS filesystem** thread alone, read [Filesystem case on major desktop OS families](../computer/git/git_core_ignorecase/filesystem_case_by_os.md). For **Git** plus **overload** plus **assistants’ checklist**, read [Git `core.ignorecase` and filesystems](../computer/git/git_core_ignorecase.md). That pair is the **living** version of “break Thread A / B / C apart.”

---

## Takeaway

If a draft **needs** two systems or a long **black-box** detour to stay honest, **refer** to an existing concept page or **add** a small new one—then **link**—instead of **stretching** the page you are on.
