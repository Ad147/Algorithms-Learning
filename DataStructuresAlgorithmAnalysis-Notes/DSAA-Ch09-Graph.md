DSAA-Ch09-Graph.md


Notes of Data Structures and Algorithm Analysis in C++
================================================================================

Ad  
<ar><r>

Init: 19Mar27


Chapter 9 Graph Algorithms
--------------------------------------------------------------------------------

In this chapter, we will...

- Show several real-life problems, which can be converted to problems on graphs.
- Give algorithms to solve several common graph problems.
- Show how the proper choice of data structures can drastically reduce the running time of these algorithms.
- See an important technique, known as depth-first search, and show how it can be used to solve several seemingly nontrivial problems in linear time.


--------------------------------------------------------------------------------


- [Chapter 9 Graph Algorithms](#chapter-9-graph-algorithms)
  - [9.1 Definitions](#91-definitions)
    - [9.1.1 Representation of Graphs](#911-representation-of-graphs)
  - [9.2 Topological Sort](#92-topological-sort)
  - [9.3 Shortest-Path Algorithms](#93-shortest-path-algorithms)
    - [9.3.1 Unweighted Shortest Paths](#931-unweighted-shortest-paths)
    - [9.3.2 Dijkstra's Algorithm](#932-dijkstras-algorithm)


--------------------------------------------------------------------------------


### 9.1 Definitions

A **graph** $G=(V, E)$ consists of a set of **vertices**, V, and a set of **edges**, E.  
Each edge is a pair (v, w), where v, w ∈ V.  
Edges are somtimes referred to as **arcs**.  
If the pair is ordered, then the graph is **directed**.  
Directed graphs are somtimes referred to as **digraphs**.  
Vertex w is **adjacent** to v if and only if (v, w) ∈ E.  
In an undirected graph with edge (v, w), and hence (w, v), w is adjacent to v and v is adjavent to w.  
Sometimes an  edge has a third component, known as either a **weight** or a **cost**.

A **path** in a graph is a sequence of vertices w1, w2, w3, ..., wN such that (wi, wi+1) ∈ E for 1<=i<N.  
The **length** of such a path is the number of edges on the path, which is equal to N-1.  
We allow a path from a vertext to itself;  
if this path contains no edges, then the path length is 0.  
If the graph contains an edge (v, v) from a vertext to itself, then the path v, v is sometimes referred to as a **loop**.  
A **simple path** is a path such that all vertices are distinct, except that the first and last could be the same.

A **cycle** in a directed graph is a path of length at least 1 such that w1 = wN;  
this cycle is simple if the path is simple.  
For undirected graphs, we require that the edges be distinct.  
A directed graph is **acyclic** if it has no cycles.  
A directed acyclic graph is sometimes referred to by its abbreviation, **DAG**.

An undirected graph is **connected** if there is a path from every vertex to every other vertext.  
A directed graph with this property is called **strongly connected**.  
If a directed graph is not strongly connected, but the underlying graph (without direction to the arcs) is connected, then the graph is said to be **weakly connected**.  
A **complete graph** is a graph in which there is an edge between every pair of vertices.

Real-life models: airport system, traffic flow.


#### 9.1.1 Representation of Graphs

**Adjacency matrix**: use a two-dimentional array to represent a graph.  
For each edge (u, v), set A[u][v] to true; or set the value equal to the weight, and use either a very large or a very small weight as a sentinel to indicate noexistent edges.

The space requirement of adjacency matrix is $Θ(|V|^2)$, and it is appropriate for **dense** graph: $|E|=Θ(|V|^2)$.

For a **sparse** graph, an **adjacency list** is better.  
For each vertex, we keep a list of all adjacent vertices.  
The space requirement is then $O(|E|+|V|)$,  which is linear in the size of the graph.

Adjacency lists are the standard way to represent graphs.  
Each edge (u, v) appears in two lists, so the space usage essentially doubles.

Because it is important to be able to quickly obtain the list of adjacent vertices for any vertex, the two basicv options are to use a map in which the keys are vertices and the values are adjacency lists, or to maintain each adjacency list as a data member of a Vertex class.


--------------------------------------------------------------------------------


### 9.2 Topological Sort

A **topological sort** is an ordering of vertices ina directed acyclic graph, such that if there is a path from vi to vj, then vj appears after vi in the ordering.  
The ordering is not neccessarily unique.

A simple algorithm to find a topological ordering is first to find any vertex with 0 indegree (**indegree** of v is the number of edges (u, v)).  
Then print this vertex and remove it, along with its edges, from the graph.  
Then we apply this same strategy to the rest of the graph.


###### Figure 9.5 Simple topological sort pseudocode

```cs
void Graph::topsort()
{
    for (int counter = 0; counter < NUM_VERTICES; counter++)
    {
        Vertex v = findNewVertexOfIndegreeZero();
        if (v == NOT_A_VERTEX)
            throw CycleFoundException{};
        v.topNum = counter;
        for each Vertex w adjacent to v
            w.indegree--;
    }
}
```

The function `findNewVertexOfIndegreeZero` scans the array of vertices and find a vertex of indegree 0.  
Each call to it takes O(|V|) time.  
Since there are |V| such calls, the running time of the algorithm is O(|V|^2).

If the graph is saparse, only a few vertices are updated during each iteration.  
we can keep all the (unassigned) vertices of indegree 0 in a *box*.  
The `findNewVertexOfIndegreeZero` returns (and removes) any vertext in the box.  
When we decrement the indegrees of the adjacent vertices, we check each vertex and place it in the box if its indegree is 0.


###### Figure 9.7 Pseudocode to perform topological sort

```cs
void Graph::toposort()
{
    Queue<Vertex> q;
    int counter = 0;

    q.makeEmpty();
    for each Vertex v
        if (v.indegree == 0)
            q.enqueue(v);

    while (!q.isEmty())
    {
        Vertex v = q.dequeue();
        v.topNum = ++counter; // Assign next number

        for each Vertex w adjacent to v
            if (--w.indegree == 0)
                q.enqueue(w);
    }

    if (counter != NUM_VERTICES)
        throw CycleFoundException{};
}
```

The time to perform this algorithm is $O(|E|+|V|)$ if adjacency lists are used.  
Computing the indegrees can be done with the following code;  
the cost of this computaion is $O(|E|+|V|)$, even though there are nested loops.

```c
for each Vertex v
    v.indegree = 0;

for each Vertex v
    for each Vertex w adjacent to v
        w.indegree++;
```


--------------------------------------------------------------------------------


### 9.3 Shortest-Path Algorithms

For the problems in this section, the input is a weighted graph:  
Associated with each edge $(v_i, v_j)$ is a cost $c_{i,j}$ to traverse the edge.  
The cost of a path v1 v2 ... vN is $\sum^{N-1}_{i=1} c_{i, i+1}$.  
This is referred to as the **weighted path length**.  
The **unweighted path length** is merely the number of edges on the path N-1.


> ##### Single-Source Shortest-Path Problem
>
> Given as input a weighted graph, G=(V, E), and a distinguished vertex, s, find the shortest weighted path from s to every other vertex in G.

If a graph has negative cost edge, there may be a loop to cause the path cost be less and less, the loop is known as a **negative-cost cycle**;  
when one is present in the graph, the shortest paths are not defined.  
Negative-cost edges are not necessarily bad, as the cycles are, but their presence seems to make the problem harder.  
For convenience, in the absence of a negative-cost cycle, the shortest path from s to s is zero.

The following sections are algorithms to solve 4 versions of the problem:

1. Unweighted shortest-path problem, solve it in $O(|E|+|V|)$.
2. Weighted shortest-path problem assuming no negative edeges, in $O(|E| log|V|)$.
3. Weighted problem with negative edges, in $O(|E|·|V|)$.
4. Weighted problem for the special case of acyclic graphs in linear time.


#### 9.3.1 Unweighted Shortest Paths

Unweighted can be considered as a special case of weighted problem in which all the edges are weight 1.

For now, suppose we are interested only in the length of the shortest paths, not in the actual paths themselves.  
Keeping track of the actual paths will turn out to be a matter of simple bookkeeping.

We can find the vertices adjacent to s, which have a distance 1 from s.  
Then the vertices adjacent to the last found vertices, which have distance 2 from s.  
...

This strategy is **breadth-first search**.  
It operates by processing vertices in layer:  
Ther vertices closest to the start are evaluated first, and the most distant vertices are evaluated last.  
This is much the same as a level-order traversal for trees.

Figure 9.15 shows the initial configuration of the table that our algorithm will use to keep track of its process.  
v3 is the start vertex.


###### Figure 9.15 Initial configuration of table used in unweighted shortest-path computation

| v   | known | dv  | pv  |
| --- | ----- | --- | --- |
| v1  | F     | ∞   | 0   |
| v2  | F     | ∞   | 0   |
| v3  | F     | 0   | 0   |
| v4  | F     | ∞   | 0   |
| v5  | F     | ∞   | 0   |
| v6  | F     | ∞   | 0   |
| v7  | F     | ∞   | 0   |
| v8  | F     | ∞   | 0   |

For each vertex, we will keep track of three pieces of information:

1. Its distance from s to in the entry dv.
2. Bookkeeping variable in the entry pv which allow us to print the actual paths.
3. The entry known is set to true after a vertex is processed.  
   Initially all are not known, including the start vertex.  
   When a vertex is marked known, we have a guarantee that no cheaper path will ever be found, and so processing for that vertex is essentially complete.

The algorithm in Figure 9.16 mimics the diagrams by declaring as known the vertices at distance d=0, then d=1, then d=2, and so on, and setting all the adjacent vertices w that still have dw=∞ to a distance dw=d+1.


###### Figure 9.16 Pseudocode for unweighted shortest-path algorithm

```cs
void Graph::unweighted(Vertex s)
{
    for each Vertex v
    {
        v.dist = INFINITY;
        v.known = false;
    }

    s.dist = 0;

    for (int currDist = 0; currDist < NUM_VERTICES; currDist++)
        for each Vertex v
            if (!v.known && v.dist == currDist)
            {
                v.known = true;
                for each Vertex w adjacent to v
                    if (w.dist == INFINITY)
                    {
                        w.dist = currDist + 1;
                        w.path = v;
                    }
            }
}
```

By tracking back through the pv variable, the actual path can be printed.

The running time of the algorithm is $O(|V|^2)$, because of the doubly nested for loops.  
An obvious inefficiency is that the outside loop continues until NUM_VERTICE-1, even if all the vertices become known.  
Although an extra test could be made to avoid this, it does not affect the worst-case running time, as the input is a linked list.

We can remove the inefficiency in much the same way as was done for topological sort.  
At any point in time, there are only two types of unknown vertices that have dv != ∞.  
Some have dv=currDist, and the rest have dv=currDist+1.  
Because of this extra structure, it is very wasteful to search through the entire table to find a proper vertex.

A very simple way is to keep two boxes.  

- Box #1 has unknown vertices with dw=currDist.
- Box #2 has unknown vertices with dw=currDist+1.

We first find vertices in box #1.  
After updating w (inside the innermost `if`), we can add w to box #2.  
After the outermost for loop terminates, box #1 is empty, and box #2 can be transeferred to box #1 for the next pass of the for loop.

We can refine this idea even further by using just one queue.  
At the start of the pass, the queue contains only vertices of distance currDist.  
Then we add adjacent vertices of distance currDist+1.  
After the last vertex at distance currDist dequeues and is processed, the queue only contains vertices of distance currDist+1.  
We merely need to begin the process by placing the start node on the queue by itself.

The refined algorithm is shown in Figure 9.18.  
It is possible that the queue might empty prematurely, if some vertices are unreachable from the start node.  
In this case, a distance of INFINITY will be reported for these nodes, which is perfectly reasonable.  
Finally, the known data member can be discarded.

Using the same analysis as was performed for topological sort, the running time is $O(|E|+|V|)$, as long as adjaceny lists are used.


###### Figure 9.18 Pseudocode for unweighted shortest-path algorithm

```cs
void Graph::unweighted(Vertex s)
{
    Queue<Vertex> q;

    for each Vertex v
        v.dist = INFINITY;

    s.dist = 0;
    q.enqueue(s);

    while (!q.isEmpth())
    {
        Vertex v = q.dequeue();

        for each Vertex w adjacent to v
            if (w.dist == INFINITY)
            {
                w.dist = v.dist + 1;
                w.path = v;
                q.euqueue(w);
            }
    }
}
```


#### 9.3.2 Dijkstra's Algorithm

