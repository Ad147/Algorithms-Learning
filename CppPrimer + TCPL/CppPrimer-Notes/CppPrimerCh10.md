CppPrimerCh10.md

C++ Primer Notes
================================================================================

Ad  
init: May13.2018

Chapter10 Generic Algorithms
--------------------------------------------------------------------------------

### 10.1 Overview

Defined in `algorithm` or `numeric`

##### Iterators make algorithms container independent, but algorithms do depend on element-type operations

> Algorithms never execute container operations  
> (they do not change the size)

--------------------------------------------------------------------------------

### 10.2 A First Look at the Algorithms

#### 10.2.1 Read-Only Algorithms

 - `find(it1, it2, value)`
 - `count(it1, it2, value)`
 - `accumulate(it1, it2, initial)` in `<numeric>` : get the sum of the range, 3rd argument determines which addition operator is used and the return type

##### Algorithms that operate on two sequences

 - `equal(c1it1, c1it2, c2it1)` : the type of the container can be different, and the element type can be different

> Algorithms that take a single iterator denoting a second sequence *assume* that the second sequence is at least as large as the first.

#### 10.2.2 Algorithms That Write Container Elements

 - `fill(it1, it2, value)` : fill the range with value

##### Algorithms do not check write operations

 - `fill_n(it1, n, value)`

##### Introducing `back_inserter` (`<iterator>`)

An insert iterator is an iterator that adds elements to a container.  
`back_inserter` will call `push_back` when assigning through the iterator.

##### Copy algorithms

 - `copy(c1it1, c1it2, c2it1)` : copy c1[it1: it2] to c2
 - `replace(it1, it2, val1, val2)` : replace val1 in the range with val2
 - `replace_copy(c1it1, c1it2, back_inserter(c2), val1, val2)` : copy the adjusted sequence to c2 and do not change the c1

#### 10.2.3 Algorithms That Reorder Container Elements

##### Eliminating duplicates

 - `sort(it1, it2)` : use `<` to compare
 - `unique(it1, it2)` : reorders the input range so that each element appears once in the front portion of the range. returns an iterator one past the unique range

--------------------------------------------------------------------------------

### 10.3 Customizing Operations

#### 10.3.1 Passing a Function to an Algorithm

##### Predicates are expressions that can be called and that returns a value that can be used as a condition

The predicates used by library algorithms are either:
 - unary predicates
 - binary predicates

 - `stable_sort(it1, it2, predicate)` : maintains the original order among equal elements

#### 10.3.2 Lambda Expressions

 - `find_it(it1, it2, predicate)` : find the first element in the range that the return of which is nonzero

##### Introducing Lambdas

`C++11` a lambda expression represents a callable unit of code.  
can be thought of as an unnamed, inline function.
 - `[capture list] (parameter list) -> return type { function body }`
 - capture list is an (often empty) list of local variables defined in the enclosing function
 - either or both of parameter list and return type can be omit but must include capture list and function body

##### Using the capture list

> A lambda may use a variable local to its surrounding function only if the lambda captures that variable in its capture list.

`[sz](const string &a) { return a.size() >= sz; };`

> The capture list is used for local nonstatic variables only; lambdas can use local statics and variables declared outside the function directly.

##### The `for_each(it1, it2, func)` algorithm (takes a callable object and calls on each element in the range)

#### 10.3.3 Lambda Capture and Return

When we define a lambda, the compiler generates a new (unnamed) **class** type that corresponds to that lambda.
We’ll see how these classes are generated in § 14.8.1 (p. 572).

When we pass a lambda to a function, we are defining both a new type and an object of that type: The argument is an unnamed object of this compiler-generated class type.
Similarly, when we use auto to define a variable initialized by a lambda, we are defining an object of the type generated from that lambda.

By default, the class generated from a lambda contains a **data member** corresponding to the variables captured by the lambda.
Like the data members of any class, the data members of a lambda are initialized when a lambda object is created.

##### Capture by value or by reference

unlike parameters, the value of a captured variable is copied when the lambda is created, not when it is called.

