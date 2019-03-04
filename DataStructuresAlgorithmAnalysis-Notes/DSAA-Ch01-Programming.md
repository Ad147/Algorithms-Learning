DSAA-Ch01-Programming.md


Notes of Data Structures and Algorithm Analysis in C++
================================================================================

Ad  
<ar><r></r></ar>

Init: 18Nov16


Chapter 1 Programming: A General Overview
--------------------------------------------------------------------------------

In this chapter, we discuss the aims and goals of this text and briefly review programming concepts and discrete mathematics. We will...

- See that how a program performs for reasonably large input is just as important as itsperformance on moderate amounts of input
- Summarize the basic mathematical background needed for the rest of the book
- Briefly review **recursion**
- Summarize some important features of C++that are used throughout the text

--------------------------------------------------------------------------------

- [Chapter 1 Programming: A General Overview](#chapter-1-programming-a-general-overview)
  - [1.1 What's This Book About?](#11-whats-this-book-about)
  - [1.2 Mathematics Review](#12-mathematics-review)
    - [1.2.1 Exponents](#121-exponents)
    - [1.2.2 Logarithms](#122-logarithms)
    - [1.2.3 Series](#123-series)
    - [1.2.4 Modular Arithmetic](#124-modular-arithmetic)
    - [1.2.5 The *P* Word](#125-the-p-word)
  - [1.3 A Brief Introduction to Recursion](#13-a-brief-introduction-to-recursion)
  - [1.4 C++ Classes](#14-c-classes)
    - [1.4.1 Basic `class` Syntax](#141-basic-class-syntax)
    - [1.4.2 Extra Constructor Syntax and Accessors](#142-extra-constructor-syntax-and-accessors)
    - [1.4.3 Separation of Interface and Implementation](#143-separation-of-interface-and-implementation)
    - [1.4.4 `vector` and `string`](#144-vector-and-string)
  - [1.5 C++ Details](#15-c-details)
    - [1.5.1 Pointers](#151-pointers)
    - [1.5.2 Lvalues, Rvalues, and References](#152-lvalues-rvalues-and-references)
    - [1.5.3 Parameter Passing](#153-parameter-passing)
    - [1.5.4 Return Passing](#154-return-passing)
    - [1.5.5 `std::swap` and `std::move`](#155-stdswap-and-stdmove)
    - [1.5.6 The Big-Five: Destructor, Copy Constructor, Move Constructor, Copy Assignment `operator=`, Move Assignment `operator=`](#156-the-big-five-destructor-copy-constructor-move-constructor-copy-assignment-operator-move-assignment-operator)
    - [1.5.7 C-style Arrays and Strings](#157-c-style-arrays-and-strings)
  - [1.6 Templates](#16-templates)
    - [1.6.1 Function Templates](#161-function-templates)
    - [1.6.2 Class Templates](#162-class-templates)
    - [1.6.3 Object, Comparable, and an Example](#163-object-comparable-and-an-example)
    - [1.6.4 Function Object](#164-function-object)
    - [1.6.5 Separate Compilation of Class Templates](#165-separate-compilation-of-class-templates)
  - [1.7 Using Matrices](#17-using-matrices)
    - [1.7.1 The Data Members, Constructor, and Basic Accessors](#171-the-data-members-constructor-and-basic-accessors)
    - [1.7.2 `operator[]`](#172-operator)
    - [1.7.3 Big-Five](#173-big-five)
  - [Summary](#summary)

--------------------------------------------------------------------------------


### 1.1 What's This Book About?

Suppose you have a group of N numbers and would like to determine the kth largest.  
This is known as the **selection problem**.  
Most students who have had a programming course or two would have no difficulty writing a program to solve this problem.  
There are quite afew “obvious” solutions.

One way to solve this problem would be to read theNnumbers into an array, sort thearray in decreasing order by some simple algorithm such as bubble sort, and then returnthe element in positionk.A somewhat better algorithm might be to read the first k elements into an array andsort them (in decreasing order).  
Next, each remaining element is read one by one.  
As a new element arrives, it is ignored if it is smaller than thekth element in the array.  
Otherwise, itis placed in its correct spot in the array, bumping one element out of the array.  
When thealgorithm ends, the element in thekth position is returned as the answer.

Both algorithms are simple to code, and you are encouraged to do so.  
The natural questions, then, are:  
Which algorithm is better?  
And, more important, Is either algorithm goodenough?  
A simulation using a random file of 30 million elements and k=15,000,000 will show that neither algorithm finishes in a reasonable amount of time;  
each requires several days of computer processing to terminate (albeit eventually with a correct answer).  
An alternative method, discussed in Chapter 7, gives a solution in about a second.  
Thus, although our proposed algorithms work, they cannot be considered good algorithms, because they are entirely impractical for input sizes that a third algorithm can handle in areasonable amount of time.

An important concept is that, in many problems, writing a working program is not good enough.  
If the program is to be run on a large data set, then the running time becomes an issue.  
Throughout this book we will see how to estimate the running time of a program for large inputs and, more important, how to compare the running times of two programs without actually coding them.  
We will see techniques for drastically improving the speed of a program and for determining program bottlenecks.  
These techniques will enable us to find the section of the code on which to concentrate our optimization efforts.

--------------------------------------------------------------------------------


### 1.2 Mathematics Review


#### 1.2.1 Exponents

$$ X^A * X^B = X^{A+B} $$

$$ X^A / X^B = X^{A-B} $$

$$ (X^A)^B = X^{AB} $$

$$ X^N + X^N = 2X^N != X^{2N} $$

$$ 2^N + 2^N = 2^{N+1} $$


#### 1.2.2 Logarithms

In computer science, all logarithms are to the base 2 unless specified otherwise.


###### Definition 1.1

$X^A = B$ if and only if $log_X(B) = A$


###### Theorem 1.1

$$ log_A(B) = log_C(B) / log_C(A); A,B,C > 0, A != 1 $$


###### Proof

...


###### Theorem 1.2

$$ log(AB) = logA + logB; A,B > 0 $$


###### Proof

...



#### 1.2.3 Series


##### Geometric series formulas:

$$ \sum_{i=0}^N 2^i = 2^{N+1} - 1 $$

$$ \sum_{i=0}^N A^i = \frac {A^{N+1} - 1} {A - 1} $$

In the latter formula, if 0 < A < 1, then

$$ \sum_{i=0}^N A^i <= 1 / (1 -A) $$


as N tends to `inf`, the sum approaches $1/(1-A)$.


##### Arithmetic series:

$$ \sum_{i=1}^N i = N(N + 1) / 2 ≈ N^2 / 2 $$

The next two formulas pop up now and then but are fairly uncommon:

$$ \sum_{i=1}^N i^2 = N(N + 1)(2N + 1) / 6 ≈ N^3 / 3 $$

$$ \sum_{i=1}^N i^k ≈ N^{k+1} / |k + 1|; k != -1 $$

The numbers $H_N$ are known as the harmonic numbers, and the sum is known as a harmonicsum.  
The error in the following approximation tends to γ≈0.57721566, which is known as **Euler’s constant**.

$$ H_N = \sum_{i=1}^N 1/i ≈ log_e(N) $$

These two formulas are just general algebraic manipulations:

$$ \sum_{i=1}^N f(N) = N f(N) $$

$$ \sum_{i=n0}^N f(i) = \sum_{i=1}^N f(i) - \sum_{i=1}^{n0-1} f(i) $$


#### 1.2.4 Modular Arithmetic

We say that A is congruent to B modulo N, written $A ≡ B (mod N)$, if N divides A−B.  
Intuitively, this means that the remainder is the same when either A or B is divided by N.  
As with equality, if $A ≡ B (mod N)$, then $A+C≡B+C(mod N)$ and $AD≡BD(mod N)$.

Often, N is a prime number.  
In that case, there are three important theorems:
1. if N is prime, then $ab≡0(mod N)$ is true if and only if $a≡0(mod N)$ or $b≡0(mod N)$.  
   In other words, if a prime number N divides a product of two numbers, it divides at least one of the two numbers.
2. if N is prime, then the equation $ax≡1(mod N)$ has a unique solution (mod N) for all 0<a<N.  
   This solution, 0<x<N, is the *multiplicative inverse*.
3. if N is prime, then the equation $x^2≡a(mod N)$ has either two solutions (mod N) for all 0<a<N, or it has no solutions.


#### 1.2.5 The *P* Word


##### Proof by Induction

A proof by induction has two standard parts:

1. Proving a *base case*, that is, establishing that a theorem is true for some small (usually degenerate) value(s); this step is almost always trivial.
2. Assuming an *inductive hypothesisis*. Generally this means that the theorem is assumed to be true for all cases up to some limit k. Using this assumption,the theorem is then shown to be true for the next value, which is typically k+1.

This proves the theorem (as long as k is finite).

As an example, we prove that the Fibonacci numbers,F0=1,F1=1,F2=2,F3=3,F4=5,...,Fi = Fi−1 + Fi−2, satisfy Fi < (5/3)^i, for i ≥ 1.  
(Some definitions have F0 = 0,which shifts the series.)  
To do this, we first verify that the theorem is true for the trivial cases.  
It is easy to verify that F1=1<5/3 and F2=2<25/9;  
this proves the basis.  
We assume that the theorem is true for i=1, 2,...,k;  
this is the inductive hypothesis.  
To prove the theorem, we need to show that Fk+1<(5/3)k+1.  
We have Fk+1=Fk+Fk−1 by the definition, and we can use the inductive  hypothesis on the right-hand side, obtaining

$$ F_{k+1} < (5/3)^k + (5/3)^{k−1} $$
$$ < (3/5) (5/3)^{k+1} + (3/5)^2 (5/3)^{k+1} $$
$$ < (3/5) (5/3)^{k+1} + (9/25) (5/3)^{k+1} $$
$$ < (3/5 + 9/25) (5/3)^{k+1} $$
$$ < (24/25) (5/3)^{k+1} $$
$$ < (5/3)^{k+1} $$

proving the theorem.


###### Theorem 1.3

If N >= 1, then $\sum_{i=1}^N i^2 = N(N + 1)(2N + 1) / 6$


###### Proof

The proof is by induction.  
For the basis, it is readily seen that the theorem is true when N=1.  
For the inductive hypothesis, assume that the theorem is true for 1 ≤ k ≤ N.  
We will establish that, under this assumption, the theorem is true for N+1.  
We have

$$ \sum_{i=1}^{N+1} i^2= \sum_{i=1}^N i^2 + (N+1)^2 $$

Applying the inductive hypothesis, we obtain

$$ \sum_{i=1}^{N+1} i^2 = N(N+1)(2N+1) / 6 + (N+1)^2 $$
$$ = (N+1) [N(2N+1) / 6 + (N+1)] $$
$$ = (N+1) (2N^2 + 7N + 6) / 6 $$
$$ = (N+1)(N+2)(2N+3)/6 $$

Thus,

$$ \sum_{i=1}^{N+1} i^2 = (N+1) [(N+1)+1] [2(N+1)+1] / 6 $$

proving the theorem.


##### Proof by Counterexample

The statement $F_k ≤ k^2$ is false.  
The easiest way to prove this is to compute $F_{11} = 144 > 11^2$.


##### Proof by Contradiction

Proof by contradiction proceeds by assuming that the theorem is false and showing that this assumption implies that some known property is false, and hence the original assumption was erroneous.  
A classic example is the proof that there is an infinite number of primes.  
To prove this, we assume that the theorem is false, so that there is some largest prime Pk.  
Let P1, P2, ..., Pk be all the primes in order and consider

$$ N = P_1 P_2 P_3···P_{k+1} $$

Clearly, N is larger than Pk, so, by assumption, N is not prime.  
However, none of P1, P2, ..., Pk divides N exactly, because there will always be a remainder of 1.  
This is a contradiction, because every number is either prime or a product of primes.  
Hence, the original assumption, that Pk is the largest prime, is false, which implies that the theorem is true.

--------------------------------------------------------------------------------


### 1.3 A Brief Introduction to Recursion

A function that is defined in terms of itself is called **recursive**.

Not all mathematically recursive functions are efficiently (or correctly) implemented by C++’s simulation of recursion.  
The idea is that the recursive function f ought to be expressible in only a few lines, just like a non recursivefunction.


###### A recursive function $f(x) = 2f(x - 1) + x^2$

```cs
int f(int x)
{
    if (x == 0) // base case
        return 0;
    else
        return 2 * f(x - 1) + x * x;
}
```


##### Printing Out Numbers

Recursion provides a very clean solution to this problem.  
To print out 76234, we need to first print out 7623 and then print out 4.  
The second step is easily accomplished with the statement `printDigit(n%10)`, but the first doesn’t seem any simpler than the original problem.  
Indeed it is virtually the same problem, so we can solve it recursively with the statement `printOut(n/10)`.


###### Recursive routine to print an integer

```cs
void printOut( int n )  // Print nonnegative n
{
    if (n>=10) { printOut(n / 10); }
    printDigit(n % 10);
}
```

We have made no effort to do this efficiently.  
We could have avoided using the mod routine  (which can be very expensive)  because n%10 = n − floor(n/10) ∗ 10 is true for positive n.


##### Recursion and Induction


###### Theorem 1.4

The recursive number-printing algorithm is correct for n >= 0.


###### Proof (By induction on the number of digits in n)

First, if n has one digit, then the program is trivially correct, since it merely makes a call to `printDigit`.  
Assume then that `printOut` works for all numbers of k or fewer digits.  
A number of k+1 digits is expressed by its first k digits followed by its least significant digit.  
But the number formed by the first k digits is exactly floor(n/10), which, by the inductive hypothesis, is correctly printed, and the last digit is n mod 10, so the program prints out any (k+1)-digit number correctly.  
Thus, by induction, all numbers are correctly printed.

The main problem with recursion is the hidden bookkeeping costs.  
Although these costs are almost always justifiable, because recursive programs not only simplify the algorithm design but also tend to give cleaner code, recursion should not be used as a substitute for a simple for loop.  
We’ll discuss the overhead involved in recursion in more detail inSection 3.6.

It is crucial to keep in mind the four basic rules of recursion:

1. *Base cases*. You must always have some base cases, which can be solved without recursion.
2. *Making progress*. For the cases that are to be solved recursively, the recursive call must always be to a case that makes progress toward a base case.
3. *Design rule*. Assume that all the recursive calls work.
4. *Compound interest rule*. Never duplicate work by solving the same instance of a problemin separate recursive calls.

The fourth rule, which will be justified (along with its nickname) in later sections, is thereason that it is generally a bad idea to use recursion to evaluate simple mathematical func-tions, such as the Fibonacci numbers.  
As long as you keep these rules in mind, recursiveprogramming should be straightforward.

--------------------------------------------------------------------------------


### 1.4 C++ Classes


#### 1.4.1 Basic `class` Syntax

members:

- data
- member functions (methods)

Typically, data members are declared `private`, thus restricting access to internal details of the class, while methods intended for general use are made `public`. This is known as **information hiding**.


#### 1.4.2 Extra Constructor Syntax and Accessors


###### `IntCell` class with revisions

```cs
// A class for simulating an integer memory cell.
class IntCell
{
  public:
    explicit IntCell(int initialValue = 0)  // Notice explicit
        : storedValue{initialValue} {}
    
    int read() const                        // Notice const
        { return storedValue; }
    
    void write(int x)
        { storedValue = x; }

  private:
    int storedValue;
};
```


##### Default Parameters


##### Initialization List

In some cases using initialization list is required:

- if a data member is `const` (meaning that it is not changeable after the object has been constructed), then the data member’s value can only be initialized in the initialization  list.
- if a datamember is itself a class type that does not have a zero-parameter constructor, then it must be initialized in the initialization list.

Initialize with the syntax:

`:storedValue{initialValue} {}`  

instead of the traditional:

`:storedValue(initialValue) {}`  

The use of braces instead of parentheses is new in C++11 and is part of a larger effort to provide a uniform syntax for initialization everywhere.  
Generally speaking, anywhere you can initialize, you can do so by enclosing initializations in braces.  
(though there is one important exception, in Section 1.4.4, relating to vectors).


##### `explicit` Constructor

**You should make all one-parameter constructors `explicit` to avoid behind-the-scenes type conversions.**  
Otherwise, there are somewhat lenient rules that will allow type conversions without explicit casting operations.  
Usually, this is unwanted behavior that destroys strong typing and can lead to hard-to-find bugs.  

As an example, consider the following:

`IntCell obj;     // obj is an IntCell`  
`obj = 37;        // Should not compile: type mismatch`

The code fragment above constructs anIntCellobjectobjand then performs an assign-ment statement.  
But the assignment statement should not work, because the right-handside of the assignment operator is not another IntCell.  
obj’s write method should have been used instead.  

However, C++ has lenient rules.  
Normally, a one-parameter constructor defines an **implicit type conversion**, in which a temporary object is created that makes an assignment (or parameter to a function) compatible.  
In this case, the compiler wouldattempt to convert

`obj = 37;        // Should not compile: type mismatch`

into

`IntCell temporary = 37;`  
`obj = temporary;`

Notice that the construction of the temporary can be performed by using the one-parameter constructor.  
The use of explicit means that a one-parameter constructor cannot be used to generate an implicit temporary.  
Thus, since IntCell’s constructor is declared explicit, the compiler will correctly complain that there is a type mismatch.


##### Constant Member Function

A member function that examines but does not change the state of its object is an **accessor**.  
A member function that changes the state is a **mutator** (because it mutates the state of theobject). 

In C++, we can mark each member function as being an accessor or a mutator.  
Doing so is an important part of the design process and should not be viewed as simply a comment.  
Indeed, there are important semantic consequences.  
For instance, mutators cannot be applied to constant objects.

To make a member function an accessor, we must add the keyword `const` after the closing parenthesis that ends the parameter type list.


#### 1.4.3 Separation of Interface and Implementation

In C++ it is more common to separate the class interface from its implementation.  
- The interface lists theclass and its members (data and functions).  
- The implementation provides implementationsof the functions.


###### `IntCell` class interface in *fileIntCell.h*

```cs
#ifndef IntCell_H
#define IntCell_H

// A class for simulating an integer memory cell.
class IntCell
{
  public:
    explicit IntCell(int initialValue = 0);
    int read() const;
    void write(int x);

  private:
    int storedValue;
};

#endif
```


###### `IntCell` class implementation in file *IntCell.cpp*

```cs

#include "IntCell.h"

// Construct the IntCell with initialValue
IntCell::IntCell(int initialValue) : storedValue{initialValue}
{
}

// Return the stored value.
int IntCell::read() const
{
    return storedValue;
}

// Store x.
void IntCell::write(int x)
{
    storedValue = x;
}
```


###### Program that uses `IntCell` in file *TestIntCell.cpp*

```cs
#include <iostream>
#include "IntCell.h"
using namespace std;

int main( )
{
    IntCell m;
    
    m.write(5);
    cout << "Cell contents: " << m.read( ) << endl;
    
    return 0;
}
```


##### Preprocessor Commands

Occasionally, a complicated project will have files including other files, and there is the danger that an interface might be read twice in the course of compiling a file.  
This can be illegal.  
To guard against this, each header fileuses the preprocessor to define a symbol when the class interface is read.


##### Scope Resolution Operator: `::`

In the implementation file, which typically ends in `.cpp`, `.cc`, or `.C`, each member function must identify the class that it is part of.  
Otherwise, it would be assumed that the functionis in global scope (and **zillions** of errors would result).  
The syntax is `ClassName::member`.The `::` is called the **scope resolution operator**.


##### Signatures Must Match Exactly

The signature of an implemented member function must match exactly the signature listed in the class interface.


##### Objects Are Declared Like Primitive Types

In C++11, we can write:

```cs
IntCell obj1;       // Zero parameter constructor, same as classic
IntCell obj2 {12};  // One parameter constructor, same as classic
IntCell obj4 {};    // Zero parameter constructor
```


#### 1.4.4 `vector` and `string`

The problem with the built-in C++ array is that it does not behave like a first-class object.  
For instance, built-in arrays cannotbe copied with =, a built-in array does not remember how many items it can store, and its indexing operator does not check that the index is valid.  
The built-in string is simply anarray of characters, and thus has the liabilities of arrays plus a few more.  
For instance, == does not correctly compare two built-in strings.

Initialize a vector in C++11:

`vector<int> daysInMonth {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};`

A vector of size 1 with a single element 12 in position 0:

`vector<int> daysInMonth {12};`

A vector of size 12:

`vector<int> daysInMonth(12); // Must use () to call constructor that takes size`

Using a **range `for`** to access every element sequentially in a collection

```cs
int sum = 0;
for(auto x : squares)
    sum += x;
```

> To change the contents, use  
> `for (auto &x : container)`  
> instead.

--------------------------------------------------------------------------------


### 1.5 C++ Details


#### 1.5.1 Pointers

A **pointer variableis** a variable that stores the address where another object resides.

To illustrate the operations that apply to pointers, we rewrite Figure 1.9 (TestIntCell.cpp) to dynamically allocate theIntCell.  
It must be emphasized that for a simple IntCell class, there is no good reason to write the C++ code this way.  
We do it only to illustrate dynamic memory allocation  in  a  simple  context.  
Later in the text, we will see more complicated classes, where this technique is useful and necessary.  

###### Figure 1.11 Program that uses pointers to IntCell (there is no compelling reason to do this)

```cs
int main()
{
    IntCell *m;

    m = new IntCell{0};
    m->write(5);
    cout << "Cell contents: " << m->read() << endl;

    delete m;
    return 0;
}
```


##### Declaration

The use of uninitialized pointers typically crashes programs, because they result in access of memory locations that do not exist.  
In general,it is a good idea to provide an initial value, either by

`IntCell *m = new IntCell{0};`

or by initializing m to the `nullptr` pointer.


##### Dynamic Object Creation

Several ways to create an object using its zero-parameter constructor:

```cpp
m = new IntCell( );    // OK
m = new IntCell{ };    // C++11
m = new IntCell;       // Preferred in this text
```


##### Garbage Collection and `delete`

When an object that is allocated by `new` is no longer referenced, the `delete` operation must be applied to the object (through a pointer).  
Otherwise, the memory that it consumes is lost (until the program terminates).  
This is known as a **memory leak**. 

Memory leaks are, unfortunately, common occurrences in many C++ programs.  
Fortunately, many sources of memory leaks can be automatically removed with care.  
One important rule is to not use `new` when an **automatic variable** can be used instead.  
In the original program, theIntCellis not allocated bynewbut instead is allocated as a local variable.  
In that case, the memory for the IntCell is automatically reclaimed when the functionin which it is declared returns.


##### Assignment and Comparison of Pointers

Assignment and comparison of pointer variables in C++ is based on the value of the pointer, meaning the memory address that it stores.


##### Accessing Members of an Object through a Pointer (`->`)


##### Address-of Operator (`&`)


#### 1.5.2 Lvalues, Rvalues, and References

An **lvalue** is an expression that identifies a non-temporary object.  
An **rvalue** is anexpression that identifies a temporary object or is a value (such as a literal constant) notassociated with any object.

As a general rule, ifyou have a name for a variable, it is an lvalue, regardless of whether it is modifiable.

`const int x = 2;`  
`intz=x+y;`  
`string str = "foo";`

For the above declarations 2,"foo", x+y, are all rvalues:
- 2 and "foo" are rvalues because they are literals.
- Intuitively, x+y is an rvalue because its value is temporary; it is certainly not x or y, but it is stored somewhere prior to being assigned to z.

In C++11, an **lvalue reference** is declared by placing an `&` after some type.  
An lvalue reference then becomes a synonym (i.e., another name) for the object it references.

In C++11, An **rvalue reference** is declared by placing an `&&` after some type.  
An rvalue reference has the same characteristics as an lvalue reference except that, unlike an lvaluereference, an rvalue reference can also reference an rvalue (i.e., a temporary).


##### lvalue references use #1: aliasing complicated names

The simplest use, which we will see in Chapter 5, is to use a local reference variable solelyfor the purpose of renaming an object that is known by a complicated expression.


##### lvalue references use #2: range `for` loops

```cs
for (auto &x : arr)
    ++x;
```


##### lvalue references use #3: avoiding a copy

In many instances, we only need the value and will not make any changes to a large object, here we can declare a reference.  
`auto` will deduce constness.

1. Reference  variables  are  often  used  to  avoid  copying  objects  across  function-call boundaries (either in the function call or the function return).
2. Syntax  is  needed  in  function  declarations  and  returns  to  enable  the  passing  andreturning using references instead of copies.


#### 1.5.3 Parameter Passing

4 ways to pass parameters in C++11:

1. **call-by-value**: for small objects and not altered by function
2. **call-by-constant-reference** (`const &`): for large objects to avoid copying and not altered
3. **call-by-(lvalue-)reference** (`&`): altered by function
4. **call-by-rvalue-reference** (`&&`): for move assignments

call-by-rvalue-reference:  
The central concept is that since an rvalue stores a temporary that isabout to be destroyed, an expression such as x=rval (where rval is an rvalue) can be implemented by a move instead of a copy;  
often moving an object’s state is much easierthan copying it, as it may involve just a simple pointer change.

This gives a primary use caseof overloading a function based on whether a parameter is an lvalue or rvalue, such as:

`string randomItem(const vector<string> &arr);      // returns random item in lvalue arr`  
`string randomItem(vector<string> &&arr);           // returns random item in rvalue arr`

`vector<string> v{"hello", "world"};`  
`cout << randomItem(v) << endl;                     // invokes lvalue method`  
`cout << randomItem({"hello", "world"}) << endl;    // invokes rvalue method`

It is easy to test that with both functions written, the second overload is called on rvalues, while the first overload is called on lvalues, as shown above.  
The most common use of this idiom is in defining the behavior of `=` and in writing constructors, and this discussion isdeferred until Section 1.5.6.


#### 1.5.4 Return Passing

The most straightforward: **return-by-value**.

Use **return-by-constant-reference** to avoid copy.  
However, the caller must also use a constant reference to access the return value, otherwise, there will still be a copy.

Historically, C++ programmers have gone to great extent to rewrite their code in an unnatural way, using techniques involving pointers or additional parameters that decrease readability and maintainability, eventually leading to programming errors.

In C++11, objects can define move semantics that can be employed when return-by-value is seen;  
in effect, the result vector will be moved to sums, and the vector implementation is optimized to allow this to be done with *little more than a pointer change*.


###### Figure 1.13 Returning of a stack-allocated rvalue in C++11

```cs
vector<int> partialSum(const vector<int> &arr)
{
    vector<int> result(arr.size( ));
    
    result[0] = arr[0];
    for(int i = 1; i < arr.size(); ++i)
        result[i] = result[i-1] + arr[i];
    
    return result;
}

vector<int> vec;
...
vector<int> sums = partialSum(vec); // Copy in old C++; move in C++11
```

In addition to the return-by-value and return-by-constant-reference idioms, functions can use return-by-reference.  
This idiom is used in a few places to allow the caller of a function to have modifiable access to the internal data representation of a class.  
Return-by-reference in this context is discussed in Section 1.7.2 when we implement a simple matrix class.


#### 1.5.5 `std::swap` and `std::move`

When swapping, if the right-hand side of the assignment operator (or constructor) is an rvalue, then if the object supports moving, we can automatically avoid copies.

Note that the name is misleading;  
`std::move` doesn’t move anything;  
rather, it makesa value subject to be moved.


###### Swapping by three copies

```cpp
void swap(double &x, double &y)
{
  double tmp = x;
  x = y;
  y = tmp;
}

void swap(vector<string> &x, vector<string> &y)
{
  vector<string> tmp = x;
  x = y;
  y = tmp;
}
```


###### Swapping by three moves; first with a type cast, second using `std::move`

```cpp
void swap(vector<string> &x, vector<string> &y)
{
  vector<string> tmp = static_cast<vector<string> &&>(x);
  x = static_cast<vector<string> &&>(y);
  y = static_cast<vector<string> &&>(tmp);
}

void swap(vector<string> &x, vector<string> &y)
{
  vector<string> tmp = std::move(x);
  x = std::move(y);
  y = std::move(tmp);
}
```


#### 1.5.6 The Big-Five: Destructor, Copy Constructor, Move Constructor, Copy Assignment `operator=`, Move Assignment `operator=`

In C++11, classes come with five special functions that are already written for you.

- destructor
- copy constructor
- move constructor
- copy assignment operator
- move assignment operator

Collectively these are the **big-five**. In many cases, you can accept the default behavior provided by the compiler for the big-five.  
Sometimes you cannot.


##### Destructor

The destructor is called whenever an object goes out of scope or is subjected to a `delete`.  
Typically, the only responsibility of the destructor is to free up any resources that were acquired during the use of the object.


##### Copy Constructor and Move Constructor

There are two special constructors that are required to construct a new object, initializedto the same state as another object of the same type.  
These are the copy constructor if the existing object is an lvalue, and the move constructor if the existing object is an rvalue (i.e., a temporary that is about to be destroyed anyway).  
For any object, such as anIntCellobject, a copy constructor or move constructor is called in the following instances:

- a declaration with initialization, such as

  `IntCell B = C;   // Copy construct if C is lvalue; Move construct if C is rvalue`  
  `IntCell B{C}; // Copy construct if C is lvalue; Move construct if C is rvalue`

  but not

  `B = C;           // Assignment operator, discussed later`

- an object passed using call-by-value (instead of by & or const &), which, as mentioned earlier, should rarely be done anyway.
- an object returned by value (instead of by&orconst &). Again, a copy constructor isinvoked if the object being returned is an lvalue, and a move constructor is invoked ifthe object being returned is an rvalue.


##### Copy Assignment and Move Assignment (`operator=`)

The assignment operator is called when `=` is applied to two objects that have both beenpreviously constructed.  
`lhs=rhs` is intended to copy the state ofrhsintolhs.Ifrhsis anlvalue, this is done by using the copy assignment operator;  
if rhs is an rvalue (i.e., a tem-porary that is about to be destroyed anyway), this is done by using the move assignment operator.  
By default, the copy assignment operator is implemented by applying the copyassignment operator to each data member in turn.


##### Defaults

If a class consists of data members that are exclusively primitive types and  objects for which the defaults make sense, the class defaults will usually make sense.  
Thus a class whose data members are `int`, `double`, `vector<int>`, `string`, and even `vector<string>` can accept the defaults.

The main problem occurs in a class that contains a data member that is a pointer.  
We will describe the problem and solutions in detail in Chapter 3;  
for now, we can sketchthe problem.

Suppose the class contains a single data member that is a pointer.  
This pointer points at a dynamically allocated object.  
The default destructor does nothing to data members that are pointers (for good reason—recall that we must delete ourselves).  
Furthermore, the copy constructor and copy assignment operator both copy the value of the pointer rather than the objects being pointed at.  
Thus, we will have two class instances that contain pointers that point to the  same object.  
This is a so-called **shallow copy**.  
Typically, we would expect a **deep copy**, in which a clone of the entire object is made.  
Thus,as a result, when a class contains pointers as data members, and deep semantics are important, we typically must implement the destructor, copy assignment, and copy constructors ourselves.  
Doing so removes the move defaults, so we also must implement move assign-ment and the move constructor.

As a general rule, either you

- accept the default for all five operations

or you should

- declare all five, and explicitly
    -  define
    -  default (use the keyword `default`)
    -  disallow each (use the keyword `delete`)

Generally we will define all five.

ForIntCell, the signatures of these operations are

```cs
~IntCell();                             // Destructor
IntCell(const IntCell &rhs);            // Copy constructor
IntCell(IntCell &&rhs);                 // Move constructor
IntCell &operator=(const IntCell &rhs); // Copy assignment
IntCell &operator=(IntCell &&rhs);      // Move assignment
```

The return type of `operator=` is a reference to the invoking object, so as to allow chained assignments `a=b=c`.  
Though it would seem that the return type should be a const reference, so as to disallow nonsense such as `(a=b)=c`, that expression is in fact allowed in C++ even for integer types.  
Hence, the reference return type (rather than the const reference returntype) is customarily used but is not strictly required by the language specification.

If you write any of the big-five, it would be good practice to explicitly consider all the others, as the defaults may be invalid or inappropriate.  
In a simple example in which debugging code is placed in the destructor, no default move operations will be generated.  
And although unspecified copy operations are generated, that guarantee is deprecated and might not be in a future version of the language.  
Thus, it is best to explicitly list the copy-and-move operations again:

```cs
~IntCell() { cout << "Invoking destructor" << endl; }   // Destructor
IntCell(const IntCell &rhs) = default;                  // Copy constructor
IntCell(IntCell &&rhs) = default;                       // Move constructor
IntCell &operator=(const IntCell &rhs) = default;       // Copy assignment
IntCell &operator=(IntCell &&rhs) = default;            // Move assignment
```

Alternatively, we could disallow all copying and moving of `IntCell`s

```cs
IntCell(const IntCell &rhs) = delete;               // No Copy constructor
IntCell(IntCell &&rhs) = delete;                    // No Move constructor
IntCell &operator=(const IntCell &rhs) = delete;    // No Copy assignment
IntCell &operator=(IntCell &&rhs) = delete;         // No Move assignment
```

If the defaults make sense in the routines we write, we will always accept them.  
However, if the defaults do not make sense, we will need to implement the destructor, copy-and-move constructors, and copy-and-move assignment operators.  
When the default does not work, the copy assignment operator can generally be implemented by creating a copy using the copy constructor and then swapping it with the existing object.  
The move assignment operator can generally be implemented by swapping member by member.


##### When the Default Do Not Work

The most common situation in which the defaults do not work occurs when a data member is a pointer type and the pointer is allocated by some object member function (suchas the constructor).  
As an example, suppose we implement the IntCellby dynamically allocating an int, as shown in Figure 1.16.  
For simplicity, we do not separate the interfaceand implementation.


###### Figure 1.16 Data members is a pointer; defaults are no good

```cs
class IntCell
{
  public:
    explicit IntCell(int initialValue = 0)
    { storedValue = new int{initialValue}; }

    int read() const
    { return *storedValue; }
    void write(int x)
    { *storedValue = x; }

  private:
    int *storedValue;
};
```

There are now numerous problems that are exposed in Figure 1.17.

First, the output is three 4s, even though logically only `a` should be 4.  
The problem is that the default copy assignment operator and copy constructor copy the pointer `storedValue`.  
Thus `a.storedValue`, `b.storedValue`, and `c.storedValue` all point at the same int value.  
These copies are shallow;  
the pointers rather than the pointees are copied.

A second, less obvious problem is a memory leak.  
The int initially allocated by a’s constructor remains allocated and needs to be reclaimed.  
The int allocated by c’s constructor is no longer referenced by any pointer variable.  
It also needs to be reclaimed, but we no longer have a pointer to it.


###### Figure 1.17 Simple function that exposes problems in Figure 1.16

```cs
int f()
{
    IntCell a{2};
    IntCell b = a;
    IntCell c;

    c = b;
    a.write(4);
    cout << a.read() << endl << b.read() << endl << c.read() << endl;

    return 0;
}
```

To fix these problems, we implement the big-five.  
The result (again without separation of interface and implementation) is shown in Figure 1.18.  
As we can see, once the destructor is implemented, shallow copying would lead to a programming error: Two IntCell objects would have storedValue pointing at the sameint object.  
Once the first IntCell object’s destructor was invoked to reclaim the object that its storedValue pointer was viewing, the second IntCell object would have a stale storedValue pointer.  
This is why C++11 has deprecated the prior behavior that allowed default copy operations even if a destructor was written.


###### Figure 1.18 Data member is a pointer; big-five is written

```cs
class IntCell
{
  public:
    explicit IntCell(int initialValue = 0)
    { storedValue = new int{initialValue}; }
    
    ~IntCell()                                              // Destructor
    { delete storedValue; }
    
    IntCell(const IntCell &rhs)                             // Copy constructor
    { storedValue = new int{*rhs.storedValue}; }
    
    IntCell(IntCell &&rhs) : storedValue{rhs.storedValue}   // Move constructor
    { rhs.storedValue = nullptr; }
    
    IntCell &operator=(const IntCell &rhs)                  // Copy assignment
    {
        if (this != &rhs)
            *storedValue = *rhs.storedValue;
        return *this;
    }
    
    IntCell &operator=(IntCell &&rhs)                       // Move assignment
    {
        std::swap(storedValue, rhs.storedValue);
        return *this;
    }
    
    int read( ) const
    { return *storedValue; }
    void write( int x )
    { *storedValue = x; }
    
  private:
    int *storedValue;
};
```

The copy assignment operator at lines 16–21 uses a standard idiom of checking for aliasing at line 18 (i.e., a self-assignment, in which the client is making a call `obj=obj`) and then copying each data field in turn as needed.  
On completion, it returns a referenceto itself using *this.  
InC++11, copy assignment is often written using a **copy-and-swap** idiom, leading to an alternate implementation:

```cs
IntCell &operator=(const IntCell &rhs)  // Copy assignment
{
    IntCell copy = rhs;
    std::swap(*this, copy);
    return *this;
}
```

Line 18 places a copy of `rhs` into copy using the copy constructor.  
Then this copyis swapped into `*this`, placing the old contents into copy.  
On return, a destructor is invoked for copy, cleaning up the old memory.

For IntCell this is a bit inefficient, but for other types, especially those with many complex interacting data members, it can be a reasonably good default.  
Notice that if swap were implemented using the basic copy algorithm in Figure 1.14, the copy-and-swap idiom would not work, because there would be mutual nonterminating recursion.  
In C++11 we have a basic expectation that swapping is implemented either with three moves or by swapping member by member.

The move constructor at lines 13 and 14 moves the data representation from rhs into *this; then it sets rhs’ primitive data (including pointers) to a valid but easily destroyed state.  
Note that if there is non-primitive data, then that data must be moved in the initialization list.  
For example, if there were also `vector<string> items`, then the constructor would be:

```cs
IntCell(IntCell &&rhs) : storedValue{rhs.storedValue},  // Move constructor
                         items{std::move(rhs.items)}
{ rhs.storedValue = nullptr; }
```

Finally, the move assignment operator at lines 23–27 is implemented as a member-by-member swap.  
Note that sometimes it is implemented as a single swap of objects in the same manner as the copy assignment operator, but that only works if swap itself is implemented as a member-by-member swap.  
If swap is implemented as three moves, then we would have mutual nonterminating recursion.


#### 1.5.7 C-style Arrays and Strings

The C++ language provides a built-in C-style array type.  
To declare an array, `arr1` , of 10 integers, one writes:

`int arr1[10];`

`arr1` is actually a pointer to memory that is large enough to store 10 ints, rather than a first-class array type.  

If the size is unknown, we must explicitly declare a pointer and allocate memory via `new[]`.  
For instance,

`int *arr2 = new int[n];`

Now arr2 behaves like arr1, except that it is not a constant pointer.  
Thus, it can be made to point at a larger block of memory.  
However, because memory has been dynamically allocated, at some point it must be freed with `delete[]`:

`delete [ ] arr2;`

Otherwise, a memory leak will result, and the leak could be significant if the array is large.

Built-in C-style strings are implemented as an array of characters.  
To avoid having to pass the length of the string, the special null-terminator `’\0’` is used as a character thatsignals the logical end of the string.  
Strings are copied by `strcpy`, compared with `strcmp`, and their length can be determined by `strlen`.  
Individual characters can be accessed by the array indexing operator.

These strings have all the problems associated with arrays, including difficult memory management, compounded by the fact that when strings arecopied, it is assumed that the target array is large enough to hold the result.  
When it is not, difficult debugging ensues, often because room has not been left for the null terminator.

It is almost always better to use the `vector` and `string` class, but you may be forced to use the C-style when interacting with library routines that are designed to work with both C and C++.  
It also is occasionally necessary (but this is rare) to use the C-style in a section ofcode that must be optimized for speed.

--------------------------------------------------------------------------------


### 1.6 Templates


#### 1.6.1 Function Templates

A **function template** is not an actual function, but instead is a pattern for what could become a function.


###### Figure 1.19 `findMax` function template

```cs
// Return the maximum item in array a.
// Assumes a.size() > 0.
// Comparable objects must provide operator< and operator=
template<typename Comparable>
const Comparable &findMax(const vector<Comparable> &a)
{
    int mainIndex = 0;

    for (int i = 1; i < a.size(); ++i)
        if (a[maxIndex] < a[i])
            maxIndex = i;
    
    return a[maxIndex];
}
```

It should be noted that an expansion for each new type generates additional code;  
this is known as **code bloat** when it occurs in large projects.  

It is customary to include, prior to any template, comments that explain what assumptions are made about the template argument(s).  
This includes assumptions about what kinds ofconstructors are required.

Note that if there is a nontemplate and atemplate and both match, then the nontemplate gets priority.  
Also note that if there are twoequally close approximate matches, then the code is illegal and the compiler will declarean ambiguity.


#### 1.6.2 Class Templates

If we implement class templates as a single unit, then there is very little syntax baggage.  
Many class templates are, in fact, implemented this way because, currently, separate com-pilation of templates does not work well on many platforms.  
Therefore, in many cases, theentire class, with its implementation, must be placed in a `.h` file.  
Popular implementationsof the STL follow this strategy.

An alternative, discussed in Appendix A, is to separate the interface and implementa-tion of the class templates.  
This adds extra syntax and baggage and historically has beendifficult for compilers to handle cleanly.  
To avoid the extra syntax throughout this text, weprovide, when necessary, in the online code, class templates with no separation of interfaceand implementation.  
In the figures, the interface is shown as if separate compilation wasused, but the member function implementations are shown as if separate compilation wasavoided.  
This allows us to avoid focusing on syntax.


#### 1.6.3 Object, Comparable, and an Example

In this text, we repeatedly use `Object` and `Comparable` as generic types.  
`Object` is assumed to have a zero-parameter constructor, an `operator=`, and a copy constructor.  
`Comparable`, as suggested in the `findMax` example, has additional functionality in the form of `operator<` that can be used to provide a total order.


#### 1.6.4 Function Object

In Section 1.6.1, we showed how function templates can be used to find  the maximum item in an array.

However, the template has an important limitation: It works only for objects that have an `operator<` function defined, and it uses that `operator<` as the basis for all com-parison decisions.  
In many situations, this approach is not feasible.

The solution, in these cases, is to rewrite findMaxto accept as parameters an array of objects and a comparison function that explains how to decide which of two objects is the larger and which is the smaller.  
In effect, the array objects no longer know how tocompare themselves;  
instead, this information is completely decoupled from the objects inthe array.

An ingenious way to pass functions as parameters is to notice that an object contains both data and member functions, so we can define a class with no data and one member function, and pass an instance of the class.  
In effect, a function is being passed by placing it inside an object.  
This object is commonly known as a **function object**.

Figure 1.24 shows the simplest implementation of the function object idea.  
findMax takes a second parameter, which is a generic type.  
In order for the findMax template to expand without error, the generic type must have a member function named `isLessThan`, which takes two parameters of the first generic type (Object) and returns a bool.  
Otherwise, an error will be generated at line 9 when the template expansion  is attempted by the compiler.


###### Figure 1.24 Simplest idea of using a function object as a second parameter to `findMax`; output is ZEBRA

```cs
// Generic findMax, with a function object, Version #1.
// Precondition: a.size( ) > 0.
template <typename Object, typename Comparator>
const Object &findMax(const vector<Object> &arr, Comparator cmp)
{
    int maxIndex = 0;
    
    for(int i = 1; i < arr.size(); ++i)
        if(cmp.isLessThan(arr[maxIndex], arr[i]))
            maxIndex = i;
    
    return arr[maxIndex];
}

class CaseInsensitiveCompare
{
  public:
    bool isLessThan(const string &lhs, const string &rhs) const
    { return strcasecmp(lhs.c_str(), rhs.c_str()) < 0; }
};

int main()
{
    vector<string> arr = {"ZEBRA", "alligator", "crocodile"};
    cout << findMax(arr, CaseInsensitiveCompare{}) << endl;
    
    return 0;
}
```

C++ function objects are implemented using this basic idea, but with some fancy syntax.  
1. First, instead of using a function with a name, we use operator overloading.  
   Instead of the function being isLessThan, it is operator().  
2. Second, when invoking `operator()`, `cmp.operator()(x,y)` can be shortened to `cmp(x,y)`(in other words, it looks like a function call, and consequently `operator()` is known as the function call operator).  
   As a result, the name of the parameter can be changed to the more meaningful `isLessThan`, and the call is `isLessThan(x,y)`.  
3. Third, we can provide a version offindMaxthat works without a func-tion object.  
   The implementation uses the Standard Library function object templateless(defined in header filefunctional) to generate a function object that imposes the normaldefault ordering.

Figure 1.25 shows the implementation using the more typical, somewhat cryptic, C++ idioms.


###### Figure 1.25 Using a function object C++ style, with a second version offindMax; output is ZEBRA, then crocodile

```cs
// Generic findMax, with a function object, C++ style.
// Precondition: a.size( ) > 0.
template <typename Object, typename Comparator>
const Object &findMax(const vector<Object> &arr, Comparator isLessThan)
{
    int maxIndex = 0;
    
    for (int i = 1; i < arr.size(); ++i)
        if (isLessThan(arr[maxIndex], arr[i]))
            maxIndex = i;
    
    return arr[maxIndex];
}

// Generic findMax, using default ordering.
#include <functional>

template <typename Object>
const Object &findMax(const vector<Object> &arr)
{
    return findMax(arr, less<Object>{});
}

class CaseInsensitiveCompare
{
  public:
    bool operator()(const string &lhs, const string &rhs) const
    { return strcasecmp(lhs.c_str(), rhs.c_str()) < 0; }
};

int main()
{
    vector<string> arr = {"ZEBRA", "alligator", "crocodile"};
    
    cout << findMax(arr, CaseInsensitiveCompare{}) << endl;
    cout << findMax(arr) << endl;
    
    return 0;
}
```


#### 1.6.5 Separate Compilation of Class Templates

Like regular classes, class templates can be implemented either entirely in their declarations, or we can separate the interface from the implementation.  
However, compiler support for separate compilation of templates historically has been weak and platform-specific.  
Thus, in many cases, the entire class template with its implementation is placed ina single header file.  
Popular implementations of the Standard Library follow this strategyto implement class templates.

--------------------------------------------------------------------------------


### 1.7 Using Matrices

The C++ library does not provide a matrix class.  
However, a reasonable matrix class can quickly be written.  
The basic idea is to use a vector of vectors.  
Doing this requires additional knowledge of operator overloading.  
For the matrix, we define `operator[]`,  namely, the array-indexing operator.  
The matrix class is given in Figure 1.26.


###### Figure 1.26 A complete `matrix` class

```cs
#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
using namespace std;

template <typename Object>
class matrix
{
  public:
    matrix(int rows, int cols) : array(rows)
    {
        for (auto &thisRow : array)
            thisRow.resize(cols);
    }
    
    matrix(vector<vector<Object>> v) : array{v} {}
    matrix(vector<vector<Object>> &&v) : array{std::move(v)} {}
    
    const vector<Object> &operator[](int row) const
    { return array[row]; }
    vector<Object> &operator[](int row)
    { return array[row]; }
    
    int numrows() const
    { return array.size( ); }
    int numcols( ) const
    { return numrows() ? array[0].size() : 0; }
        
  private:
    vector<vector<Object>> array;
};

#endif // MATRIX_H
```


#### 1.7.1 The Data Members, Constructor, and Basic Accessors


#### 1.7.2 `operator[]`

The idea of `operator[]` is that if we have a matrix m, then m[i] should return a vector corresponding to row i of matrix m.  
If this is done, then m[i][j] will give the entry in position j for vector m[i], using the normal vector indexing operator.  
Thus, the matrix operator[] returns a vector<Object> rather than an Object.

Should operator[] return-by-reference or return-by-constant-reference?  
Consider the following method (ignore the possibility of aliasing or incompatible sizes, neither of which affects the algorithm):

```cs
void copy(const matrix<int> &from, matrix<int> &to)
{
    for(int i = 0; i < to.numrows(); ++i)
        to[i] = from[i];
}
```

In the copy function, we attempt to copy each row in matrix `from` into the corresponding row in matrix `to`.  
Clearly, if `operator[]` returns a constant reference, then `to[i]` cannot appear on the left side of the assignment statement.  
Thus, it appears that `operator[]` should return a reference.  
However, if we did that, then an expression such as `from[i] = to[i]` would compile, since `from[i]` would not be a constant vector, even though `from` was a constant matrix.  
That cannot be allowed in a good design.

So what we really need is for `operator[]` to return a constant reference for `from`, but a plain reference for `to`.  
In other words, we need two versions of `operator[]`, which differonly in their return types.  
That is not allowed.  
However, there is a loophole:  
Since member function constness (i.e., whether a function is an accessor or a mutator) is part of the signature, we can have the accessor version of `operator[]` return a constant reference, and have the mutator version return the simple reference.  
Then, all is well.  
This is shown inFigure 1.26.


#### 1.7.3 Big-Five

These are all taken care of automatically, because thevectorhas taken care of it. Therefore, this is all the code needed for a fully functioning matrix class.

--------------------------------------------------------------------------------


### Summary

This chapter sets the stage for the rest of the book.  
The time taken by an algorithm con-fronted with large amounts of input will be an important criterion for deciding if it is agood algorithm.  
(Of course, correctness is most important.)  
We will begin to address theseissues in the next chapter and will use the mathematics discussed here to establish a formalmodel.

--------------------------------------------------------------------------------

EOF
