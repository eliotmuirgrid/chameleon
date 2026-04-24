# Spaces in file names and the command line

**Concept:** On the command line, a **space** usually **splits** one command into **separate words**. Each word is often treated as its **own argument** (its own file name, folder name, or option). That is how [the command line](command_line.md) turns typing into instructions; on macOS you can try it in [Using the terminal](using_the_terminal.md).

So a single file called `My Report.pdf` can look like **two** names—`My` and `Report.pdf`—unless you **quote** or **escape** the space. The shell does not automatically know you meant one path; it follows simple splitting rules first.

That makes everyday actions easier to get wrong: copy, move, delete, open, run a script, or pass a path into another tool. Errors can be noisy (“file not found”) or dangerous (the command acts on the **wrong** argument).

**Spaces still work** if you always wrap paths in quotes (`"My Report.pdf"`) or escape each space (`My\ Report.pdf`). The problem is **forgetting** that extra care in a quick one-liner, in automation, or when pasting instructions.

**Practical habit:** Prefer names without spaces when you expect command-line use—often **hyphens** (`my-report.pdf`), **underscores** (`my_report.pdf`), or **single glued words** (`myreport.pdf`). Same file on disk; fewer surprises when typing.
