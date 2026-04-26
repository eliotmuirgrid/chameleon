# Rule: Approved Shell Language Only

## Scope

This rule applies to all shell task code and all agents (human and machine).

## Must

- MUST use commands defined in `language/computer/shell`.
- MUST keep task-level scripts free of OS-specific command details.
- MUST keep OS-specific behavior inside approved wrappers.

## Must Not

- MUST NOT use raw shell commands when an approved wrapper exists.
- MUST NOT create a new wrapper without explicit household consent.

## If Missing Wrapper

1. MUST stop implementation.
2. MUST explain the missing concept and why it is required.
3. MUST request household approval for a new wrapper name and behavior.
4. MUST wait for approval before creating the wrapper.

## Portability

- MUST write shell task code so it can run on a future operating system that does not exist yet.
- MUST target zero porting effort in task-level code when that operating system arrives.

## Enforcement Checklist (Pass/Fail)

- PASS only if all shell commands come from `language/computer/shell` wrappers.
- FAIL if raw shell commands are used where a wrapper exists.
- FAIL if a new wrapper is added without explicit household approval.
- PASS only if OS-specific logic is isolated to approved wrappers.