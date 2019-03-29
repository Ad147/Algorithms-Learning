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

