DSAA-Ch01.md

Notes of Data Structures and Algorithm Analysis in C++
================================================================================

Ad  
<ar><r></r></ar>  
Init: 18Nov16

Chapter 1 Programming: A General Overview
--------------------------------------------------------------------------------

- See that how a program performs for reasonably large input is just as important as itsperformance on moderate amounts of input
- Summarize the basic mathematical background needed for the rest of the book
- Briefly review **recursion**
- Summarize some important features of C++that are used throughout the text

--------------------------------------------------------------------------------

###### Table of Contents

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

--------------------------------------------------------------------------------

### 1.1 What's This Book About?

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

$$ log_A(B) = log_C(B) / logC(A); A,B,C > 0, A != 1 $$

###### Theorem 1.2

$$ log(AB) = logA + logB; A,B > 0 $$

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

###### Theorem 1.3

If N >= 1, then $\sum_{i=1}^N i^2 = N(N + 1)(2N + 1) / 6$

##### Proof by Counterexample

##### Proof by Contradiction

--------------------------------------------------------------------------------

### 1.3 A Brief Introduction to Recursion

A function that is defined in terms of itself is called **recursive**.

Not all mathematically recursive functions are efficiently (or correctly) implemented by C++’s simulation of recursion.  
The idea is that the recursive function f ought to be expressible in only a few lines, just like a non recursivefunction.

###### A recursive function $f(x) = 2f(x - 1) + x^2$

```cpp
int f(int x)
{
    if (x == 0) // base case
        return 0;
    else
        return 2 * f(x - 1) + x * x;
}
```

##### Printing Out Numbers

##### Recursion and Induction

The main problem with recursion is the hidden bookkeeping costs.

It is crucial to keep in mind the four basic rules of recursion:
1. *Base cases*. You must always have some base cases, which can be solved without recursion.
2. *Making progress*. For the cases that are to be solved recursively, the recursive call must always be to a case that makes progress toward a base case.
3. *Design rule*. Assume that all the recursive calls work.
4. *Compound interest rule*. Never duplicate work by solving the same instance of a problemin separate recursive calls.

--------------------------------------------------------------------------------

### 1.4 C++ Classes

#### 1.4.1 Basic `class` Syntax

members, member functions (methods), constructors.

#### 1.4.2 Extra Constructor Syntax and Accessors

###### `IntCell` class with revisions

```cpp
// A class for simulating an integer memory cell.
class IntCell
{
  public:
    explicit IntCell(int initialValue = 0)
        : storedValue{initialValue} {}
    int read() const { return storedValue; }
    void write(int x) { storedValue = x; }

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
The use of braces instead of parentheses is new in C++11 and is part of a larger effortto provide a uniform syntax for initialization everywhere.  
Generally speaking, anywhere you can initialize, you can do so by enclosing initializations in braces.  
(though there is one important *exception*, in Section 1.4.4, relating to vectors)

##### `explicit` Constructor

**You should make all one-parameter constructors `explicit` to avoid behind-the-scenes type conversions.**  Otherwise, there are somewhat lenient rules that will allow type conversions without explicit casting operations.  
Usually, this is unwanted behavior that destroys strong typing and can lead to hard-to-find bugs.  

As an example, consider the following:  
`IntCell obj;     // obj is an IntCell`  
`obj = 37;        // Should not compile: type mismatch`  
The code fragment above constructs anIntCellobjectobjand then performs an assign-ment statement.  
But the assignment statement should not work, because the right-handside of the assignment operator is not another IntCell.  
obj’s write method should have been used instead.  

However, C++ has lenient rules.  
Normally, a one-parameter constructor defines an *implicit type conversion*, in which a temporary object is created that makes an assignment (or parameter to a function) compatible.  
In this case, the compiler wouldattempt to convert  
`obj = 37;        // Should not compile: type mismatch`  
into  
`IntCell temporary = 37;`  
`obj = temporary;`  
Notice that the construction of the temporary can be performed by using the one-parameter constructor.  
The use of explicit means that a one-parameter constructor cannot be used to generate an implicit temporary.  
Thus, since IntCell’s constructor is declared explicit, the compiler will correctly complain that there is a type mismatch.

