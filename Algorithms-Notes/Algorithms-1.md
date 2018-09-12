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

```java
// binary search
// file: BinarySearch.java
import java.util.Arrays;

public class BinarySearch
{
    public static int rank(int key, int[] a)
    {
        int lo = 0;
        int hi = a.length - 1;
        while (lo <= hi)
        {
            int mid = lo + (hi - lo) / 2;
            if (key < a[mid]) hi = mid - 1;
            else if (key > a[mid]) lo = mid + 1;
            else return mid;
        }
        return -1;
    }

    public static void main(String[] args)
    {
        int[] whitelist = In.readInts(args[0]);
        Arrays.sort(whitelist);
        while (!StdIn.isEmpty())
        {
            int key = StdIn.readInt();
            if (rank(key, whitelist) == -1)
                StdOut.println(key);
        }
    }
}
```

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

###### Task: matrix-matrix multiplication

```java
// matrix-matrix multiplication
// square matrices
// a[][]*b[][] = c[][]
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

###### Square root method

```java
// sqare root (Newton's method)
public static double qurt(double c) // signature of the method
{                                   // method body
    if (c < 0) return Double.NaN;
    double err = 1e-15;
    double t = c;
    while (Math.abs(t - c/t) > err * t)
        t = (c/t + t) / 2.0;
    return t;
}
```

##### Properties of methods

 - Arguments are passed by value
 - Method names can be overloaded
 - A method has a single return value but may have multiple return statements
 - A method can have side effects

##### Recursion

There are 3 improtant rules of thumb in developing recursive programs:
 - The recursion has a base case-we always include a conditional statement as the first statement in the program that has a return
 - Recursive calls must address subproblems that are smaller in some sense, so that recursive calls converge (收敛) to the base case
 - Recursive calls should not address subproblems that overlap

```java
// recursive rank() in BinarySearch
public static int rank(int key, in[] a)
{return rank(key, a, 0, a.length - 1);}

public static int rank(int key, int[] a, int lo, int hi)
{
    // index of key in a[], if present, is not smaller than lo and not larger than hi
    if (lo > hi) return -1;
    int mid = lo + (hi - lo) / 2;
    if (key < a[mid]) return rank(key, a, lo, mid - 1);
    else if (key > a[mid]) return rank(key, a, mid + 1, hi);
    else return mid;
}
```

##### Basic programming model

##### Modular programming

##### Unit testing

##### External Libraries

 - Standard system libraries: `Math Integer Double String StringBuilder System`
 - Improted system libraries: `java.util.Arrays`
 - Our standard libraries: `StdIn StdOut StdDraw StdRandom StdStats In Out`

#### APIs

###### `public class Math`

|                                         |                                     |
| --------------------------------------- | ----------------------------------- |
| `static double abs(double a)`           | absolute value                      |
| `static double max(double a, double b)` | maximum of a & b                    |
| `static double min(double a, double b)` | minimum of a & b                    |
|                                         |
| `static double sin(double theta)`       | sine function                       |
| `static double cos(double theta)`       | cosine function                     |
| `static double tan(double theta)`       | tangent function                    |
| Note: angles are radians.               | `toDegree() toRadians()` to convert |
| `asin() acos() atan()` for inverse      |
| `static double exp(double a)`           | exponential (e^a)                   |
| `static double log(double a)`           | natural log (ln a)                  |
| `static double pow(double a, double b)` | raise a to the bth power (a^b)      |
|                                         |
| `static double random()`                | random number in [0, 1)             |
| `static double sqrt(double a)`          | square root                         |
|                                         |
| `static double E`                       | value of e (constant)               |
| `static double PI`                      | value of pi (constant)              |

##### Java libraries

##### Our standard libraries

###### `public class StdRandom`

|                                               |                                |
| --------------------------------------------- | ------------------------------ |
| `static void initialize(long seed)`           | initialize                     |
| `static double random()`                      | real between 0 and 1           |
| `static int uniform(int N)`                   | integer between 0 and N-1      |
| `static int uniform(int lo, int hi)`          | integer between lo and hi-1    |
| `static double uniform(double lo, double hi)` | real between lo and hi         |
| `static boolean bernoulli(double p)`          | true with probability p        |
| `static double gaussian()`                    | normal, mean 0, std dev 1      |
| `static double gaussion(double m, double s)`  | normal, mean m, std dev s      |
| `static int discrete(double[] a)`             | i with probability a[i]        |
| `static void shuffle(double[] a)`             | randomly shuffle the array a[] |

```java
// Implementations of static methods in StdRandom library

// intending random double in [a, b)
public static double uniform(double a, double b)
{return a + StdRandom.random() * (b-a)};

// intending random int in [0..N)
public static int uniform(int N)
{return (int) (StdRandom.random() * N;)}

// intending random int in [lo..hi)
public static int uniform(int lo, int hi)
{return lo + StdRandom.uniform(hi - lo);}

// intending random int drawn from discrete distribution
// (i with probability a[i])
public static int discrete(double[] a)
{
    // entries in a[] must sum to 1
    double r = StdRandom.random();
    double sum = 0.0;
    for (int i = 0; i < a.length; i++)
    {
        sum += a[i];
        if (sum >= r) return i;
    }
    return -1;
}

