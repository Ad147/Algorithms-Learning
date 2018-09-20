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

> As C++ is preferred, the rest of this chapter will be simply noted.

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

###### A list of selected ADTs used in this book

##### Geometric objects

###### Some APIs for grometric objects

##### Information Processing

###### Sample APIs for commercial applications (dates and transactions)

##### Strings.

###### Java `String` API (partial list of methods)

###### Typical string-processing code

##### Input and output revisited

###### API for our data type for input/output streams and drawings

#### Implementing an abstract data type

###### Anatomy of a class that defines a data type (class Counter)

##### Instance variables

##### Constructors

##### Instance methods

##### Scope

##### API, clients, and implementations

To develop an abstract data type, we think about the needs of a client, then accommodate them in an ADT, folllowing three steps:
 - Specify an API. Two goals when specifying an API, first, to enable clear and correct client code. Second, to be able to implement the operations.
 - Implement a Java class that meets the API specifications: choose the instance variables, write constructors and the instance methods.
 - Develop multiple test clients to validate the design decisions.

###### An abstract data type for a simple counter

| `public class Counter` |                                      |
| ---------------------- | ------------------------------------ |
| `Counter(String id)`   | create a counter named id            |
| `void increment()`     | increment the counter                |
| `int tally()`          | number of increments sincce creation |
| `String toString()`    | string representation                |

###### typical client

```java
public class Flips
{
    public static void main(String[] args)
    {
        int T = Integer.parseInt(args[0]);

        Counter heads = new Counter("heads");
        Counter tails = new Counter("tails");

        for (int t = 0; t < T; t++)
            if (StdRandom.bernoulli(0.5))
                heads.increment();
            else tails.increment();

        StdOut.println(heads);
        StdOut.println(tails);
        int d = heads.tally() - tails.tally();
        StdOut.println("delta: " + Math.abs(d));
    }
}
```

###### implementation

```java
public class Counter
{
    private final String name;
    private int count;

    public Counter(String id)
    {name = id;}

    public void increment()
    {count++;}

    public int tally()
    {return count;}

    public String toString()
    {return count + " " + name;}
}
```

###### application

```java
% java Flips 1000000
500172 heads
499828 tails
delta: 344
```

#### More ADT implementations

##### Date

###### An ADT to encapsulate dates, with **two implementations**

| API: `public class Date`             |                       |
| ------------------------------------ | --------------------- |
| `Date(int month, int day, int year)` | create a date         |
| `int month()`                        | month                 |
| `int day()`                          | day                   |
| `int year()`                         | year                  |
| `String toString()`                  | string representation |

###### test client

```java
public static void main(String[] args)
{
    int m = Integer.parseInt(args[0]);
    int d = Integer.parseInt(args[1]);
    int y = Integer.parseInt(args[2]);
    Data data = new Date(m, d, y);
    StdOut.println(date);
}
```

###### implementation (first)

```java
public class Date
{
    private final int month;
    private final int day;
    private final int year;

    public Date(int m, int d, int y)
    {month = m; day = d; year = y;}

    public int month()
    {return month;}
    public int day()
    {return day;}
    public int year()
    {return year;}
    public String toString()
    {return month() + "/" + day() + "/" + year();}
}
```

###### alternate implementation

```java
public class Date
{
    private final int value;

    public Date(int m, int d, int y)
    {value = y * 512 + m * 32 + d;}

    public int month()
    {return (value / 32) % 16;}
    public int day()
    {return value % 32;}
    public int year()
    {return value / 512;}
    public String toString()
    {return month() + "/" + day() + "/" + year();}
}
```

###### application of Date

```java
% java Date 12 31 1999
12/31/1999
```

##### Maintaining multiple implementations

##### Accumulator

##### Visual accumulator

#### Data-type design

##### Encapsulation

> You do not need to know how a data type is implemented in order to use it and you can assume that a client knows nothing but the API.

##### Designing APIs

> Provide to clients the methods they need and no others.

##### ALgorithms and abstract date types

###### Binary search recast as an object-oriented program (an ADT for search in a set of integers)

##### Interface inheritance

##### Implementation inheritance

##### String conversion

##### Wrapper types

##### Equality

Some properties of `equals()`

Some steps to build `equals()`

##### Memory management

##### Immutability

##### Design by contract

##### Exceptions and errors

##### Assertions

##### Summary

### 1.3 Bags, Queues, and Stacks

The implementations here are models of implementations later in the book and **worthy of careful study**.

#### APIs of the three

###### APIs for fundamantal generic iterable collections

| `public class Bag<Item> implements Iterable<Item>` |                            |
| -------------------------------------------------- | -------------------------- |
| `Bag()`                                            | create an empty bag        |
| `void add(Item item)`                              | add an item                |
| `boolean isEmpty()`                                | is the bag empty           |
| `int size()`                                       | number of items in the bag |

