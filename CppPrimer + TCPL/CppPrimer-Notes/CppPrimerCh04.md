CppPrimerCh04.md

C++ Primer Notes
================================================================================

Ad  
init: Apr27.2018

Chapter4 Expressions
--------------------------------------------------------------------------------

### Operator Precedence Table

| Associativity | Operator      | Function               | Use                    |
| ------------- | ------------- | ---------------------- | ---------------------- |
| L             | ::            | global scope           | ::name                 |
| L             | ::            | class scope            | class::name            |
| L             | ::            | namespace scope        | namespace::name        |
|               |
| L             | .             | member selectors       | object.member          |
| L             | ->            | member selectors       | pointer->member        |
| L             | []            | subscript              | expr[expr]             |
| L             | ()            | function call          | name(expr_list)        |
| L             | ()            | type construction      | type(expr_list)        |
|               |
| R             | ++            | postfix increment      | lvalue++               |
| R             | --            | postfix decrement      | lvalue--               |
| R             | typeid        | type ID                | typeid(type)           |
| R             | typeid        | run-time type ID       | typeid(expr)           |
| R             | explicit cast | type conversion        | cast_name\<type>(expr) |
|               |
| R             | ++            | prefix increment       | ++lvalue               |
| R             | --            | prefix decrement       | --lvalue               |
| R             | ~             | bitwise NOT            | ~expr                  |
| R             | !             | logical NOT            | !expr                  |
| R             | -             | unary minus            | -expr                  |
| R             | +             | unary plus             | +expr                  |
| R             | *             | dereference            | *expr                  |
| R             | &             | address-of             | &lvalue                |
| R             | ()            | type conversion        | (type) expr            |
| R             | sizeof        | size of object         | sizeof expr            |
| R             | sizeof        | size of type           | sizeof (type)          |
| R             | sizeof        | size of parameter pack | sizeof...(name)        |
| R             | new           | allocate object        | new type               |
| R             | new[]         | allocate array         | new type[size]         |
| R             | delete        | deallocate object      | delete expr            |
| R             | delete[]      | deallocate array       | delete[] expr          |
| R             | noexcept      | can expr throw         | noexcept(expr)         |
|               |
| L             | ->*           | ptr to member select   | ptr->*ptr_to_member    |
| L             | .*            | ptr to member select   | obj.*ptr_to_member     |
|               |
| L             | *             | multiply               | expr * expr            |
| L             | /             | divide                 | expr / expr            |
| L             | %             | modulo (remainder)     | expr % expr            |
|               |
| L             | +             | add                    | expr + expr            |
| L             | -             | subtract               | expr - expr            |
|               |
| L             | <<            | bitwise shift left     | expr << expr           |
| L             | >>            | bitwise shift rifht    | expr >> expr           |
|               |
| L             | <             | less than              | expr < expr            |
| L             | <=            | less than or equal     | expr <= expr           |
| L             | >             | greater than           | expr > expr            |
| L             | >=            | greater than or equal  | expr >= expr           |
|               |
| L             | ==            | equality               | expr == expr           |
| L             | !=            | inequality             | expr != expr           |
|               |
| L             | &             | bitwise AND            | expr & expr            |
|               |
| L             | ^             | bitwise XOR            | expr ^ expr            |
|               |
| L             | \|            | bitwise OR             | expr \| expr           |
|               |
| L             | &&            | logical AND            | expr && expr           |
|               |
| L             | \|\|          | logical OR             | expr \|\| expr         |
|               |
| R             | ?:            | conditional            | expr?expr:expr         |
|               |
| R             | =             | assignment             | lvalue = expr          |
| R             | *=, /=, %=    | compound assign        | lvalue += expr, etc.   |
| R             | +=, -=        |
| R             | <<=, >>=      |
| R             | &=, \|=, ^=   |
|               |
| R             | throw         | throw exception        | throw expr             |
|               |
| L             | ,             | comma                  | expr, expr             |

--------------------------------------------------------------------------------

### 4.1

#### 4.1.1

unary, binary and ternary operators

Lvalues and Rvalues

 - roughly speaking, when using an object as an rvalue, actually using its **value (content)**. And when using an object as an lvalue, using its **identity (location in memory)**.

When applying `decltype` to an expression, the result is a **reference** if the expression yields an lvalue

#### 4.1.2 Precedence and Associativity

#### 4.1.3

Precedence specifies how the operands are grouped, but not the order in which the operands are evaluated.  
Most operators make no guarantees about when or how its poerands are evaluated.  
> That is, if the subexpressions change the same variable, without specifying the order of evaluate, the result can be undefined.
> --Ad

Four operators do guarantee the order:

 - logical AND `&&`
 - logical OR `||`
 - conditional operator `?:`
 - comma operator `,`

