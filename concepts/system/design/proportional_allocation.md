# Proportional allocation

## Concept

**Proportional allocation** means splitting a **total** across parts by **share of size**. Each part gets the same fraction of the total as its size is of the whole.

For food tracking, a common use is: **total calories in a batch** divided by **share of cooked weight** eaten.

## Why

You often know calories **for ingredients** and the **final weight** of the dish, but not calories **per bowl**. If the mixture is uniform, each gram inherits the same calorie density.

## Method

**Definitions (plain language)**

- **C_total** — total calories of all ingredients combined (before or after cooking; see assumptions).
- **W_total** — total weight of the portion you are allocating over (usually **cooked** batch weight in grams).
- **W_serving** — grams you eat.

**Calories in one serving**

`C_serving = C_total × (W_serving / W_total)`

**Equivalent form** (calories per gram, then scale):

`C_serving = (C_total / W_total) × W_serving`

**Macros** — same structure: multiply **total protein** (or fat, carbs) by `W_serving / W_total` when you assume the mixture is uniform.

## Assumptions

- **Uniform mixture** — every gram of the final dish has about the same calorie density (stirred soup, mixed stew). This fails if layers differ (e.g. undressed salad vs oil at the bottom).
- **Conserved totals** — ingredient calories sum to **C_total**; you are not double-counting oil left in the pan unless you include it in **W_total**.

When these break, treat layers separately or measure the actual portion.

## Quick test

1. Does **W_serving / W_total** add up to **1** across all servings you allocate (allowing rounding)?
2. If you ate the whole batch, do you recover **C_total**?

Worked food math: [Soup — calories per serving](../../health/nutrition/soup_calories_per_serving.md). Clean weights: [Zeroing (taring) a scale](../../health/nutrition/tare_scale.md). If you flatten reality too hard, you raise [entropy](entropy.md)—splits are only as good as the uniform-mixture story.