| `public class Queue<Item> implements Iterable<Item>` |                                      |
| ---------------------------------------------------- | ------------------------------------ |
| `Queue()`                                            | create an empty queue                |
| `void enqueue(Item item)`                            | add an item                          |
| `Item dequeue()`                                     | remove the least recently added item |
| `boolean isEmpty()`                                  | empty                                |
| `int size()`                                         | number of items                      |

| `public class Stack<Item> implements Iterable<Item>` |                                     |
| ---------------------------------------------------- | ----------------------------------- |
| `Stack()`                                            | create an empty stack               |
| `void push(Item item)`                               | add an item                         |
| `Item pop()`                                         | remove the most recently added item |
| `boolean isEmpty()`                                  | empty                               |
| `int size()`                                         | number of items                     |

##### Generics

##### Autoboxing

Automatically casting a primitive type to a wrapper type is known as auto *boxing*.

##### Iterable collections

##### Bags

A bag is a collection where removing items is not supported.
Its purpose is to provide clients with the ability to collect items and to iterate.
The order of iteration is unspecified.

##### FIFO queues (first-in-first-out)

##### Pushdown stacks (LIFO)

##### Arithmetic expression evaluation

Manipulate the stacks in four cases:
 - Push *operands* onto the operand stack
 - Push *operators* onto the operator stack
 - Ignore *left* parenthese
 - On encountering a *right* parenthesis, pop an operator, pop the requisite number of operands, and push onto the operand stack the result of applying that operator to those operands.

###### Dijkstra's Two-Stack Algorithm for Expression Evaluation

```java
public class  Evaluate
{
    public static void main(String[] args)
    {
        Stack<String> ops  = new Stack<String>();
        Stack<Double> vals = new Stack<Double>();
        while (!StdIn.isEmpty())
        {
            // Read token, push if operator.
            String s = StdIn.readString();
            if      (s.equals("("))               ;
            else if (s.equals("+"))    ops.push(s);
            else if (s.equals("-"))    ops.push(s);
            else if (s.equals("*"))    ops.push(s);
            else if (s.equals("/"))    ops.push(s);
            else if (s.equals("sqrt")) ops.push(s);
            else if (s.equals(")"))
            {
                // Pop, evaluate, and push result if token is ")".
                String op = ops.pop();
                double v = vals.pop();
                if      (op.equals("+"))    v = vals.pop() + v;
                else if (op.equals("-"))    v = vals.pop() - v;
                else if (op.equals("*"))    v = vals.pop() * v;
                else if (op.equals("/"))    v = vals.pop() / v;
                else if (op.equals("sqrt")) v = Math.sqrt(v);
                vals.push(v);
            }  // Token not operator or paren: push double value.
            else vals.push(Double.parseDouble(s));
        }
        StdOut.println(vals.pop());
    }
}
```

This Stack client uses two stacks to evaluate arithmetic expressions.
For simplicity, this code *assumes that the expression is fully parenthesized*, with numbers and characters separated by whitespace.

#### Implementing collections

##### Fixed-capacity stack

###### Implementation of `FixedCapacityStackOfStrings`

```java
public class FixedCapacityStackOfStrings
{
    private String[] a;
    private int N;

    public FixedCapacityStackOfStrings(int cap)
    {a = new String[cap];}
    public boolean isEmpty() {return N == 0;}
    public int size() {return N;}
    public void push(String item) {a[N++] = item;}
    public String pop() {return a[--N];}
}
```

##### Generics of the ADT

To make the ADT generic, replace `String` with `Item`.
And declare the class with a *type parameter* `Item`:  
`public class FixedCapacityStack<Item>`  
For generic array creation is disallowed in Java, use:  
`a = (Item[]) new Object[cap];`

##### Array resizing

Modify the array implementation to dynamically adjust the size of the array a[].
 - When the array is full, copy the data to an new array of double size
 - When poping the array to only 1/4 data left, make the size 1/2

##### Loitering

Setting the array entry corresponding to the popped item to `null` to avoid loitering.

##### Iteration

Use `interface Iterable<Item>` to make the container iterable

###### **Algorithm 1.1** Pushdown (LIFO) stack (resizing array implementation)

```java
import java.util.Iterator;
public class ResizingArrayStack<Item> implements Iterable<Item>
{
    private Item[] a = (Item[]) new Object[1];
    private int N = 0;

    public boolean isEmpty() {return N == 0;}
    public int size() {return N;}

    public void resize(int max)
    {
        // move stack to a new array of size max
        Item[] temp = (Item[]) new Object[max];
        for (int i = 0; i < N; i++)
            temp[i] = a[i];
        a = temp;
    }

    public void push(Item item)
    {
        // add item to top of stack
        if (N == a.length) resize(2 * a.length);
        a[N++] = item;
    }

    public Item pop()
    {
        // remove item from top of stack
        Item item = a[--N];
        a[N] = null;
        if (N > 0 && N == a.length / 4) resize(a.length/2);
        return item;
    }

    public Iterator<Item> iterator()
    {return new ReverseArrayIterator();}

    private class ReverseArrayIterator implements Iterator<Item>
    {
        // support LIFO interation
        private int i = N;
        public boolean hasNext() {return i > 0;}
        public Item next() {return a[--i];}
        public void remove() {}
    }
}
```

