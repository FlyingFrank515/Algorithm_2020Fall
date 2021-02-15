# Algorithm_2020Fall #
Programming assignment of Algorithm, 2020fall, NTUEE

## PA1 Sorting ## 
Implement Sorting algorithms below and compare the advantages/disadvantages of them.
* Insertion sort
* Merge sort
* Quick sort
* Heap sort

## PA2 Maximum Planar Subset ## 
Given is a set C of n chords of a circle. We assume that no two chords of C share an endpoint.
Number the endpoints of these chords from 0 to 2n - 1, clockwise around the circle. Let
M(i; j); i <= j, denote the number of chords in the maximum planar subset (i.e., no two chords overlap each other
in the subset) in the region formed by the chord ij and the arc between the endpoints i and j.
You are asked to write a program that computes the number of chords in the maximum planar subset in a circle of n chords, i.e., compute
M(0; 2n - 1), and reports the details of each chords.

SOL: **Dynamic programming(Top Down)**

WARNING: Control your memory usage well!!

## PA3 Cycle Breaking ##
Given a simple graph G = (V;E) which may contain cycles, we want to remove some edges to make the graph acyclic with minimum total cost (weight).

### For undirected graph: ###
Try modifing Kruskal's algorithm for minimum spanning tree.

### For directed graph: ### 
This is a NP-hard Problem. But we still can design algorithm to find reasonable answers (maybe not the most optimal).
1. Treat all directed edges as undirected, and run Cycle Breaking for undirected graph.
2. trying to add back those edges that has been deleted.(in the decreasing order, and only add back edges with weight > 0).

For this problem, we must ensure that all vertices are weakly connected in the end.

In **PA3/b07901021_pa3/**, there's a file named **correct.cpp**. This program can check the validity of your output answer, more details can be found in the comment of **correct.cpp**.  