##### Implicit captures (can mix with explicit)

###### Lambda Capture List

|                      |                                                                                                                  |
| -------------------- | ---------------------------------------------------------------------------------------------------------------- |
| []                   | Empty capture list. The lambda may not use variables                                                             |
| [names]              | names is a comma-separated list of names local to the enclosing function. defaults to be copied                  |
| [&]                  | implicit by reference capture list.                                                                              |
| [=]                  | implicit by value capture list                                                                                   |
| [&, identifier_list] | identifier_list is a comma-separated list of zero or more variables captured by value. must not be preceded by & |
| [=, reference_list]  | variables inlcuded in the list are captured by reference                                                         |

##### Mutable lambdas

`[v1] () mutable { return ++v1; };`

##### Specifying the lambda return type

> By default, if a lamnda body contains any statements other than a return, that lambda is assumed to return void.

 - `transform(it1, it2, it, callable)` : call on the range [it1, it2), the result in it. if the it == it1, the result will override the range

#### 10.3.4 Binding Arguments

##### `C++11` The library bind function (`<functional>`) (a general-purpose function adaptor):

takes a callable and generates a new callable
 - `auto newCallable = bind(callable, arg_list);` : arg_list is the arguments for callable
 - the arg_list may contain placeholders `_1` `_2` (`std::placeholders::_1`) to represent the parameters of newCallable
 - `bind(check_size, _1, sz)` : takes one argument and pass the argument and sz to check_size

##### Using bind to reorder parameters

##### Binding reference parameters

by using `ref()` `cref()` (`<functional>`): returns an object that contains the given reference and that is itself copyable.

--------------------------------------------------------------------------------

### 10.4 Revisiting Iterators

`<iterator>` :
 - insert iterators: used to insert elements into container
 - stream iterators: bound to i/o streams. used to iterate the associted IO stream
 - reverse iterator: move backward
 - move iterator: special-purposed. move rather than copy

#### 10.4.1 Insert Iterators

###### Insert iterator operations

|                 |                                                                         |
| --------------- | ----------------------------------------------------------------------- |
| it = t          | inserts t at the position denoted by it. call push_back/front or insert |
| *it, ++it, it++ | do nothing to it. each returns it                                       |

 - `back_inserter` : creates an iter that uses push_back
 - `front_inserter` : uses push_front
 - `inserter` : uses insert. takes a second argument that is a iterator to denote the insert position

#### 10.4.2 iostream Iterator

The stream iterators treat their corresponding stream as a sequence of elements of a specified type.

###### `istream_iterator` Operations

|                              |                                                                          |
| ---------------------------- | ------------------------------------------------------------------------ |
| istream_iterator\<T> in(is); | in reads values of type T from input stream is                           |
| istream_iterator\<T> end;    | off-the-end iterator for an istream_iterator that reads values of type T |
| in1 == in2                   | in1 and in2 must read the same type. equal if bound to the same stream   |
| in1 != in2                   |
| *in                          | returns the value read from the stream                                   |
| in->mem                      |
| ++in, in++                   | reads the next value from the input stream                               |

##### `istream_iterator` are permitted to use lazy evaluation

###### `ostream_iterator` Operations

|                                 |                                                                             |
| ------------------------------- | --------------------------------------------------------------------------- |
| ostream_iterator\<T> out(os);   | out writes values of type T to output                                       |
| ostream_iterator\<T> out(os, d) | writes values followed by d. d points to a null-terminated character array. |
| out = val                       | writes val to the ostream using <<                                          |
| *out, \++out, out++             | do nothing to out. returns out                                              |

 - must bind an ostream_iterator to a specific stream. there is no empty of off-the-end ostream_iterator

#### 10.4.3 Reverse Iterators

##### Reverse iterators require decrement operators

 - with `reverse_iterator` 's `base()` member, which gives the corresponding ordinary iterator:  
   `auto rcomma = find(line.crbegin(), line.crend(), ',');`  
   `cout << string(rcomma.base(), line.cend()) << endl;`

