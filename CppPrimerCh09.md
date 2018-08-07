C++ Primer Notas de Estudio
===========================
Ad  
init: May09.2018

Chapter9 Sequential Containers
---------------------------
### 9.1 Overview of the Sequential Containers

||Sequential | Container | Types
-|--------------------------|-|-
`vector`    | flexible-size array   | fast random access    | fast insert/delete at back
`deque`     | double-ended queue    | fast random access    | fast insert/delete at front or back
`list`      | Doubly linked list    | only bidirectional sequential access  | fast insert/delete at any point
`forward_list`  | Singly linked list| only sequential access in one direction   | fast insert/delete at any 
`array`     | Fixed-size array      | fast random access    | cannot add or remove elements
`string`    | similar to vector constains characters | fast random access   | fast insert/delete at the back

`C++11` The `forward_list` and `array` were added by the new standard.  
`array` is a safer, easier-to-use alternative to built-in arrays.
- `forward_list` does not have `size` operation

##### Deciding which sequential container to use
- unless with a good reason, use a `vector`
- if the program has lots of small elements and space overhead matters, donot use `list` `forward_list`
- if requiring random access, use `vector` or `deque`
- if need to insert/delete in the middle, use `list` `forward_list`
- if need insert/delete at the front and back, use `deque`
- if need insert in the middle only in reading, and then need random access:
    - decide whether actually need to add elements in the middle, or using vector and `sort()`
    - if must, using `list` for the input phase and copy to vector

-----------------------------------------------------------------

### 9.2 Container Library Overview

||Container Operations (for all container types)
-|--------------------
**Type Aliases**    | 
iterator            | type of iterator for this container type
const_iterator      | can read but not change
size_type           | unsigned integral type big enough
difference_type     | signed integral type holds the distance between two iterators
value_type          | element type
reference           | element's lvalue type, like value_type&
const_reference     | const lvalue
**Construction**    |
C c;                | default constructor, empty container
C c1(c2);           | copy
C c(b, e);          | copy elements from the range denoted by iterators b and e (not for array)
C c{a, b, c}        | list initialization
**Assignment and swap** |
c1 = c2             | replace elements in c1 with those in c2
c1 = {a, b, c}      | replace with the list (not for array)
a.swap(b)           | swap elements in a with those in b
swap(a, b)          | equivalent to above
**Size**            |
c.size()            | number of elements (not for forward_list)
c.max_size()        | maximum number of elements c can hold
c.empty()           | false if c has any elements
**Add/Remove Elements** | (not valid for array) Note: the interface to these operations varies by container type
c.insert(args)      | copy element(s) as specified by args into c
c.emplace(inits)    | use inits to construct an element in c
c.erase(args)       | remove element(s) specified by args
c.clear()           | remove all elements from c; return void
**Equality and**    | **Relational Operations**
==, !=              | for all types
<, <=, >, >=        | (not valid for unordered associative containers)
**Obtain Iterators**|
c.begin(), c.end()  | return iterator to the first, one past the last element in c
c.cbegin(), c.cend()| return const_iterator
**Addtional Members**| **of Reversible Containers** (not valid for forward_list)
reverse_iterator    | iterator that addresses elements in reverse order
const_reverse_iterator | reverse iterator that cannot write
c.rbegin(), c.rend()| return iterator to the last ,one past the first element
c.crbegin(), c.crend()| return const_reverse_iterator

#### 9.2.1 Iterators

##### Iterator ranges
is denoted by a pair of iterators

is called a left-inclusive interval.

##### Programming Implications of Using Left-Inclusive Ranges
three convinient properties:
- if begin == end, the range is empty
- if begin != end, then begin refers to the first element
- imcrement begin until begin == end

#### 9.2.2 Container Type Members

#### 9.2.3 `begin` and `end` Members

> When write access is not needed, use cbegin and cend.

#### 9.2.4 Defining and Initializing a Container

