CppPrimer-Ch17-LibFacilities.md

C++ Primer Notes
================================================================================

Ad147  
<ar><r>

init: 18Nov06/19Jan24

Chapter 17 Specialized Library Facilities
--------------------------------------------------------------------------------

- [Chapter 17 Specialized Library Facilities](#chapter-17-specialized-library-facilities)
  - [17.1 The `tuple` Type](#171-the-tuple-type)
    - [17.1.1 Defining and Initializing `tuple`s](#1711-defining-and-initializing-tuples)
    - [17.1.2 Using a `tuple` to Return Multiple Values](#1712-using-a-tuple-to-return-multiple-values)
  - [17.2 The `bitset` Type](#172-the-bitset-type)
    - [17.2.1 Defining and Initializing `bitset`s](#1721-defining-and-initializing-bitsets)
    - [17.2.2 Operations on `bitset`s](#1722-operations-on-bitsets)
  - [17.3 Regular Expressions](#173-regular-expressions)
    - [17.3.1 Using the Regular Expression Library](#1731-using-the-regular-expression-library)
    - [17.3.2 The Match and Regex Iterator Types](#1732-the-match-and-regex-iterator-types)
    - [17.3.3 Using Subexpressions](#1733-using-subexpressions)
    - [17.3.4 Using `regex_replace`](#1734-using-regexreplace)
  - [17.4 Random Numbers](#174-random-numbers)
    - [17.4.1 Random-Number Engines and Distribution](#1741-random-number-engines-and-distribution)
    - [17.4.2 Other Kinds of Distributions](#1742-other-kinds-of-distributions)
  - [17.5 The IO Library Revisited](#175-the-io-library-revisited)
    - [17.5.1 Formatted Input and Output](#1751-formatted-input-and-output)
    - [17.5.2 Unformatted Input/Output Operations](#1752-unformatted-inputoutput-operations)
    - [17.5.3 Random Access to a Stream](#1753-random-access-to-a-stream)
  - [Chapter Summary](#chapter-summary)

--------------------------------------------------------------------------------

The latest standard greatly increased the size and scope of the library.  
Indeed, theportion of the standard devoted to the library more than doubled between the firstrelease in 1998 and the 2011 standard.  
As a result, covering every C++ library class iswell beyond the scope of this Primer.

### 17.1 The `tuple` Type

A tuple is a template that is similar to a pair (§ 11.2.3, p. 426).  
Each pair typehas different types for its members, but every pair always has exactly two members.  
A tuple also has members whose types vary from one tuple type to another, but atuple can have any number of members.  
Each distinct tuple type has a fixednumber of members, but the number of members in one tuple type can differ fromthe number of members in another.

A tuple is most useful when we want to **combine some data into a single object** but do not want to bother to define a data structure to represent those data.  
The tuple type, along with itscompanion types and functions, are defined in the `tuple` header.

###### Operations on tuples

|     | Operation/Description                                                                                                                                                                                                    |
| --- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ |
| op  | `tuple<T1, T2, ..., Tn> t;`                                                                                                                                                                                              |
| >>> | t is a tuple with as many members as there are types T1...Tn. The members are value initialized.                                                                                                                         |
| op  | `tuple<T1, T2, ..., Tn> t(v1, v2, ..., vn);`                                                                                                                                                                             |
| >>> | t is a tuple with types T1...Tn in which each member is initialized from the corresponding initializer vi. This constructor is explicit.                                                                                 |
| op  | `make_tuple(v1, v2, ..., vn)`                                                                                                                                                                                            |
| >>> | Returns a tuple initialized from the given initializers. The type of the tuple is inferred from the types of the initializers.                                                                                           |
| ops | `t1 == t2` `t1 != t2`                                                                                                                                                                                                    |
| >>> | Two tuples are equal if they have the same number of members and if each pair of members are equal. Use each member's underlying `==` operator. Once a member is found to be unequal, subsequent members are not tested. |
| op  | `t1 relop t2`                                                                                                                                                                                                            |
| >>> | Relational operations on tuples using dictionary ordering. The tuples must have the same number of members. Members of t1 are compared with the corresponding members from t2 using the < operator.                      |
| op  | `get<i>(t)`                                                                                                                                                                                                              |
| >>> | Returns a reference to the ith data member of t; if t is an lvalue, the result is an lvalue reference; otherwise, it is an rvalue reference. All members of a tuple are public.                                          |
| op  | `tuple_size<tupleType>::value`                                                                                                                                                                                           |
| >>> | A class template that can be instantiated by a tuple type and has a public constexpr static data member named value of type size_t that is number of members in the specified tuple type.                                |
| op  | `tuple_element<i, tupleType>::type`                                                                                                                                                                                      |
| >>> | A class template that can be instantiated by an integral constant and a tuple type and has a public member named type that is the type of the specified members in the specified tuple type.                             |

> ##### Note
> A tuple can be thought of as a “quick and dirty” data structure.

#### 17.1.1 Defining and Initializing `tuple`s

When we define a tuple, we name the type(s) of each of its members:

```cpp
tuple<size_t, size_t, size_t> threeD; // all three members set to 0
tuple<string, vector<double>, int, list<int>>
    someVal("constants", {3.14, 2.718}, 42, {0,1,2,3,4,5});
```

This tuple constructor isexplicit (§ 7.5.4, p. 296), so we must use the direct initialization syntax:

```cpp
tuple<size_t, size_t, size_t> threeD = {1,2,3}; // error
tuple<size_t, size_t, size_t> threeD {1,2,3};    // ok
```

Alternatively, similar to the make_pair function (§ 11.2.3, p. 428), the library defines a `make_tuple` function that generates a tuple object:

```cpp
// tuple that represents a bookstore transaction: ISBN, count, price per book
auto item = make_tuple("0-999-78345-X", 3, 20.00);
```

##### Accessing the Members of a tuple

A pair always has two members, which makes it possible for the library to give these members names (i.e., first and second).  
No such naming convention is possible for tuple because there is no limit on the number of members a tuple type can have.  
As a result, the members are unnamed.  
Instead, we access the members of a tuple through a library function template named `get`.  
To use get we must specify an explicit template argument (§ 16.2.2, p. 682), which is the position of the member we wantto access.  
We pass a tuple object to get, which returns a reference to the specified member:

```cs
auto book = get<0>(item);       // returns the first member of item
auto cnt = get<1>(item);        // returns the second member of item
auto price = get<2>(item)/cnt;  // returns the last member of item
get<2>(item) *= 0.8;            // apply 20% discount
```

The value inside the brackets must be an integral constant expression (§ 2.4.4, p. 65).  
As usual, we count from 0, meaning that get<0> is the first member.

If we have a tuple whose precise type details we don’t know, we can use two auxilliary class templates to find the number and types of the tuple’s members:

```cs
typedef decltype(item) trans;                       // trans is the type of item
// returns the number of members in object's of type trans
size_t sz = tuple_size<trans>::value;               // returns 3
// cnt has the same type as the second member in item
tuple_element<1, trans>::type cnt = get<1>(item);   // cnt is an int
```

To use `tuple_size` or `tuple_element`, we need to know the type of a tuple object.  
As usual, the easiest way to determine an object’s type is to use `decltype` (§2.5.3, p. 70).  
Here, we use decltype to define a type alias for the type of item, which we use to instantiate both templates.

tuple_sizehas a public static data member named value that is thenumber or members in the specified tuple.  
The tuple_element template takes anindex as well as a tuple type.  
tuple_element has a public type member namedtype that is the type of the specified member of the specified tuple type.  
Like get,tuple_element uses indices starting at 0.

##### Relational and Equality Operators

The tuple relational and equality operators behave similarly to the corresponding operations on containers (§ 9.2.7, p. 340).  
These operators execute pair wise on the members of the left-hand and right-hand tuples.  
We can compare two tuples only if they have the same number of members.  
Moreover, to use the equality or inequality operators, it must be legal to compare each pair of members using the `==` operator; to use the relational operators, it must be legal to use `<`.  

> ##### Note
> Because tuple defines the `<` and `==` operators, we can pass sequences of tuples to the algorithms and can use a tuple as key type in an ordered container.

#### 17.1.2 Using a `tuple` to Return Multiple Values

A common use of tuple is to return multiple values from a function.

##### 1) A Function That Returns a tuple

##### 2) Using a tuple Returned by a Function

--------------------------------------------------------------------------------

### 17.2 The `bitset` Type

#### 17.2.1 Defining and Initializing `bitset`s

###### Ways to Initialeze a `bitset`

##### 1) Initializing a `bitset` from an `unsigned` Value

##### 2) Initializing a `bitset` from a `string`

> ##### Note
> The indexing conventions of `string`s and `bitset`s are inversely related: The character in the `string` with the highest subscript (the rightmost character) is used to initialize the low-order bit in the `bitset` (the bit with subscript 0).  
> When you initialize a bitset from a string, it is essential to remember this difference.

#### 17.2.2 Operations on `bitset`s

###### `bitset` Operations

##### 1) Retrieving the Value of a `bitset`

> ##### Note
> These operations throw an `overflow_error` exception (§ 5.6, p. 193) if the value in the `bitset` does not fit in the specified type.

##### 2) `bitset` IO Operators

##### 3) Using `bitset`s

--------------------------------------------------------------------------------

### 17.3 Regular Expressions

###### Regular Expression Library Components

###### Arguments to `regex_search` and `regex_match`

#### 17.3.1 Using the Regular Expression Library

##### 1) Specifying Options fro a `regex` Object

###### `regex` (and `wregex`) Operations

##### 2) Errors in Specifying or Using a Regular Expression

> ##### Note
> It is important to realize that the syntactic correctness of a regular expressionis evaluated at run time.

###### Regular Expression Error Conditions

> ##### Advice: Avoid Creating Unnecessary Regular Expressions
> As we’ve seen, the “program” that a regular expression represents is compiled at run time, not at compile time.  
> Compiling a regular expression can be a surprisingly slow operation, especially if you’re using the extended regular-expression grammar or are using complicated expressions.  
> As aresult, constructing a regex object and assigning a new regular expression to an existing regex can be time-consuming.  
> To minimize this overhead, youshould try to avoid creating more regex objects than needed.  
> In particular,if you use a regular expression in a loop, you should create it outside the loop rather than recompiling it on each iteration.

##### 3) Regular Expression Classes and the Input Sequence Type

###### Regular Expression Library Classes

#### 17.3.2 The Match and Regex Iterator Types

###### `sregex_iterator` Operations

##### 1) Using an `sregex_iterator`

###### Using an `sregex_iterator`

##### 2) Using the Match Data

###### `smatch` Operations

###### Submatch Operations

###### The `smatch` Object Representing a Particular Match

#### 17.3.3 Using Subexpressions

##### 1) Subexpression for Data Validation

##### 2) Using the Submatch Operations

#### 17.3.4 Using `regex_replace`

###### Regular Expression Replace Operations

##### 1) Replacing Only Part of the Input Sequence

##### 2) Flags to Control Matches and Formatting

###### Match Flags

##### 3) Using Format Flags

--------------------------------------------------------------------------------

### 17.4 Random Numbers

Prior to `C++11`, both C and C++ relied on library `rand`.

Therand function has several problems: Many, if not most, programs need randomnumbers in a different range from the one produced by rand.  
Some applications require random floating-point numbers.  
Some programs need numbers that reflect anonuniform distribution.  
Programmers often introduce nonrandomness when they tryto transform the range, type, or distribution of the numbers generated by rand.

The random-number library, defined in the random header, solves these problems through a set of cooperating classes: **random-number engines** and **random-number** distribution classes.  
An engine generates a sequence of unsigned random numbers.  
A distribution uses an engine to generate random numbers of a specified type, in a given range, distributed accordingto a particular probability distribution.

###### Random Number Library Components

|              |                                                              |
| ------------ | ------------------------------------------------------------ |
| Engine       | Types that generate a sequence of random `unsigned` integers |
| Distribution | Types that use an engine to return numbers according to      |
|              | a particular probability distribution                        |

> ##### Best Practices
> C++ programs should not use the library `rand` function.  
> Instead, they should use the `default_random_engine` along with an appropriate distribution object.

#### 17.4.1 Random-Number Engines and Distribution

The random-number engines are function-object classes (§ 14.8, p. 571) that define a call operator that takes no arguments and returns a random unsigned number.  
We can generate raw random numbers by calling an object of a random-number enginetype:

```cs
default_random_engine e;  // generates random unsigned integers
for (size_t i = 0; i < 10; ++i)
    // e() "calls" the object to produce the next random number
    cout << e() << " ";
```

Here, we defined an object named `e` that has type `default_random_engine`.  
Inside the `for`, we call the object e to obtain the next random number.

The library defines several random-number engines that differ in terms of their performance and quality of randomness.  
Each compiler designates one of theseengines as the default_random_engine type.  
This type is intended to be the engine with the most generally useful properties.  

###### Random Number Engine Operations

|                       |                                                                    |
| --------------------- | ------------------------------------------------------------------ |
| `Engine e`            | Default constructor; uses the default seed for the engine type     |
| `Engine e(s);`        | Uses the integral value `s` as the seed                            |
| `e.seed(s)`           | Reset the state of the engine using the seed s                     |
| `e.min()` `e.max()`   | The smallest and largest numbers this generator will generate      |
| `Engine::result_type` | The `unsigned` integral type this engine generates                 |
| `e.discard(u)`        | Advance the engine by `u` steps; `u` has type `unsigned long long` |

For most purposes, the output of an engine is not directly usable, which is why we described them earlier as raw random numbers.  
The problem is that the numbers usually span a range that differs from the one we need.  
*Correctly* transforming therange of a random number is surprisingly hard.

##### 1) Distribution Types and Engines

To get a number in a specified range, we use an object of a distribution type:

```cs
// uniformly distributed from 0 to 9 inclusive
uniform_int_distribution<unsigned> u(0,9);
default_random_engine e;        // generates unsigned random integers
for (size_t i = 0; i < 10; ++i)
    // u uses e as a source of numbers
    // each call returns a uniformly distributed value in the specified range
    cout << u(e) << " ";
```

Here we define u as a `uniform_int_distribution<unsigned>`.  
That type generates uniformly distributed unsigned values.  
When we define an object of this type, we can supply the minimum and maximum values we want.  
In this program, `u(0,9)` says that we want numbers to be in the range 0 to 9 inclusive.  
The random number distributions use inclusive ranges so that we can obtain every possible value of the given integral type.

Like the engine types, the distribution types are also function-object classes.  
The distribution types define a call operator that takes a random-number engine as its argument.  
The distribution object uses its engine argument to produce random numbers that the distribution object maps to the specified distribution.

Note that we pass the engine object itself, `u(e)`.  
Had we written the call as `u(e())`, we would have tried to pass the next value generated by e to u, whichwould be a compile-time error.  
We pass the engine, not the next result of the engine,because some distributions may need to call the engine more than once.

> ##### Note
> When we refer to a **random-number generator**, we mean the combination of a distribution object with an engine.

##### 2) Comparing Random Engines and the rand Function

It is worth noting that the outputof calling a `default_random_engine` object is similar to the output of `rand`.  
Engines deliver unsigned integers in a system-defined range.  
The range for rand is 0 to RAND_MAX.  
The range for an engine type is returned by calling the min and maxmembers on an object of that type:  
`cout << "min: " << e.min() << " max: " << e.max() << endl;`  

##### 3) Engines Generate a Sequence of Numbers

Random number generators have one property that often confuses new users:  
Even though the numbers that are generated appear to be random, a given generator returns the same sequence of numbers each time it is run.  
The fact that the sequenceis unchanging is very helpful during testing.  
On the other hand, programs that userandom-number generators have to take this fact into account.

As one example, assume we need a function that will generate a vector of 100 random integers uniformly distributed in the range from 0 to 9.  
We might think we’d write this function as follows:

```cs
// almost surely the wrong way to generate avectorof random integers
// output from this function will be the same 100 numbers on every call!
vector<unsigned> bad_randVec()
{
    default_random_engine e;
    uniform_int_distribution<unsigned> u(0,9);
    vector<unsigned> ret;
    for (size_t i = 0; i < 100; ++i)
        ret.push_back(u(e));
    return ret;
}
```

However, this function will return the same vector every time it is called.

The right way to write our function is to make the engine and associated
distribution objects static (§ 6.1.1, p. 205):

```cs
// returns a vector of 100 uniformly distributed random numbers
vector<unsigned> good_randVec()
{
    // because engines and distributions retain state, they usually should be
    // defined as static so that new numbers are generated on each call
    static default_random_engine e;
    static uniform_int_distribution<unsigned> u(0,9);
    vector<unsigned> ret;
    for (size_t i = 0; i < 100; ++i)
        ret.push_back(u(e));
    return ret;
}
```

Becausee and u are `static`, they will hold their state across calls to the function.  
The first call will use the first 100 random numbers from the sequence u(e)generates, the second call will get the next 100, and so on.

> ##### Warning
> A given random-number generator always produces the same sequence of numbers.  
> A function with a local random-number generator should make that generator (both the engine and distribution objects) `static`.  
> Otherwise, the function will generate the identical sequence on each call.

##### 4) Seeding a Generator

The fact that a generator returns the same sequence of numbers is helpful during debugging.  
However, once our program is tested, we often want to cause each run of the program to generate different random results.  
We do so by providing a seed.  
A seed is a value that an engine can use to cause it to start generating numbers at a new point in its sequence.

We can seed an engine in one of two ways:

- Provide the seed when creating an engine object
- Call the engine’s seed member

```cs
default_random_engine e1;               // uses the default seed
default_random_engine e2(2147483646);   // use the given seed value
// e3 and e4 will generate the same sequence because they use the same seed
default_random_engine e3;               // uses the default seed value
e3.seed(32767);                         // call seed to set a new seed value
default_random_engine e4(32767);        // set the seed value to 32767

for (size_t i = 0; i != 100; ++i)
{
    if (e1() == e2()) { cout << "unseeded match at iteration: " << i << endl; }
    if (e3() != e4()) { cout << "seeded differs at iteration: " << i << endl; }
}
```

Here we define four engines.  
The first two, e1 and e2, have different seeds andshould generate different sequences.  
The second two, e3 and e4, have the sameseed value.  
These two objects will generate the same sequence.

Picking a good seed, like most things about generating good random numbers, is surprisingly hard.  
Perhaps the most common approach is to call the system `time` function.  
This function, defined in the `ctime` header, returns the number of seconds since a given epoch.  
The time function takes a single parameter that is a pointer to a structure into which to write the time.  
If that pointer is null, the function just returnsthe time:

```cs
default_random_engine e1(time(0));  // a somewhat random seed
```

Because time returns time as the number of seconds, this seed is useful only for applications that generate the seed at second-level, or longer, intervals.  

> ##### Warning
> Usingtime as a seed usually doesn’t work if the program is run repeatedlyas part of an automated process;  
> it might wind up with the same seedseveral times.


#### 17.4.2 Other Kinds of Distributions

The engines produce unsigned numbers, and each number in the engine’s range has
the same likelihood of being generated.  
Applications often need numbers of different types or distributions.  
The library handles both these needs by defining different distributions that, when used with an engine, produce the desired results.  


###### Distribution Operations

|             |                                                                              |
| ----------- | ---------------------------------------------------------------------------- |
| Dist d;     | Dedault constructor; makes d ready to use.                                   |
|             | Other constructors depend on the type of Dist; see A.3                       |
|             | The distribution constructors are `explicit`.                                |
| d(e)        | Successive calls with the same e produce a sequence of random numbers        |
|             | according to the distribution type of d; e is a random-number engine object. |
| d.min/max() | Return the smallest and largest numbers d(e) will generate.                  |
| d.reset()   | Reestablish the state of d so that subsequent uses of d dont                 |
|             | depend on values d has already generated.                                    |


##### 1) Generating Random Real Numbers

Programs often need a source of random floating-point values.  
In particular, programs frequently need random numbers between zero and one.

The most common, but *incorrect*, way to obtain a random floating-point from `rand` is to divide the result of rand() by RAND_MAX, which is a system-defined upper limitthat is the largest random number that rand can return.  
This technique is incorrect because random integers usually have less precision than floating-point numbers, in which case there are some floating-point values that will never be produced as output.

With the new library facilities, we can easily obtain a floating-point random number.  
We define an object of type uniform_real_distribution and let the libraryhandle mapping random integers to random floating-point numbers.  
As we did foruniform_int_distribution, we specify the minimum and maximum values whenwe define the object:

```cs
default_random_engine e; // generates unsigned random integers
// uniformly distributed from 0 to 1 inclusive
uniform_real_distribution<double> u(0,1);

for (size_t i = 0; i < 10; ++i)
    cout << u(e) << " ";
```

This code is nearly identical to the previous program that generated unsigned values.  
However, because we used a different distribution type, this version generates different results.


##### 2) Using the Distribution’s Default Result Type

With one exception, which we’ll cover in § 17.4.2 (p. 752), the distribution types are templates that have a single template type parameter that represents the type of the numbers that the distribution generates.  
These types always generate either afloating-point type or an integral type.

Each distribution template has a default template argument (§ 16.1.3, p. 670).  
The distribution types that generate floating-point values generate double by default.  
Distributions that generate integral results use int as their default.  
Because the distribution types have only one template parameter, when we want to use the defaultwe must remember to follow the template’s name with empty angle brackets to signify that we want the default (§ 16.1.3, p. 671):

```cs
// empty<> signify we want to use the default result type
uniform_real_distribution<> u(0,1); // generates doubleby default
```


##### 3) Generating Numbers That Are Not Uniformly Distributed

In addition to correctly generating numbers in a specified range, another advantage ofthe new library is that we can obtain numbers that are nonuniformly distributed.  
Indeed, the library defines 20 distribution types! These types are listed in § A.3 (p.882).

As an example, we’ll generate a series of normally distributed values and plot the resulting distribution.  
Because `normal_distribution` generates floating-point numbers, our program will use the `lround` function from the `cmath` header to round each result to its nearest integer.  
We’ll generate 200 numbers centered around amean of 4 with a standard deviation of 1.5.  
Because we’re using a normal distribution,we can expect all but about 1 percent of the generated numbers to be in the rangefrom 0 to 8, inclusive.  
Our program will count how many values appear that map tothe integers in this range:

```cs
default_random_engine e;        // generates random integers
normal_distribution<> n(4,1.5); // mean 4, standard deviation 1.5
vector<unsigned> vals(9);       // nine elements each 0
for (size_t i = 0; i != 200; ++i)
{
    unsigned v = lround(n(e));  // round to the nearest integer
    if (v < vals.size())        // if this result is in range
        ++vals[v];              // count how often each number appears
}

for (size_t j = 0; j != vals.size(); ++j)
    cout << j << ": " << string(vals[j], '*') << endl;
```

We start by defining our random generator objects and a vector named vals.  
We’ll use vals to count how often each number in the range 0 . . . 9 occurs.  
Unlike most of our programs that use vector, we allocate vals at its desired size.  
By doing so,we start out with each element initialized to 0.

Inside the for loop, we call lround(n(e)) to round the value returned by n(e)to the nearest integer.  
Having obtained the integer that corresponds to our floating-point random number, we use that number to index our vector of counters.  
Becausen(e) can produce a number outside the range 0 to 9, we check that the number we got is in range before using it to index vals.  
If the number is in range, we incrementthe associated counter.

When the loop completes, we print the contents of vals, which will generate outputsuch as

```sh
0: ***
1: ********
2: ********************
3: **************************************
4: **********************************************************
5: ******************************************
6: ***********************
7: *******
8: *
```

Here we print a string with as many asterisks as the count of the times the current value was returned by our random-number generator.  
Note that this figure is not perfectly symmetrical.  
If it were, that symmetry should give us reason to suspect the quality of our random-number generator.


##### 4) The `bernoulli_distribution` Class

We noted that there was one distribution that does not take a template parameter.  
That distribution is the bernoulli_distribution, which is an ordinary class, not a template.  
This distribution always returns a bool value.  
It returns true with a given probability.  
By default that probability is .5.

As an example of this kind of distribution, we might have a program that plays agame with a user.  
To play the game, one of the players—either the user or the program—has to go first.  
We could use a `uniform_int_distribution` object witha range of 0 to 1 to select the first player.  
Alternatively, we can use a Bernoulli distribution to make this choice.  
Assuming that we have a function named play thatplays the game, we might have a loop such as the following to interact with the user:

```cs
string resp;
default_random_engine e;    // e has state, so it must be outside the loop!
bernoulli_distribution b;   // 50/50 odds by default
do
{
    bool first = b(e);      // if true, the program will go first
    cout << (first ? "We go first"
                   : "You get to go first") << endl;
    // play the game passing the indicator of who goes first
    cout << ((play(first)) ? "sorry, you lost"
                           : "congrats, you won") << endl;
    cout << "play again? Enter 'yes' or 'no'" << endl;
} while (cin >> resp && resp[0] == 'y');
```

We use a do while (§ 5.4.4, p. 189) to repeatedly prompt the user to play.

> ##### Warning
> Because engines return the same sequence of numbers (§ 17.4.1, p. 747), itis essential that we declare engines outside of loops.  
> Otherwise, we’d createa new engine on each iteration and generate the same values on eachiteration.  
> Similarly, distributions may retain state and should also be definedoutside loops.

One reason to use a `bernoulli_distribution` in this program is that doing so lets us give the program a better chance of going first:

```cs
bernoulli_distribution b(.55); // give the house a slight edge
```

If we use this definition for b, then the program has 55/45 odds of going first.

--------------------------------------------------------------------------------

### 17.5 The IO Library Revisited

- format control
- unformatted IO
- random access


#### 17.5.1 Formatted Input and Output

The library defines a set of **manipulators** (§ 1.2, p. 7), listed in Tables 17.17 (p.757) and 17.18 (p. 760), that modify the format state of a stream.  
A manipulator is afunction or object that affects the state of a stream and can be used as an operand toan input or output operator.  
Like the input and output operators, a manipulator returns the stream object to which it is applied, so we can combine manipulators and data in a single statement.

Our programs have already used one manipulator, `endl`, which we “write” to an output stream as if it were a value.  
But endl isn’t an ordinary value; instead, it performs an operation:  
It writes a newline and flushes the buffer.


##### 1) Many Manipulators Change the Format State

Manipulators are used for two broad categories of output control:
- controlling the presentation of numeric values
- controlling the amount and placement of padding

Most of the manipulators that change the format state provide set/unset pairs; one manipulator sets the format state to a new value and the other unsets it, restoring the normal default formatting.

> ##### Warning
> Manipulators that change the format state of the stream usually leave the format state changed for all subsequent IO.

The fact that a manipulator makes a persistent change to the format state can be useful when we have a set of IO operations that want to use the same formatting.  
Indeed, some programs take advantage of this aspect of manipulators to reset thebehavior of one or more formatting rules for all its input or output.  
In such cases, thefact that a manipulator changes the stream is a desirable property.

However, many programs (and, more importantly, programmers) expect the state of the stream to match the normal library defaults.  
In these cases, leaving the state of the stream in a nonstandard state can lead to errors.  
As a result, it is usually best to undo whatever state changes are made as soon as those changes are no longerneeded.


##### 2) Controlling the Format of Boolean Values

One example of a manipulator that changes the formatting state of its object is the `boolalpha` manipulator.  
By default, bool values print as 1 or 0.  
We can override this formatting byapplying the boolalpha manipulator to the stream:

```cpp
cout << "default bool values: " << true << " " << false
     << "\nalpha bool values: " << boolalpha << true << " " << false << endl;
```

When executed, this program generates the following:

```sh
default bool values: 1 0
alpha bool values: true false
```

Once we “write” boolalpha on cout, we’ve changed how cout will print boolvalues from this point on.  
Subsequent operations that print bools will print them aseither true or false.

To undo the format state change to cout, we apply `noboolalpha`:

```cpp
bool bool_val = get_status();
cout << boolalpha       // sets the internal state of cout
     << bool_val
     << noboolalpha;    // resets the internal state to default formatting
```

Here we change the format of bool values only to print the value of bool_val.  
Once that value is printed, we immediately reset the stream back to its initial state.


##### 3) Specifying the Base for Integral Values

By default, integral values are written and read in decimal notation.  
We can changethe notational base to octal or hexadecimal or back to decimal by using the manipulators `hex`, `oct`, and `dec`:

```cpp
cout << "default: " << 20 << " " << 1024 << endl;
cout << "octal: " << oct << 20 << " " << 1024 << endl;
cout << "hex: " << hex << 20 << " " << 1024 << endl;
cout << "decimal: " << dec << 20 << " " << 1024 << endl;
```

When compiled and executed, this program generates the following output:

```sh
default: 20 1024
octal: 24 2000
hex: 14 400
decimal: 20 1024
```

Notice that like boolalpha, these manipulators change the format state.  
They affect the immediately following output and all subsequent integral output until theformat is reset by invoking another manipulator.

> ##### Note
> The `hex`, `oct`, and `dec` manipulators affect only integral operands; the representation of floating-point values is unaffected.


##### 4) Indicating Base on the Output

By default, when we print numbers, there is no visual cue as to what notational base was used.  
Is 20, for example, really 20, or an octal representation of 16? When weprint numbers in decimal mode, the number is printed as we expect.  
If we need toprint octal or hexadecimal values, it is likely that we should also use the `showbase` manipulator.  
The showbase manipulator causes the output stream to use the sameconventions as used for specifying the base of an integral constant:
- A leading 0x indicates hexadecimal.
- A leading 0 indicates octal.
- The absence of either indicates decimal.

Here we’ve revised the previous program to use showbase:

```cpp
cout << showbase;   // show the base when printing integral values
cout << "default: " << 20 << " " << 1024 << endl;
cout << "in octal: " << oct << 20 << " " << 1024 << endl;
cout << "in hex: " << hex<< 20 << " " << 1024 << endl;
cout << "in decimal: " << dec << 20 << " " << 1024 << endl;
cout << noshowbase; // reset the state of the stream
```

The revised output makes it clear what the underlying value really is:

```sh
default: 20 1024
in octal: 024 02000
in hex: 0x14 0x400
in decimal: 20 1024
```

The `noshowbase` manipulator resets cout so that it no longer displays the notational base of integral values.

By default, hexadecimal values are printed in lowercase with a lowercase x.  
We can display the X and the hex digits a–f as uppercase by applying the `uppercase` manipulator:

```cpp
cout << uppercase << showbase << hex
     << "printed in hexadecimal: " << 20 << " " << 1024
     << nouppercase << noshowbase << dec << endl;
```

This statement generates the following output:  
`printed in hexadecimal: 0X14 0X400`  
We apply the `nouppercase`, `noshowbase`, and `dec` manipulators to return the stream to its original state.


##### 5) Controlling the Format of Floating-Point Values

We can control three aspects of floating-point output:
- How many digits of precision are printed
- Whether the number is printed in hexadecimal, fixed decimal, or scientific notation
- Whether a decimal point is printed for floating-point values that are whole numbers

By default, floating-point values are printed using six digits of precision; the decimal point is omitted if the value has no fractional part; and they are printed in either fixeddecimal or scientific notation depending on the value of the number.  
The library chooses a format that enhances readability of the number.  
Very large and very smallvalues are printed using scientific notation.  
Other values are printed in fixed decimal.


##### 6) Specifying How Much Precision to Print

By default, precision controls the total number of digits that are printed.  
When printed, floating-point values are rounded, not truncated, to the current precision.  
Thus, if thecurrent precision is four, then 3.14159 becomes 3.142; if the precision is three, then it is printed as 3.14.

We can change the precision by calling the precision member of an IO object orby using the setprecision manipulator.  
The precision member is overloaded (§6.4, p. 230).  
One version takes an int value and sets the precision to that new value.  
It returns the previous precision value. The other version takes no arguments and
returns the current precision value.  
The `setprecision` manipulator takes anargument, which it uses to set the precision.

> ##### Note
> The `setprecision` manipulators and other manipulators that take arguments are defined in the `iomanip` header.

The following program illustrates the different ways we can control the precisionused to print floating-point values:

```cpp
// cout.precisionreports the current precision value
cout << "Precision: " << cout.precision() << ", Value: " << sqrt(2.0) << endl;
// cout.precision(12) asks that 12 digits of precision be printed
cout.precision(12);
cout << "Precision: " << cout.precision() << ", Value: " << sqrt(2.0) << endl;
// alternative way to set precision using thesetprecisionmanipulator
cout << setprecision(3);
cout << "Precision: " << cout.precision() << ", Value: " << sqrt(2.0) << endl;
```

When compiled and executed, the program generates the following output:

```sh
Precision: 6, Value: 1.41421
Precision: 12, Value: 1.41421356237
Precision: 3, Value: 1.41
```

###### Table Manipulators Defined in iostream

|     |                |                                        |
| --- | -------------- | -------------------------------------- |
|     | `boolalpha`    | Display true and false as strings      |
| *   | `noboolalpha`  | Display true and false as 0, 1         |
|     | `showbase`     |
| *   | `noshowbase`   |
|     | `showpoint`    |
| *   | `noshowpoint`  |
|     | `showpos`      |
| *   | `noshowpos`    |
|     | `uppercase`    |
| *   | `nouppercase`  |
| *   | `dec`          |
|     | `hex`          |
|     | `oct`          |
|     | `left`         |
|     | `right`        |
|     | `internal`     |
|     | `fixed`        |
|     | `scientific`   |
|     | `hexfloat`     |
|     | `defaultfloat` |
|     | `unitbuf`      |
| *   | `nounitbuf`    |
| *   | `skipws`       |
|     | `noskipws`     |
|     | `flush`        |
|     | `ends`         |
|     | `endl`         |
|     |                | * *indicates the default stream state* |

This program calls the library sqrt function, which is found in the cmath header.  
The sqrt function is overloaded and can be called on either a float, double, or long double argument.  
It returns the square root of its argument.


##### 7) Specifying the Notation of Floating-Point Numbers

> ##### Best Practices
> Unless you need to control the presentation of a floating-point number (e.g.,to print data in columns or to print data that represents money or apercentage), it is usually best to let the library choose the notation.

We can force a stream to use scientific, fixed, or hexadecimal notation by using theappropriate manipulator.  
The scientific manipulator changes the stream to usescientific notation.  
The fixed manipulator changes the stream to use fixed decimal.

`C++11` Under the new library, we can also force floating-point values to use hexadecimal format by using `hexfloat`.  
The new library provides another manipulator, named defaultfloat.  
This manipulator returns the stream to its default state in which itchooses a notation based on the value being printed.

These manipulators also change the default meaning of the precision for the stream.  
After executing scientific, fixed, or hexfloat, the precision value controls the number of digits after the decimal point.  
By default, precision specifies the totalnumber of digits—both before and after the decimal point.  
Using fixed orscientific lets us print numbers lined up in columns, with the decimal point in afixed position relative to the fractional part being printed:

```cpp
cout << "default format: " << 100 * sqrt(2.0) << '\n'
     << "scientific: " << scientific << 100 * sqrt(2.0) << '\n'
     << "fixed  decimal: " << fixed << 100 * sqrt(2.0) << '\n'
     << "hexadecimal: " << hexfloat << 100 * sqrt(2.0) << '\n'
     << "use defaults: " << defaultfloat << 100 * sqrt(2.0) << "\n\n";
```

produces the following output:

```sh
default format: 141.421
scientific: 1.414214e+002
fixed decimal: 141.421356
hexadecimal: 0x1.1ad7bcp+7
use defaults: 141.421
```

By default, the hexadecimal digits and the e used in scientific notation are printed in lowercase.  
We can use the uppercase manipulator to show those values inuppercase.


##### 8) Printing the Decimal Point

By default, when the fractional part of a floating-point value is 0, the decimal point is not displayed.  
The showpoint manipulator forces the decimal point to be printed:

```cpp
cout << 10.0 << endl;           // prints10
cout << showpoint << 10.0       // prints10.0000
     << noshowpoint << endl;    // revert to default format for the decimal point
```

The `noshowpoint` manipulator reinstates the default behavior.  
The next output expression will have the default behavior, which is to suppress the decimal point if thefloating-point value has a 0 fractional part.


##### 9) Padding the Output

When we print data in columns, we often need fairly fine control over how the data are formatted.  
The library provides several manipulators to help us accomplish thecontrol we might need:
- setw to specify the minimum space for the next numeric or string value.
- left to left-justify the output.
- right to right-justify the output. Output is right-justified by default.
- internal controls placement of the sign on negative values. internal left-justifies the sign and right-justifies the value, padding any intervening space withblanks.
- setfill lets us specify an alternative character to use to pad the output. By default, the value is a space.

> ##### Note
> `setw`, like `endl`, does not change the internal state of the output stream.  
> It determines the size of only the next output.

The following program illustrates these manipulators:

```cpp
int i = -16;
double d = 3.14159;
// pad the first column to use a minimum of 12 positions in the output
cout << "i: " << setw(12) << i << "next col" << '\n'
     << "d: " << setw(12) << d << "next col" << '\n';
// pad the first column and left-justify all columns
cout << left
     << "i: " << setw(12) << i << "next col" << '\n'
     << "d: " << setw(12) << d << "next col" << '\n'
     << right;  // restore normal justification
// pad the first column and right-justify all columns
cout << right
     << "i: " << setw(12) << i << "next col" << '\n'
     << "d: " << setw(12) << d << "next col" << '\n';
// pad the first column but put the padding internal to the field
cout << internal
     << "i: " << setw(12) << i << "next col" << '\n'
     << "d: " << setw(12) << d << "next col" << '\n';
// pad the first column, using # as the pad character
cout << setfill('#')
     << "i: " << setw(12) << i << "next col" << '\n'
     << "d: " << setw(12) << d << "next col" << '\n'
     << setfill(' ');   // restore the normal pad character
```

When executed, this program generates

```sh
i:      -16next col
d:    3.14159next col
i: -16     next col
d: 3.14159   next col
i:     -16next col
d:    3.14159next col
i: -     16next col
d:    3.14159next col
i: -#########16next col
d: #####3.14159next col
```

###### Table Manipulators Defined in `iomanip`

|                   |                                       |
| ----------------- | ------------------------------------- |
| `setfill(ch)`     | Fill whitespace with `ch`             |
| `setprecision(n)` | Set floating-point precision to `n`   |
| `setw(w)`         | Read or write value to `w` characters |
| `setbase(b)`      | Output integers in base `b`           |


##### 9) Controlling Input Formatting

By default, the input operators ignore whitespace (blank, tab, newline, formfeed, andcarriage return).  
The following loop

```cpp
char ch;
while (cin >> ch)
    cout << ch;
```

given the input sequence

```sh
a b  c
d
```

executes four times to read the characters a through d, skipping the intervening blanks, possible tabs, and newline characters.  
The output from this program is  
`abcd`

The `noskipws` manipulator causes the input operator to read, rather than skip,whitespace.  
To return to the default behavior, we apply the skipws manipulator:

```cpp
cin >> noskipws;    // set cin so that it reads whitespace
while (cin >> ch)
    cout << ch;
cin >> skipws;      // reset cin to the default state so that it discards whitespace
```

Given the same input as before, this loop makes seven iterations, reading whitespaceas well as the characters in the input.  
This loop generates

```sh
a b  c
d
```


#### 17.5.2 Unformatted Input/Output Operations

So far, our programs have used only **formatted IO** operations.  
The input and outputoperators (`<<` and `>>`) format the data they read or write according to the type beinghandled.  
The input operators ignore whitespace; the output operators apply padding,precision, and so on.

The library also provides a set of low-level operations that support **unformatted IO**.  
These operations let us deal with a stream as a sequence of uninterpreted bytes.


##### 1) Single-Byte Operations

Several of the unformatted operations deal with a stream one byte at a time.  
These operations, which are described in Table 17.19, read rather than ignore whitespace.  
For example, we can use the unformatted IO operations get and put to read and write the characters one at a time:

```cs
char ch;
while (cin.get(ch))
    cout.put(ch);
```

This program preserves the whitespace in the input.  
Its output is identical to theinput.  
It executes the same way as the previous program that used noskipws.

###### 2) Table Single-Byte Low-Level IO Operations

|                  |                                                                   |
| ---------------- | ----------------------------------------------------------------- |
| `is.get(ch)`     | Put the next byte from the istream is in character ch. Return is. |
| `os.put(ch)`     | Put the character ch onto the ostream os. Return os.              |
| `is.get()`       | Returns next byte from is as an int.                              |
| `is.putback(ch)` | Put the character ch back on is; return is.                       |
| `is.unget()`     | Move is back one byte; return is.                                 |
| `is.peek()`      | Return the next byte as an int but doesnt remove it.              |


##### 3) Putting Back onto an Input Stream

Sometimes we need to read a character in order to know that we aren’t ready for it.  
In such cases, we’d like to put the character back onto the stream.  
The library givesus three ways to do so, each of which has subtle differences from the others:

- `peek` returns a copy of the next character on the input stream but does not change the stream. The value returned by peek stays on the stream.
- `unget` backs up the input stream so that whatever value was last returned is still on the stream. We can call unget even if we do not know what value was last taken from the stream.
- `putback` is a more specialized version of unget: It returns the last value read from the stream but takes an argument that must be the same as the one that was last read.

In general, we are guaranteed to be able to put back at most one value before thenext read.  
That is, we are not guaranteed to be able to call putback or unget successively without an intervening read operation.


##### 4) `int` Return Values from Input Operations

The `peek` function and the version of get that takes no argument return a character from the input stream as an int.  
This fact can be surprising; it might seem morenatural to have these functions return a char.

The reason that these functions return an int is to allow them to return an **end-of-file** marker.  
A given character set is allowed to use every value in the char range torepresent an actual character.  
Thus, there is no extra value in that range to use torepresent end-of-file.

The functions that return int convert the character they return to unsigned char and then promote that value to int.  
As a result, even if the character set hascharacters that map to negative values, the int returned from these operations willbe a positive value (§ 2.1.2, p. 35).  
The library uses a negative value to representend-of-file, which is thus guaranteed to be distinct from any legitimate charactervalue.  
Rather than requiring us to know the actual value returned, the iostreamheader defines a const named EOF that we can use to test if the value returned from get is end-of-file.  
It is essential that we use an int to hold the return fromthese functions:

```cs
int ch; // use an int,not a char to hold the return from get()
// loop to read and write all the data in the input
while ((ch = cin.get()) != EOF)
    cout.put(ch);
```


##### 5) Multi-Byte Operations

Some unformatted IO operations deal with chunks of data at a time.  
These operations can be important if speed is an issue, but like other low-level operations, they areerror-prone.  
In particular, these operations require us to allocate and manage the character arrays (§ 12.2, p. 476) used to store and retrieve data.  
The multi-byteoperations are listed in Table 17.20.

###### Table Multi-Byte Low-Level IO Operations

|     |                                                                        |
| --- | ---------------------------------------------------------------------- |
| op  | `is.get(sink, size, delim)`                                            |
| >>> | Reads up to size bytes from is and stores them in the character array  |
|     | beginging at the address pointed to by sink. Reads until encountering  |
|     | the delim character or until it has read size bytes or encounters EOF. |
|     | If delim is present, it is left on the istream and not read into sink. |
| op  | `is.getline(sink, size, delim)`                                        |
| >>> | Same as the 3-argument version of `get` but reads and discards delim.  |
| op  | `is.read(sink, size)`                                                  |
| >>> | Reads up to size bytes into the character array sink. Return is.       |
| op  | `is.gcount()`                                                          |
| >>> | Returns number of bytes by the last unformatted read operation.        |
| op  | `os.write(source, size)`                                               |
| >>> | Writes size bytes from the character array source to os. Return os.    |
| op  | `is.ignore(size, delim)`                                               |
| >>> | Reads and ignores at most size characters up to and including delim.   |
|     | Unlike the other unformatted functions, ignore has default arguments:  |
|     | size defaults to 1 and delim to EOF.                                   |

The `get` and `getline` functions take the same parameters, and their actions are similar but not identical.  
In each case, `sink` is a char array into which the data areplaced.  
The functions read until one of the following conditions occurs:

- `size - 1` characters are read
- End-of-file is encountered
- The delimiter character is encountered

The difference between these functions is the treatment of the delimiter:

- get leaves the delimiter as the next character of the istream
- getline reads and discards the delimiter

In either case, the delimiter is not stored in sink.

> ##### Warning
> It is a common error to intend to remove the delimiter from the stream but to forget to do so.


##### 6) Determining How Many Characters Were Read

Several of the read operations read an unknown number of bytes from the input.  
We can call `gcount` to determine how many characters the last unformatted input operation read.  
It is essential to call gcount before any intervening unformatted inputoperation.  
In particular, the single-character operations that put characters back on the stream are also unformatted input operations.  
If `peek`, `unget`, or `putback` are called before calling `gcount`, then the return value will be 0.


#### 17.5.3 Random Access to a Stream

The various stream types generally support random access to the data in their associated stream.  
We can reposition the stream so that it skips around, reading firstthe last line, then the first, and so on.  
The library provides a pair of functions to seek to a given location and to tell the current location in the associated stream.

> ##### Note
> Random IO is an inherently system-dependent.  
> To understand how to usethese features, you must consult your system’s documentation.

Although these seek and tell functions are defined for all the stream types, whether they do anything useful depends on the device to which the stream is bound.  
On most systems, the streams bound to `cin`, `cout`, `cerr`, and `clog` do *not* support random access—after all, what would it mean to jump back ten places when we’re writing directly to cout?  
We can call the seek and tell functions, but these functions will fail at run time, leaving the stream in an invalid state.

> ##### Caution: Low-Level Routines Are Error-Prone
> In general, we advocate using the higher-level abstractions provided by the library.  
> The IO operations that return int are a good example of why.
> 
> It is a common programming error to assign the return, from get or peek to a char rather than an int.  
> Doing so is an error, but an error the compiler will not detect.  
> Instead, what happens depends on the machine and on the input data.  
> For example, on a machine in which chars are implemented as unsigned chars, this loop will run forever:
> 
> ```cpp
> char ch;  // using a char here invites disaster!
> // the return from cin.get is converted to char and then compared to an int
> while ((ch = cin.get()) != EOF)
>     cout.put(ch);
> ```
> 
> The problem is that when get returns EOF, that value will be converted to an unsigned char value.  
> That converted value is no longer equal to theint value of EOF, and the loop will continue forever.  
> Such errors are likely to be caught in testing.
> 
> On machines for which chars are implemented as signed chars, we can’t say with confidence what the behavior of the loop might be.  
> What happens when an out-of-bounds value is assigned to a signed value is up to the compiler.  
> On many machines, this loop will appear to work, unless acharacter in the input matches the EOF value.  
> Although such characters are unlikely in ordinary data, presumably low-level IO is necessary only when weread binary values that do not map directly to ordinary characters andnumeric values.  
> For example, on our machine, if the input contains acharacter whose value is '\377', then the loop terminates prematurely.  
> '\377' is the value on our machine to which −1 converts when used as asigned char.  
> If the input has this value, then it will be treated as the(premature) end-of-file indicator.
> 
> Such bugs do not happen when we read and write typed values.  
> If you can use the more type-safe, higher-level operations supported by the library, do so.

> ##### Warning
> Because the `istream` and `ostream` types usually do not support random access, the remainder of this section should be considered as applicable to only the `fstream` and `sstream` types.


##### Seek and Tell Functions

To support random access, the IO types maintain a marker that determines where the next read or write will happen.  
They also provide two functions:

- One repositions the marker by seeking to a given position;  
- the second tells us the current position of themarker.

The library actually defines two pairs of seek and tell functions, which are described in Table 17.21.  
One pair is used by input streams, the other by outputstreams.  
The input and output versions are distinguished by a suffix that is either a gor a p.  
The g versions indicate that we are “getting” (reading) data, and the p functions indicate that we are “putting” (writing) data.

###### Table: Seek and Tell Functions

|                    |                                                                      |
| ------------------ | -------------------------------------------------------------------- |
| `tellg()`          | Return the current position of the marker in an input stream (tellg) |
| `tellp()`          | or an output stream (tellp)                                          |
| `seekg(pos)`       | Reposition the marker in an input or output stream to the given      |
| `seekp(pos)`       | absolute address in the stream. pos is usually a value returned by   |
|                    | a previsous call to the corresponding tellg or tellp function.       |
| `seekp(off, from)` | Reposition the marker for an input or output stream integral number  |
| `seekg(off, from)` | `off` characters ahead or behind `from`. from can be one of          |
|                    | - `beg`, seek relative to the beginning of the stream                |
|                    | - `cur`, seek relative to the current position of the stream         |
|                    | - `end`, seek relative to the end of the stream                      |

Logically enough, we can use only the g versions on an istream and on the types `ifstream` and `istringstream` that inherit from `istream` (§ 8.1, p. 311).  
We can use only the p versions on an ostream and on the types that inherit from it, `ofstream` and `ostringstream`.  
An iostream, fstream, or stringstream canboth read and write the associated stream;  
we can use either the g or p versions onobjects of these types.


##### There Is Only One Marker

The fact that the library distinguishes between the “putting” and “getting” versions ofthe seek and tell functions can be misleading.  
Even though the library makes this distinction, it maintains only a single marker in a stream—there is not a distinct read marker and write marker.  
When we’re dealing with an input-only or output-only stream, the distinction isn’teven apparent.  
We can use only the g or only the p versions on such streams.  
If we attempt to call tellp on an ifstream, the compiler will complain.  
Similarly, it will not let us call seekg on an ostringstream.

The `fstream` and `stringstream` types can read and write the same stream.  
In these types there is a single buffer that holds data to be read and written and a singlemarker denoting the current position in the buffer.  
The library maps both the g and ppositions to this single marker.

> ##### Note
> Because there is only a single marker, we *must* do a `seek` to reposition the marker whenever we switch between reading and writing.


##### Repositioning the Marker

There are two versions of the seek functions:

- One moves to an “absolute” address within the file;
- the other moves to a byte offset from a given position:

```cpp
// set the marker to a fixed position
seekg(new_position);    // set the read marker to the given pos_type location
seekp(new_position);    // set the write marker to the given pos_type location
// offset some distance ahead of or behind the given starting point
seekg(offset, from);    // set the read marker offset distance from from
seekp(offset, from);    // offset has type off_type
```

The possible values for from are listed in Table 17.21 (on the previous page).

The arguments, new_position and offset, have machine-dependent types named pos_type and off_type, respectively.  
These types are defined in bothistream and ostream.  
pos_type represents a file position and off_typerepresents an offset from that position.  
A value of type off_type can be positive ornegative;  
we can seek forward or backward in the file.


##### Accessing the Marker

The `tellg` or `tellp` functions return a pos_type value denoting the currentposition of the stream.  
The tell functions are usually used to remember a location sothat we can subsequently seek back to it:

```cs
// remember the current write position in mark
ostringstream writeStr; // output stringstream
ostringstream::pos_type mark = writeStr.tellp();
// ...
if (cancelEntry)
    // return to the remembered position
    writeStr.seekp(mark);
```


##### Reading and Writing to the Same File

Let’s look at a programming example.  
Assume we are given a file to read.  
We are towrite a newline at the end of the file that contains the relative position at which eachline begins.  
For example, given the following file,

```sh
abcd
efg
hi
j
```

the program should produce the following modified file:

```sh
abcd
efg
hi
j
5 9 12 14
```

Note that our program need not write the offset for the first line—it always occurs atposition 0.  
Also note that the offset counts must include the invisible newline characterthat ends each line.  
Finally, note that the last number in the output is the offset forthe line on which our output begins.  
By including this offset in our output, we candistinguish our output from the file’s original contents.  
We can read the last number inthe resulting file and seek to the corresponding offset to get to the beginning of ouroutput.

Our program will read the file a line at a time.  
For each line, we’ll increment acounter, adding the size of the line we just read.  
That counter is the offset at whichthe next line starts:

```cs
int main()
{
    // open for input and output and preposition file pointers to end-of-file
    // file mode argument see § 8.4 (p. 319)
    fstream inOut("copyOut", fstream::ate | fstream::in | fstream::out);
    if (!inOut)
    {
        cerr << "Unable to open file!" << endl;
        return EXIT_FAILURE; // EXIT_FAILUREsee § 6.3.2 (p. 227)
    }
    // inOut is opened in ate mode, so it starts out positioned at the end
    auto  end_mark  =  inOut.tellg();   // remember original end-of-file position
    inOut.seekg(0, fstream::beg);       // reposition to the start of the file
    size_t cnt = 0;                     // accumulator for the byte count
    string line;                        // hold each line of input
    // while we haven't hit an error and are still reading the original data
    while (inOut && inOut.tellg() != end_mark && getline(inOut, line)) { // and  can  get  another  line  ofinput
        cnt += line.size() + 1;         // add 1 to account for the newline
        auto mark = inOut.tellg();      // remember the read position
        inOut.seekp(0, fstream::end);   // set the write marker to  the end
        inOut << cnt;                   // write the accumulated length
        // print a separator if this is not the last line
        if (mark != end_mark) { inOut << " "; }
        inOut.seekg(mark);              // restore the read position
    }
    inOut.seekp(0, fstream::end);       // seek to the end
    inOut << "\n";                      // write a newline at end-of-file
    return 0;
}
```

Our program opens its fstream using the in, out, and ate modes (§ 8.4, p. 319).  
The first two modes indicate that we intend to read and write the same file.  
Specifying ate positions the read and write markers at the end of the file.  
As usual, we check that the open succeeded, and exit if it did not (§ 6.3.2, p. 227).

Because our program writes to its input file, we can’t use end-of-file to signal whenit’s time to stop reading.  
Instead, our loop must end when it reaches the point atwhich the original input ended.  
As a result, we must first remember the original end-of-file position.  
Because we opened the file in ate mode, inOut is already positionedat the end.  
We store the current (i.e., the original end) position in end_mark.  
Having remembered the end position, we reposition the read marker at the beginning of thefile by seeking to the position 0 bytes from the beginning of the file.

The while loop has a three-part condition:  
We first check that the stream is valid;  
if so, we check whether we’ve exhausted our original input by comparing the currentread position (returned by tellg) with the position we remembered in end_mark.  
Finally, assuming that both tests succeeded, we call getline to read the next line ofinput.  
If getline succeeds, we perform the body of the loop.

The loop body starts by remembering the current position in mark.  
We save that position in order to return to it after writing the next relative offset.  
The call to seekprepositions the write marker to the end of the file.  
We write the counter value andthen seekg back to the position we remembered in mark.  
Having restored themarker, we’re ready to repeat the condition in the while.

Each iteration of the loop writes the offset of the next line.  
Therefore, the lastiteration of the loop takes care of writing the offset of the last line.  
However, we stillneed to write a newline at the end of the file.  
As with the other writes, we call seekpto position the file at the end before writing the newline.

--------------------------------------------------------------------------------

### Chapter Summary

This chapter covered additional IO operations and four library types: `tuple`, `bitset`,regular expressions, and random numbers.

A `tuple` is a template that allows us to bundle together members of disparate types into a single object.
Each `tuple` contains a specified number of members, but the library imposes no limit on the number of members we can define for a given `tuple` type.

A `bitset` lets us define collections of bits of a specified size.
The size of a `bitset` is not constrained to match any of the integral types, and can even exceed them.
In addition to supporting the normal bitwise operators (§ 4.8, p. 152), `bitset` defines a number of named operations that let us manipulate the state of particular bits in the `bitset`.

The regular-expression library provides a collection of classes and functions: The `regex` class manages regular expressions written in one of several common regular-expression languages.
The match classes hold information about a specific match.
These classes are used by the `regex_search` and `regex_match` functions.
These functions take a `regex` object and a character sequence and detect whether theregular expression in that `regex` matches the given character sequence.
The `regex` iterator types are iterator adaptors that use `regex_search` to iterate through aninput sequence and return each matching subsequence.
There is also a `regex_replace` function that lets us replace the matched part of a given inputsequence with a specified alternative.

The random-number library is a collection of random-number engines anddistribution classes.
A random-number engine returns a sequence of uniformly distributed integral values.
The library defines several engines that have different performance characteristics.
The `default_random_engine` is defined as the engine that should be suitable for most casual uses.
The library also defines 20 distribution types.
These distribution types use an engine to deliver random numbers of aspecified type in a given range that are distributed according to a specified probabilitydistribution.
