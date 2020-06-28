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

> p15