##### Initializing a container as a copy of another container:
1. directly copy. must match
2. (excepting array) copy a range of elements denoted by a pair of iterators  
the container can be difference and the elements should be able to converted

||Defining and Initializing Containers
-|------------------------------------------------------------
C c;        | default constructor. elements default-initialized if c is an array, empty container otherwise
C c1(c2)    | copy. they must have the same type. (also same size for array)
C c1 = c2   | as above
C c{a, b, c}| list initialization. elements type must match (compatible)
C c = {a, b, c} |as above
C c(b,e)    | elements in the range b and e. (not valid for array)
|| **for sequential containers: (not include array)**
C seq(n)    | seq has n value-initialized elements. (not valid for string)
C seq(n, t) | seq has n elements with value t.

##### Library `array`s have fixed size
`array<int, 42> ia;`

A default-constructed array has as many elements as its size with the default initialized value.

It is worth noting that the library `array` type is able to copy or assign.

#### 9.2.5 Assignment and `swap`

|| Container Assignment Operations
-|--------------------------------
c1 = c2     | replace c1. must be the same type.
c = {a, b}  | (not valid for array)
swap(c1, c2)| exchange elements. they must have the same type. swap is usually much faster than copying
c1.swap(c2) |
|           | **assign operations not valid for associative containers or array**
seq.assign(b, e)    | the iterator b, e must not refer to elements in seq
seq.assign(il)      | replace with elements in initializer list il
seq.assign(n, t)    | the same as the constructor

Because the size of the right-hand operand might differ from the size of the left-hand operand, the array type does not support assign and it does not allow assignment from {}

##### Using `swap`
> Excepting `array`, `swap` does not copy, delete or insert any elements and is guaranteed to run in constant time.

- with the exception of `string`, iterators, references and pointers into the containers are not invalidated. They refer to the same elements as thay did before swap:  
iter denoted the element in vec1 before swap, and then denoted the element in vec2

- a call to swap on a `string` may invalidate iterators, references and pointers

- swapping arrays does exchange the elements

`C++11` as a matter of habit, it is best to use the nonmember version of swap.

#### 9.2.6 Container Size Operations

Exception: `forward_list` provides `max_size` and `empty`, but not `size`

#### 9.2.7 Relational Operators

- `==` `!=` : every container supports
- `>` `>=` ... : except the unordered associative containers

Comparing two containers:
- if both have the same size and elements, they are equal
- if they have different sizes but every element of the smaller one is equal to the correspoding element, then the smaller one is less
- if neither container is an initial subsequence of the other, then the comparison depends on comparing the first unequal elements.

##### Relational operators use their element's relational operator
which means if the element type has no relational operator defined, the comparison between containers is unvalid.

----------------------------------------

### 9.3 Sequential Container Operations

#### 9.3.1 Adding Elements to a Sequential Container

|| Operations That Add Elements to a Sequential Container (not for array)
-|-------------------------------------------------------
c.push_back(t)          | creates an element with value t or constructed from args at the end of c. return void (not for forward_list)
c.emplace_back(args)    | as above
c.push_front(t)         | on the front of c. return void. (not valid for vector or string)
c.push_emplace(args)    | as above
c.insert(p, t)          | creates before the element denoted by iterator p. returns an iterator referring to the element that was added
c.emplace(p, args)      | as above
c.insert(p, n, t)       | inserts n elements with value t before the element denoted by iterator p. returns an iterator to the first element inserted. if n is zero, returns p.
c.insert(p, b, e)       | inserts the elements from the range denoted by iterators b and e before the elements denoted by p. b and e may not refer to element in c. returns an iterator to the first element.
c.insert(p, il)         | il is a braced list of element values

> **Adding elements to a vector, string or deque potentially invalidates all existing iterators, references and pointers into the container.**

##### Using `push_back`

##### Using `push_front`

##### Adding elements at a specified point in the container

