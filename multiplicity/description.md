# Multiplicity - advanced problem.

ASD, correctional exam. Available memory: 256 MB.

# Problem description:

There are n intervals [a_i, b_i] with multiplicities. The multiplicity of i-th interval is k_i. For any integer x we define kro(x) as the sum of multiplicities of 
such intervals [a_i,b_i] which contain x. Your question is to find out the number of unordered pairs {x,y}, such that kro(x) > 0, kro(y) > 0 and kro(x) != kro(y).

# Input:

In the first line of standard input there is one integer n (1 <= n <= 500 000) - the number of intervals. The next n rows contains the description of intervals, it is
every row has 3 integer numbers a_i, b_i, k_i (1<= a_i <= b_i <= 10^9, 1 <= k_i <= 1000), separated by space charakter, describing respectively the interval [a_i,b_i]
and his multiplicity k_i.

# Output:

Your program has to print on standard output flow one integer number - the number of unordered pairs satisfying the condition described in problem description.

# Example:

For an input:         
```
3		
1 3 2
3 4 3
3 5 1
```
the correct answer is: 9.

Explanation: All interested pairs are: ```{1,3}, {1,4}, {1,5}, {2,3}, {2,4}, {2,5}, {3,4}, {3,5}, {4,5}```.

# UNDERSTANDING THE ALGORITHM BEFORE READING IMPLEMENTATION.

**Main goal**

The main goal is to find the number of unordered pairs which have different (nonzero) multiplicities. 
Assume we are able to get from input the next information: (multiplicity, number of elements that have exactly this multiplicity) - then we are done. Indeed if we 
know the exact distribution of multiplicities the we linearly find the number of all unordered pairs (how?). 

** Main difficulties **:

The main difficulty is to find the way to get that inforamtion. As we see from the problem description there could be potentially quite large number n (and thus there 
could be a large number of intervals) so a "bad" solution will not pass tests. 

# Correct but slow solutions:

The reader can try to think about the O(n^2) solution. In my opinion one of the standard approach is to use the AVL (balanced BST) trees which will hold a disjoint
intervals and left subtree contains intervals with less first coordinate and right subtree contains intervals with grater first coordinate.
The insertion of some interval [a,b] with multiplicity y to the root could look like this: 

** Step 1 **: Let root contains [c,d] as interval and k as his multiplicity.
** Step 2 **: Check the way [a,b] intersects [c,d]:
```
		If ([a,b] and [c,d] are disjoint) do:
			 compare a and c

			 if a <= c do:
				 insert [a,b] to the left subtree of the root
			 else
				 insert [a,b] to the right subtree of the root.

		Else if ([a,b] is contained in [c,d], it is {c, [a,b], d}) do:
			create three intervals: [c, a - 1], [a, b], [b + 1, d]
			update root interval: set root interval to [a,b] and root multiplicity as k + y
			set [c, a - 1] and [b + 1, d] as new left and right childs.

		Else if ([a,b] intersects with [c,d] in the next way: [a {c  b]  d}) do:
			similar code here...
```


The problem of that approach is that there is a high cost of keeping the presented structure to be balanced (it is AVL) because one interval can be splited on to 
many disjoint pieces and thus to insert them one need to do a lot of single AVL insertions. This approach could potentialy have O(n^2) time complexity. An interested
reader could look at the implementation of AVL approach in [AVL_slow_approach.cpp file.](https://github.com/MrRuper/Algorithms-and-Data-Structures/blob/main/multiplicity/AVL_slow_approach.cpp)



# Correct and fast solution O( n * log(n) ):

Let us think for a moment about faster solutions. Lets take the example showed in description.txt file. 

3
1 3 2
3 4 3
3 5 1

Lets create the vector of size 2 * n which will hold all endpoints and their multiplicities given in the input and let us moreover remember the "type" of the endpoint, i.e. the 
start point will be marked as "+" and end point as "-". Finally lets sort that vector getting:

all_endpoints = [{1, "+", 2}, {3, "+", 3}, {3, "+", 1}, {3, "-", 2}, {4, "-", 3}, {5, "-", 1}].

You can also remove copies of the same endpoints getting:

without_copies = [{1, "+", 2}, {3, "+", 4}, {3, "-", 2}, {4, "-", 3}, {5, "-", 1}].

To end this we can note that without_copies vector describes the whole structure of the input intervals, i.e. we can generate all intervals with different 
degrees just linearly walking through this vector. To make it clear we generate:

[1, 2], 2 
[3, 3], 6
[4, 4], 4
[5, 5], 1 

