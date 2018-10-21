Algorithms-3.md

Notes of Algorithms 4th edition
================================================================================

Ad  
Init: 18Oct15

3 Searching
--------------------------------------------------------------------------------

We use the term *symbol table* to describe an abstract mechanism where we save information (a value) that we can later search for and retrieve by specifying a key.

Symbol tables are sometimes called *dictionaries* or *indices*.

### 3.1 Symbol Tables

> **Definition.**  
> A symbol table is a data structure for key-value pairs that supports two operations: insert (put) a new pair into the table and search for (get) the value associated with a given key.

#### API of symbol tables

###### API for a generic basic symbol table

| `public class ST<Key, Value>`  |                                                |
| ------------------------------ | ---------------------------------------------- |
| `ST()`                         | create a symbol table                          |
| `void put(Key key, Value val)` | put key-value pair into the table              |
|                                | (remove key from table if value is null)       |
| `Value get(Key key)`           | value paired with key (null if  key is absent) |
| `void delete(Key key)`         | remove key (and its value) from table          |
| `boolean contains(Key key)`    | is there a value paired with key?              |
| `boolean isEmpty()`            | is the table empty?                            |
| `int size()`                   | number of key-value pairs in the table         |
| `Iterable<Key> keys()`         | all the keys in the table                      |

##### Generics

##### Duplicate keys

We adopt the following conventions in all of our implementations:
 - Only one value is associated with each key (no duplicate keys in a table)
 - When a client puts a key-value pair into a table already containing that key (and an associated value), the new value replaces the old one.

##### Null keys

Keys must not be null.

##### Null values

We also adopt the convention that no key can be associated with the value null.

##### Deletion

Deletion in symbol tables generally involves one of two strategies:
lazy deletion, where we associate keys in the table with null, then perhaps remove all such keys at some later time;
and eager deletion, where we remove the key from the table immediately.

##### Shorthand method

###### Default implementations

| method                  | default implementation     |
| ----------------------- | -------------------------- |
| `void delete(Key key)`  | `put(key, null);`          |
| `boolean contains(key)` | `return get(key) != null;` |
| `boolean isEmpty()`     | `return size() == 0;`      |

##### Iteration

##### Key equality

#### Ordered symbol tables

Several symbol-table implementations take advantage of order among the keys that is implied by Comparable to provide efﬁcient implementations of the put() and get() operations.
More important, in such implementations, we can think of the symbol table as *keeping the keys in order* and consider a signiﬁcantly expanded API that deﬁnes numerous natural and useful operations involving relative key order

###### API for a generic ordered symbol table

| `public class ST<Key extends`        | `Comparable<Key>, Value>`                     |
| ------------------------------------ | --------------------------------------------- |
| `ST()`                               | create a symbol table                         |
| `void put(Key key, Value val)`       | put key-value pair into the table             |
|                                      | (remove key from table if value is null)      |
| `Value get(Key key)`                 | value paired with key (null if key is absent) |
| `void delete(Key key)`               | remove key (and its value) from table         |
| `boolean contains(Key key)`          | is there a value paired with key?             |
| `boolean isEmpty()`                  | is the table empty?                           |
| `int size()`                         | number of key-value pairs in the table        |
| `Key min()`                          | smallest key                                  |
| `Key max()`                          | largest key                                   |
| `Key floor(Key key)`                 | largest key less than or equal to key         |
| `Key ceiling(Key key)`               | smallest key greater than or equal to key     |
| `int rank(Key key)`                  | number of keys less than key                  |
| `Key select(int k)`                  | key of rank k                                 |
| `void deleteMin()`                   | delete smallest key                           |
| `void deleteMax()`                   | delete largest key                            |
| `int size(Key lo, Key hi)`           | number of keys in [lo..hi]                    |
| `Iterable<Key> keys(Key lo, Key hi)` | keys in [lo..hi], in sorted order             |
| `Iterable<Key> keys()`               | all keys in the table, in sorted order        |

##### Minimum and maximum

##### Floor and ceiling

##### Rank and selection

##### Range queries

##### Exceptional cases

##### Shorthand methods

For economy in the text, we assume that the following default implementations are included in any implementation of the ordered symbol-table API unless otherwise speciﬁed:

###### Default implementations of redundant order-based symbol-table methods

| method                     | default implementation                |
| -------------------------- | ------------------------------------- |
| `void deleteMin()`         | `delete(min());`                      |
| `void deleteMax()`         | `delete(max());`                      |
| `int size(Key lo, Key hi)` | `if (hi.compareTo(lo) < 0) return 0;` |
|                            | `else if (contains(hi))`              |
|                            | `return rank(hi) - rank(lo) + 1;`     |
|                            | `else return rank(hi) - rank(lo);`    |
| `Iterable<Key> keys()`     | `return keys(min(), max());`          |

##### Key equality (revisited)

##### Cost model

> **Searching cost model.**  
> When studying symbol-table implementations, we count compares (equality tests or key comparisons).
> In (rare) cases where compares are not in the inner loop, we count array accesses.

#### Sample clients

We now consider two clients:
 - a test client that we use to trace algorithm behavior on small inputs
 - a performance client that we use to motivate the development of efﬁcient implementations

##### Test client

###### Basic symbol-table test client

```java
public static void main(String[] args)
{
    ST<String, Integer> st;
    st = new ST<String, Integer>();
    for (int i = 0; !StdIn.isEmpty(); i++)
    {
        String key = StdIn.readString();
        st.put(key, i);
    }
    for (String s : st.keys())
        StdOut.println(s + " " + st.get(s));
}
```

