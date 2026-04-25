`prompt` sends text to the Cursor CLI agent in the `~/chameleon` workspace.

How it works:

1. Collects all command arguments into one string with `PROMPT="$*"`.
2. Calls:
   - `agent -p --workspace "$WORKSPACE" "$PROMPT" --trust`
3. The agent receives text as a prompt; it does not execute markdown files directly.

Examples:

- `./prompt Add a new concept directory called gardening`
- `./prompt "$(cat command.md)"`
