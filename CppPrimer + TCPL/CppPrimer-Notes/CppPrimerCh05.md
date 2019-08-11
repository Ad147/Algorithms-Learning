CppPrimerCh05.md

C++ Primer Notes
================================================================================

Ad  
init: Apr29.2018

Chapter5 Statements
--------------------------------------------------------------------------------

### 5.1 Simple Statement

`expression statement`  
`null statement` : `;`  

`compound statment` (blocks): `{ }` is used requiring a single statement but needing more in logic.  

 - i.e. **the `while` and `for` require a single statement**

--------------------------------------------------------------------------------

### 5.2 Statement Scope

--------------------------------------------------------------------------------

### 5.3 Conditional Statements

#### 5.3.1 The `if` Statement

`if (condition) statement`  
`if (condition) statement1 else statement2`

Nested if statements (remember braces)

Dangling `else` : in C++ else is matched with the closest preceding unmatched if.

#### 5.3.2 The `switch` Statement

```cpp
switch (condition)
{
    case 1:
        statement1;
        break;
    case 2:
        statement2;
        break;
    ...
    default:
        statement;
        break;
}
```

Variable dedinitions inside the body of a switch

```cpp
case true:
    int i = 0;  //  error: control bupasses an explocitly initialized variable
    int j;      //  ok: j is not initialized
    break;
case false:
    j = 1;      //  ok: assign a value to j
    if (i)      //  i is in scope but wasnot initialized
```

Any control jumped to the false case would bypass the initialization of i  
If needed, defining the variables inside a block `{ }`

--------------------------------------------------------------------------------

### 5.4 Iterative Statements (loops)

#### 5.4.1 The while Statement

`while (condition) statement`

Generally used when:

 - wanting to iterate indefinitely: read input
 - wanting to access to the loop control variable after the loop finishes

#### 5.4.2 Traditional for Statement

`for (initializer; conditon; expression) statement`

A for header can omit any of the three statements  
including the `condition` **while the `while` loop must have a condition**

#### 5.4.3 Range for Statement

`for (declaration : expression) statement`

 - expression must represent a sequence
 - use `auto` to deduce the type
 - defined as a `reference` if need writing

A range for is defined in terms of the equivalent traditional for:

```cpp
for (auto beg = v.begin(), end = v.end(); beg != end; ++beg)
{
    auto &r = *beg;
    r *= 2;
}
```

So that we can understand why a range for cannot be used to add elements to a vector

#### 5.4.4 The do while Statement

`do statement while (condition) ;`

 - ends with a semicolon `;`
 - doesnot allow variable definitions inside the condition

--------------------------------------------------------------------------------

### 5.5 Jump Statements

 - `break`
 - `continue`
 - `goto`
 - `return`

#### 5.5.1 The break Statement

Only affects **4 types of loops and switch**

#### 5.5.2 The continue Statement

Terminates the current iteration of the nearest enclosing **loop** and immediately begins the next iteration.

#### 5.5.3 The goto Statement

Provides an unconditional jump from the goto to a another statement **in the same function**.  
`goto label;` (label is an identifier that identifies a statement: `end: return;`)

 - goto cannot bypass a variable definition and use it without definition
 - goto can jump backward over an already definition (will destroy the variable and reconstruct)

--------------------------------------------------------------------------------

### 5.6 try Blocks and Exception Handling

Exception handling involves:

 - `throw expressions` : which the detecting part uses to indicate that it encountered something it cannot handle. We say that a throw raises an exception.
 - `try blocks` : which the handling part uses to deal with an exception A try block starts with the keyword try and ends with one or more catch clauses. (aka exception handlers).
 - A set of `exception classes` that are used to pass information about what happened between a throw and an associated catch.

#### 5.6.1 A throw Expression

`throw runtime_error("Data must refer to same ISBN");`  
The `runtime_error` is defined in `stdexcept`

#### 5.6.2 The try Block

```cpp
try
{
    program-statements
}
catch (exception-declaration)
{
    handler-statements
}
catch ...
```

err.what() returns a string literal that the runtime_error initialized with

If no appropriate catch is found, execution is transferred to a library function named `terminate`. (if theres no try in a program, also execute the terminate)

#### 5.6.3 Standard Exceptions

 - `exception` header defines the most general kind of exception class
 - `stdexcept` defines several gerneral-purpose exception classes
 - `new` defines the `bad_alloc` exception type
 - `type_info` defines the `bad_cast`

Standard exception classes defined in \<stdexcept>:
|                  |                                                                                     |
| ---------------- | ----------------------------------------------------------------------------------- |
| exception        | The most general kind of problem                                                    |
| runtime_error    | Problem that can be detected only at run time                                       |
| range_error      | Run-time error: result generated outside the range of values that are meaningful    |
| overflow_error   | Run-time error: computation that overflow                                           |
| underflow_error  | Run-time error: computation that underflow                                          |
| logic_error      | Error in the logic of the program                                                   |
| domain_error     | Logic error: argument for which no result exists                                    |
| invalid_argument | Logic error: inappropriate argument                                                 |
| length_error     | Logic error: attempt to create an object larger than the maximum size for that type |
| out_of_range     | Logic error: used a value outside the valid range                                   |

Operations for the library exception classes:

 - create
 - copy
 - assign  

The `exception` , `bad_alloc` , and `bad_cast` can only be default initialized  
while other exceptions cannot be default initialized, must supply an initializer

The exception types define only a single operation named `what`  
which takes no arguments and returns a `const char*` that points to a C-style character string to provide some sort of textual description of the exception thrown

--------------------------------------------------------------------------------

EOF
