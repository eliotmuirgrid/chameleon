## Team Workflow

The team runs a single mission profile: one workflow, one shared toolset, repeatable execution.

## Install For Every Teammate

1. Clone or update `~/chameleon`.
2. Run:
   - `~/chameleon/language/computer/shell/ai.install`
3. Reload your shell:
   - `source ~/.zshrc`
4. Confirm installed commands:
   - `git.publish --help` (or run with a message)
   - `git.republish --help` (or run with a message)
   - `ai.prompt "test prompt"`

## Current Command Set

- `ai.install`: update your shell `PATH` for `~/chameleon/language/computer/shell`.
- `git.publish`: stage, commit, and push from `~/chameleon`.
- `git.republish`: amend the latest commit message and push safely.
- `ai.prompt`: send text to the Cursor CLI agent.

## Continuous Update Model

- Commands run directly from the repository path.
- Pulling latest changes updates behavior immediately.
- No copied binaries, no symlinks, and no stale installed versions.

## Why This Works (Theory of Constraints)

- Throughput is constrained more by inconsistent execution than by raw speed.
- Shared scripts create a stable operating loop across the team.
- Repetition standardizes handoffs and lowers coordination noise.
- One repo improvement upgrades the constrained step for every operator.
- Consistency compounds into lower rework, faster recovery, and sustained tempo.
