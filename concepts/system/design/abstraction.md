# Abstraction (system design)

**Abstraction** means hiding messy detail behind a **simpler surface** so you can think and work with **fewer moving parts**.

You still depend on what is underneath—you just **do not name every piece** every time. A steering wheel **abstracts** the linkage to the wheels; a function name **abstracts** a block of steps; “save this file” **abstracts** bytes, blocks, and drivers.

Abstractions **trade detail for clarity**. That trade is good when the hidden layer **behaves** the way the simple surface **promises**. When it does not, you get a [leaky abstraction](leaky_abstraction.md): hidden details break through and you must care about them anyway. [Separation of concerns](separation_of_concerns/concept.md) helps keep each layer nameable; [small packets](small_packet.md) of work or data are often what one abstraction wraps into a single named move.
