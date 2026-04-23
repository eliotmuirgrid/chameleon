# Kitchen sink page

## Concept

A **kitchen sink page** is a page where **several related** ideas have been **dumped together** because they **connect**. One file tries to carry the whole neighborhood.

## Why it hurts

That choice **feels efficient** at first: one place to scroll, one bookmark, no new files to name. In practice it **raises** [cognitive load](../system/design/cognitive_load/README.md): the reader must **hold** many identities at once, and edits keep **tugging** different threads in the same paragraph. The shape is close to an [overloaded concept](overloaded_concept.md), just organized by **convenience for the writer** instead of **one job per page**.

## Better pattern

Prefer a **small index page** that **points** to **separate identity pages**—each concept gets **its own home**. That is the same spirit as the [two-layer detail pattern](detail.md) and [recursive concept decomposition](breakup_concepts_into_web.md): **structure** carries the relationships so each file can stay a [small packet](../system/design/small_packet.md) of meaning.

## Linking

This pattern also **improves linking**. Instead of sending someone to a **fragile section anchor** inside a **long** file, you link to a **real file**. Paths to files stay **stable** as headings move; [inline links](inline_links.md) land on a page whose **title and job** match what you meant. For path rules, see [Concept - Relative Links](relative_links.md).

**Example:** cross-platform notes link to [ext4](../computer/storage/common_filesystems/ext4.md) (its **own** page), not to a `#ext4` anchor inside a six-format glossary. The split is documented as a [glossary packet split](recursive_decomposition_practice.md#glossary-packet-split).
