CppPrimerCh02.md

C++ Primer Notes
================================================================================

Ad  
init: Apr20.2018  

Chapter2 Variables and Basic Types
--------------------------------------------------------------------------------

### 2.1 Primitive Built-in Types

#### 2.1.1

#### Arithmetic types

| Type        | Meaning                           | Minimum size                              |
| ----------- | --------------------------------- | ----------------------------------------- |
| bool        | boolean                           | NA                                        |
| char        | character                         | 8 bits                                    |
| wchar_t     | wide character                    | 16 bits                                   |
| char16_t    | Unicode character                 | 16 bits                                   |
| char32_t    | Unicode character                 | 32 bits                                   |
| short       | short integer                     | 16 bits                                   |
| int         | integer                           | 16 bits                                   |
| long        | long integer                      | 32 bits                                   |
| long long   | long integer                      | 64 bits                                   |
| float       | single-precision floating-point   | 6 significant digits (typically 32 bits)  |
| double      | double-precision floating-point   | 10 significant digits (typically 64 bits) |
| long double | extended-precision floating-point | 10 significant digits (96 or 128 bits)    |

To get the max value of a type:
> ```cpp
> double d = std::numeric_limits<double>::max();
> ```
> by Milo

`C++11` On most machine:

 - **a byte = 8 bits**
 - **a word = 32/64 bits**.

an `address` is associate with one byte  
`char` is signed or unsigned in different machine

#### Deciding type:

