# Tracker (macros & day logs)

Daily macro planning and logs for **Eliot** and **Subrina**. Targets are **not** identical: each person has **their own** goals, so the tracker applies [**Separation of concerns**](../concepts/system/design/separation_of_concerns.md) — **separate reports per person** instead of one blended “household” total.

**Why:** [Diet reports example](../concepts/system/design/separation_of_concerns/diet_report.md) explains the two questions (shared batch vs each person vs targets) and how files map to that.

## Files

| File | Role |
|------|------|
| [`targets_eliot.md`](targets_eliot.md) | Eliot’s daily targets |
| [`targets_subrina.md`](targets_subrina.md) | Subrina’s daily targets |
| [`foods.md`](foods.md) | Shared density table for logging |
| [`data.md`](data.md) | Consolidated raw table for all dates; first columns are **Date** and **Person** |
| `YYYY-MM-DD-summary.md` | Optional **hub** for that day (links to per-person reports + shared reference) |
| `YYYY-MM-DD-summary-eliot.md` / `…-subrina.md` | That person’s day vs **their** targets |
| `YYYY-MM-DD-shared.md` | Shared meals & split rules *(reference only)* |

Eliot-only snacks, beer, or add-ons are rows with **Person = Eliot**; Subrina-only items use **Person = Subrina** in [`data.md`](data.md). Shared meals are split using the rules in that day’s **`YYYY-MM-DD-shared.md`** (or the hub **`YYYY-MM-DD-summary.md`** that links to it).

## Concepts

- [`shared_nutrition_plan_eliot_subrina.md`](../concepts/health/nutrition/shared_nutrition_plan_eliot_subrina.md) — shared plan context.
