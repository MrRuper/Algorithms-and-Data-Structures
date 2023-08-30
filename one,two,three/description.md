# One,two,three - advanced problem

ASD, lab exam. Available memory: 128 MB.

# Problem description

In this task, you are given a sequence of numbers $a_1, ..., a_n$, where each $a_i$ belongs to $\{1, 2, 3\}$, and the elements of the sequence
change due to a series of assignments. More precisely, each operation consists of assigning a new value (from the set $\{1, 2, 3\}$)
to one of the elements in the sequence. Your task is to determine at which moments the sequence contains the subsequence $1, 2, 3$.

# Input

The first line of the input contains a single integer, $n$ ($1 \leq n \leq 500,000$), which denotes the length of the input sequence.
The second line contains a description of the sequence: the i-th number in the line represents the element $a_i$ ($a_i \in \{1, 2, 3\}$).
The third line contains a single integer, $m$ ($1 \leq m \leq 500,000$), indicating the number of assignments.
Each of the following m lines contains two integers, $i$ and $x$ ($1 \leq i \leq n, x \in \{1, 2, 3\}$), representing an assignment "$a_i := x$". 
In an assignment, it might occur that $x$ is equal to the current value of the element $a_i$ (see example).

# Output

Your program should output $m + 1$ lines. Each line should contain a single word: TAK (YES) or NIE (NO), indicating whether the sequence at that particular
moment contains the subsequence $1, 2, 3$ or not. The first word corresponds to the initial sequence, while the subsequent $m$ words correspond 
to whether the subsequence is present after each assignment.

# Example

```For the input:              correct answer is: 

5				TAK
2 1 2 3 2			TAK
4				NIE
1 3				TAK
2 2				TAK
1 1
1 1
```

# Understanding the algorithm before reading implementation