##### Performance client

###### A symbol-table client

```java
public class FrequencyCounter
{
    public static void main(String[] args)
    {
        int minlen = Integer.parseInt(args[0]); // key-length cutoff
        ST<String, Integer> st = new ST<String, Integer>();
        while (!StdIn.isEmpty())
        {
            // Build symbol table and count frequencies.
            String word = StdIn.readString();
            if (word.length() < minlen) continue; // Ignore short keys.
            if (!st.contains(word)) st.put(word, 1);
            else                    st.put(word, st.get(word) + 1);
        }
        // Find a key with the highest frequency count.
        String max = "";
        st.put(max, 0);
        for (String word : st.keys())
            if (st.get(word) > st.get(max))
                max = word;
        StdOut.println(max + " " + st.get(max));
    }
}
```

This ST client counts the frequency of occurrence of the strings in standard input, then prints out one that occurs with highest frequency.
The command-line argument speciﬁes a lower bound on the length of keys considered.

#### Sequential search in an unordered linked list

###### ALGORITHM 3.1 Sequential search (in an unordered linked list)

```java
public class SequentialSearchST<Key, Value>
{
    private Node first; // first node in the linked list

    private class Node
    {
        // linked list node
        Key key;
        Value val;
        Node next;
        public Node(Key key, Value val, Node next)
        {
            this.key = key;
            this.val = val;
            this.next = next;
        }
    }

    public Value get(Key key)
    {
        // search for key, return associated value
        for (Node x = first; x != null; x = x.next)
            if (key.equals(x.key))
                return x.val; // search hit
        return null;          // search miss
    }

    public void put(Key key, Value val)
    {
        // search for key. update value if found; grow table if new
        for (Node x = first; x != null; x = x.next)
            if (ket.equals(x.key))
            { x.val = val; return; }       // search hit: update val
        first = new Node(key, val, first); // search miss: add new node
    }
}
// Implementations of size(), keys(), and eager delete() are left for exercises.
```

Analyzing symbol-table algorithms is more complicated than analyzing sorting algorithms because of the difﬁculty of characterizing the sequence of operations that might be invoked by a given client.
As noted for FrequencyCounter, the most common situation is that, while search and insert patterns are unpredictable, they certainly are not random.
For this reason, we pay careful attention to worst-case performance.

> **Proposition A.**  
> Search misses and  insertions in an (unordered) linked-list symbol table having N key-value pairs both require N compares, and search hits N compares in the worst case. In particular, inserting N distinct keys into an initially empty linked-list symbol table uses ~N 2/2 compares.
>
> **Proof:**  
> When searching for a key that is not in the list, we test every key in the table against the search key. Because of our policy of disallowing duplicate keys, we need to do such a search before each insertion.
>
> **Corollary.**  
> Inserting N distinct keys into an initially empty linked-list symbol table uses ~N 2/2 compares.

It is easy to show that the average number of compares for a random search hit is ~ N/2: the get() method in Algorithm 3.1 uses 1 compare to ﬁnd the ﬁrst key, 2 compares to ﬁnd the second key, and so forth, for an average cost of (1 + 2 + ... + N )/ N = (N + 1)/2 ~ N/2.

#### Binary search in an ordered array

###### Algorithms 3.2 Binary search (in an ordered array)

```java
public class BinarySearchST<Key extends Comparable<Key>, Value>
{
    private Key[] keys;
    private Value[] vals;
    private int N;

    public BinarySearchST(int capacity)
    {
        // see algorithm 1.1 for standard array-resizing code
        keys = (Key[]) new Comparable[capacity];
        vals = (Value[]) new Object[capacity];
    }
    public int size()
    { return N; }

    public Value get(Key key)
    {
        if (isEmpty()) return null;
        int i = rank(key);
        if (i < N && keys[i].compareTo(key) == 0) return vals[i];
        else return null;
    }
    public int rank(Key key)
    // see p381

    public void put(Key key, Value val)
    {
        // search for key. update value if found; grow table if new
        int i = rank(key);
        if (i < N && keys[i].compareTo(key) == 0)
        { vals[i] = val; return; }
        for (int j = N; j > i; j--)
        { keys[j] = keys[j-1]; vals[j] = vals[j-1]; }
        keys[i] = key;
        vals[i] = val;
        N++;
    }

    public void delete(Key key)
    // see exercise 3.1.16 for this method
}
```

This ST implementation keeps the keys and values in parallel arrays.
The put() implementation moves larger keys one position to the right before growing the table as in the array-based stack implementation in Section 1.3. Array-resizing code is omitted here.

##### Binary search

###### Recursive binary search

```java
public int rank(Key key, int lo, int hi)
{
    if (hi < lo) return lo;
    int mid = lo + (hi - lo) / 2;
    int cmp = key.compareTo(keys[mid]);
    if (cmp < 0)
        return rank(key, lo, mid-1);
    else if (cmp > 0)
        return rank(key, mid+1, hi);
    else
        return mid;
}
```

##### Other operations

###### Algorithm 3.2 (continued) Binary search in an ordered array (iterative)

```java
public int rank(Key key)
{
    int lo = 0, hi = N - 1;
    while (lo <= hi)
    {
        int mid = lo + (hi - lo) / 2;
        int cmp = key.compareTo(keys[mid]);
        if (cmp < 0) hi = mid - 1;
        else if (cmp > 0) lo = mid + 1;
        else return mid;
    }
    return lo;
}
```