This generic, iterable implementation of stack API is a model for collection ADTs that with an array.

#### Linked lists

> A linked list is a recursive data structure that is either empty (null) or a reference to a node having a generic item and a reference to a linked list.

##### Node record

##### Building a linked list

##### Insert at the beginning

##### Remove from the beginning

##### Insert at the end

##### Insert/remove at other positions

Easy operations for linked lists:
 - Insert at the beginning
 - Remove from the beginning
 - Insert at the end
not so easy:
 - Remove a given node (including the tail)
 - Insert a new node **before** a given node

##### Traversal

##### Stack implementation

###### **Algorithm 1.2** Pushdown stack (linked-list implementation)

```java
public class Stack<Item>
{
    private Node first; // top of stack (most recently added node)
    private int N; // number of items
    private class Node
    {
        // nested class to define nodes
        Item item;
        Node next;
    }

    public boolean isEmpty() {return first == null;} // or N == 0
    public int size() {return N;}
    public void push(Item item)
    {
        // add item to top of stack
        Node oldfirst = first;
        first = new Node();
        first.item = item;
        first.next = oldfirst;
        N++;
    }
    public Item pop()
    {
        // remove item from top of stack
        Item item = first.item;
        first = first.next;
        N--;
        return item;
    }
    // see p155 for iterator()
}
```

##### Queue implementation

###### **Algorithm 1.3** FIFO queue

```java
public class Queue<Item>
{
    private Node first; // link to least recently added node
    private Node last; // link to most recently added node
    private int N; // number of items on the queue
    private class Node
    {
        // nested class to define nodes
        Item item;
        Node next;
    }

    public boolean isEmpty() {return first == null;}
    public int size() {return N;}
    public void enqueue(Item item)
    {
        // add item to the end of the list
        Node oldlast = last;
        last = new Node();
        last.item = item;
        last.next = null;
        if (isEmpty()) first = last;
        else oldlast.next = last;
        N++;
    }
    public Item dequeue()
    {
        // remove item from the beginning of the list
        Item item = first.item;
        first = first.next;
        if (isEmpty()) last = null;
        N--;
        return item;
    }
    // see p155 for iterator() implementation
}
```

##### Bag implementation

###### **Algorithm 1.4** Bag

```java
import java.util.Iterator;
public class Bag<Item> implements Iterable<Item>
{
    private Node first; // first node in list
    private class Node
    {
        Item item;
        Node next;
    }

    public void add(Item item)
    {
        // same as push() in Stack
        Node oldfirst = first;
        first = new Node();
        first.item = item;
        first.next = oldfirst;
    }
    public Iterator<Item> iterator()
    {return new ListIterator();}
    private class ListIterator implements Iterator<Item>
    {
        private Node current = first;
        public boolean hasNext() {return current != null;}
        public void remove() {}
        public Item next()
        {
            Item item = current.item;
            current = current.next;
            return item;
        }
    }
}
```

#### Overview

##### Data structures

In approaching a new application domain, to identify computational challenges and use data abstraction to address them, proceeding as follows:
 - Specify an API
 - Develop client code with reference to specify application
 - Describe a data structure (representation of the set of values) that can serve as the basis for the instance variables in a class that will implement an ADT that meets the specification in the API
 - Describe algorithms (approaches to implementing the set of operations) that can serve as the basis for implementing the instance methods in the class
 - Analyze the performance characteristics of the algorithms

###### Examples of data structures developed in this book

| data structure                 | section  | ADT                    | representation            |
| ------------------------------ | -------- | ---------------------- | ------------------------- |
| parent-link tree               | 1.5      | UnionFind              | array of integers         |
| binary search tree             | 3.2, 3.3 | BST                    | two links per node        |
| string                         | 5.1      | String                 | array, offset, and length |
| binary heap                    | 2.4      | PQ                     | array of objects          |
| hash table (separate chaining) | 3.4      | SeparateChainingHashST | arrays of linked lists    |
| hash table (linear probing)    | 3.4      | LinearProbingHashST    | two arrays of objects     |
| graph adjacency lists          | 4.1, 4.2 | Graph                  | array of Bag objects      |
| trie                           | 5.2      | TrieST                 | node with array of links  |
| ternary search trie            | 5.3      | TST                    | three links per node      |

### 1.4 Analysis of Algorithms

### 1.5 Case Study: Union-Find
