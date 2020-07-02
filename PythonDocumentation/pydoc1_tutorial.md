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

- `def functionName(formalParameters)`
- first line of function body can optionally be a string literal, as documentation string, or docstring
- > p27

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