This method uses the classic method described in the text to compute the number of keys in the table that are smaller than key. Compare key with the key in the middle: if it is equal, return its index; if it is less, look in the left half; if it is greater, look in the right half.

###### Algorithm 3.2 (continued) Ordered symbol-table operations for binary search

```java
public Key min()
{ return keys[0]; }
public Key max()
{ return keys[N-1]; }
public Key select(int k)
{ return keys[k]; }
public Key ceiling(Key key)
{
    int i = rank(key);
    return keys[i];
}
public Key floor(Key key)
// see exercise 3.1.17
public Key delete(Key key)
// see exercise 3.1.16
public Iterable<Key> keys(Key lo, Key hi)
{
    Queue<Key> q = new Queue<Key>();
    for (int i = rank(lo); i < rank(hi); i++)
    q.enqueue(keys[i]);
    if (contains(hi))
        q.enqueue(keys[rank(hi)]);
    return q;
}
```

#### Analysis of binary search

> **Proposition B.**  
> Binary search in an ordered array with N keys uses no more than lg N + 1 compares for a search (successful or unsuccessful).
>
> **Proof:**
> long..

Despite its guaranteed logarithmic search, BinarySearchST still does not enable us to use clients like FrequencyCounter to solve huge problems, because the put() method is too slow.
Binary search reduces the number of compares, but not the running time, because its use does not change the fact that the number of array accesses required to build a symbol table in an ordered array is quadratic in the size of the array when keys are randomly ordered (and in typical practical situations where the keys, while not random, are well-described by this model).

> **Proposition B (continued).**  
> Inserting a new key into an ordered array of size N uses  ~ 2N array accesses in the worst case, so inserting N keys into an initially empty table uses ~ N 2 array accesses in the worst case.
>
> **Proof:** Same as for Proposition A.

#### Preview

For a static table (with no insert operations allowed), it is worthwhile to initialize and sort the table, as in the version of binary search that we considered in Chapter 1 (see page 99).
Even when the bulk of the key-value pairs is known before the bulk of the searches (a common situation in applications), it is worthwhile to add to BinarySearchST a constructor that initializes and sorts the table (see Exercise 3.1.12).

###### Cost summary for basic symbol-table implementations

| algorithm (data structure)                | worst-case cost | (after N inserts) | average-case cost | (after N random inserts) | efficiently support ordered operations? |
| ----------------------------------------- | --------------- | ----------------- | ----------------- | ------------------------ | --------------------------------------- |
|                                           | search          | insert            | search hit        | insert                   |                                         |
| sequential search (unordered linked list) | N               | N                 | N/2               | N                        | no                                      |
| binary search (ordered array)             | lg N            | 2N                | lg N              | N                        | yes                                     |

###### Pros and cons of symbol-table implementations

| underlying data structure       | implementation         | pros                                        | cons                                     |
| ------------------------------- | ---------------------- | ------------------------------------------- | ---------------------------------------- |
| linked list (sequential search) | SequentialSearchST     | best for tiny STs                           | slow for large STs                       |
| ordered array (binary search)   | BinarySearchST         | optimal search and space, order-based ops   | slow insert                              |
| binary search tree              | BST                    | easy to implement, order-based ops          | no guarantees space for links            |
| balanced BST                    | RedBlackBST            | optimal search and insert, order-based ops  | space for links                          |
| hash table                      | SeparateChainingHashST | fast search/insert for common types of data | need hash for each type                  |
|                                 | LinearProbingHashST    |                                             | no order-based ops space for links/empty |

--------------------------------------------------------------------------------

### 3.2 Binary Search Trees

> **Definition. A**  
> binary search tree (BST) is a binary tree where each node has a Comparable key (and an associated value) and satisﬁes the restriction that the key in any node is larger than the keys in all nodes in that node’s left subtree and smaller than the keys in all nodes in that node’s right subtree.

#### Basic implementation

###### Algorithm 3.3 Binary search tree symbol table

```java
public class BST<Key extends Comparable<Key>, Value>
{
    private Node root; // root of BST

    private class Node
    {
        private Key key;          // key
        private Value val;        // associated value
        private Node left, right; // links to subtrees
        private int N;            // # nodes in subtree rooted here

        public Node(Key key, Value val, int N)
        { this.key = key; this.val = val; this.N = N; }
    }

    public int size()
    { return size(root); }
    private int size(Node x)
    {
        if (x == null) return 0;
        else return x.N;
    }

    public Value get(Key key)
    // see p399
    public void put(Key key, Value val)
    // see p399

    // see p407 for min(), max(), floor(), and ceiling()
    // see p409 for select() and rank()
    // see p411 for delete(), deleteMin(), and deleteMax()
    // see p413 for keys()
}
```

###### Algorithm 3.3 (continued) Search and insert for BSTs

```java
public Value get(Key key)
{ return get(root, key); }
private Value get(Node x, Key key)
{
    // return value associated with key in the subtree rooted at x;
    // return null if key not present in subtree rooted at x
    if (x == null) return null;
    int cmp = key.compareTo(x.key);
    if (cmp < 0) return get(x.left, key);
    else if (cmp > 0) return get(x.right, key);
    else return x.val;
}

public void put(Key key, Value val)
{
    // search for key. update value if found; grow table if new
    root = put(root, key, val);
}
private Node put(Node x, Key key, Value val)
{
    // change key's value to val if key in subtree rooted at x
    // Otherwise, add new node to subtree associating key with val
    if (x == null) return new Node(key, val, 1);
    int cmp = key.compareTo(x.key);
    if (cmp < 0) x.left = put(x.left, key, val);
    else if(cmp > 0) x.right = put(x.right, key, val);
    else x.val = val;
    x.N = size(x.left) + size(x.right) + 1;
    return x;
}
```