##### Constant Member Function

A member function that examines but does not change the state of its object is an *accessor*.  
A member function that changes the state is *amutator* (because it mutates the state of theobject). 

To make a member function an accessor, we must add the keyword `const` after the closing parenthesis that ends the parameter type list.

#### 1.4.3 Separation of Interface and Implementation

###### `IntCell` class interface in *fileIntCell.h*

```cpp
#ifndef IntCell_H2
#define IntCell_H34

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

###### `IntCell` class implementation in *fileIntCell.cpp*

```cpp

#include "IntCell.h"

// Construct the IntCell with initialValue
IntCell::IntCell(int initialValue) : storedValue{initialValue} {}

// Return the stored value.
int IntCell::read() const { return storedValue; }

// Store x.
void IntCell::write(int x) { storedValue = x; }
```

##### Preprocessor Commands

##### Scope Resolution Operator: `::`

##### Signatures Must Match Exactly

##### Objects Are Declared Like Primitive Types

```cpp
IntCell obj1;     // Zero parameter constructor, same as before
IntCell obj2{12}; // One parameter constructor, same as before
IntCell obj4{};   // Zero parameter constructor
```

#### 1.4.4 `vector` and `string`

Initialize a vector with `=` and initialization list:  
`vector<int> daysInMonth = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };`

A vector of size 1 with a single element 12 in position 0:  
`vector<int> daysInMonth { 12 };`

A vector of size 12:  
`vector<int> daysInMonth( 12 );`

Using a **range `for`** to access every element sequentially in a collection

```cpp
int sum = 0;
for( auto x : squares )
    sum += x;
```

> To change the contents, use  
> `for (auto &x : container)`  
> instead.

--------------------------------------------------------------------------------

### 1.5 C++ Details

#### 1.5.1 Pointers

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

##### Assignment and Comparison of Pointers

Assignment and comparison of pointer variables in C++is based on the value of the pointer,meaning the memory address that it stores.

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

An *rvalue reference* has the same characteristics as an lvalue reference except that, unlike an lvaluereference, an rvalue reference can also reference an rvalue (i.e., a temporary).

##### lvalue references use #1: aliasing complicated names

The simplest use, which we will see in Chapter 5, is to use a local reference variable solelyfor the purpose of renaming an object that is known by a complicated expression.

##### lvalue references use #2: range `for` loops

##### lvalue references use #3: avoiding a copy

`auto` will deduce const-ness.

1. Reference  variables  are  often  used  to  avoid  copying  objects  across  function-call boundaries (either in the function call or the function return).
2. Syntax  is  needed  in  function  declarations  and  returns  to  enable  the  passing  andreturning using references instead of copies.

#### 1.5.3 Parameter Passing

1. **call-by-value**: for small objects and not altered by function
2. **call-by-constant-reference** (`const** &`): for large objects to avoid copying and not altered
3. **call-by-(lvalue-)reference** (`&`): altered by function
4. **call-by-rvalue-reference** (`&&`): for move assignments

#### 1.5.4 Return Passing

normally return-by-value.

uses return-by-constant-referenceto avoid copy.  
However, the caller must also use a constant reference to access the return value, otherwise, there will still be a copy.

In C++11, objects can define move semantics that can be employed when return-by-value is seen;  
in effect, the result vector will be moved to sums, and the vector implementation is optimized to allow this to be done with little more than a pointer change.

In addition to the return-by-value and return-by-constant-reference idioms, functionscan use return-by-reference.  
This idiom is used in a few places to allow the caller of afunction to have modifiable access to the internal data representation of a class.  
Return-by-reference in this context is discussed in Section 1.7.2 when we implement a simple matrixclass.

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

// #### 1.5.6 The Big-Five: Destructor, Copy Constructor, Move Constructor, Copy Assignment `operator=`, Move Assignment `operator=`

