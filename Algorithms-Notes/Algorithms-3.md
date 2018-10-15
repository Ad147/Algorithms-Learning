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
