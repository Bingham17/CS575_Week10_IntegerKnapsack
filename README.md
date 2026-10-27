# CS575_Week10_IntegerKnapsack

This time, a dynamic programming classic.  Input files will give you the weight of the knapsack, the number of items, and then each item as a weight/value pair.  Find the maximum value of items you can fit in the knapsack, and then print out the items you selected.

For example:

3 6
3 5
2 2
6 3
There are three items to consider, an a maximum capacity of 6 for the knapsack (that's the 3 6 on the first line). After that, each item is given as the weight and value (first item weighs 3, is worth 5). Which items do you put in?

For this example, your best solution is the first and second item, with a total weight of 5, and a value of 7.  Here's a second case, with 10 items, and a maximum capacity of 5.  Most of the items are worth 1, and have a weight of 1, but the fourth and last are different.  The maximum value is 15.

There may be more than one possible answer, but the maximum value should match

10 5
1 1
1 1
1 1
1 2
1 1
1 1
1 1
1 1
1 1
1 10
