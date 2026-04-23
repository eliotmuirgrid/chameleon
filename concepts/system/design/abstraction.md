# Abstraction (system design)

**Abstraction** means hiding messy detail behind a **simpler surface** so you can think and work with **fewer moving parts**.

You still depend on what is underneath—you just **do not name every piece** every time. A steering wheel **abstracts** the linkage to the wheels; a function name **abstracts** a block of steps; “save this file” **abstracts** bytes, blocks, and drivers.

Abstractions **trade detail for clarity**. That trade is good when the hidden layer **behaves** the way the simple surface **promises**.

## See also

- [Leaky abstraction](leaky_abstraction.md) — when hidden details **break through** and you must care about them anyway.
- [Separation of concerns](separation_of_concerns/concept.md) — split jobs so each layer can be named and changed.
- [Small packet](small_packet.md) — small units of work or data; abstractions often wrap many small steps into one named move.