##### Representation

We deﬁne a private nested class to deﬁne nodes in BSTs, just as we did for linked lists. Each node contains a key, a value, a left link, a right link, and a node count.

size(x) = size(x.left) + size(x.right) + 1

##### Search

##### Insert

##### Recursion

Elementary BSTs are often implemented with nonrecursive code (see Exercise 3.2.12)—we use recursion in our implementations both to make it easy for you to convince yourself that the code is operating as described and to prepare the groundwork for more sophisticated algorithms.

#### Analysis

The running times of algorithms on binary search trees depend on the shapes of the trees, which, in turn, depend on the order in which keys are inserted.
In the best case, a tree with N nodes could be  perfectly balanced, with ~ lg N nodes between the root and each null link.
In the worst case there could be N nodes on the search path. The balance in typical trees turns out to be much closer to the best case than the worst case.

> **Proposition C.**  
> Search hits in a BST built from N random keys require ~ 2 ln N (about 1.39 lg N) compares, on the average.
>
> **Proof:**  
> The number of compares used for a search hit ending at a given node is 1 plus the depth. Adding the depths of all nodes, we get a quantity known as the internal path length of the tree. Thus, the desired quantity is 1 plus the average internal path length of the BST, which we can analyze with the same argument that we used for Proposition K in Section 2.3: Let CN be the total internal path length of a BST built from inserting N randomly ordered distinct keys, so that the average cost of a search hit is 1 CN / N. We have C0 = C1 = 0 and for N > 1 we can write a recurrence relationship that directly mirrors the recursive BST structure:  
> CN = N  1  (C0  CN1) / N + (C1  CN2)/N   . . .  (CN1  C0 )/N  
> The N  1 term takes into account that the root contributes 1 to the path length of each of the other N  1 nodes in the tree; the rest of the expression accounts for the subtrees, which are equally likely to be any of the N sizes. After rearranging terms, this recurrence is nearly identical to the one that we solved in Section 2.3 for quicksort, and we can derive the approximation CN ~ 2N  ln N.
>
> **Proposition D.**  
> Insertions and search misses in a BST built from N random keys require ~ 2 ln N (about 1.39 lg N) compares, on the average.
>
> **Proof:**  
> Insertions and search misses take one more compare, on the average, than search hits. This fact is not difﬁcult to establish by induction (see Exercise 3.2.16).

##### Experiments

#### Order-based methods and deletion

##### Minimum and maximum in BSTs

##### Floor and ceiling in BSTs

###### ALGORITHM 3.3 (continued) Min, max, floor, and ceiling in BSTs

```java
public Key min()
{
    return min(root).key;
}
private Node min(Node x)
{
    if (x.left == null) return x;
    return min(x.left);
}

public Key floor(Key key)
{
    Node x = floor(root, key);
    if (x == null) return null;
    return x.key;
}
private Node floor(Node x, Key key)
{
    if (x == null) return null;
    int cmp = key.compareTo(x.key);
    if (cmp == 0) return x;
    if (cmp < 0)  return floor(x.left, key);
    Node t = floor(x.right, key);
    if (t != null) return t;
    else           return x;
}
```

##### Selection

##### Rank

###### ALGORITHM 3.3 (continued) Selection and rank in BSTs

```java
public Key select(int k)
{
    return select(root, k).key;
}
private Node select(Node x, int k)
{
    // Return Node containing key of rank k.
    if (x == null) return null;
    int t = size(x.left);
    if      (t > k) return select(x.left,  k);
    else if (t < k) return select(x.right, k-t-1);
    else            return x;
}

public int rank(Key key)
{ return rank(key, root); }
private int rank(Key key, Node x)
{
    // Return number of keys less than x.key in the subtree rooted at x.
    if (x == null) return 0;
    int cmp = key.compareTo(x.key);
    if      (cmp < 0) return rank(key, x.left);
    else if (cmp > 0) return 1 + size(x.left) + rank(key, x.right);
    else              return size(x.left);
}
```

##### Delete the minimum/maximum

##### Delete

###### ALGORITHM 3.3 (continued) Deletion in BSTs

```java
public void deleteMin()
{
    root = deleteMin(root);
}
private Node deleteMin(Node x)
{
    if (x.left == null) return x.right;
    x.left = deleteMin(x.left);
    x.N = size(x.left) + size(x.right) + 1;
    return x;
}

public void delete(Key key)
{ root = delete(root, key); }
private Node delete(Node x, Key key)
{
    if (x == null) return null;
    int cmp = key.compareTo(x.key);
    if      (cmp < 0) x.left  = delete(x.left,  key);
    else if (cmp > 0) x.right = delete(x.right, key);
    else
    {
        if (x.right == null) return x.left;
        if (x.left == null) return x.right;
        Node t = x;
        x = min(t.right); // See page 407.
        x.right = deleteMin(t.right);
        x.left = t.left;
    }
    x.N = size(x.left) + size(x.right) + 1;
    return x;
}
```

##### Range queries in BSTs

To implement the keys() method that returns the keys in a given range, we begin with a basic recursive BST traversal method, known as  *inorder traversal*. To illustrate the method, we consider the task of printing all the keys in a BST in order. To do so, print all the keys in the left subtree (which are less than the key at the root by deﬁnition of BSTs), then print the key at the root, then print all the keys in the right subtree (which are greater than the key at the root by deﬁnition of BSTs), as in the code at left.