// randomly shuffle the elements in an array of double values
public static void shuffle(double[] a)
{
    int N = a.length;
    for (int i = 0; i < N; i++)
    {
        // exchange a[i] with random element in a[i..N-1]
        int r = i + StdRandom.uniform(N-i);
        double temp = a[i];
        a[i] = a[r];
        a[r] = temp;
    }
}
```

###### `public class StdStats`

|                                    |                          |
| ---------------------------------- | ------------------------ |
| `static double max(double[] a)`    | largest value            |
| `static double min(double[] a)`    | smallest value           |
| `static double mean(double[] a)`   | average                  |
| `static double var(double[] a)`    | sample variance (方差)   |
| `static double stddev(double[] a)` | sample stadard deviation |
| `static double median(double[] a)` | median                   |

##### Your own libraries

It is worthwhile to consider every program that you write as a library implementation.

#### Strings

A `String` is a Java data type but not a primitive type

##### Concatenation

 - Concatenation operator (+)

##### Conversion

 - `parseInt(String s)`: convert s to int
 - `toString(int i)`
 - `parseDouble(String s)`: convert s to double
 - `toString(double x)`

##### Automatic conversion

If one of the arguments of `+` is a String, Java automatically converts the other to a String.

##### COmmand-ine arguments

#### Input and output

##### Commands and arguments

###### Typical operating-system commands

|                                                      |                      |
| ---------------------------------------------------- | -------------------- |
| .java file name                                      | compile Java program |
| .class file name (no ext) and command-line arguments | run Java program     |
| any text file name                                   | print file contents  |

##### Standard output

| `public class StdOut`               |                              |
| ----------------------------------- | ---------------------------- |
| `static void print(String s)`       | print s                      |
| `static void println(String s)`     | print s, followed by newline |
| `static void println()`             | print a newline              |
| `static void printf(String f, ...)` | formatted print              |

##### Standard input

| `public class StdIn` |                                     |
| -------------------- | ----------------------------------- |
| `isEmpty()`          |                                     |
| `readInt()`          |                                     |
| `readDouble()`       |
| `readChar()`         |
| `readString()`       |
| `hasNextLine()`      | is there another line in the input? |
| `readLine()`         |
| `readAll()`          |

##### Redirection and piping

`% java RandomSeq 1000 100.0 200.0 > data.txt`  
write the output to `data.txt`

`% java Average < data.txt`  
read from the txt

`% java RandomSeq 1 0 2 | java Average`
"piping": redirect the output of one program to the input of another

##### Input and output from a file

###### Read data from files

| `public class In`                          |                 |
| ------------------------------------------ | --------------- |
| `static int[] readInts(String name)`       | read int values |
| `static double[] readDoubles(String name)` |
| `static String[] readStrings(String name)` |

| `public class Out`                           |                  |
| -------------------------------------------- | ---------------- |
| `static void write(int[] a, String name)`    | write int values |
| `static void write(double[] a, String name)` |
| `static void write(String[] a, String name)` |

Note: *StdIn and StdOut are supported (omit name argument)*

##### Standard drawing (basic methods)

 - `StdDraw.point(x0, y0)`
 - `StdDraw.line(x0, y0, x1, y1)`
 - `text(x, y, s)`
 - `circle/filledCircle(x, y, r)`
 - `ellipse/square/rectangle/polygon()`

##### Stadard drawing (control methods)

`setXscale()/setPenRadius()/setPenColor()/setFont()/setCanvasSize()/Clear()/show()`  
Using predefined colors: `StdDraw.RED` and so on

 - There are some examples of `StdDraw` plotting on the book

#### Binary Search

##### Binary search

##### Development client

For every algorithm implementation, we include a development client main() that can use with sample input files to learn about the algorithm and to test its performance.

##### Whitelisting

> When possible, our development clients are intended to mirror practical situations and demonstrate the need for the algorithm at hand. The process is known as *whitelisting*

##### Performance

#### Perspective

#### Q&A

 - Q. How to initialize a double variable to infinity?
 - A. `Double.POSITIVE_INFINITY` & `Double.NEGATIVE_INFINITY`

 - Q. Use < and > to compare String?
 - A. No. The operators are only for primitive types

 - Q. Can a static method take another static method as an argument in Java?
 - A. No.

--------------------------------------------------------------------------------

> For the reason that C++ is preferred to use, the rest parts of this chapter will be simplified.

### 1.2 Data Abstraction

#### Using abstract data types

##### API for an abstract data type

###### An API for a counter

| `public class Counter` |                                     |
| ---------------------- | ----------------------------------- |
| `Counter(String id)`   | create a counter named id           |
| `void increment()`     | increment the counter by one        |
| `int tally()`          | number of increments since creation |
| `String toString()`    | string representation               |

Even though the basis of a data-type definition is a set of values, the role of the values is not visible from the API, only the operations on those values.

##### Inherited methods

##### Client code

##### Objects

##### Creating objects

Each time that a client uses `new()`, the system
 - Allocates memory space for the object
 - Invokes the constructor to initialize its value
 - Returns a reference to the object

##### Invoking instance methods

##### Using objects

##### Assignment statements

The assignment statement does not create a new object, just another reference to an existing object. known as "aliasing".

##### Objects as arguments

##### Objects as return values

##### Arrays are objects

##### Arrays of objects

#### Examples of abstract date types

### 1.3 Bags, Queues, and Stacks

### 1.4 Analysis of Algorithms

### 1.5 Case Study: Union-Find
