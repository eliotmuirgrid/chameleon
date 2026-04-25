## Team Workflow

The team runs a single mission profile: one workflow, one shared toolset, repeatable execution.

## Install For Every Teammate

1. Clone or update `~/chameleon`.
2. Run the installer:
   - `./language/computer/shell/ai.install`
3. Add your bin directory to `PATH` if needed:
   - `export PATH="$HOME/.local/bin:$PATH"`
4. Reload your shell:
   - `source ~/.zshrc`
5. Confirm installed commands:
   - `git.publish --help` (or run with a message)
   - `git.republish --help` (or run with a message)
   - `prompt "test prompt"`

## Current Command Set

- `ai.install`: installs and links shell tools into your bin directory.
- `git.publish`: stage, commit, and push from `~/chameleon`.
- `git.republish`: amend the latest commit message and push safely.
- `prompt`: send text to the Cursor CLI agent.

## Why This Works (Theory of Constraints)

- Throughput is constrained more by inconsistent execution than by raw speed.
- Shared scripts create a stable operating loop across the team.
- Repetition standardizes handoffs and lowers coordination noise.
- One repo improvement upgrades the constrained step for every operator.
- Consistency compounds into lower rework, faster recovery, and sustained tempo.
