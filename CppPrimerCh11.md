CppPrimerCh11.md

C++ Primer Notes
================================================================================

Ad  
init: May17.2018

Chapter11 Associative Container
--------------------------------------------------------------------------------

|| Asscociative Container Types
-|-----------------------------
Elements ordered by Key |
map `<map>`                     | associative array. holds key-value pairs
set `<set>`                     | container in which the key is the value
multimap `<map>`                | map in which a key can appear multiple times
multiset `<set>`                | a key can appear multiple times
Unordered Collections   |
unordered_map `<unordered_map>` | map organized by a hash function
unordered_set `<unordered_set>` | organized by hash
unordered_multimap              | hashed map with multiple
unordered_multiset              |

### 11.1 Using an Associative Container

```cpp
map<string, size_t> word_count;
set<string> exlude{...};

while (cin >> word)
    if (exlude.find(word) == exclude.end())
        ++word_count[word];

for (const auto &w : word_count)
    cout << w.first << w.second << endl;
```

--------------------------------------------------------------------------------

### 11.2 Overview of the Associative Containers

#### 11.2.1 Defining an Associative Container

#### 11.2.2 Requirements on Key Type

By default, the key type use `<` to compare keys

##### Key Types for Ordered Containers
can supply own operation to use in place of `<`  
the comparison function must have properties:
- 2 keys cannot both be "less than" each other
- 传递性: if k1 < k2, k2 < k3 => k1 < k3
- if neither of two keys is "less than" the other, then they are equal

#### 11.2.3 The `pair` Type `<utility>` (template)

|| Operations on `pair`s
-|----------------------
pair<T1, T2> p;         |
pair<T1, T2> p(v1, v2); | the first and the second members are initialized from v1 and v2
pair<T1, T2> p{v1, v2}; | equivalent to p(v1, v2)
make_pair(v1, v2)       | returns a pair initialized from v1 and v2. type is inferred
p.first                 | return the (public) data member of p named first
p.second                | return the (public) data memeber named second
p1 relop p2             | relational operators (< > <= >=). p1 < p2 if p1.first < p2.first or if !(p2.first < p1.first)&&p1.second < p2.second
p1 == p2, p1 != p2      |

The data members of pair is public: `first` and `second`

--------------------------------------------------------------------------------

### 11.3 Operations on Associative Containers

|| Associative Container Additional Type Aliases
-|----------------------------------------------
key_type    | Type of the key
mapped_type | (for map only) type that associated with key
value_type  | for sets, same as key_type. for maps, `pair<const key_type, mapped_type>`

#### 11.3.1 Associative Container Iterators

`mapIt->first` `mapIt->second`

##### Iterators for sets are const

##### Associative Containers and Algorithms
In general, do not use the generic algorithms with the associative containers.
- associatives have member `find` which is much faster than generic find

#### 11.3.2 Adding Elements

|| Associative Container `insert` Operations
-|------------------------------------------
c.insert(v)     | v is value_type object
c.emplace(args) | for map and set, the element is inserted only if the correspoding key is not already in c. 
|| **returns a pair of an iterator to the element and a bool indicating whether the element was inserted**
|| for multimap and multiset, inserts the given element and returns an iterator to the new element.
c.insert(b, e)  | b and e are c::value_type. returns void
c.insert(il)    | il is a braced list. returns void
|| for map and set, inserts elements with keys not in c. for multi, insert each
c.insert(p, v)  | like insert(v), but uses iterator p as a hint indicating where to begin search. 
c.emplace(p, args) | returns an iterator to the element with the given key

#### 11.3.3 Erasing Elements

|| Removing Elements from an Associative Container
-|------------------------------------------------
c.erase(k)  | removes every element with key k. returns size_t indicating the number removed
c.erase(p)  | removes the element denoted by p. returns an iterator to the elment after p
c.erase(b, e) | removes the elements in the range. return e

#### 13.3.4 Subscripting a map

|| Subscripting Operation for map and unordered_map
-|-------------------------------------------------
c[k]    | returns the element with key k. **if k is not in c, add a new, value-initialized element with key k**
c.at(k) | checked access to the element with key k. throws an out_of_range exception if k is not in c

#### 13.3.5 Accessing Elements

|| Operations to Find Elements in an Associative Container
-|--------------------------------------------------------
|| `lower_bound` `upper_bound` not valid for unordered containers
|| subscript and `at` only for `map` `unordered_map` that are not const
c.find(k)       | returns an iterator to the first element with key k
c.count(k)      | returns the number of elements with key k
c.lower_bound(k)| returns an iterator to the first element with key not less than k
c.upper_bound(k)| returns an iterator to the first element with key greater than k
c.equal_range(k)| returns a pair of iterators denoting with k. if k not present, both c.end()

##### Using `find` instead of subscript for `map`s

##### `multimap` `multiset` elements with same key are adjacent

##### A different, iterator-oriented solution

```cpp
for (auto beg = c.lower_bound(search_item), end = c.upper_bound(search_item);
     beg != end; ++beg)
    cout << beg->second << endl;
```

##### The `equal_range` function

```cpp
for (auto pos = c.equal_range(search_item); pos.first != pos.second; ++pos.first)
    cout << pos.first->second << endl;
```

#### 11.3.6 A Word Transformation Map

--------------------------------------------------------------------------------

### 11.4 The Unodered Containers

`C++11` defines 4 unordered associative containers.  
Use hash function and the key's == operator to organize elements.  

> Use an unordered container if the key type is inherantly unordered or if performance testing reveals problems that hashing might solve

##### Managing the buckets

|| Unordered Container Management Operations
-|------------------------------------------
**Bucket Interface**    |
c.bucket_count()        | number of buckets in use
c.max_bucket_count()    | largest number of buckets this container can hold
c.bucket_size(n)        | number of elements in the nth bucket
c.bucket(k)             | bucket in which elements with key k would be found
**Bucket Iteration**    |
local_iterator          | iterator type that can access elements in a bucket
const_local_iterator    | const version
c.begin(n), c.end(n)    | iterator in bucket n
c.cbegin(n), c.cend(n)  | const
**Hash Policy**         |
c.load_factor()         | average number of elements per bucket. returns float
c.max_load_factor()     | average bucket size that c tries to maintain. c adds buckets
c.rehash(n)             | reorganize storage so that bucket_count >= n and bucket_count > size/max_load_factor
c.reserve(n)            | reorganize so that c can hold n elements without a rehash

- define an unordered multimap with user-define functions:  
`unordered_multiset<SaleData, decltype(hashFunc)*, decltype(equalOperatorFunc)*> uomset;`

--------------------------------------------------------------------------------

EOF
