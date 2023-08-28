# Drainage - advanced problem.

ASD, lab exam. Available memory: 256 MB.

# Problem description

Bajtocja is situated in a relatively marshy area. This region can be represented as a rectangle consisting of $n \cdot m$ fields,
some of which are passable, while others are occupied by swamps. Lately, merchants residing in cities A and B
decided to establish a trade route connecting these cities, which is a sequence of unit fields leading from city A to city B,
where any two consecutive fields should share a common side. It's not clear whether it's possible to mark out such a route
without draining the swamps. Your task is to determine the minimum number of swampy fields that need to be drained
in order to create at least one trade route connecting cities A and B.

# Input

The first line of the standard input contains two integers, $n$ and $m$ ($2 \leq n,m \leq 1000$), separated by a single space. Each of the 
following $n$ lines contains $m$ characters, where 

- The caracter '.' represents an empty field (passable)
- The character '#' represents a swamp.
- The character 'A' represents the location of city A.
- The character 'B' represents the location of city B.

You can assume that the input contains exactly one 'A' letter and exactly one 'B' letter.

# Output

The first and only line of the standard output should contain a non-negative integer, indicating the number of fields that need to be drained 
in order to have a path connecting cities A and B.

# Example

For an input

```
5 6
..#.A.
#####.
.#.#.#
.#.B#.
.#.#..
```

the correct answer is: $2$.

# Understanding the algorithm before reading implementation

This is just Dijkstra approach to the graph representing Bajtocja country.
