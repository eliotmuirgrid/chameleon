# Git (concepts)

Git and the layers around it (hosting, cross-platform filename behavior). These pages live under **Computer** because Git is often used from a terminal and is core tooling for how this repository evolves. Git implements [source control (the idea)](../../pareto/general/source_control.md); the rest of the computer guides sit under [Computer (concepts)](../README.md).

## Pages

- [Git (in plain terms)](git.md) — what Git does: history, merge, general-purpose use.
- [Git `core.ignorecase` and filesystems](git_core_ignorecase.md) — portable Git paths vs **three OS families**’ filesystem case rules; [overloaded concept](../../concept/overloaded_concept.md) with a [filesystem-only detail page](git_core_ignorecase/filesystem_case_by_os.md); also a [leaky abstraction](../../system/design/leaky_abstraction.md) example.
- [GitHub, Bitbucket, and Git](github_bitbucket_and_git.md) — local Git vs optional hosting sites.
