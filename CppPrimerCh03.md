C++ Primer Notas de Estudio
===========================
Ad  
init: Apr22.2018

Chapter3 Strings, Vectors, and Arrays
-------------------------------------
### 3.1 Namespace `using` Declarations
**The safest way** to use `using` is a `using declaration` for each name:  
`using namespace::name;`  
**Headers** should not include `using`

### 3.2 Library `string` Type
#### 3.2.1
Direct Initialization
|||
-|-
string s1           | Default initialization, empty
string s2(s1)       | s2 is a copy of s1
string s3("str")    | s3 is a copy of the string literal
string s4(n, 'c')   | s4 initialized with n copies of 'c'
string s5{"str"}    | New standard way?

Copy Initialization
|||
-|-
string s2 = s1      | The same as s2(s1)
string s3 = "str"   | Equivalent to s3("str")
string s4 = string(n, 'c') | No compensating advantages

#### 3.2.2
Operations on string
|||
-|-
os << s         | Writes `s` onto output stream `os`. Returns `os`
is << s         | Reads whitespace-separated string from `is` into `s`. Returns `is`
getline(is, s)  | Reads a line of input from `is` into `s` . Returns `is`
s.empty()       | Returns `true` or `false` depends on whether `s` is empty
s.size()        | Returns number of characters with `string::size_type` (unsign)
s[n]            | Returns a reference to the `char` in position n
s1 + s2         | Returns a `string` that is the concatenation of `s1` and `s2`
s1 = s2         | Replaces `s1` with a copy of `s2`
==, !=          | Returns `true` or `false`
<, <=, >, >=    | Comparisons are case-sensitive and use dictionary ordering

using `+` to add a `string` and literal/string literal, ++at least one `string` for each `+`++ (including the `string` yielded by subexpression (i.e. `s + " "`))

**string literal differs from library `string`**

#### 3.2.3
Use C library by `cname` not `name.h`, that defined in `std` namespace

`<cctype>`  | Functions
-|-
isalnum()   | is a letter or a digit
isalpha()   | is a letter
iscntrl()   | is a control character
isdigit()   | is a digit
isgraph()   | is not a space but is printable
islower()   | is a lowercase letter
isprint()   | is a printable character (including spcae)
ispunct()   | is a punctuation character
isspace()   | is whitespace (space/tab/vertical tab/return/newline/formfeed)
isupper()   | is an uppercase letter
isxdigit()  | is a hexadecimal digit
tolower()   | return the lowercase equivalent or the unchanged
toupper()   | return the uppercase equivalent or the unchanged

`C++11` Use **range for** statement to iterate through ++every elements++ in a sequence and perform some operation on each value in the sequence:
```cpp
for (declaration : expression) {statement}
//  for example
string str{"Hello"};
for (auto c : str)
    cout << c << endl;
```
Must define the loop variable as a **reference** if want to ++change++ the value in the string

Using a subsript for iteration
```cpp
//  change the first word to uppercase
string s{"some string"};
if (!s.empty())
    for (decltype(s.size()) index{0}; index != s.size() && !isspace(s[index]); ++index)
        s[index] = toupper(s[index]);
```

### 3.3 Library `vector` Type
- `vector` is a **container**
- `vector` is a **class template**: use `< >` to specify the type
- can hold `vector`
- cannot hold `reference`

**Instantiation**: The process that the compiler uses to create classes or functions from templates.

Before `C++11` , the old-style declaration for a `vector` of `vevtors` :  
`vector<vector<int> >` rather than `vector<vector<int>>`

#### 3.3.1 
Define `vector`||
-|-
vector<T> v1        | `vector` holds objects of type `T`. Default initializaiton, v1 is empty
vector<T> v2(v1)    | v2 has a copy of v1
vector<T> v2 = v1   | The same as above
vector<T> v3(n, val)| v3 has `n` elements with value `val`
vector<T> v4(n)     | v4 has n copies of a value-initialized object
vector<T> v5{a, b}  | v5 has many elements as there are initializers
vector<T> v5 = {a, b}| Equivalent to above

> ```cpp
> // 2. cast an array to a vector
> int a[5] = {0, 1, 2, 3, 4};
> vector<int> v4(a, *(&a + 1));
> ```
> (LeetCode)

- List initialization: `vector<int> iv{1,2,3};`
- Value initialization: `vector<int> iv(10);`

When using `{ }` to initialize, if list initialization is not available, the compiler will look for other ways to initialize:  
`vector<string> sv{10,'X'};` is equal to using `( )`

#### 3.3.2 Use `vec.push_back()` to add elements to `vector`

`vector` grows efficiently, Using a empty `vector` is even efficient than using a expected sized `vector` (not like C/Java)

Cannot use range `for` to add elements to `vector` (The body of a range for must not change the size of the loop sequence)

