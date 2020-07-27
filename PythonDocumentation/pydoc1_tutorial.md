pydoc1_tutorial.md

Python Tutorial (3.8.3)
================================================================================

A~0f27

The tutorial informally introduces basic concepts and features of Python;  
For standard objects and modules, see *library-index*;  
For a more formal definition of the language, see *reference-index*;  
To write extensions in C/C++, read *extending-index* and *c-api-index*

Chapter 1 Whetting Your Appetite
--------------------------------------------------------------------------------

Python is just the language for you:

Shell scripts are best at moving around files and changing text data, but not GUI apps;  
C/C++ takes a lot of development time.

Python offers more structre and support for large programs than shell;  
On the other hand, more error cheching than C.

The interpreter can be used to experiment with features, to write throw-away programs, to test functions during bottom-up program development, or as a desk calculator.

Programs written in Pyton are typically much shorter than C/C++:
1. high-level data types make complex operations in a single statement
2. statement grouping by indentation instead of brackets
3. no variable declarations

Extensibility: easy to add new built-in functions or module in C to the interpreter, either to perform critical operations at max speed, or to link Python programs to libs that may only be avaiable in binary form.

By the way, the language is named after the BBC show "Monty Python’s Flying Circus" and has nothing to do with
reptiles.

Chapter 2 Using the Python Interpreter
--------------------------------------------------------------------------------

### 2.2 The Interpreter and Its Environment

#### 2.2.1 Source Code Encoding

Python source files are treated as encoded in UTF-8 by default;  
To declare another encoding, add a special comment at first line of file, like:  
`# -*- coding: cp1252 -*-`.

One exception to the first line rule is a UNIX "shebang" line, like:  
`#!/usr/bin/env python3`  
`# -*- coding: cp1252 -*-`

Chapter 3 An Informal Introduction to Python
--------------------------------------------------------------------------------

Comments start with the hash character `#`, and extend to the end of the physical line.

### 3.1 Using Python as a Calculator

#### 3.1.1 Numbers

Operators: `+` `-` `*` `/` `//` `%` `**`

Division `/` always returns a float, `//` returns int.

In interactive mode, the last printed expression is assigned to variable `_`.

In addition to int and float, there are other types of numbers: `Decimal` and `Fraction`.

Built-in support for complex numbers, use `j` or `J` suffix to indicate imaginary part (3+5j).

#### 3.1.2 Strings

- strings enclosed in `'...'` or `"..."`
- concatenate by `+`
- repeat by `*`
- strings can be indexed
- strings are immutable (cannot assign)

#### 3.1.3 Lists

- `lst = [1, 2, 3]`
- negative index (start with -1)
- slice (end index exclusive)
- concatenation: `[1, 2] + [3, 4]`
- `list.append()`
- assignment to slices: `lst[2:4] = [4, 5]`
- `len(lst)`

### 3.2 First Steps Towards Programming

- multiple assignment: `a, b = 0, 1`
- in conditions, zero and empty sequences are false
- in `print()`
  - items are split by a space
  - the keyword argument `end` can be used to avoid newline or end output with custom string: `print(a, end=',')`

Chapter 4 More Control Flow Tools
--------------------------------------------------------------------------------

### 4.1 `if` Statements

- `if` `elif` `else`
- `if...elif...elif...` sequence is a subtitute for switch or case statements in other languages

### 4.2 `for` Statements

- python's `for` iterates over items of any sequence

### 4.3 The `range()` Function

- `range(end)`
- `range(beg, end, step)`
- to iterate over indices of a sequence:
  - `range(len(lst))`
  - `enumerate(lst)`
- to get a list from a range: `list(rang(7))`

### 4.4 `break` and `continue` Statements, and `else` Clauses on Loops

- loops can have an `else` clause, executed when the loop terminated *not* by a `break`
- `try` (exception handling) can also have a `else`, runs when no exception occurs

### 4.5 `pass` Statements

`pass` does nothing, like `;` in C

### 4.6 Defining Functions

- `def functionName(formalParameters):`
- first line of function body can optionally be a string literal, as documentation string, or docstring
- `global` `nonlocal`
- even functions without a return do return a value: `None`

### 4.7 More on Defining Functions

Arguments of functions have 3 forms:

#### 4.7.1 Default Argument Values