###### ALGORITHM 3.3 (continued) Range searching in BSTs

```java
public Iterable<Key> keys()
{ return keys(min(), max()); }
public Iterable<Key> keys(Key lo, Key hi)
{
    Queue<Key> queue = new Queue<Key>();
    keys(root, queue, lo, hi);
    return queue;
}
private void keys(Node x, Queue<Key> queue, Key lo, Key hi)
{
    if (x == null) return;
    int cmplo = lo.compareTo(x.key);
    int cmphi = hi.compareTo(x.key);
    if (cmplo < 0) keys(x.left, queue, lo, hi);
    if (cmplo <= 0 && cmphi >= 0) queue.enqueue(x.key);
    if (cmphi > 0) keys(x.right, queue, lo, hi);
}
```

##### Analysis of order-based operations

> **Proposition E.**  
> In a  BST, all operations take time proportional to the height of the tree, in the worst case.
>
> **Proof:**  
> All of these methods go down one or two paths in the tree. The length of any path is no more than the height, by deﬁnition.

**In summary**, BSTs are not difﬁcult to implement and can provide fast search and insert for practical applications of all kinds *if* the key insertions are well-approximated by the random-key model.

###### Cost summary for basic symbol-table implementations (updated)

| algorithm (data structure)                | worst-case cost | (after N inserts) | average-case cost | (after N random inserts) | efficiently support |
| ----------------------------------------- | --------------- | ----------------- | ----------------- | ------------------------ | ------------------- |
|                                           | search          | insert            | search hit        | insert                   | ordered operations? |
| sequential search (unordered linked list) | N               | N                 | N/2               | N                        | no                  |
| binary search (ordered array)             | lg N            | 2N                | lg N              | N                        | yes                 |
| binary tree search (BST)                  | N               | N                 | 1.39 lg N         | 1.39 lg N                | yes                 |

#### Q&A of binary search trees

Q.  I’ve seen BSTs before, but not using recursion. What are the tradeoffs?

A. Generally,  recursive implementations are a bit easier to verify for correctness; nonrecursive implementations are a bit more *efﬁcient*.
See Exercise 3.2.13 for an implementation of get(), the one case where you might notice the improved efﬁciency.
If trees are unbalanced, the depth of the  function-call stack could be a problem in a recursive implementation.
Our primary reason for using recursion is to ease the transition to the balanced BST implementations of the next section, which deﬁnitely are easier to implement and debug with recursion.

--------------------------------------------------------------------------------

### 3.3 Balanced Search Trees

#### 2-3 search trees

> **Definition.**  
> A 2-3 search tree is a tree that is either empty or
>  - A 2-node, with one key (and associated value) and two links, a left link to a 2-3 search tree with smaller keys, and a right link to a 2-3 search tree with larger keys
>  - A 3-node, with two keys (and associated values) and three links, a left link to a 2-3 search tree with smaller keys, a middle link to a 2-3 search tree with keys between the node’s keys, and a right link to a 2-3 search tree with larger keys
>
> As usual, we refer to a link to an empty tree as a null link.

##### Search in a 2-3 tree

##### Insert into a 2-node

The primary reason that 2-3 trees are useful is that we can do insertions and still maintain perfect balance.
It is easy to accomplish this task if the node at which the search terminates is a 2-node: we just replace the node with a 3-node containing its key and the new key to be inserted.

##### Insert into a tree consisting of a single 3-node

To be able to perform the insertion, we temporarily put the new key into a 4-node, a natural extension of our node type that has three keys and four links. Creating the 4-node is convenient because it is easy to convert it into a 2-3 tree made up of three 2-nodes, one with the middle key (at the root), one with the smallest of the three keys (pointed to by the left link of the root), and one with the largest of the three keys (pointed to by the right link of the root). Such a tree is a 3-node BST and also a perfectly balanced 2-3 search tree, with all the null links at the same distance from the root.

##### Insert into a 3-node whose parent is a 2-node

In this case, we can still make room for the new key while maintaining perfect balance in the tree, by making a temporary 4-node as just described, then splitting the 4-node as just described, but then, instead of creating a new node to hold the middle key, moving the middle key to the node’s parent.

##### Insert into a 3-node whose parent is a 3-node

Again, we make a temporary 4-node as just described, then split it and insert its middle key into the parent. The parent was a 3-node, so we replace it with a temporary new 4-node containing the middle key from the 4-node split. Then, we perform precisely the same transformation on that node. That is, we split the new 4-node and insert its middle key into its parent. Extending to the general case is clear: we continue up the tree, splitting 4-nodes and inserting their middle keys in their parents until reaching a 2-node, which we replace with a 3-node that does not need to be further split, or until reaching a 3-node at the root.

##### Splitting the root

If we have 3-nodes along the whole path from the insertion point to the root, we end up with a temporary 4-node at the root.
In this case we can proceed in precisely the same way as for insertion into a tree consisting of a single 3-node. We split the temporary 4-node into three 2-nodes, increasing the height of the tree by 1.

##### Local transformations

##### Global properties

these local transformations preserve the global properties that the tree is ordered and perfectly balanced: the number of links on the path from the root to any null link is the same.

**Unlike standard BSTs**, which grow down from the top, 2-3 trees grow up from the bottom.

> **Proposition F.**  
> Search and insert operations in a 2-3 tree with N keys are guaranteed to visit at most lg N nodes.
>
> **Proof:** The height of an N-node 2-3 tree is between  ⎣log3 N⎦ = ⎣(lg N)/(lg 3)⎦ (if the tree is all 3-nodes) and  ⎣lg N⎦ (if the tree is all 2-nodes) (see Exercise 3.3.4).

