# Special case: overloaded concepts

## Concept

Sometimes a concept starts **branching** too much. It touches **too many** other ideas at once. That is usually a **signal** from the system itself: **this concept is carrying too much weight**. The [concept standard](../concept.md) already asks for **one main idea per page**—when a page keeps fighting that rule, listen to the signal.

When that happens, the work is to [separate the concerns](../system/design/separation_of_concerns/concept.md). You **break** the overloaded idea into **smaller, clearer** concepts—closer to [small packets](../system/design/small_packet.md) of meaning—then **link** between them. Each page stays **simple**; the **web of links** keeps the relationships visible. A common move is the [two-layer detail pattern](detail.md): a short hub plus a matching folder of detail pages instead of one endless file.

The goal is **not** to remove complexity. The goal is to **move complexity into the structure**—headings, separate pages, cross-links—so the reader is **not forced to hold everything in their head at once**. That is the same pressure [cognitive load](../system/design/cognitive_load/README.md) describes: too many unrelated threads in one view cost attention you do not get back.
