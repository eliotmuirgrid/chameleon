# One Rule To Rule Them All

This repository keeps its persistent AI guidance in:

- `.cursor/rules/one-rule-to-rule-them-all.mdc`

That file is the single always-on Cursor rule for this repository when opened at the repo root.

This document lives at the top level of the repository, adjacent to `cpp` and `lua`.

## What It Teaches

- Preserve existing user edits and avoid reverting unrelated work.
- Prefer current project names: `COR*`, `TEST*`, and `CORcommandLine`.
- Avoid reintroducing legacy names such as `COL*`, `UNIT*`, and `CLI*`.
- In `cpp/`, prefer project-local includes in package form such as `#include <COR/CORlog.h>` rather than quoted local forms like `#include "CORlog.h"`.
- Use `#pragma once` in headers.
- Use the copyright line:
  `// Copyright (C) 2026 Eliot Muir.  All rights reserved.`
- Do not add `// Date:` lines.
- Put function/method opening braces on the same line as `)` or after the initializer list.
- Leave control-flow brace style alone unless explicitly asked to change it.
- Favor readability and simple makefiles.

## Recreate On A New Machine

If this file exists but the Cursor rule does not, tell an agent something like:

`Create an always-on Cursor rule at .cursor/rules/one-rule-to-rule-them-all.mdc using docs/ai/one-rule-to-rule-them-all.md as the source of truth. If you are working from inside cpp/, use ../docs/ai/one-rule-to-rule-them-all.md instead.`

If you want a shorter prompt, this is enough:

`Please make the one rule to rule them all for this repo. Read docs/ai/one-rule-to-rule-them-all.md and create the matching always-on Cursor rule. If you are working inside cpp/, read ../docs/ai/one-rule-to-rule-them-all.md.`

## Updating The Rule

When conventions change:

1. Update `.cursor/rules/one-rule-to-rule-them-all.mdc`
2. Update this document to match
3. Keep the rule short and concrete

## Workspace Note

There is an older copy of this rule under `cpp/.cursor/rules/` from when the project was commonly opened from inside `cpp/`. The root-level rule is now the active source for root-opened sessions.
