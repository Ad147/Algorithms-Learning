DSAA-Ch01.md

Notes of Data Structures and Algorithm Analysis in C++
================================================================================

Ad  
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

$f(x) = 2f(x - 1) + x^2$

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

// ### 1.4 C++ Classes