The primary purpose of balancing is to provide insurance against a bad worst case, but we would prefer the overhead cost for that insurance to be low.

#### Red-black BSTs

##### Encoding 3-nodes

The basic idea behind red-black BSTs is to encode 2-3 trees by starting with standard BSTs (which are made up of 2-nodes) and adding extra information to encode 3-nodes. We think of the links as being of two different types: red links, which bind together two 2-nodes to represent 3-nodes, and black links, which bind together the 2-3 tree.  Speciﬁcally, we represent 3-nodes as two 2-nodes connected by a single red link that  leans left (one of the 2-nodes is the left child of the other).
We refer to BSTs that represent 2-3 trees in this way as red-black BSTs.

##### An equivalent d eﬁnition

Another way to proceed is to deﬁne red-black BSTs as BSTs having red and black links and satisfying the following three restrictions:
 - Red links lean left
 - No node has two red links connected to it
 - The tree has perfect black balance: every path from the root to a null link has the same number of black links.

There is a 1-1 correspondence between red-black BSTs deﬁned in this way and 2-3 trees.

##### A 1-1 correspondence

we get the best of both worlds: the simple and efﬁcient search method from standard BSTs and the efﬁcient insertion-balancing method from 2-3 trees.

##### Color representation

we encode the color of links in nodes, by adding a boolean instance variable color to our Node data type, which is true if the link from the parent is red and false if tit is black.

##### Rotations

The implementation that we will consider might allow right-leaning red links or two red links in a row during an operation, but it always corrects these conditions before completion, through judicious use of an operation called rotation that switches the orientation of red links.

##### Resetting the link in the parent after a rotation

##### Insert into a single 2-node

A red-black BST with 1 key is just a single 2-node. Inserting the second key immediately shows the need for having a rotation operation. If the new key is smaller than the key in the tree, we just make a new (red) node with the new key and we are done: we have a red-black BST that is equivalent to a single 3-node. But if the new key is larger than the key in the tree, then attaching a new (red) node gives a right-leaning red link, and the code root = rotateLeft(root); completes the insertion by rotating the red link to the left and updating the tree root link. The result in both cases is the red-black representation of a single 3-node, with two keys, one left-leaning red link, and black height 1.

##### Insert into a 2-node at the bottom

We insert keys into a red-black BST as usual into a BST, adding a new node at the bottom (respecting the order), but always connected to its parent with a red link. If the parent is a 2-node, then the same two cases just discussed are effective.

##### Insert into a tree with two keys (in a 3-node)

This case reduces to three subcases: the new key is either less than both keys in the tree, between them, or greater than both of them. Each of the cases introduces a node with two red links connected to it; our goal is to correct this condition.
 - The simplest of the three cases is when the new key is larger than the two in the tree and is therefore attached on the rightmost link of the 3-node, making a balanced tree with the middle key at the root, connected with red links to nodes containing a smaller and a larger key. If we ﬂip the colors of those two links from red to black, then we have a balanced tree of height 2 with three nodes, exactly what we need to maintain our 1-1 correspondence to 2-3 trees. The other two cases eventually reduce to this case.
 - If the new key is smaller than the two keys in the tree and goes on the left link, then we have two red links in a row, both leaning to the left, which we can reduce to the previous case (middle key at the root, connected to the others by two red links) by rotating the top link to the right.
 - If the new key goes between the two keys in the tree, we again have two red links in a row, a right-leaning one below a left-leaning one, which we can reduce to the previous case (two red links in a row, to the left) by rotating left the bottom link.

##### Flipping colors

In addition to ﬂipping the colors of the children from red to black, we also ﬂip the color of the parent from black to red. A critically important characteristic of this operation is that, like rotations, it is a local transformation that preserves perfect black balance in the tree.

##### Keeping the root black

Note that the black height of the tree increases by 1 whenever the color of the color of the root is ﬂipped from black to red.

##### Insert into a 3-node at the bottom

Now suppose that we add a new node at the bottom that is connected to a 3-node. The same three cases just discussed arise.

##### Passing a red link up the tree

**In summary, we can maintain** our 1-1 correspondence between 2-3 trees and red-black BSTs during insertion by judicious use of three simple operations: left rotate, right rotate, and color ﬂip.
We can accomplish the insertion by performing the following operations, one after the other, on each node as we pass up the tree from the point of insertion:
 - If the right child is red and the left child is black, rotate left
 - If both the left child and its left child are red, rotate right
 - If both children are red, ﬂip colors

#### Implementation

###### Algorithm 3.4 Insert for red-black BSTs

```java
public class RedBlackBST<Key extends Comparable<Key>, Value>
{
    private Node root;
    private class Node // BST node with color bit (see p433)

    private boolean isRed(Node h)    // see p433
    private Node rotateLeft(Node h)  // see p434
    private Node rotateRight(Node h) // see p434
    private void flipColors(Node h)  // see p436
    private int size()               // see p398

    public void put(Key key, Value val)
    {
        // search for key. update value if found; grow table if new
        root = put(root, key, val);
        root.color = BLACK;
    }
    private Node put(Node h, Key key, Value val)
    {
        if (h == null) // do standard insert, with red link to parent
            return new Node(key, val, 1, RED);
        int cmp = key.cmopareTo(h.key);
        if (cmp < 0) h.left = put(h.left, key, val);
        else if (cmp > 0) h.right = put(h.right, key, val);
        else h.val = val;

        if (isRed(h.right) && !isRed(h.left)) h = rotateLeft(h);
        if (isRed(h.left) && isRed(h.left.left)) h = rotateRight(h);
        if (isRed(h.left) && isRed(h.right)) flipColor(h);

        h.N = size(h.left) + size(h.right) + 1;
        return h;
    }
}
```

