# Shared nutrition plan (draft) — Eliot & Subrina

**Status:** Draft for discussion. Numbers live in the tracker as **`targets_eliot.tsv`** and **`targets_subrina.tsv`** (`cpp/tracker/`). This note ties goals to food concepts—not a prescription.

---

## Why this exists

You often eat together and have **different primary goals**. **Family breakfast** is a **key part of the plan:** you **eat together** then, so **breakfast should carry a substantial share** of the day’s food—**protein, carbs, and fiber**—not a token meal. **Later meals** (lunch, dinner, snacks) **fill in** what is left toward each person’s targets. **Cooking culture:** you can still make **custom dishes per person**—**the same plate is not required** when targets or tolerances differ.

- **Eliot (54, ~219 lb):** Move toward a **healthier body composition** — **lose fat** while **building or preserving muscle**. That implies eating **fewer calories than you burn in a full day** (see **Terms** below), **high protein**, and **enough carbohydrate** to train and recover (see [Carbohydrates](carbohydrates.md)). **Adequate fat** supports hormones and absorption of fat-soluble vitamins; **fiber** (from whole plants) supports satiety, gut health, and blood-vessel and metabolic health.

- **Subrina (26, ~141 lb):** **Not** focused on weight loss. Goal is **strength** and **better body composition** (more muscle relative to fat). Training emphasis includes **left/right symmetry** so one side does not compensate for the other—that is mainly **program design** (unilateral work, volume balance, possible physio input), with **nutrition** supporting **recovery** and **protein** for tissue adaptation.

---

## Principles (shared table, different portions)

| Theme | Eliot | Subrina |
|--------|--------|---------|
| **Energy** | Eat **less than you burn** in a day (see **Terms**); cap in `targets_eliot.tsv` | Roughly **maintenance** (same calories in and out) or a **small surplus** if lean gain is the priority |
| **Protein** | **First priority** in a deficit | **High** relative to body weight for recomposition |
| **Carbs** | **Sufficient**, not zero — supports training and muscle sparing ([Carbohydrates](carbohydrates.md)) | **Sufficient** for sessions; can flex with workload |
| **Fat** | Enough for health; capped to fit calories | Enough for health; not driven by a sharp deficit |
| **Fiber / plants** | Vegetables, fruit, legumes as volume and fiber | Same — variety and micronutrients |
| **Dairy** | **Use freely** within targets — good protein density (milk, yogurt, cottage cheese, whey, etc.) | **Not in large quantities** — **no** yogurt, cottage cheese, big milk drinks, or cheese-forward plates; **butter in cooking is fine** |
| **Alcohol** | **0** in targets (optional personal choice) | **0** in targets |
| **Breakfast (family)** | Aim for **~35–45%** of **daily calories** and a **large share of protein** at breakfast; lunch/dinner **lighter** if needed to stay within cap | Same idea: **~35–45%** of calories at breakfast when you eat together; **balance the rest** across lunch, dinner, snacks |

### Dairy in practice

- **Subrina** avoids **large servings of dairy** (e.g. yogurt, cottage cheese, cream-heavy sauces, big cheese courses). **Butter used in cooking** is **OK** and matches how you want flavor and fat in the pan. If she uses **protein powder**, a **non-dairy** type (e.g. egg white, pea, soy) usually fits better than whey—whatever she tolerates.
- **Eliot** can **use dairy in quantity** where it helps **protein** and **portions** (cottage cheese, yogurt, whey, etc.).
- **Kitchen rule:** you **do not have to eat the same dish**. Parallel builds—**her plate / his plate**—are normal when dairy or macros diverge.

### Family breakfast in practice

- **Plan the day from breakfast outward:** decide **rough breakfast macros first** (eggs, oats, fruit, **Eliot’s** yogurt/cottage cheese/whey, **Subrina’s** non-dairy starches and proteins), then **assign** what remains to lunch and dinner.
- **Post-workout** food can **line up with breakfast** when timing matches (e.g. oats, fruit, dairy on the same table)—so **fuel and family meal** reinforce each other instead of competing.
- **Kids / household:** the shared table matters for rhythm; **your targets** still split on **each person’s** log.

---

## Files to use

| File | Purpose |
|------|---------|
| [`cpp/tracker/targets_eliot.tsv`](../../../../cpp/tracker/targets_eliot.tsv) | Eliot’s daily macro / calorie / fiber targets |
| [`cpp/tracker/targets_subrina.tsv`](../../../../cpp/tracker/targets_subrina.tsv) | Subrina’s daily macro / calorie / fiber targets |
| [`cpp/tracker/foods.tsv`](../../../../cpp/tracker/foods.tsv) | Shared density table for logging |
| Daily logs | `YYYY-MM-DD.tsv` per person where needed |

**Naming:** Use **`targets_eliot.tsv`** and **`targets_subrina.tsv`** only (no shared single `targets.tsv`) so tracker layout stays symmetric.

---

## What we still need (to tighten the plan)

1. **How much you move** — Job (desk vs on feet), steps, **resistance sessions per week**, cardio. That sets roughly **how many calories you burn per day**. Eliot’s **2000 kcal cap** only produces fat loss if it is **below** that burn; Subrina’s **~2200** is a **guess** until activity is known.

2. **Training schedule** — Which days are **hard** lower-body / upper-body / full body? That drives **carb timing** (still daily totals first).

3. **Medical context** — Meds, lipids, blood pressure, diabetes risk, kidney function (relevant to very high protein), eating history.

4. **Food culture & kitchen** — Who cooks, batch-cook vs daily, budget, foods you **won’t** eat. **Family breakfast** is the **main shared meal** for planning—**substantial** portions, then **lighter** lunch/dinner as needed. **Dairy:** Subrina **limits quantity** (no yogurt/cottage cheese style plates; **butter in cooking OK**); Eliot **uses** dairy freely for protein. **Custom dishes per person** when it helps—**same plate not required**.

5. **Symmetry work (Subrina)** — **Which** side/movements feel weak or asymmetric? A coach or PT can translate that into **exercise selection**; nutrition only supplies **fuel and protein** for adaptation.

6. **Rate of loss (Eliot)** — Target **~0.25–0.75%** body weight per week as a sustainable band (rule of thumb), adjusted by **scale trend** and **gym performance**.

---

## Next step

Turn this draft into a **one-week meal outline** that **starts with family breakfast** each day (largest or joint meal), then **lunch / dinner / snacks**. Use **two tracks** where useful—**Subrina’s dishes / Eliot’s dishes**—or **shared components + person-specific add-ons** (e.g., Eliot + yogurt or whey; Subrina + extra carb on training days; **butter in shared cooking** where you both want it).

---

## Terms (plain language)

- **Calories burned per day (often called TDEE — *total daily energy expenditure*)** — Everything you burn: **at rest** (keeping organs running), **digesting food**, **non-exercise movement** (fidgeting, walking to the car), and **planned exercise**. If you eat **less** than this total, you are in a **calorie deficit**; **about the same** is **maintenance**; **more** is a **surplus**.

- **Maintenance** — Most days, calories in ≈ calories out; weight is roughly stable.

- **Deficit** — Deliberately under maintenance to use stored energy (often body fat). Eliot’s targets assume a **controlled deficit** while keeping protein high.

- **Recomposition** — Gaining muscle while losing fat or staying the same weight; needs **training** + **enough protein**; calories may be near maintenance or a **small** deficit/surplus depending on the person.
