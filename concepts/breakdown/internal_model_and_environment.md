# Tool internal model and environment

## Concept

Many tools have internal rules.
The environment (OS, filesystem, shell, network, other programs) has its own rules.

Keep these two stories separate on the page.
If you mix them, readers cannot tell where behavior comes from.

## Why

- Fewer wrong assumptions
- Lower [cognitive load](../system/design/cognitive_load/README.md)
- Clearer [separation of concerns](../system/design/separation_of_concerns/concept.md)

Related idea: [leaky abstraction](../system/design/leaky_abstraction.md).

## Example

[Git `core.ignorecase` and filesystems](../computer/git/git_core_ignorecase.md) separates Git behavior from filesystem behavior and links the filesystem thread to [Filesystem case on major desktop OS families](../computer/git/git_core_ignorecase/filesystem_case_by_os.md).