- `def func(arg1, arg2=2, arg3="hi"):`
- `in` tests whether sequence contains
- **important warning**: the default value evaluated only once, if the default is a mutable (list, dict, instance of classes), the result will accumulate:
```py
def f(a, L=[]):
    L.append(a)
    return L

f(1)
f(2)
# will get
[1]
[1, 2]

# to avoid:
def f(a, L=None):
    if L is None:
        L = []
    L.append(a)
    return L
```

#### 4.7.2 Keyword Arguments

- use keyword arg can ignore order of args:
  - `func(1, arg4=[1], arg3="hello")`
  - but keyword args must follow positional args
- a final formal parameter of the form `**name` receives a dictionary containing all keyword arguments except for those corresponding to a formal parameter
- this may be combined with a formal parameter of the form `*name` which receives a tuple containing the positional arguments beyond the formal parameter list
- `*name` must occur before `**name`

#### 4.7.3 Special Parameters

```py
def f(pos1, pos2, /, pos_or_kwd, *, kwd1, kwd2):
      -----------    ----------     ----------
          |              |              |
          |     Positional or keyword   |
          |                             - Keyword only
          -- Positional only
```

Use case of the 3 parameters:
- Use positional-only if you want the name of the parameters to not be available to the user. This is useful when parameter names have no real meaning, if you want to enforce the order of the arguments when the function is called or if you need to take some positional parameters and arbitrary keywords.
- Use keyword-only when names have meaning and the function definition is more understandable by being explicit with names or you want to prevent users relying on the position of the argument being passed.
- For an API, use positional-only to prevent breaking API changes if the parameter’s name is modified in the future.

#### 4.7.4 Arbitary Argument Lists

- `def f(*args)`
- the args will be wrapped up in a tuple

#### 4.7.5 Unpacking Argument Lists

- when args are already in a list or tuple but need to be unpacked for a function call requiring separate positional args:
  - use `*` to unpack list or tuple
  - `range(*lst)`
- use `**` to unpack dict

#### 4.7.6 Lambda Expressions

- small anonymous functions can be created with the `lambda` keyword
- `lambda a, b: a+b` returns the sum of its two args
- lambda functions can be used wherever function objects are required
- lambdas are syntactically restricted to a single expression
- semantically, they are just syntactic sugar for a normal function definition
- like nested function definitions, lambda functions can reference variables from the containing scope

#### 4.7.7 Documentation Strings

- first line should always be a short, concise summary of purpose, begin with a capital letter and end with a period
- if there are more lines, the second line should be blank
- example:
```py
def my_function():
    """Do nothing, but document it.

    No, really, it doesn't do anything.
    """
    pass

>>> print(my_function.__doc__)
Do nothing, but document it.

    No, really, it doesn't do anything.
```

#### 4.7.8 Function Annotations

- function annotations are completely optional metadata information about the types used by user-defined functions
- annotations are stored in the `__annotations__` attribute of the function as a dictionary and have no effect on any other part of the function
- parameter annotations: `(param: str = "default")`
- return annotations: `f() -> int`

The following example has a positional argument, a keyword argument, and the return value annotated:
```py
>>> def f(ham: str, eggs: str = 'eggs') -> str:
...     print("Annotations:", f.__annotations__)
...     print("Arguments:", ham, eggs)
...     return ham + ' and ' + eggs
...
>>> f('spam')
Annotations: {'ham': <class 'str'>, 'return': <class 'str'>, 'eggs': <class 'str'>}
Arguments: spam eggs
'spam and eggs'
```

### 4.8 Intermezzo: Coding Style

Every Python developer should read PEP8 at some point;  
here are the most important points extracted from PEP8:

- 4-space indentation, no tabs
- wrap lines, do not exceed 79 chars
- use blank lines to separate funcs, classes and blocks inside funcs
- when possible, put comments on a line of their own
- use docstrings
- use spaces around ops and commas, but not brackets
- `UpperCamelCase` for classes, `lowercase_with_underscores` for funcs, always use `self` as first method arg

Chapter 5 Data Structures
--------------------------------------------------------------------------------

### 5.1 More on Lists

All list methods:
- `append(x)` == `a[len(a):] = [x]`
- `extend(iterable)`: append all items from iterable, == `a[len(a):] = iterable`
- `insert(i, x)`
- `remove(x)`: remove the first item with value x
- `pop([i])`: remove item at i, and return it; if no i, remove tail
- `clear()` == `del a[:]`
- `index(x[, start[, end]])`: return index of first value x
- `count(x)`
- `sort(key=None, reverse=False)`
- `reverse()`: reverse in place
- `copy()` == `a[:]`

