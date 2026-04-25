`ai.prompt` sends text to the Cursor CLI agent in the `~/chameleon` workspace.

How it works:

1. Collects all command arguments into one string with `PROMPT="$*"`.
2. Calls:
   - `agent -p --workspace "$WORKSPACE" "$PROMPT" --trust`
3. The agent receives text as a prompt; it does not execute markdown files directly.

Examples:

- `ai.prompt Add a new concept directory called gardening`
- `ai.prompt "$(cat command.md)"`
