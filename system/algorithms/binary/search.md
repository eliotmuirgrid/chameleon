# Binary search

**Binary search** finds a target in **sorted** data by repeatedly checking the middle and discarding half the remaining range.

## Preconditions

- Data is sorted in a known order.
- You can compare the target with the middle value.

## Core variables

- **Low** - start index of current search range.
- **High** - end index of current search range.
- **Mid** - middle index of current search range.
- **Target** - value you are searching for.

## How it works

1. Check the middle value.
2. If it matches, stop.
3. If target is smaller, keep the lower half.
4. If target is larger, keep the upper half.
5. Repeat until found or range is empty.

## Why it matters

- Very fast on large sorted lists.
- Reduces search space by 50% each step.
- Lower effort than scanning every item one by one.

Each step is a tight [small packet](../../design/small/packet.md) of work; the same halving idea shows up in [recursion](recursion.md) when subproblems shrink the same way.

## Failure mode

If data is not sorted correctly, results can be wrong.
