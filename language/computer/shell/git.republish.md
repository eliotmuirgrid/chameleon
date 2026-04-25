`git.republish` amends the latest commit message in `~/chameleon`.

How it works:

1. Sets `WORKSPACE="$HOME/chameleon"`.
2. Collects all command arguments into one replacement message with `NEW_MSG="$*"`.
3. Reads the current commit (`OLD_HEAD`) before amending.
4. Runs:
   - `git -C "$WORKSPACE" commit --amend -m "$NEW_MSG"`
5. If the old commit is already on the upstream branch, asks before a safe force push:
   - `git -C "$WORKSPACE" push "$REMOTE" "$BRANCH:$REMOTE_BRANCH" --force-with-lease="$REMOTE_BRANCH:$OLD_HEAD"`
6. If not yet pushed, performs a normal push to the tracked upstream.

Examples:

- `git.republish Added documentation for shell scripts`
- `git.republish $'Fix title\n\nClarify shell install steps'`
