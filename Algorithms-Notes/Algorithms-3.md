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

| algorithm (data structure)                | worst-case cost | (after N inserts) | average-case cost | (after N random inserts) | efficiently support ordered operations? |
| ----------------------------------------- | --------------- | ----------------- | ----------------- | ------------------------ | --------------------------------------- |
|                                           | search          | insert            | search hit        | insert                   |                                         |
| sequential search (unordered linked list) | N               | N                 | N/2               | N                        | no                                      |
| binary search (ordered array)             | lg N            | 2N                | lg N              | N                        | yes                                     |
| binary tree search (BST)                  | N               | N                 | 1.39 lg N         | 1.39 lg N                | yes                                     |

#### Q&A of binary search trees

Q.  I’ve seen BSTs before, but not using recursion. What are the tradeoffs?

A. Generally,  recursive implementations are a bit easier to verify for correctness; nonrecursive implementations are a bit more *efﬁcient*.
See Exercise 3.2.13 for an implementation of get(), the one case where you might notice the improved efﬁciency.
If trees are unbalanced, the depth of the  function-call stack could be a problem in a recursive implementation.
Our primary reason for using recursion is to ease the transition to the balanced BST implementations of the next section, which deﬁnitely are easier to implement and debug with recursion.

--------------------------------------------------------------------------------