##### Inserting a Range of Elements
`C++11` insert that take a count or a range return an iterator to the first element inserted.

##### Using the return from insert

##### Using the Emplace Operations
`C++11` introduced `emplace_front` `emplace` `emplace_back` that construct rather than copy elements.  
Passing arguments to a constructor for the element type.

#### 9.3.2 Accessing Elements

|| Operations to Access Elements in a Sequential Container
-|--------------------------------------------------------
|| `at` and subscipt operator valid only for string, vector, deque and array.
c.back()    | returns a reference to the last element in c. undefined if c is empty (not for forward_list)
c.front()   | returns a reference to the first element in c. undefined if c is empty
c[n]        | returns a reference to the element indexed by the unsigned integral value n. undefined if n >= c.size()
c.at(n)     | returns a reference to the element indexed by n. if the index is out of range, throws an out_of_range exception

##### The access members return references
If the container is a const, the return will be a reference to const

##### Subscripting and safe random access
If wanting to ensure the index is valid, use `at` member instead.

#### 9.3.3 Erasing Elements

|| `erase` Operations on Sequential Containers (not valid for array)
-|------------------------------------------------------------------
c.pop_back()    | removes last element. undefined if c is empty. returns void (not for forward_list)
c.pop_front()   | removes first element. undefined if empty. returns void (not for vector and string)
c.erase(p)      | removes the element denoted by iterator p and returns an iterator to the one after the deleted
c.erase(b, e)   | removes the range denoted by iterator b and e. returns an iterator to the element after the last one that was deleted
c.clear()       | removes all the elements in c. return void

> Removing elements anywhere but the beginning or end of a `deque` invalidates all iterators, references and pointers.  
> (for vector or string, invalidates the after deleted elements.)

##### The pop operations return void, so if needing the value, must store befor pop

#### 9.3.4 Specialized `forward_list` Operations

To add or remove a element in a forward_list, it needs to access the predecessor.  
So instead, the list have different operations of add and remove

|| Operations to Insert or Remove Elements in a forward_list
-|----------------------------------------------------------
lst.before_begin()          | iterator denoting the nonexistent element just before the beginning of the list
lst.cbefore_begin()         | const version
lst.insert_after(p, t)      | inserts elements **after** the one denoted by p. returns an iterator to the last inserted element.
lst.insert_after(p, n, t)   | n is a count, t is an object
lst.insert_after(p, b, e)   | b, e are iterators
lst.insert_after(p, il)     | il ia a braced list. undefined if p is off-the-end
emplace_after(p, args)      | Uses args to construct an element after p
lst.erase_after(p)          | removes the element **after** p. returns an iterator to after the one deleted, or off-the-end. undefined if p denotes the last or o-t-e
lst.erase_after(b, e)       | removes the range from the one **after** b up to but **not including** the one denoted by e

#### 9.3.5 Resizing a Container

|| Sequential Constainer Size Operations (not valid for array)
-|--------------------------------------
c.resize(n)     | resize c so that it has n elements. if n < c.size(), the excess elements are discarded. if new elements must be added, they are value initialized.
c.resize(n, t)  | resize c to have n elements. any elements added have value t

> If resize() shrinks the container, then iterators, references, and pointers to the deleted elements are invalidated; resize on a vector, string, deque potentially invalidates all iterators, & and *.

#### 9.3.6 Container Operations May Invalidate Iteraors

**Invalidating iterators, references and pointers:**

After adding elements to a container:
- `vector` `string` : invalidating the after ones. invalidating all if reallocated
- `deque` : invalidating all if added to middle. invalidating iterators but not ref and ptr if added at front or back
- `list` `forward_list` : remain valid

After removing an element:
- `list` `f_list` : remain valid
- `deque` : invalidated all if removed at middle. invalidate o-t-e iterator if remove at back. invalidate nothing if removing at front
- `vector` `string` : remain valid before the removal point

##### Writing loops that change a container

