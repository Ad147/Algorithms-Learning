Algorithms-1.md

Notes of Algorithms 4th edition
================================================================================

Ad  
Init: 2018Jul31

1 Fundamentals
--------------------------------------------------------------------------------

> The term `algorithm` is used to describe a finite, deterministic, and effective problem-solving method suitable for implementation as a computer program.
>
> Algorithms and data structures go hand in hand.  
> Data structures exist as the byproducts or end products of algorithms and that we must therefore study them to understand the algorithms.

### 1.1 Basic Programming Model

> As Java is very similar to C++, many of the contents are ignored.

#### Basic Structure of a Java Program

A Java program (class) is either a *library of static methods* (functions) or a *data type definition*.

Five(?) components, the basis of programming in Java:
 - Primitive data types
 - Statements: declarations, assignments, conditionals, loops, calls, and returns
 - Arrays
 - Static methods
 - Strings
 - Input/output sets
 - Data abstraction

#### Primitive Data Types and Expressions

###### Basic building blocks for Java programs

| Term                | Examples                  | Definition                                                                              |
| ------------------- | ------------------------- | --------------------------------------------------------------------------------------- |
| primitive data type | `int double boolean char` | a set of values and a set of operations on those values (built in to the Java language) |
| identifier          | `a abc ab$ ab123`         | a sequence of letters, digits, and $, the first of which is not a digit                 |
| variable            | [any identifier]          | names a data-type value                                                                 |
| operator            | `+ - * /`                 | names a data-type operation                                                             |
| literal             | `int 1 0 -42`             | source-code representation of a value                                                   |
|                     | `double 2.0 1.0e-15 3.14  |                                                                                         |
|                     | `boolean true false`      |                                                                                         |
|                     | `char 'a' '+' '9' '\n'`   |                                                                                         |
| expressions         | `int lo + (hi - lo)/2`    | a literal, a value, or a sequence of operations                                         |
|                     | `double 1.0e-15 * t`      | on literals and/or variables that produces a value                                      |
|                     | `boolean lo <= hi`        |                                                                                         |

##### Expressions

Among logical operators, `!` is the highest precedence, followed by `&&` and then `||`

##### Type conversion

 - `(int) 3.7` is 3
 - `(double) 3` is 3.0

##### Other primitive types

 - 64-bit integers: `long`
 - 16-bit integers: `short`
 - 16-bit characters: `char`
 - 8-bit integers: `byte`
 - 32-bit single-precision real numbers: `float`

#### Statements

#### Shortcut notations

 - Initializing declaration: `int i = 1;`
 - Implicit assignment: `i++;` `i += 1;`
 - Single-statement blocks: if `if`/`while` has only one single statement, the `()` may be omitted
 - `for` notations

#### Arrays

##### Creating and initializing an array

 - Declare the array name and type
 - Create the array
 - Initialize the array values

```java
// long form
double[] a;        // declaration
a = new double[N]; // creaation
for (int i = 0; i < N; i++)
    a[i] = 0.0;    // initialization

// short form
double[] a = new double[N];

// initializing declaration
int[] a = {1, 1, 2};
```

###### Task: matrix-matrix multiplication (square matrices) a[][]*b[][] = c[][]

```java
int N = a.length;
double[][] c = new double[N][N];
for (int i = 0; i < N; ++i)
    for (int j = 0; j < N; ++j)
    {
        // compute dot product of row i and column j
        for (int k = 0; k < N; ++k)
            c[i][j] += a[i][k] * b[k][j];
    }
```

#### Static Methods

### 1.2 Data Abstraction

### 1.3 Bags, Queues, and Stacks

### 1.4 Analysis of Algorithms

### 1.5 Case Study: Union-Find