###### Node representation for red-black BSTs

```java
private static final boolean RED = true;
private static final boolean BLACK = false;
private class Node
{
    Key key;          // key
    Value val;        // associated date
    Node left, right; // subtrees
    int N;            // # nodes in this subtree
    boolean color;    // color of link from parent to this node

    Node(Key key, Value val, int N, boolean color)
    {
        this.key = key;
        this.val = val;
        this.N = N;
        this.color = color;
    }
}

private boolean isRed(Node x)
{
    if (x == null) return false;
    return x.color == RED;
}
```

###### Left rotate (right link of h)

```java
Node rotateLeft(Node h)
{
    Node x = h.right;
    h.right = x.left;
    x.left = h;
    x.color = h.color;
    h.color = RED;
    x.N = h.N;
    h.N = size(h.left) + size(h.right) + 1;
    return x;
}
```

###### Right rotate (left link of h)

```java
Node rotateRight(Node h)
{
    Node x = h.left;
    h.left = x.right;
    x.right = h;
    x.color = h.color;
    h.color = RED;
    x.N = h.N;
    h.N = size(h.left) + size(h.right) + 1;
    return x;
}
```

###### Flipping colors to split a 4-node

```java
void flipColors(Node h)
{
    h.color = RED;
    h.left.color = BLACK;
    h.right.color = BLACK;
}
```

The code for the recursive put() for red-black BSTs is identical to put() in elementary BSTs except for the three if statements after the recursive calls, which provide near-perfect balance in the tree by maintaining a 1-1 correspondence with 2-3 trees, on the way up the search path. The ﬁrst rotates left any right-leaning 3-node (or a right-leaning red link at the bottom of a temporary 4-node); the second rotates right the top link in a temporary 4-node with two left-leaning red links; and the third ﬂips colors to pass a red link up the tree (see text).

#### Deletion in red-black BSTs

##### Top-down 2-3-4 trees

To implement this algorithm with redblack BSTs, we
 - Represent 4-nodes as a balanced subtree of three 2-nodes, with both the left and right child connected to the parent with a red link
 - Split 4-nodes on the way down the tree with color ﬂips
 - Balance 4-nodes on the way up the tree with rotations, as for insertion

##### Delete the minimum

To ensure that we do not end up on a 2-node, we perform appropriate transformations on the way down the tree to preserve the invariant that the current node is not a 2-node (it might be a 3-node or a temporary 4-node).
First, at the root, there are two possibilities: if the root is a 2-node and both children are 2-nodes, we can just convert the three nodes to a 4-node; otherwise we can borrow from the right sibling  if necessary to ensure that the left child of the root is not a 2-node. Then, on the way down the tree, one of the following cases must hold:
 - If the left child of the current node is not a 2-node, there is nothing to do.
 - If the left child is a 2-node and its immediate sibling is not a 2-node, move a key from the sibling to the left child.
 - If the left child and its immediate sibling are 2-nodes, then combine them with the smallest key in the parent to make a 4-node, changing the parent from a 3-node to a 2-node or from a 4-node to a 3-node.

Following this process as we traverse left links to the bottom, we wind up on a 3-node or a 4-node with the smallest key, so we can just remove it, converting the 3-node to a 2-node or the 4-node to a 3-node. Then, on the way up the tree, we split any unused temporary 4-nodes.

##### Delete in red-black BSTs

#### Properties of red-black BSTs

*all symbol-table operations in red-black BSTs are guaranteed to be logarithmic in the size of the tree* (except for range search, which additionally costs time proportional to the number of keys returned). We repeat and emphasize this point because of its importance.

##### Analysis of red-black BSTs

> **Proposition G.**  
> The height of a red-black BST with N nodes is no more than 2 lg N.
>
> **Proof sketch:**  
> The worst case is a 2-3 tree that is all 2-nodes except that the leftmost path is made up of 3-nodes. The path taking left links from the root is twice as long as the paths of length ~ lg N that involve just 2-nodes. It is possible, but not easy, to develop key sequences that cause the construction of red-black BSTs whose average path length is the worst-case 2 lg N. If you are mathematically inclined, you might enjoy exploring this issue by working Exercise 3.3.24.
>
> **Property H.**  
> The average length of a path from the root to a node in a red-black BST with N nodes is ~1.00 lg N.
>
> **Evidence:**  
> Typical trees, such as the one at the bottom of the previous page (and even the one built by inserting keys in increasing order at the bottom of this page) are quite well-balanced, by comparison with typical BSTs (such as the tree depicted on page 405). The table at the top of this page shows that path lengths (search costs) for our FrequencyCounter application are about 40 percent lower than from elementary BSTs, as expected. This performance has been observed in countless applications and experiments since the invention of red-black BSTs.

##### Ordered symbol-table API

One of the most appealing features of red-black BSTs is that the complicated code is limited to the put() (and deletion) methods.
Our code for the minimum/maximum, select, rank, ﬂoor, ceiling and range queries in standard BSTs can be used *without any change*, since it operates on BSTs and has no need to refer to the node color.

Algorithm 3.4, together with these methods (and the deletion methods), leads to a complete implementation of our ordered symbol-table API.

