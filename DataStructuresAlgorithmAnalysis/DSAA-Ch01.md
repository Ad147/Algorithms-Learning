DSAA-Ch01.md

Notes of Data Structures and Algorithm Analysis in C++ 4th Edition
================================================================================

Ad  
Init: 18Nov16

Chapter 1 Programming: A General Overview
--------------------------------------------------------------------------------

 - See that how a program performs for reasonably large input is just as important as itsperformance on moderate amounts of input
 - Summarize the basic mathematical background needed for the rest of the book
 - Briefly review **recursion**
 - Summarize some important features of C++that are used throughout the text

### 1.1 What's This Book About?

### 1.2 Mathematics Review

#### 1.2.1 Exponents

X^A * X^B == X^(A+B)

X^A / X^B == X^(A-B)

(X^A)^B == X^(A*B)

X^N + X^N == 2 \* X^N != X^(2\*N)

2^N + 2^N == 2^(N+1)

#### 1.2.2 Logarithms

In computer science, all logarithms are to the base 2 unless specified otherwise.

##### Definition 1.1

X^A == B if and only if logX(B) == A

##### Theorem 1.1

logA(B) == logC(B) / logC(A) ; A,B,C > 0, A != 1

##### Theorem 1.2

log(AB) == logA + logB ; A,B > 0

#### 1.2.3 Series
