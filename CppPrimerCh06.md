CppPrimerCh06.md

C++ Primer Notes
================================================================================

Ad  
init: Apr30.2018

Chapter6 Functions
--------------------------------------------------------------------------------

### 6.1 Function Basics

When calling a function,

 1. first the function initializes parameters from the corresponding arguments,
 2. then it reansefers control to the function.

Execution of a function ends when a return statement is encountered:

 1. it returns the value in the return,
 2. and transfers control out of the called function back to the calling function.

types and number of parameters and arguments

 - The type of arguments must match the corresponding parameters in the same way that the initializers match objects initialized
 - the number must be the same

#### 6.1.1 Local Objects

 - **The scope of a name**: *the part of the program's text* in which that name is visible
 - **The lifetime if an object**: *the time during the program's execution* that the object exists

##### Local `static` Objects: whose lifetime continues across calls to the function

(until the termination of the program)

#### 6.1.2 Function Declarations (aka function prototype)

`return_type function_name(parameter_type parameter_name);`

##### Declarations in Header

> The header that *declares* a function should be included in the source file that *defines* that function.

#### 6.1.3 Separate Compilation

--------------------------------------------------------------------------------

### 6.2 Argument Passing:

 - "**passed by reference**" or "**called by reference**"
 - "**passed by value**" or "**called by value**"

#### 6.2.1 Passing Arguments by Value

The value of the initializer is **copied**

 - changes made to the parameters donot change the arguments
 - passing by value incluing pointers

> In C++, generallu use **reference** parameters to access objects outside a function.

#### 6.2.2 Passing Arguments by Reference

##### Using references to avoid copies for:

 - large class types
 - large containers
 - some class types cannot be copied

Use `const type&` parameters if no need to change the arguments

##### Using Reference Parameters to Return Additional Information

 - a function can return only a single value
 - define reference parameters to pass extra variables

#### 6.2.3 `const` Parameters and Arguments

 - top-level const is ignored when copying values to parameters:  

`void f(const int i) {}` and `void f(int i) {}` can only defined once

Initializing an object with a `low-level const` from a `nonconst` or `const` is ok.
While not vice versa.

##### Use Reference to `const` When Possible

#### 6.2.4 Array Parameters

 - using arrays is actually using pointers

##### To tell functions the size of arrays:

 - using a marker to specify the extent(character string): `\0`
 - using the standard library conventions: `void f(const int *beg, const int *end)` `f(begin(arr), end(arr));`
 - pass a size parameter explicitly

#### 6.2.5 main: Handling Command-Line Options

`int main(int argc, char *argv[]) {}` :  

 - argc passes the number of strings in argv
 - argv is an array of pointers to C-style character strings
 - argv[0] contains the program's **name**, not user input

#### 6.2.6 Functions with Varying Parameters

`C++11` provides two primary ways to write a function with varying number of arguments:

 - `initializer_list<T> list;` : for unknown number of atguments of a **single type**
 - variadic template: for varying types

| `initializer_list`                  | Operations                                              |
| ----------------------------------- | ------------------------------------------------------- |
| initializer_list\<T> list;          | default initialization (empty)                          |
| initializer_list\<T> list{a, b...}; | copy elements of initializers. **elements are `const`** |
| list2(list)                         | copying or assigning does not copy elements,            |
| list2 = list                        | but sharing the elements to both list                   |
| list.size()                         |
| list.begin()                        |
| list.end()                          |

 - enclose the sequence in `{}` when passing a sequence to an `initializer_list`

##### Ellipsis Parameters

Allow programs to interface to C code that uses a C library facility named `varargs`  
not for other purpose

--------------------------------------------------------------------------------

### 6.3 Return Types and the return Statement

#### 6.3.1 Functions with No Return Value

 - `return;` used in `void f()` : analogous to `break;` in loops

#### 6.3.2 Functions That Return a Value

##### Values are returned in the same way as variables and parameters are initialized

##### Never return a Reference or Pointer to a Local Object (including temporary string)

##### Reference Returns are Lvalues (while others are rvalues)

so the return is able to be assigned (if not a const reference)

##### `C++11` List Initializing the Return Value

Functions can return a braced list of values like: `vector`  
it can be empty, one element, two or more...

##### Return from main

To make return values machine independent, the `cstdlib` header defines two **preprocessor** variables used to indicate success or failure: `return EXIT_FAILURE;` `return EXIT_SUCCESS;`  

 - must not precede them with `std::` cause they are preprocessor variables

##### Recursion

A function that calls itself is a recursive function

#### 6.3.3 Returning a Pointer to an Array

Using type alias to simplify the declaratin of a function returns a pointer to an array:

```cpp
using arrT = int[10];
typedef int arrT[10];   //  noting: it is the same as above
arrT* func(int i);
```

##### Declaring a Function that Returns a Pointer to an Arrar

Just like `int (*p)[10];` to declare a pointer to an array of 10 ints:  
`type (*function(parameter_list))[dimension]`

