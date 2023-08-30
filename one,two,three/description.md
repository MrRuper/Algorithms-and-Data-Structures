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
Each of the following m lines contains two integers, $i$ and $x$ ($1 \leq i \leq n, x \in \{1, 2, 3\}$), representing an assignment $"a_i := x"$. 
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

Here I am using the full binary tree to solve that problem. You might see that the brutal solution (it is inserting new value and linearly walking through the 
the array to find $\{1,2,3\}$ subsequence) works in $O(n)$ time complexity in the sense that every insert will take $O(n)$ time to decide whether there is $\{1,2,3\}$
or not. It turns out that if there will be for example $n$ insert commands then our brutal solution will take $O(n^2)$ time and as a consequence will be to slow to 
pass all tests.

# "Counter tree"

This data structure appears in various algorithmic problems and allows us to reduce the time comlexity of insert to $O(log(n))$. To do that we initiate a full binary
tree with at least n leaves (so for example in the the example from the problem description our $n = 5$ and thus the full binary must have $2^{3} = 8$ leaves). 
Our leaves will represent the input vector. So in our case our tree will look like that:

```           
		      x(?)                 <-   not leaf leavel
                /            \
	      y(?)            z(?)         <-   not leaf level
            /   \           /    \
           /	 \         /      \
         d(?)	 h(?)	  l(?)	  f(?)     <-   not leaf level := "NLL"
         / \     / \     / \     / \
        2   1   2   3   2   ?   ?   ?      <-   leaf level := "LL"
        
```

the $?$ means that in that moment we don't know what to put there (. 

Note: every ? begining from "NLL" corresponds to some interval: y vertex corresponds to sequence {2,1,2,3}, l vertex corresponds to {2, ?}, f to {?, ?}, h to {2,3}
and finally the root it is x corresponds to whole {2,1,2,3,2,?,?,?}.

We would like to fastly work with insertions of new values to the leaves so the main idea is to send the information from leaf up to the root that new value was inserted and that takes only the height of our tree (so $O(log(n))$). Lets now assume that we insert for example "2" on some index and we send this information up 
to the root. When we are somewhere in the middle of the tree then we would like to know whether on the left there is 1 and on the right there is 3 and if it is true 
then indeed we have 1, 2, 3 in tree. If we insert "1" we would like to know whether on right we have {2,3} and so on. It turns out now that our node has to keep this informations:
- existence of "1" in subtree,
- existence of "2" in subtree,
- existence of "3" in subtree,
- existence of sequence 1,2 in subtree,
- existence of sequence 2,3 in subtree,
- existence of sequence 1, 2, 3 in subtree.

and now after each insert command program has to update these informaion which cost only $log(n)$. 

# Few words about implementation

Whole binary tree could be implemented in array: firstly for a given $n$ we find the size of that tree (find number of leaves and then the size of tree is 2 * (number of leaves) - 1). To find a "father" of some child node you simply divide index of child node by 2. In the same way for a given "father" node you find left and right child by myltiplying by 2 for left child and multiplying by 2 and adding 1 for right child.
