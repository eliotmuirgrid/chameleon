# Leaky abstraction (system design)

**Leaky abstraction** means an abstraction that **mostly** hides complexity, but **fails** in places: reality **seeps through**, and you suddenly need the details you were told you could ignore. It presupposes a working [abstraction](abstraction.md): a simple surface with something real underneath.

The simple surface still helps day to day. The leak shows up at **edges**: different hardware, another OS, scale, errors, or two systems that **promised the same thing** but **disagree** underneath. [Open systems vs closed systems](../../pareto/general/open/versus/closed.md) is the wider portability story when those edges are other tools or hosts. [Separation of concerns](separation_of_concerns/concept.md) is how you redraw boundaries once a leak appears.

When a leak appears, you fix it by **learning the hidden layer** just enough, **adding rules** (conventions, tests, guards), or **choosing a different boundary**—not by pretending the leak is not there.

## Example in this repo

- [Git `core.ignorecase` and filesystems](../../computer/git/git_core_ignorecase.md) — Git’s idea of a path vs how macOS, Windows, and Linux actually treat [letter case](../../computer/letter_case.md) in filenames.
