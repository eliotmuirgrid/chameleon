# Rule: No directory meta list files

A directory already lists its contents.

Do not add a separate file that only repeats that list.

Why this is good:

- It removes duplicate maintenance work.
- It lowers [cognitive load](../../../../cognition/load.md).
- It pushes better [separation of concerns](../../../../system/design/separation/concerns.md).

There basically should *never* be an index.md rule.  There is zero flexibility on this.

Related rule style: [Markdown writing rule link](../../../../communication/markdown/rules/no-meta-file.md).