- unsign (not negative)
- int (integer arithmetic, long is as int)
- long long (larger number)
- char/bool (*only* for characters or truth values)
- double (float hasn't enough precision, and extra cost is negligible, while long double cost too much )

#### 2.1.2

#### Type convensions:

 - assign out-of-range value to unsigned type: get remainder of value modulo values the type can hold
 - assign out-of-range value to signed type: result is undefined

#### 2.1.3

`20` (demical) = `024` (octal) = `0x14` (hexadecimal)

Floating-point literals include either a demical point or an exponent specified using scientific notation.

#### Escape sequence:

|                 |
| --------------- | ------ | -------------- | ---- | ------------ | ----- |
| newline         | \n \12 | horizontal tab | \t   | alert(bell)  | \a \7 |
| vertical tab    | \v     | backspace      | \b   | double quote | \\"   |
| backslash       | \\\    | quention mark  | \\?  | single quote | \\'   |
| carriage return | \r     | formfeed       | \f   |
| null            | \0     | octal          | \111 | hexadecimal  | \x111 |

#### Specifying the type of a literal:

 - Character and character string lierals

| Prefix | Meaning                      | Type     |
| ------ | ---------------------------- | -------- |
| u      | Unicode 16 character         | char16_t |
| U      | Unicode 32 character         | char32_t |
| L      | wide charater                | wchar_t  |
| u8     | utf-8 (string literals only) | char     |

- Integer literals and Floating-point literals

| Suffix | Minimum type | Suffix | Type        |
| ------ | ------------ | ------ | ----------- |
| u/U    | unsigned     | f/F    | float       |
| l/L    | long         | l/L    | long double |
| ll/LL  | long long    |

To get the name and size of a literal:

```cpp
#include <typeinfo>
typeid(a).name();
sizeof(a);
```

--------------------------------------------------------------------------------

### 2.2 Variables

#### 2.2.1

Initialization & Assignment:

 - Initialization: give value when created
 - Assignment: obliterate current value, replace with new one

#### `C++11` List initialization (the first two)

```cpp
int i{0};
int i = {0};
int i = 0;
int i(0);
```

Property: compiler don't allow information loss if using list initialization

#### Declarations and Definitions

```cpp
extern int i;   //  declare
int j;          //  declare and define
extern int pi = 3.14    //  define (override extern)
```

Scope of a name delimited by curly braces  
**Better** define a object near it's first used

#### Nested scope

```cpp
int i = 0;  //  global scope
int main()
{
    std::cout << i << std::endl;    //  print 0
    int i = 1;                      //  block scope, hide global i
    std::cout << i << std::endl;    //  print 1
    std::cout << ::i << std::endl;  //  print 0
    return 0;
}
```

Do not define with the same name

--------------------------------------------------------------------------------

### 2.3 Compound Types

#### 2.3.1

 - Reference is not object
 - Reference must be initialized
 - can not refer to a different object
 - can not refer to other reference

`C++11` 3 ways to obtain a null pointer:

```cpp
int *p1 = nullptr;  //  C++11
int *p2 = 0;
int *p3 = NULL;     //  #inlcude cstdlib
```

Modern C++ program should use `nullptr`

--------------------------------------------------------------------------------

### 2.4 `const` Qualifier

By defaylt, `const` are local to a file  
So use `extern` on both definition and declaration:

```cpp
//  definition and declaration in file.cpp
extern const int buffer = 123;
//  declaration in file.h
extern const int buffer;
```

#### 2.4.1

Reference to `const` must be `const`
> A `const reference` is a `reference to const`

++While a `const pointer` != `pointer to const`++

bind a `reference to const` (also `pointer to const`) to a nonconst object, a literal, or a more general expression:

```cpp
int i = 42;
const int &r1 = i;      //  refer to nonconst
const int &r2 = 42;     //  refer to constant
const int &r3 = r1 * 2; //  refer to const expression
```

**For the compiler will replace const object with constant when compiling**  

A `const reference` (also `pointer to const`) cannot change the value it refer to

bind a reference to different type:

```cpp
double dval = 3.14;
const int &ri = dval;
//  compiler transform the code into sth like:
const int temp = dval;
const int &ri = temp;
```

#### 2.4.2

 - `const pointer` : `int *const ptr{nullptr}` cannot change the address stored
 - `pointer to const` : `const int *ptr{nullptr}` cannot change the value which point to

> `pointer/reference to const` ++**think**++ they point/refer to `const`

#### 2.4.3

 - Top-level const: `const pointer` (const itself for any type)
 - Low-level const: `pointer to const` (for compound types )

When copying (assign) objects

 - Top-level const always ignored (copying donot change value)
 - Low-level const must match or can be converted (`const` = `const`, `nonconst` = `nonconst`, `const` = `nonconst`)

#### 2.4.4

A `const expression` whose value cannot change, and that is ++determined at compile++

`C++11` use `constexpr` to declare constant expressions (ask compiler to verify)

`constexpr int *p` == `int const *p`

--------------------------------------------------------------------------------

### 2.5 Dealing with Types

#### 2.5.1

define a type alias:

1. `typedef int amount, *amountPointer;`
2. `C++11` `using amount = int;`

#### 2.5.2

`C++11` Specifier `auto` make the compiler to deduce the type from initializer  

 - `auto` must be initialized
 - variables defined in a declaration must be the same **base type**
 - `auto` ignores top-level `const` and keep low-level `const`
 - use `const auto` if wanted a top-level `const`
 - when ask for reference to auto, top-level `const` is not ignored (`const auto &r = 17;`)

#### 2.5.3

`C++11` use `decltype` to deduce a type form an **expression** but not initialize with it  
while it keep top-level `const` and reference:

```cpp
const int ci = 0, &cir = ci;
decltype(ci) x = 0;     //  x is const int
decltype(cir) y = x;    //  y is reference to const int
```

`decltype` an expression can return a reference **(when the expression yield a lvalue)**:

```cpp
int i{17}, *p = &i, &r = i;
decltype(r + 0) ii{7};  //  addition yields an int
decltype(*p) rr{ii};    //  a reference is yielded
```

--------------------------------------------------------------------------------

### 2.6 Defining Our Own Data Structures

#### 2.6.1 

Remember the semicolon at the end of a class definition

`C++11` in-class initializer will be used to initialize data members without initialization

#### 2.6.2

Use `#ifndef` to avoid multiple definition

```cpp
#ifndef XXX_H
#define XXX_H
    The content
#endif
```

or  

##### `#pragma once`

Put the definition of the class in the header file, and that of the members in the source file

--------------------------------------------------------------------------------

EOF