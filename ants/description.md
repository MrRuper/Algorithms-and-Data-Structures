# Ants - advanced problem.

ASD laboratory exam. Available memory: 256 MB.

# Problem description
There is n ants standing on the one line. Each ant has its own position on that line it is are indexed by some number from the interval $[1,n]$.
Treser gives commands to the ants. He commands to all ants which are standing on $[l,r]$ to move to the new index $d$ ($d \in [l,r]$). Treser would like to know
how much ants have to change their position and move to another location on the line.

# Input 
The first row of the standard input has two integer numbers n and q ($1 \leq n, q \leq 500 000$), where n is the number of ants and q is the number of Treser's 
commands. The second row has non decresed sequence of integers where each element is from $[1,n]$ and it describes the initial positions of ants. After that there 
is q lines describing commands. Each of that rows has 3 integer numbers l,r,d ($1 \leq l \leq d \leq r \leq n$).

# Output 
Your program has to print q lines where each line is the answer on Treser's command.

# Example
For an input:
```
5 3
1 2 2 4 5
3 5 3
1 1 1
1 2 2
```

the correct answer is 
```
2
0
1
```

and for the input 
```
6 2
1 2 3 4 5 6
1 4 2
3 6 5
```

the correct answer is 
```
3
1
```


# Solution

Let us note that when Treser gives command l r d it means that all ants from $[l,r]$ move to $d$, so the whole $[l,r]$ except of one index $d$ is now empty. 
We can use this fact by keepig positions of ants in some map (map could hold (index on the line)->(how much ants are standing there)) and we can update it by
searching the first index which is $\geq l$ and second index which is $\leq r$ in that map. Once we have it we linearly walk in that fragment counting how much ants are there 
and simply removes all that block from map inserting to map new pair (d, sum of ants). 
Let us look at the second example (it is just shorter :shipit:):

Denote that map by m so at the begining our m is [{1,1}, {2,1}, {3,1}, {4,1}, {5,1}, {6,1}]. 
Now we get the command 
```
 1 4 2
 ```

 and that means all ants from $[1,4]$ now move to $2$ thus we find $1$ and $4$ in our map and remember there positions in it1,it2:

```
[{1,1}, {2,1}, {3,1}, {4,1}, {5,1}, {6,1}]
     / \                  / \ 	
      |                    |
	it1                 it2
```

so we go from it1 to it2 and count how much elements are between them: 1 + 1 + 1 + 1 = 4 but remember that element d does not change it's position
thus you have to take a difference 4 - 1 = 3. After that we delete all block between it1 and it2 and insert new pair {2,4} to m:

``` 
aftert delete: m = [{5,1}, {6,1}]
after insert: m = [{2,3}, {5,1},{6,1}]
```

The second command is:
```
3, 6, 2
```

so we would like to find 3 and 6 as we did before but note that there is no 3 in map! That means that we need to find index which is grater or equal 3 and still less
than 6. In our case it is index 5, so it1 will point to 5 and it2 will point to 6. The next part is the same as before.

# What is the time complexity of such algorithm?
That is not an easy question because each command will make our map shorter. We can for sure say that: creating map is O(n * log(n)) and if the map  has m-elements 
then to find it1 and it2 we will wait for O(log(m)) time. After that we need to walk through that fragment (the worse scenario is whole map lenght, it is m) in O(m)
and delete fragment in amortized O(1). At the end we insert new element in O(log(m)). Finally each command takes us O(m + log(m)). 
