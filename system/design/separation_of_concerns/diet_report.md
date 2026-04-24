# Separation of concerns — example: diet reports

Back to: [Hub](../separation_of_concerns.md) · [Concept](concept.md) · [Code example](code.md)

---

## Two different questions (do not merge them)

Diet tracking here involves **separate concerns**:

| Concern | Question it answers | If you mixed it with the other |
|--------|----------------------|--------------------------------|
| **Shared meal / batch** | What was cooked? How is the pan split? | You still need this, but it is **not** anyone’s personal total. |
| **Each person vs their targets** | Did **Eliot** hit **his** caps? Did **Subrina** hit **hers**? | A single “household total” **blurs** whether **either** person met **their** protein or calories. |

Same idea as the [hub](../separation_of_concerns.md): **one home for one job**—forks in one drawer, **your** totals in **your** report.

---

## How that maps to files

- **Targets (two homes):** [`targets_eliot.md`](../../../../tracking/targets_eliot.md) and [`targets_subrina.md`](../../../../tracking/targets_subrina.md) — different numbers on purpose.
- **Raw logs (one consolidated table):** [`data.md`](../../../../tracking/data.md) in [`tracking/`](../../../../tracking/) with **Date** first and **Person** second — filter rows per person/day as needed.
- **Day write-ups (optional):** either **one** `YYYY-MM-DD-summary.md` with **two** sections plus shared detail, or **split files** — `YYYY-MM-DD-summary.md` as a **hub**, `YYYY-MM-DD-summary-eliot.md`, `YYYY-MM-DD-summary-subrina.md`, and `YYYY-MM-DD-shared.md` for batch/split math only ([example](../../../../tracking/2026-04-12-summary.md)).

Shared breakfast/lunch math (splits, batch totals) lives in **shared** (or the shared section of a monolithic summary); **each person’s** file compares **their** intake to **their** targets.

---

## Concrete example *(2026-04-12)*

- [**Hub**](../../../../tracking/2026-04-12-summary.md) — links to the two **person** reports and **shared** cooking reference ([Separation of concerns](../../../../concepts/system/design/separation_of_concerns.md)).
- [**Eliot — report**](../../../../tracking/2026-04-12-summary-eliot.md) · [**Subrina — report**](../../../../tracking/2026-04-12-summary-subrina.md)
- [**Shared — reference**](../../../../tracking/2026-04-12-shared.md) — breakfast batch, lunch splits, marinade notes

Cross-links back to [concept](concept.md) and this page. Tracker layout: [`README.md`](../../../../tracking/index.md).

---

## Cross-reference

- [Code](code.md) — same *pattern* in software (modules by job).