> **Proposition I.**  
> In a red- black BST, the following operations take logarithmic time in the worst case: search, insertion, ﬁnding the minimum, ﬁnding the maximum, ﬂoor, ceiling, rank, select, delete the minimum, delete the maximum, delete, and range count.
>
> **Proof:**  
> We have just discussed get(), put(), and the deletion operations. For the others, the code from Section 3.2 can be used verbatim (it just ignores the node color). Guaranteed logarithmic performance follows from Propositions E and G, and the fact that each algorithm performs a constant number of operations on each node examined.

###### Cost summary for basic symbol-table implementations (updated 2)

| algorithm (data structure)                | worst-case cost | (after N inserts) | average-case cost | (after N random inserts) | efficiently support |
| ----------------------------------------- | --------------- | ----------------- | ----------------- | ------------------------ | ------------------- |
|                                           | search          | insert            | search hit        | insert                   | ordered operations? |
| sequential search (unordered linked list) | N               | N                 | N/2               | N                        | no                  |
| binary search (ordered array)             | lg N            | 2N                | lg N              | N                        | yes                 |
| binary tree search (BST)                  | N               | N                 | 1.39 lg N         | 1.39 lg N                | yes                 |
| 2-3 tree search (red-black BST)           | 2 lg N          | 2 lg N            | 1.00 lg N         | 1.00 lg N                | yes                 |

--------------------------------------------------------------------------------

### 3.4 Hash Tables

Search algorithms that use hashing consist of two separate parts.
The ﬁrst part is to compute a hash function that transforms the search key into an array index.
Ideally, different keys would map to different indices.
This ideal is generally beyond our reach, so we have to face the possibility that two or more different keys may hash to the same array index.
Thus, the second part of a hashing search is a   collision-resolution process that deals with this situation.
After describing ways to compute hash functions, we shall consider two different approaches to collision resolution: *separate chaining* and *linear probing*.

Hashing is a classic example of a  time-space tradeoff. If there were no memory limitation, then we could do any search with only one memory access by simply using the key as an index in a (potentially huge) array.

With hashing, you can implement search and insert for symbol tables that require constant (amortized) time per operation in typical applications, making it the method of choice for implementing basic symbol tables in many situations.

#### Hash functions

The hash function transforms keys into array indices.

If we have an array that can hold M key-value pairs, then we need a hash function that can transform any given key into an index into that array: an integer in the range [0, M – 1]. We seek a hash function that both is easy to compute and uniformly distributes the keys: for each key, every integer between 0 and M – 1 should be equally likely (independently for every key).

The hash function depends on the key type.  Strictly speaking, *we need a different hash function for each key type that we use*.

##### Typical example

U.S. social security number

##### Positive integers

The most commonly used method for hashing integers is called *modular hashing*: we choose the array size M to be prime and, for any positive integer key k, compute the remainder when dividing k by M.

##### Floating-point numbers

If the keys are real numbers between 0 and 1, we might just multiply by M and round off to the nearest integer to get an index between 0 and M – 1.

##### Strings

 Modular hashing works for long keys such as strings, too: we simply treat them as huge integers.

##### Compound keys

For example, suppose that search keys are of type Date, which has three integer ﬁelds: day (two-digit day), month (twodigit month), and year (four-digit year).We compute the number  
`int hash = (((day * R + month) % M ) * R + year) % M;`  
which, if the value of R is sufﬁciently small that no overﬂow occurs, is an integer between 0 and M – 1, as desired.

##### Java conventions

`hashCode()` returns a 32-bit integer.

##### Converting a `hashCode()` to an array index

Since our goal is an array index, not a 32-bit integer, we combine hashCode() with modular hashing in our implementations to produce integers between 0 and M – 1, as follows:  
`private int has(Key x)`  
`{ return (x.hashCode() & 0x7fffffff) % M; }`  
This code masks off the sign bit (to turn the 32-bit number into a 31-bit nonnegative integer) and then computes the remainder when dividing by M, as in modular hashing.

##### User-defined `hashCode()`

###### Implementing hashCode() in a user-defined type

```java
public class  Transaction
{
    ...
    private final String who;
    private final Date when;
    private final double amount;
    public int hashCode()
    {
        int hash = 17;
        hash = 31 * hash + who.hashCode();
        hash = 31 * hash + when.hashCode();
        hash = 31 * hash + ((Double) amount).hashCode();
        return hash;
    }
    ...
}
```

##### Software caching

If computing the hash code is expensive, it may be worthwhile to cache the hash for each key.
That is, we maintain an instance variable hash in the key type that contains the value of hashCode() for each key object (see Exercise 3.4.25).

**In summary, we have three primary requirements** in implementing a good hash function for a given data type:
 - It should be consistent—equal keys must produce the same hash value
 - It should be efﬁcient to compute
 - It should uniformly distribute the keys.

Still, you should be vigilant whenever using hashing in situations where good performance is critical, because a bad hash function is a classic example of a performance bug: everything will work properly, but much more slowly than expected.

> **Assumption J** (uniform hashing assumption).  
> The hash functions that we use uniformly and independently distribute keys among the integer values between 0 and M – 1.
>
> **Discussion:**  
> With all of the arbitrary choices that we have made, we certainly do not have hash functions that uniformly and independently distribute keys in this strict mathematical sense. Indeed, the idea of implementing consistent functions that are guaranteed to uniformly and independently distribute keys leads to deep theoretical studies that tell us that computing such a function easily is likely to be a very elusive goal. In practice, as with random numbers generated by Math.random(), most programmers are content to have hash functions that cannot easily be distinguished from random ones. Few programmers check for independence, however, and this property is rarely satisﬁed.

#### Hashing with separate chaining