#### 3.3.3
`vector` Operations
|||
-|-
v.empty()   | If v is empty.
v.size()    | Returns the elements number.
v.push_back(t) | Adds an element to end
v[n]        | Return a reference to the element at position n.
v1 = v2     | Replaces v1 with elements in v2.
v1 = {a, b...} | Replaces v1 with the list.
v1 ==/!= v2 | If v1 and v2 are equal.
<, <=, >, >=| Comparison.

- Subcripting does not add elements (compiler cannot detect)

### 3.4 Introducing Iterators
#### 3.4.1
Iterators are used to access the elements in containers

- `v.begin()` returns an iterator that denotes the first element  
- `v.end()` returns that denotes the **"one past the end"**
- If the container is empty, begin() and end() return the same
- The types are `vector<int>::iterator` or `vector<int>::const_iterator`

|||
-|-
*iter       | Return a reference to the element denoted by the iterator `iter`
iter->mem   | Dereference `iter` and fetches the member named `mem` from the underlying element. Equivalent to `(*iter).mem`
++iter      | Increments `iter` to refer to the next element in the container
--iter      | Decrements `iter`
iter1 == iter2 | If the two iterators denotes the same element or the off-the-end iterator for the same container
iter1 != iter2 |

> C++ programmers use `!=` as a matter of habit, rather than `<` in C/Java, for the containers always have `==` and `!=` , not the `<` .

`C++11` `v.cbegin()` and `v.cend()` return the `const_iterator`

#### 3.4.2 Iterator Arithmetic (vector and string)
|||
-|-
iter + n    | Adding
iter - n    | Subtracting
iter += n   | Coumpound-assignment for iterator addition
iter -= n   | subtraction
iter1 - iter2 | yields the distance of the two elements, with a type of `difference_type`
<, <=, >, >= | Relational operators

### 3.5 Arrays
#### 3.5.1
- the dimension of array must be const experssion
- initialiaze character array with string literal (remember the `\0` at the end of a string literal)
- No copy initialization or assignment

Declarations
```cpp
int *ptrs[10];              //  a array of ten pointers to integer
int &refs[10]{/* ? */};     //  error
int (*ptrArr)[10]{&arr};    //  a pointer to an array of ten integers
int (&refArr)[10]{arr};     //  a reference to an array of ten integers
int *(&refPtrs)[10]{ptrs};  //  a reference to an array of ten pointers to integer
```

#### 3.5.2
- the subscript of a array is defined with type `size_t` (in header`cstddef`)

#### 3.5.3
> In most expressions, when we use an object of array type, we are really using a pointer to the first element in that array.

Use `auto` to define an object with an initializer of a array, will get a pointer  
While using `decltype` will give an array. (arrays cannot assigned by pointer)

Pointers to array support operations as iterators on vector/string  
(To add, subtract and compare)

- To get the `off-the-end` pointer: `int *p = &arr[10]` (arr has 10 elements)

##### `C++11` supplies `begin()` and `end()` functions in the header `<iterator>`  
to help to get the first and one past last position of an array (return pointers)

The subtraction between two pointers yields an object with type `ptrdiff_t` defined in `cstddef`

> Unlike subscripts for vector and string, the index of the bult-in subscript operator is not an unsigned type (which means the subscript can be negative)

#### 3.5.4
C-style character strings functions (in `cstring`)
|||
-|-
strlen(p)   | Returns the length, not counting the `null`
strcmp(p1, p2)  | Returns 0 if ==, positive if >, negative if <
strcat(p1, p2)  | Appends p2 to p1 and returns p1
strcpy(p1, p2)  | Copies p2 into p1 and returns p1

#### 3.5.5
Interfaces to C:
- Use a null-terminated character array to initialize or assign a `string`
- Use a null-terminated character array as one operand to the `string` operations
- `const char *pstr = str.c_str();` returns a C-style character string

Using an array to initialize a `vector`
```cpp
int iarr[]{0, 1, 2, 3, 4, 5};
vector<int> ivec(begin(iarr), end(iarr));
vector<int> subVec(iarr + 1, iarr +4);
```

### 3.6 Multidimensional arrays
> In a two-dimensional array, the first dimensional is usually referred to as the row and the second as the column.

Use a range for to iterate a multidimensional array
```cpp
size_t cnt{0};
for (auto &row : ia)        //  notice the reference using
    for (auto &col : row)
        col = cnt;
        ++cnt;
```

> To use a multidimensional array in a range for, the loop control variable for all but the innermost array must be references.

- `int *ip[4];` : array of pointers to int
- `int (*ip)[4];` : pointer to an array of 4 ints

Use pointers to iterate arrays
```cpp
for (auto p = ia; p != ia + 3; ++p)
{
    for (auto q = *p; q != *p +4; ++q)  //  notice the *p
        cout << *q << ' ';
    cout << endl;
}
//  in a esier way
for (auto p = begin(ia); p != end(ia); ++p)
{
    for (auto q = begin(*p); q != end(*p); ++q)
        cout << *q << ' ';
    cout << endl;
}
```
