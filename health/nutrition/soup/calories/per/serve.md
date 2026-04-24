# Soup — calories per serving (proportional allocation)

## Concept

For a **mixed soup** where ingredients are combined, you can estimate calories in one serving by **share of final cooked weight**, using [proportional allocation](../../../../../system/design/proportional/allocation.md).

## Example (numbers are illustrative)

You log ingredients from `foods.md` (or labels) and sum calories:

| Ingredient        | Amount | Calories (from reference) |
| ----------------- | ------ | --------------------------: |
| Chicken stock     | 500 ml ≈ 500 g (if density ≈ 1) | 50 |
| Potatoes, diced   | 200 g  | 160 |
| Carrots           | 100 g  | 41  |
| Onion             | 80 g   | 32  |
| Olive oil (in pot)| 15 g   | 120 |

**C_total** ≈ **403 kcal** (sum of the column).

After cooking, you strain or pour the batch into one container and weigh **only the soup** (tare the pot if needed — [tare scale](tare_scale.md)).

Suppose **W_total** = **950 g** cooked (water evaporation changed weight; that is why you use **cooked** weight for the uniform batch).

**Calories per gram** of this batch:

`C_total / W_total` = 403 / 950 ≈ **0.42 kcal/g**

**One serving:** you ladle **257 g** into a bowl (**W_serving** = 257).

`C_serving` = 403 × (257 / 950) ≈ **109 kcal**

Round to match your logging precision (whole kcal vs one decimal).

## Why this matches the model

The soup is treated as **one uniform liquid** — each gram has about the same calorie density. That is the same assumption as in the main [proportional allocation](../../../../../system/design/proportional/allocation.md) page.

## When to be careful

- **Oil or cream not fully mixed** — stir before ladling, or allocate fat separately.
- **Solids left in the pot** — if you only eat broth, **W_serving** should reflect what is in the bowl, and **W_total** should match what you measured for the whole batch you are splitting.

Definitions and assumptions live on [proportional allocation](../../../../../system/design/proportional/allocation.md). Clean weights use [zeroing (taring) a scale](tare_scale.md). Imperfect days still benefit from **good enough** splits—see [nutritional tracking realities](../../../nutritional/tracking/realities.md).