> assing a reverse iter from a plain iter, the resulting iter does not refer to the same element

--------------------------------------------------------------------------------

### 10.5 Structure of Generic Algorithms

| Iterator Categories    |
| ---------------------- | ------------------- | ----------- | ------------------------ |
| input iterator         | read, but not write | single-pass | increment only           |
| output iterator        | write, but not read | single-pass | increment only           |
| forward iterator       | read and write      | multi-pass  | increment only           |
| bidirectional iterator | read and write      | multi-pass  | increment and descrement |
| random-access iterator | read and write      | multi-pass  | full iterator arithmetic |

#### 10.5.1 The Five Iterator Categories

##### Input iterators must provide:

 - `==` `!=`
 - `++` (pre/suf-fix)
 - `*` and appear only on the right-hand side of an assignment
 - `->`

##### Output iterators:

 - `++` (pre/suf-fix)
 - `*` and appear only on the left-hand side of an assignment

##### Forward iterators:

support all the operations of both input and output  
moreover, can read or write the same element multiple times

##### Bidirectional iterators:

in addition, supports `--`

##### Random-access iterators:

 - `<` `>` `<=` `>=`
 - `+` `+=` `-` `-=`
 - `[n]`

the `sort` require random-access iterators (array, deque, string, vector)

#### 10.5.2 Algorithm Parameter Patterns

Most of the algoritms  have one of the following four forms:
 - alg(beg, end, oher args);
 - alg(beg, end, dest, other args);
 - alg(beg, end, beg2, other args);
 - alg(beg, end, beg2, end2, other args);

##### Algorithms with a single destination iterator

a `dest` parameter is an iterator that denotes a destination in which the algorithm can output  
assuming that it is safe (enough) to write as many elements as needed

##### Algorithms with a second input sequence

take either beg2 alone or beg2 and end2 use those iters to denote a second input range  
assuming that the range starting with beg2 is at least as large as the 1st range

#### 10.5.3 Algorithm Naming Conventions

##### Some algoritms use overloading to pass a predicate

##### Algorithms with `if` versions

Algorithms that take an element value typically have a second named version that takes a predicate in place of the value.

##### Distinguishing versions that copy from those that do not:

 - `_copy`
 - `_copy_if`

--------------------------------------------------------------------------------

### 10.6 Container-Specific Algorithms

`list` and `forward_list` define several algorithms as members
 - the generic `sort` can not used in lists
 - other in the table can achive much better performance than generic ones

###### Algorithms That are Members of `list` and `forward_list`

|                       |                                                                        |
| --------------------- | ---------------------------------------------------------------------- |
| lst.merge(lst2)       | Merges elements from lst2 onto lst. Both lists must be sorted. use `<` |
| lst.merge(lst2, comp) | Elements are removed from lst2. use the given comp                     |
| lst.remove(val)       | calls erase to remove each element == val or                           |
| lst.remove_if(pred)   | for which the given unary predicate succeeds                           |
| lst.reverse()         |
| lst.sort()            | using `<`                                                              |
| lst.sort(comp)        | using the given comparison operation                                   |
| lst.unique()          | calls erase to remove consecutive copies. use `==`                     |
| lst.unique(pred)      | using given binary predicate                                           |

##### The `splice` members is particular to list data structure

###### Arguments to the list and forward_list splice Members

|                 |                                                                                                                                   |
| --------------- | --------------------------------------------------------------------------------------------------------------------------------- |
|                 | `lst.splice(args)` or `flst.splice_after(args)`                                                                                   |
| (p, lst2)       | p is an iterator to an element in lst. moves all lst2 into lst before p. remove lst2. lst2 should be the same type and not be lst |
| (p, lst2, p2)   | p2 is a valid iterator into lst2. moves the element p2 into lst. lst2 can be the same as lst                                      |
| (p, lst2, b, e) | b and e must denote a valid range in lst2. lst2 can be the same as lst but p must not denote an element in the given range.       |

##### The list-specific operations do not change the containers

--------------------------------------------------------------------------------

EOF