##### Avoid storing the iterator returned from end()

------------------------------------------------------------------

### 9.4 How a `vector` Grows

> In fact, its performance is good enough that in practice a vector usually grows more efficiently than a list or a deque, even though the vector has to move all of its elements each time it reallocates memory.

##### Members to manage capacity

|| Container Size Management (for `vector` and `string`)
-|------------------------------------------------------
c.shrink_to_fit()   | request to reduce capacity() to equal size(). (also for deque)
c.capacity()        | number of elements c can have before reallocation is necessary
c.reserve(n)        | allocate space for at least n elements

> Every implementation is required to follow a strategy that ensures that it is efficient to use push_back to add elements to a vector.  
> The execution time of creating an n-element vector by calling push_back n times on an initially empty vector must never be more than a constant multiple of n.

-------------------------------------------------------------

### 9.5 Additional `string` Operations

#### 9.5.1 Other Ways to Construct `string`s

|| Additional Ways to Construct strings
-|-------------------------------------
|| n, len2 and pos2 are all unsigned values
string s(cp, n);    | s is a copy of the first n characters in the array to which cp points. that array must have at least n characters
string s(s2, pos2); | s is a copy of characters in string s2 starting at the index pos2. undefined if pos2 > s2.size()
string s(s2, pos2, len2);   | s is a copy of len2 characters from s2 starting at pos2

##### The `substr` operation

|| Substring Operation
-|--------------------
s.substr(pos, n)    | return a string containing n characters from s starting at pos. pos defaults to 0. n defaults to a value that causes the library to copy all

#### 9.5.2 Other Ways to Change a `string`

|| Operations to Modify `string`s
-|-------------------------------
s.insert(pos, args)     | insert characters specified by args before pos. pos can be an index or an iterator. version taking index returns ref; the other returns iterator
s.erase(pos, len)       | remove len characters starting at position pos. if len omitted, remove till the end. returns ref
s.assign(args)          | replace characters in s according to args. returns ref
s.append(args)          | append args to s. returns a ref
s.replace(range, args)  | remove range of characters from s and replace them with args. range is either an index and a length or a pair of iterators into s. returns ref
|| args can be one of the following: append and assign can use all forms
|| str must be distinct from s and the iterators b and e may not refer to s
str             | string
str, pos, len   | up to len chars from str starting at pos
cp, len         | up to len chars from the array pointed to by cp
cp              | null-terminated array 
n, c            | n copies of char c
b, e            | in the range by iter b and e
initializer list| comma-separated list of chars enclosed in brace

##### args for replace and insert depend on how range or pos is specified
||||||
:---------------:|:------------:|:-----------:|:------------:|:----------:
replace          | replace      | insert      | insert       | args can be
(pos, len, args) | (b, e, args) | (pos, args) | (iter, args) |
yes              | yes          | yes         | no           | str
yes              | no           | yes         | no           | str, pos, len
y|y|y|n|cp, len
y|y|n|n|cp
y|y|y|y|n, c
n|y|n|y|b2, e2
n|y|n|y|initializer list

##### The many overloaded ways to change a string

#### 9.5.3 `string` Search Operations

- search operations return the index of the disired character or `npos` (unsigned -1) if not found

|| `string` Search Operations
-|---------------------------
s.find(args)            | find the first occurrence of args in s
s.rfind(args)           | find the last occurrence of args
s.find_first_of(args)   | find the first occurence of any character from args in s
s.find_last_of(args)    | find last occurrence of any character from args
s.find_first_not_of(args)   | find the first character in s that is not in args
s.find_last_not_of(args)| find the last character in s that is not in args

|| `args` must be one of
-|----------------------
c, pos      | look for the char c starting at position posin s. pos defaults to 0
s2, pos     | look for the string s2 starting at position pos in s. pos defaults to 0
cp, pos     | look for the C-style null-teminated string pointed to by cp. 
cp, pos, n  | look for the first n characters in the array pointed to by cp. no default for pos and n

