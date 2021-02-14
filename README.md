# Simple implementation of the knapsack algorithm

Just a quick little practice project, that implements the 0/1 knapsack algorithm.
The algorithm makes use of [dynamic programming](https://en.wikipedia.org/wiki/Dynamic_programming), which means it tries to split a bigger problem into smaller sub-problems.
This implementation does not work recursively but iteratively. The general idea is the following:
- Start from the smallest sub-problem (only the first item and a capacity of 1) and go to the biggest sub-problem (the last item and full capacity).
- Whenever a certain item does not fit into the given capacity, mark it as 0 in the "Keep" matrix and take the value from the same weight column but from the previous item row from the "Sub-problem" matrix (Which means 0 if it is the first item).
- When the current item does fit exactly into the given capacity, compare its value to the value of the same weight column one row above, when the current item's value is greater take the new value otherwise take the value from the row above. Mark the item in the "Keep" matrix with a 1, if it surpassed the previous row.
- When the current item's weight is smaller than the given capacity, get the sum of the current item's value and the value in the previous row at the column for the remaining weight and compare that sum to the value on the previous row for the given capacity. When the sum is greater insert that sum into the "Sub-problem" matrix at the current item & capacity, otherwise take the value from the previous row. Mark the item with a 1 in the "Keep" table, if the sum was greater than the previous row.

The maximum possible value can now be found within the "Sub-problem" matrix at row = number of items - 1, column = max weight - 1.
In order to get the optimal combination of items, go through the keep table starting at the bottom-right corner, whenever you find a 0 reduce the row index by 1.
Whenever you find a 1 take the item, reduce the column index by the weight of the taken item and the row index by 1.

## Building the project

```bash
git clone
cd knapsack_algorithm
meson build
ninja -C build
# max weight = 4, first item (weight: 1, value: 2), second item (weight: 3, value: 4)
./build/knapsack 4 1 2 3 4
```
