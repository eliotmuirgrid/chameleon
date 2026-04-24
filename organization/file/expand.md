# Organizaton / File / Expand

When a markdown filename contains `_`, convert each `_` into one folder level.

The final segment stays the filename.

If there is no `_`, do not change the path.

## Examples

- `patient_advocate.md` -> `patient/advocate.md`
- `legal_aid_intake_worker.md` -> `legal/aid/intake/worker.md`

## Why

This creates a clear folder tree and removes long underscore compound names.