> As a example to see how to ++**understand a declaration**++:  
> `int (*func(int i))[10];`  
> - `func(int)` : func can be called with an int argument
> - `(*func(int))` : the result of the call can be dereference
> - `(*func(int))[10]` : dereferencing the result yields an array of size ten
> - `int (*func(int))[10]` : the element type in the array is int

##### `C++11` Using a Trailing Return Type (to simplify the decalration of functions with complicated return types, i.e. pointers/references to arrays)

`auto func(int i) -> int(*)[10];`

##### Using `decltype` to simplify declaration

--------------------------------------------------------------------------------

### 6.4 Overloaded Functions

 - Functions that have **the same name** but **different parameter lists** and that appear in **the same scope** are **overloaded**
 - top-level const has no effect on the objects that can be passed to function:  
   `int function(int* p);` == `int function(int* const p);`
 - while low-level effects:  
   `int function(int& r);` != `int function(const int& r);`

Not to overloading when the function name can provides extra information that make function easier to understand.

##### const_cast and Overloading (guarantee safe when change the constness)

##### Calling Overloaded Function (Function matching, aka overload resolution)

 - best match
 - no match, error
 - more than one matches: ambiguous call

#### 6.4.1 Overloading and Scope

As usual, if declaring a name in an inner scope, that name **hides** uses of that name declared in an outer scope. Names donot overload across scopes.

--------------------------------------------------------------------------------

### 6.5 Features for Specialized Uses

#### 6.5.1 Default Arguments

`type function(type para1, type para2 = 1, type para3 = 2);`

##### Default Argument Declarations

A latter declaration after the first declaration can add default value to parameters, but cannot change the defaults written.

##### Default Argument Initializers

#### 6.5.2 `inline` and `constexpr` Functions

Calling functions is apt to be slower than evaluating the equivalent expression.

##### `inline` Functions Avoid Function Call Overhead

`inline` is only a *request* to the compiler. It may choose to ignore.

##### `constexpr` Functions

`C++11` A `constexpr` function is that can be used in a constant expression  
it must meet certain restrictions: The rtypes of return and parameters must be literal types, and the body must contain exactly one return.

 - `constexpr` functions are implicitly `inline`.
 - the body can contain other statements that generate no actions at run time: `;` `using` `type alias`
 - not required to return a constant expression (just need value determined at compile time)

##### Put `inline` and `constexpr` Functions in Header Files (definitions)

#### 6.5.3 Aids for Debugging

With two preprocessor facilities: `assert` and `NDEBUG` , the program can contain debugging code executed only in developed.

##### The `assert` ++Preprocessor Macro++ (like a inline function)

 - defined in \<cassert> and no need to `std::` (cause it is preprocessed)
 - `assert(expr);` : writes a message and terminates the program if expr is false  
while doing nothing if true

##### The `NDEBUG` Preprocessor Variable

If `NDEBUG` is defined, assert does nothing.  
By default, `NDEBUG` is not defined.  
`#define NDEBUG`

The compiler defined several variable (local static array of const char) for debugging:
 - `__func__` : holds the name of function
 - `__FILE__` : name of file
 - `__LINE__` : current line number
 - `__TIME__` : compiled time
 - `__DATE__` : compiled date

--------------------------------------------------------------------------------

### 6.6 Function Matching

##### Determine the Candidate and Viable Functions

Match the number and types of parameters from candidate functions to get viable functions  
then look for a best matching function, if any

 - no matching -> error  
 - more than one matching the same -> error

#### 6.6.1 Argument Type Conversions

To determine the best match, the compiler ranks conversions:
 1. An exact match which happens when:
    - The argument and parameter types are identical
    - The argument is converted from an array or function type to pointer type
    - A top-level const is added to or discarded from the argument
 2. Match through a const conversion
 3. Match through a promotion
 4. Match through an arithmetic or pointer conversion
 5. Match through a class-type conversion

- important to remember that the small integral types always promoted to int or larger
- all the arithmetic conversions are **treated as equivalent** to each other

--------------------------------------------------------------------------------

### 6.7 Pointers to Functions

A function's type is determined by its return type and the types of its parameters.

 - declaration:  
   `returnType (*ptrFun)(parameterType1, parameterType2);`
 - assignment:  
   `ptrFun = function;` == `ptrFun = &function;`
 - using pointer to call function:  
   `ptrFun(argument1, argument2);` == `(*ptrFun)(argument1, argument2);`
 - no conversions between function pointers

##### Pointers to Overloaded Functions must match the return and arguments so that the compiler can determine which to point to

##### Function Pointer Parameters

pointers to function can be parameters

Use typedef and decltype to simplify the declaration of function pointers  
 - noting that `decltype` will not change the function type to the function pointer

##### Returning a Pointer to Function

The compiler will not automatically convert the function type to function pointer type

Using a trailing return to simplify a declaration of a function that returns a pointer to function:
`int (*f1(int))(int*, int);` == `auto f1(int) -> int (*)(int*, int);`

--------------------------------------------------------------------------------

EOF