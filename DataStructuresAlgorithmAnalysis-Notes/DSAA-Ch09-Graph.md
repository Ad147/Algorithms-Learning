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
    - [9.3.3 Graphs with Negative Edge Costs](#933-graphs-with-negative-edge-costs)
    - [9.3.4 Acyclic Graphs](#934-acyclic-graphs)
    - [9.3.5 All-Pairs Shortest Path](#935-all-pairs-shortest-path)
    - [9.3.6 Shortest Path Example](#936-shortest-path-example)
  - [9.4 Network Flow Problems](#94-network-flow-problems)
    - [9.4.1 A Simple Maximum-Flow Algorithm](#941-a-simple-maximum-flow-algorithm)


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

When it comes to weighted graph, the ideas from the unweighted case can still be used.

We keep all the same information as before:

- Each vertex is marked as either known or unknown.  
- A tentative distance dv is kept for each vertex.  
  This distance turns out to be the shortest path length from s to v using only known vertices as intermediates.  
- We record pv, which is the last vertex to cause a change to dv.

The general method to solve the single-source shortest-path problem is nkonw as **Dijkstra's algorithm**.  
This 30-yr-old solution is a prime example of a **greed algorithm**.  
Greedy algorithms generally solve a problem in stages by doing what appears to be the best thing at each stage.  
Example: making change in U.S. currency.  
The main problem with greedy algorithms is that they do not always work (not the optimal solution).  

Dijkstra's algorithm proceeds in stages, just like the unweighted shortest-path algorithm.  
At each stage, select a vertex which has the smallest dv among all the unknown vertices and declares that the shortest path from s to v is known.  
The remainder of a stage consists of updating the values of dw.

We set $d_w=d_v+c_{v,w}$ if the new value for dw would be an improvement.  
Put simple, the algorithm decides whether or not it is a good idea to use v on the path to w.  
The original cost, dw, is the cost without using v;  
the new cost is the cheapest path using v (and only known vertices).


###### Figure 9.29 Vertex class for Dijkstra's algorithm (pseudocode)

```cs
// PSEUDOCODE sketch of the Vertex structure.
// In real C++, path would be of type Vertex *,
// and many of the code fragments that we describe
// require either a dereferencing * or use the
// -> operator instead of the . operator.
// Needless to say, this obscures the basic algorithmic ideas.
struct Vertex
{
    List adj;       // Adjacency list
    bool known;
    DistType dist;  // DistType is probably int
    Vertex path;    // Probably Vertex *, as mentioned above
    // Other data and member functions as needed
}
```

The path can be printed out using the recursive routine in Figure 9.30.


###### Figure 9.30 Routine to print the actual shortest path

```cs
// Print shortest path to v after dijkstra has run.
// Assume that the path exists.
void Graph::printPath(Vertex v)
{
    if (v.path != NOT_A_VERTEX)
    {
        printPath(v.path);
        cout << "to ";
    }
    cout << v;
}
```


###### Figure 9.31 Pseudocode for Dijkstra's algorithm

```cs
void Graph::dijkstra(Vertex s)
{
    for each Vertex v
    {
        v.dist = INFINITY;
        v.known = false;
    }

    s.dist = 0;

    while (there is an unknown distance vertex)
    {
        Vertex v = smallest unknown distance vertex;

        v.known = true;

        for each Vertex w adjacent to v
            if (!w.known)
            {
                DistType cvw = cost of edge from v to w;

                if (v.dist + cvw < w.dist)
                {
                    // Update w
                    decrease(w.dist to v.dist + cvw);
                    w.path = v;
                }
            }
    }
}
```

A proof by contradiction will show that this algorithm always works as long as no edge has a negative cost.  
If any edge has negative cost, the algorithm could produce the wrong answer.

The running time depends on how the vertices are manipulated.  
If we use the obvious algorithm of sequentially scanning the vertices to find the minimum dv, each phase will take O(|V|) time to find the minimum, and thus O(|V|^2) will be spent finding the minimum over the course of the algorithm.  
The time for updating dw is constant per update, and there is at most one update per edge for a total of O(|E|).  
Thus, the total running time is $O(|E|+|V|^2) = O(|V|^2)$.  
If the graph is dense, with $|E|=Θ(|V|^2)$, this algorithm is not only simple but also essentially optimal, since it runs in time linear in the number of edges.

If the graph is sparse, with $|E| = Θ(|V|)$, this algorithm is too slow.  
In this case, the distance would need to be kept in a priority queue.  
There are actually two ways to do this.

Selection of the vertex v is a `deleteMin` operation.  
The update of w's distance can be implement two ways.

1. Treat the update as a `decreaseKey` operation.  
   The time to find the minimum is then O(log|V|), as is the time to perform updates, which amount to `decreaseKey` operations.  
   This gives a running time of $O(|E|log|V| + |V|log|V|) = O(|E|log|V|)$, an improment over the previous bound for sparse graphs.  
   Since priority queue donot efficiently support the `find` operation, the location in the priority queue of each value of di will need to be maintained and updated whenever di changes in the priority queue.  
   If the priority queue is implemented by a binary heap, this will be messy.  
   If a pairing heap (Chapter 12) is used, the code is not too bad.
2. Insert w and the new value dw into the priority queue every time w's distance changes.  
   Thus, there may be more than one representation for each vertex.  
   When the `deleteMin` removes the smallest vertext from the queue, it must check if the vertext is known or not.  
   If it is, ignore it and another `deleteMin` performed.  
   Although this method is superior from a software point of view (???), and is certainly much easier to code, the size of the priority queue could get to be as large as |E|.  
   This does not affect the asymptotic time bounds, sing |E|<=|V|^2 implies that log|E|<=2log|V|.  
   Thus we still get an O(|E|log|V|) algorithm (???).  
   However, the space requirement does increase, and this could be important in some applications.  
   Morevoer, because this method requires |E| `deleteMin` instead of only |V|, it is likely to be slower in practice.

Notice that for the typical problems, such as computer main and mass transit commutes, the graphs are typically very sparse because most vertices have only a couple of edges, so it is important in many applications to use a priority queue to solve this problem.

If the Fibonacci heap (chapter 11) is used, the running time is O(|E|+|V|log|V|).  
Fibonacci heaps have a good theoritical bounds but a fair amount of overhead, so it is not clear whether using Fibonacci heaps is actually better in practice than Dijkstra's algorithm with binary heaps.  
To date, there are no meaningful average-case results for this algorithm.


#### 9.3.3 Graphs with Negative Edge Costs

If the graph has negative edge costs, then Dijkstra's algorithm does not work.  
The problem is that once a vertex, u, is declared known, it is possible that from some other unkown vertex, v, there is a path back to u that is very negative.  
In such a case, taking a path from s to v back to u is better than going from s to u without using v.

A combination of the weighted and unweighted algorithms will solve the problem, but at the cost of a drastic increase in running time.  
We forget about the concept of known vertices, since our algorithm need to be able to change its mind.  
We begin by placing s on a queue.  
Then, at each stage, we dequeue a vertex v.  
We find all vertices w adjacent to v such that $d_w > d_v + c_{v,w}$.  
We update dw and pw, and place w on a queue if it is not already there.  
A bit can be set for each vertex to indicate presence in the queue.  
We repeat the process until the queue is empty.


###### Figure 9.32 Pseudocode for weighted shortest-path algorithm with negative edge costs

```cs
void Graph::weightedNegative(Vertex s)
{
    Queue<Vertex> q;

    for each Vertex v
        v.dist = INFINITY;
    
    s.dist = 0;
    q.enqueue(s);

    while (!q.isEmpty())
    {
        Vertex v = q.dequeue();

        for each Vertex w adjacent to v
            if (v.dist + cvw < w.dist)
            {
                // Update w
                w.dist = v.dist + cvw;
                w.path = v;
                if (w is not already in q)
                    q.enqueue(w);
            }
    }
}
```

Although the algorithm works if there are no negative-cost cycles, it is no longer true that the code in the inner loop is executed once per edge.  
Each vertex can dequeue at most |V| times, so the running time is $O(|E|·|V|)$ if adjacency lists are used.


#### 9.3.4 Acyclic Graphs

If the graph is known to be acyclic, we can improve Dijkstra's algorithm by changing the order in which vertices are declared known, otherwise known as the vertex selection rule.  
The new rule is to select vertices in topological order.  
The algorithm can be done in one pass, since the selections and updates can take place as the topological sort is being performed.

The running time is $O(|E|+|V|)$, since the selection takes constant time.

An important use of acyclic graphs is **critical path analysis**.  
The nodes represent activities and edges represent precedence relationships.  
The problem can be:  
What is the earliest completion time for the project?

To perform these calculations, we convert the activity-node graph to an **event-node graph**.  
Each event corresponds to the completion of an activity and all its dependent activities.  
Events rachable from a node v in the event-node graph may not commence until after the event v is completed.  
This graph can be constructed automatically or by hand.  
Dummy edges and nodes may need to be inserted in the case where an activity depends on several others.

To find the ealiest completion time of the project, we merely need to find the length of the longest path from the first event to the last event.  
For general graphs, the longest-path problem generally does not make sense, because of the possibility of **positive-cost cycles**.  
Since the event-node graph is acyclic, we need not worry about cycles.  
In this case, it is easy to adapt the shortest-path algorithm to compute the earliest completion time for all nodes in the graph.  
If $EC_i$ is the earliest completion time for node i, then the applicable rules are

$$ EC_1 = 0 $$

$$ EC_w = \underset{(v, w)\in E}{max} (EC_v + c_{v, w}) $$

We can also compute the lastest time, $LC_i$, that each event can finish without affecting the final completion time.  
The formulas to do this are

$$ LC_n = EC_n $$

$$ LC_v = \underset{(v, w)\in E}{max} (LC_w - c_{v, w}) $$

These values can be computed in linear time by maintaining, for each vertex, a list of all adjacent and preceding vertices.  

The **slack time** for each edge in the event-node graph represents the amount of time that the completion of the corresponding activity can be delayed without delaying the overall completion.  
It is easy to see that

$$ Slack_{v, w} = LC_w - EC_v - c_{v, w} $$

Some activities have zero slack.  
These are critical activities, which must finish on schedule.  
There is at least one path consisting entirely of zero-slack edeges;  
such a path is a **critical path**.


#### 9.3.5 All-Pairs Shortest Path

To find the shortest paths between all pairs of vertices in the graph, we can run the single-source algorithm |V| times.

In Chapter 10, there is an $O(|V|^3)$ algorithm to solve the problem for weighted graphs.  
Although, for dense graphs, this is the same bound as running a simple (nonpriority queue) Dijkstra's algorithm |V| times, the loops are so tight that the specialized all-pairs algorithm is likely to be faster in practice.  
On sparse graphs, it is faster to run |V| Dijkstra's algorithms coded with priority queue.


#### 9.3.6 Shortest Path Example

Here are some C++ routines to compute word ladders.  
In a word ladder each word is formed by changing one character in the ladder's previous word.

This is an unweighted shortest problem in which each word is a vertex, and two vertices have edges (in both directions)  between them if they can be converted to each other with a one-character substitution.

In Section 4.8, a map in which the keys are words, and the values are vectors containing the words that can result from a one-character transfromation is created.  
It represents the graph, in adjacency list format.  
We now need to write one routine to run the single-source unweighted shortest-path algorithm and a second routine to output the sequence of words.


###### Figure 9.38 C++ code to find word ladders

```cs
// Runs the shortest path calculation from the adjacency map, returning a vector
// that contains the sequence of word changes to get from first to second.
unordered_map<string, string>
findChain(const unordered_map<string, vector<string>> &adjacentWords,
          const string &first, const string &second)
{
    unordered_map<string, string> previousWord;
    queue<string> q;

    q.push(first);

    while(!q.empty())
    {
        string current = q.front(); q.pop();
        auto itr = adjacentWords.find(current);

        const vector<stirng> &adj = itr->second;
        for (string &str : adj)
            if (previousWord[str] == "")
            {
                previousWord[str] = current;
                q.push(str);
            }
    }
    previousWord[first] = "";

    return previousWord;
}

// After the shortest path calculation has run, computes the vector that
// contains the sequence of words changes to get from first to second.
vector<string> getChainFromPreviousMap(
    const unordered_map<string, string> &previous, const string &second)
{
    vector<string> result;
    auto &prev = const_cast<unordered_map<string, string> &>(previous);

    for (string current = second; current != ""; current = prev[current])
        result.push_back(current);
    
    reverse(begin(result), end(result));
    return result;
}
```

The `const_cast` is needed because `operator[]` cannot be applied on an immutable map.


--------------------------------------------------------------------------------


### 9.4 Network Flow Problems

Suppose a directed graph G=(V, E) with edge capacities c_{v, w} is given.  
The capacities could represent the amount of water that could flow through a pipe or the amount of traffic that could flow on a street between two intersections.  
There are 2 vertices:

- `s`: **source**
- `t`: **sink**

Through any edge, (v, w), at most c_{v, w} units of "flow" may pass.  
At any vertex, v, that is not s or t, the total flow conming in must equal the total flow going out.  
The maximum-flow problem is to determine the maximum amount of flow that can pass from s to t.  
The eventual algorithm will work even if the graph has a cycle.

For the problem, we can cut the graph into two parts:

- One part contains `s` and some other vertices.
- The other contains `t` and some other.

Since flow must cross through the cut, the total capacity of all edges (u, v) where u is in s's partion and v is in t's partion is a bound on the maximum flow.  
Any graph has a large number of cuts;  
the cut with minimum total capacity provides a bound on the maximum flow.  
And the minimum cut capacity is exactly equal to the maximum flow.


#### 9.4.1 A Simple Maximum-Flow Algorithm

