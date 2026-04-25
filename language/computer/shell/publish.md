`publish` stages, commits, and pushes changes in `~/chameleon`.

How it works:

1. Sets `WORKSPACE="$HOME/chameleon"`.
2. Collects all command arguments into one commit message with `COMMIT_MSG="$*"`.
3. Runs git with `git -C "$WORKSPACE" ...`, so your shell directory does not change.
4. Executes:
   - `git -C "$WORKSPACE" add .`
   - `git -C "$WORKSPACE" commit --all -m "$COMMIT_MSG"`
   - `git -C "$WORKSPACE" push`

Examples:

- `./publish update gardening notes`
- `./publish $'Add gardening concept\n\nAdd cilantro and flower notes'`

Behavior note:

- `./publish This is a multiline comment` is one line, not a multiline commit message.
