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
