# Subsequences - advanced problem.

ASD laboratory exam. Available memory: 64 MB.

# Problem description.

We get a sequence of numbers $a = a_1,a_2,a_3,...,a_n$ and natural number k. How much different connected subsequences of a sequence a which has at most k different 
elements?
Subsequences are different if and only if they are placed in different positions. Additionally we assume only non degenerate susequences.

# Input
In the first row of standard input You get two numbers n and k ($1 \leq n, k \leq  500 000), separated by one Space char. The second row has n-integers $a_i$ 
separated by Space char ($0 \leq a_i \leq 1 000 000 000$).

# Output
You program has to print only one number - the number of different connected subsequences of a with at most k different elements.

# Example 
For an input:
```
5 2 
4 2 3 2 3
```

The correct answer is 12.

# Explanation of the Example
```
There are 12 searched subsequences:
- 5 one elemented subsequences (2) and (5);
- 4 two elemented subsequences (4,2), (2,3), (3,2), (2,3);
- 2 three elemented subsequences (2,3,2), (3,2,3);
- 1 four elemented subsequence (2,3,2,3).

Note that (2,2,3) is a subsequence of a with 2 different elements but it is not connected, thus we don't count it.
```