--------------------------------------------------------------------------------

### 4.2 Arithmetic Operators

 - m%n `has the same sign as` m`
 - `(-m)/n` and `m/(-n)` == `-(m/n)`
 - `m%(-n)` == `m%n`
 - `(-m)%n` == `-(m%n)`

--------------------------------------------------------------------------------

### 4.3 Logical and Relational

The logical AND and OR always evaluate their left operand before the right

Define str as a `const reference` in the `range for` if iterating a string and donot need to write to the elements. (cause donot need to copy a `string` that large)

--------------------------------------------------------------------------------

### 4.4 Assignment Operators

The left-hand operand of an assignment operator must be a **modifiable lvalue**

- Assignment is right associative
- In compound assignment operation, the left-hand operand is eveluated only once, while twice in an ordinary assignment

--------------------------------------------------------------------------------

### 4.5 Increment and Decrement Operators

Difference between ++i and i++:

 - the prefix operators return the objcet **itself** as an lvalue
 - the postfix operators return a copy of the object's **original value** as an rvalue

> Use postfix operators only when necessary  
> The reason is simple: The prefix version avoids unnecessary work.  
> It increments the value and returns the incremented version.  
> The postfix operator must store the original value so that it can return the unincremented value as its result.

Combining dereference and increment in a single expression:

 - `*p++` : an idiom used for `cout << *pbeg++ << endl;` in loops

--------------------------------------------------------------------------------

### 4.6 The Member Access Operators

 - the arrow operator requires a pointer operand and yields an lvalue
 - the dot operator yields an lvalue if the member fetches an lvalue, otherwise rvalue

--------------------------------------------------------------------------------

### 4.7 The Conditional Operator

`cond ? expr1 : expr2;`

Nesting conditional operations no more than two or three times:

```cpp
R = (A > 9) ? "Good"
            : (A < 6) ? "Bad" : "OK";
```

--------------------------------------------------------------------------------

### 4.8 The Bitwise Operator

As usual, if an operand is a "small integer", its value is first promoted to a larger integral type.

> Because there are no guarantee for how the sign bit is handled, we strongly recommend using unsigned types with the bitwise operations.

--------------------------------------------------------------------------------

### 4.9 The sizeof Operator

 - `sizeof` a reference returns the size of the object which is referenced
 - `sizeof` a dereferenced pointer returns the size of the object to which the pointer points
 - `sizeof` an array is the size of the entire array, and note that it doesnot convert the array to a pointer
 - `sizeof` a `string` or a `vector` returns only the size of the **fixed part** of these types but not the size used by the elements

--------------------------------------------------------------------------------

### 4.10 Comma Operator

 - `comma` evaluates from left to right
 - the result is the right-hand operand expression
 - used in `for` loop: `for (; ; ++i, --n)`

--------------------------------------------------------------------------------

### 4.11 type Conversions

When implicit conversions occur

 - integral types smaller than int are promoted to larger
 - nonbool expressions are converted to bool
 - in initializations and assignments, the right-hand is converted to the left-hand type
 - in arithmetic and relational expressions with operands of mixed types, converted to a common type
 - conversions also happen during function calls

#### 4.11.1

 - `int` and `unsigned int` : `int` will be converted

#### 4.11.2 Other implicit conversions

Array:

 - `array` to `pointer`: in most expressions, when using an array, it is automatically converted to a pointer
 - exception: `decltype(arr)` `&arr` `sizeof(arr)` `typeid(arr)` `int& ref{arr}`

Pointer:

 - `0` and `nullptr` can be converted to any pointer type
 - pointer to any `nonconst` type can be converted to `void*`, and any to `const void*`

And

 - conversions to `bool`
 - conversion `to const` : for pointers and references
 - conversions defined by class types: i.e. `while (cin >> s)`

#### 4.11.3 Explicit Conversions

Named casts:
`cast-name<type> (expression);`

cast-names: `static_cast` `dynamic_cast` `const_cast` `reinterpret_cast`

static_cast: often useful when a larger arithmetic type is assigned to a smaller type.  
`double slope = static_cast<double>(j) / i;`  
`void* p = &d; double *dp = static_cast<double*>(p);`

const_cast: converts a const object to a nonconst type "casts away the const"  
only changes constness, and other casts cannot change constness  
`const char *pc; char *p = const_cast<char*>(pc);`  
but write to a const object is undefined

reinterpret_cast: generally performs a low-level reinterpretation of the bit pattern of its operands  
`int *p; char *pc = reinterpret_cast<char*>(ip);`

Old-style casts:  
`type (expr);` : function-style notation  
`(type) expr;` : C-style cast notation

> Avoid Casts

--------------------------------------------------------------------------------

EOF
