# Special case: overloaded concepts

## Concept

Sometimes a concept starts **branching** too much. It touches **too many** other ideas at once. That is usually a **signal** from the system itself: **this concept is carrying too much weight**. The [concept standard](../concept.md) already asks for **one main idea per page**—when a page keeps fighting that rule, listen to the signal.

When that happens, the work is to [separate the concerns](../system/design/separation_of_concerns/concept.md). You **break** the overloaded idea into **smaller, clearer** concepts—closer to [small packets](../system/design/small_packet.md) of meaning—then **link** between them. Each page stays **simple**; the **web of links** keeps the relationships visible. A common move is the [two-layer detail pattern](detail.md): a short hub plus a matching folder of detail pages instead of one endless file.

The goal is **not** to remove complexity. The goal is to **move complexity into the structure**—headings, separate pages, cross-links—so the reader is **not forced to hold everything in their head at once**. That is the same pressure [cognitive load](../system/design/cognitive_load/README.md) describes: too many unrelated threads in one view cost attention you do not get back.

This idea should be applied to new concepts whenever they are added.

**Concrete example in this repo:** [Git `core.ignorecase` and filesystems](../computer/git/git_core_ignorecase.md) bundles **(a)** how **Windows, macOS, and Linux** typically treat **case** in filenames, **(b)** how **Git** keeps a **portable** path model across clones, and **(c)** what the **`core.ignorecase`** setting is for. The page names that overload up front, points assistants at **which thread belongs where**, and links filesystem-only depth to [Filesystem case on major desktop OS families](../computer/git/git_core_ignorecase/filesystem_case_by_os.md).

For the **step habit** (split, link, repeat), see [Recursive concept decomposition (break up into a web)](breakup_concepts_into_web.md).