int can not be compared to str, None can not be compared to other types

#### 5.1.2 Queue

Lists are not efficient to be queues;  
use `colloections.deque`:
- `append()`
- `popleft()`

#### 5.1.3 List Comprehensions

```py
lst = [(x, y) for x in [1, 2, 3] for y in [3, 1, 4] if x != y]

# is equivalent to:

lst = []
for x in [1, 2, 3]:
    for y in [4, 5, 6]:
        if x != y:
            lst.append((x, y))
```

#### 5.1.4 Nested List Comprehensions

```py
matrix = [
    [1, 2, 3, 4],
    [5, 6, 7, 8],
    [9, 10, 11, 12],
]

# transpose rows and columns:

[[row[i] for row in matrix] for i in range(4)]

# get [[1, 5, 9], [2, 6, 10], [3, 7, 11], [4, 8, 12]]

# is equivalent to:

transposed = []
for i in range(4):
    transposed.append([row[i] for row in matrix])

# and is the same as:

transposed = []
for i in range(4):
    transposed_row = []
    for row in matrix:
        transposed_row.append(row[i])
        transposed.append(transposed_row)
```

### 5.2 The del Statement

- delete slices: `del a[0:7]`
- delete entire variable: `del a`

### 5.3 Tuples and Sequences

Tuples are immutable, but it is possible to create tuples containing mutable objects.

Tuples usually contain a heterogeneous sequence of elems that are accessed via unpacking or indexing

- create tuple of size 1: `t = "hello",`
- unpacking: `x, y, z = t`

### 5.4 Sets

- create: `{1, 2,...}`
- empty set creating: `set()`
- math ops:
  - union: `a | b`
  - intersection: `a & b`
  - diff: `a - b`
  - `a ^ b` (in a or b but not both)
- set comprehension: `a = {x for x in "abractaw" if x not in "abc"}`

### 5.5 Dictionaries

- only immutable can be keys
- empty dict: `d = {}`
- creating: `d = {"apple": 1, "banana": 2}`
- add: `d["peach"] = 3`
- `list(d)`: a list of keys in insertion order
- `sorted(d)`: a list of keys in sorted order
- constructor: `dict([("a", 1), ("b", 2)])`
- dict comprehension: `{x: x**2 for x in (2, 4)}` 
- when keys are simple strings: `dict(a=1, b=2)`

### 5.6 Looping Techiques

- retrieve index/key and value at the same time:
  - `enumerate(lst)` for lists
  - `dict.items()` for dicts
- loop over 2+ seqs at the same time:
  - `zip(lst1, lst2)`
- loop seq in reverse:
  - `reversed(lst)`
- loop seq in sorted order:
  - `sorted(lst)`
- sometimes need to change a list while loop; but it is simpler and safer to create a new

### 5.7 More on Conditions

Used in conditions:
- `in` `not in`
- `is` `is not` (check identity)
- chained comparison `a < b == c`

Note that in Python, unlike C, assignment inside expressions must be done explicitly with the walrus operator :=.
This avoids a common class of problems encountered in C programs: typing = in an expression when == was intended.

Chapter 6 Modules
--------------------------------------------------------------------------------

A module is a file containing Python definitions and statements;  
the file name is the module name (available in `__name__`)

### 6.1 More on Modules

Variants of `import`:
- `from module import function, function2`
- `from module import *`: imports all except begining with `_`
- `import module as mod`
- `from module import function as fun`

If modules changed, interpreter shouldbe restarted;  
or use `import importlib; importlib.reload(modulename)`

#### 6.1.1 Executing modules as scripts

When run module with  
`python module.py <arguments>`  
the code will be executed with `__name__` set to `__main__`.

Therefore, to make file a script as well as module, add to end:
```py
if __name__ == "__main__":
    import sys
    function(int(sys.argv[1]))
```

This is often used either to provide a convenient user interface to a module, or for testing purposes (running the module as a script executed a test suite)

### 6.2 Standard Modules

>p50

--------------------------------------------------------------------------------

#### 7.1.1 Formatted String Literals

- also called f-strings for short
- can include expression values inside a string
- prefix with `f` or `F`, write expressions as `{expr}`
- optional format specifier control the format:
  - `f"{math.pi:.3f}"`
  - integer after `:` for padding
  - convert the value before formatted:
    - `!a` applies ascii()
    - `!s` applies str()
    - `!r` applies repr()

for ref on format specifications, see ref guide for formatspec
