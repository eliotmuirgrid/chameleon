# Source control (the idea)

Source control is a system that remembers every change you make to a group of files, so nothing is ever truly lost.

If you are used to something like Microsoft Word tracking changes in a single document, source control expands that idea to an entire folder—and makes it reliable, complete, and easy to go backwards or understand what happened.

It lets you change things freely, knowing you can always recover an earlier version.

The same idea applies when several people work on the same project: the system keeps a clear history of who changed what, so you are not stuck with last-save-wins across a pile of copies.

Different programs implement this like Git. You only need the idea first; [Git (in plain terms)](../../computer/git/git.md) is how this repo usually does it. Hosting sites on top of Git are in [GitHub, Bitbucket, and Git](../../../../computer/git/github/bitbucket/and/git.md). For the broader “open files” picture, see [Open systems vs closed systems](open_versus_closed.md).

When the same project moves between machines, [letter case](../../computer/letter_case.md) in filenames can behave differently by OS; Git’s [`core.ignorecase`](../../computer/git/git_core_ignorecase.md) tracks that reality—discipline in naming still matters for predictable results.