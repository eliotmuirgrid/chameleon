f# Zeroing (taring) a scale

When you **tare** a scale, you tell it to treat the current weight as **zero**.

Most often, that means:

1. Put your bowl or plate on the scale.
2. Press **Tare** (or **Zero**).
3. Add food.
4. The number you see is now just the food, not the bowl.

---

## Why this matters

- **Cleaner data** - You log the food weight only, which improves macro and calorie tracking.
- **Fewer mistakes** - You do not need to subtract bowl weight in your head.
- **Faster workflow** - Add one item, tare, add next item in the same bowl.
- **Better repeatability** - The same method each day gives more reliable trend data.

---

## System model view

Taring is a system-modeling method for isolating one variable.

General form:

`Measured value = target signal + background`

When you tare, you set background to zero at the start of the measurement window, so the display mostly tracks the target signal.

### Significant variables in this system

- **Target mass** - food mass you want to measure.
- **Container mass** - bowl, plate, cup, or spoon mass (background load).
- **Scale offset / baseline** - current zero point (changed by tare).
- **Displayed mass** - what the scale reports after baseline is applied.
- **Resolution and rounding** - how finely the scale can measure (for example, 1 g steps).
- **Time stability** - drift from movement, vibration, uneven surface, or delayed settling.
- **Unit selection** - grams vs ounces; mixed units increase error risk.
- **Operator sequence** - order of steps (place container, tare, add item, log, tare again).

### Held constant vs changing

- **Held constant:** container setup, unit, surface, and baseline process.
- **Changing:** only the food mass for the current ingredient.

This is why taring is an example of **isolating variables**.

---

## In plain language

Think of tare as saying:  
"Ignore everything already on the scale. Start counting from here."

---

## Quick examples

### Example 1: Bowl

- Empty bowl weighs `420 g`.
- Put bowl on scale and press tare.
- Add cottage cheese until display shows `200 g`.

Logged food = `200 g` cottage cheese (not `620 g`).

### Example 2: Multiple ingredients in one bowl

- Add oats to `30 g`, log oats.
- Press tare.
- Add blueberries to `100 g`, log blueberries.
- Press tare.
- Add peanut butter to `12 g`, log peanut butter.

Each entry is direct and clear, with no subtraction step.

---

## Common mistakes to avoid

- Forgetting to tare after placing container.
- Moving the scale to an uneven surface.
- Letting part of the bowl touch the counter.
- Using inconsistent units (`oz` one day, `g` the next).

Weights feed the [shared nutrition plan — Eliot & Subrina](shared_nutrition_plan_eliot_subrina.md) and [calorie deficit](calorie_deficit.md) math.

---