##### To loop through a string finding all occurrence:
```cpp
string::size_type pos = 0;
while ((pos = name.find_first_of(numbers, pos)) != string::npos)
{
    cout << "found number at index: " << pos << " element is " << name[pos] << endl;
    ++pos;
}
```

#### 9.5.4 The `compare` Functions

|| Possible Arguments to `s.compare()`
-|------------------------------------
s2                      | compare s to s2
po1, n1, s2             | compares n1 chars starting at pos1 from s to s2
pos1, n1, s2, po2, n2   | compares n1 chars starting at pos1 from s1 to the n2 cahrs starting at pos2 in s2
cp                      | compares s to array string cp (or pointer)
pos1, n1, cp            | compares n1 chars at pos1 to cp
pos1, n1, cp, n2        | compares n1 chars at pos1 in s to n2 chars starting from the pointer cp

#### 9.5.5 Numeric Conversions

`C++11` introduced several functions that convert between numeric data and library strings:
|| Conversions between `string` and Numbers
-|-----------------------------------------
to_string(val); | overloaded functions returning the string representation of val. val can be any arithmetic type
stoi(s, p, b)   | return the initial substring of s that has numeric content as an int, 
stol(s, p, b)   | long
stoul(s, p, b)  | unsigned long, long long, unsigned long long.
stoll(s, p, b)  | b indicates the numeric base to use for the conversion. defaulted 10
stoull(s, p, b) | p is a pointer to a size_t in which to put the index of the first nonnumeric character in s.
||p defaults to 0, in which case the function does not store the index
stof(s, p)      | return the initial numeric substring in s as float, double or long double
stod(s, p)      | 
stold(s, p)     | p has the same behavior as integer

- when converting to number, the first non-whitespace char in s must be a char that can appear in a number (numbers and `+-.`):  
`d = stod(s2.substr(s2.find_first_of("+-.0123456789")));`

--------------------------------------------------------------------

### 9.6 Container Adaptors (`stack` `queue` `priority_queue`)

> Essentially, an adaptor is a mechanism for making one thing cat like another. A container adaptor takes an existing container type and makes it act like a different type.

|| Operations and Types Common to the Container Adaptors
-|------------------------------------------------------
size_type   | Type large enough to hold the largest object
value_type  | element type
container_type  | type of the underlying container on which the adaptor is implemented
A a;        | create a new empty adaptor named a
A a(c);     | create a new adaptor named a with a copy of the container c
relational operators    | each adaptor supports all the relational operators. return the result of comparing containers
a.empty()   | 
a.size()    | 
swap(a, b)  | a and b must have the same type, including the type of the container
a.swap(b)   |

##### Defining an adaptor
- By default both `stack` and `queue` are implemented in terms of deque
- `priority_queue` is implemented on a vector
- can override the default:  
`stack<int, vector<int>> istk;`

|     | vector | deque | list
------|:------:|:-----:|:----:
stack | y      | y     | y
queue |        | y     | y
pri_q | y      | y     | 

##### Stack Adaptor (defined in `stack`)

|| Stack Operations in Addition to Common Operations
-|--------------------------------------------------
s.pop()         | removes, but does not return, the top element from the stack
s.push(item)    | creates a new top element on stack by copying or moving item,
s.emplace(args) | or by constructing the element from args
s.top()         | returns, but does not remove, the top element

##### Queue Adaptors

|| queue, priority_queue Operations in Addition to Common ones
-|------------------------------------------------------------
q.pop()     | removes, but not return, the front element or highest-priority element
q.front()   | returns, but not remove, the front element of q. for queue
q.back()    | the back element. valid only for queue
q.top()     | returns, not remove, the highest-priority element. (valid for pri_q)
q.push(item)| create an element with value item or constructed from args at the end
q.emplace(args) | of the queue or in its appropriate position in pri_q

----------------------------------------------------------------