CppPrimer-Ch14-OverloadOps.md

C++ Primer Notes
================================================================================

Ad147  
<ar><r>

Init: 18Nov01

Chapter 14 Overloaded Operations and Conversions
--------------------------------------------------------------------------------

- [Chapter 14 Overloaded Operations and Conversions](#chapter-14-overloaded-operations-and-conversions)
    - [14.1 Basic Concepts](#141-basic-concepts)
    - [14.2 Input and Output Operators](#142-input-and-output-operators)
        - [14.2.1 Overloading the Output Operator `<<`](#1421-overloading-the-output-operator)
        - [14.2.2 Overloading the Input Operator `>>`](#1422-overloading-the-input-operator)
    - [14.3 Arithmetic and Relational Operators](#143-arithmetic-and-relational-operators)
        - [14.3.1 Equality Operators](#1431-equality-operators)
        - [14.3.2 Relational Operators](#1432-relational-operators)
    - [14.4 Assignment Operators](#144-assignment-operators)
    - [14.5 Subscript Operator](#145-subscript-operator)
    - [14.6 Increment and Decrement Operators](#146-increment-and-decrement-operators)
    - [14.7 Member Access Operators](#147-member-access-operators)
    - [14.8 Function-Call Operator](#148-function-call-operator)
        - [14.8.1 Lambdas Are Function Objects](#1481-lambdas-are-function-objects)
        - [14.8.2 Library-Defined Function Objects](#1482-library-defined-function-objects)
        - [14.8.3 Callable Objects and `function`](#1483-callable-objects-and-function)
    - [14.9 Overloading, Conversions, and Operators](#149-overloading-conversions-and-operators)
        - [14.9.1 Conversion Operators](#1491-conversion-operators)
        - [14.9.2 Avoiding Ambiguous Conversions](#1492-avoiding-ambiguous-conversions)
        - [14.9.3 Function Matching and Overloading Operators](#1493-function-matching-and-overloading-operators)
    - [Chapter Summary](#chapter-summary)

--------------------------------------------------------------------------------

### 14.1 Basic Concepts

An overloaded operator function has the same number of parameters as the operator has operands.

- A unary operator has one parameter
- A binary operator has two

In a binary operator, the left-hand operand is passed to the first parameter and the right-hand operand to the second.  
Except for the overloaded function-call operator, operator(), an overloaded operator may not have default arguments.

> ##### Note
> When an overloaded operator is a member function, `this` is bound to the left-hand operand.  
> Member operator functions have one less (explicit) parameter than the number of operands.

An operator function must either be a member of a class or have at least one parameter of class type:  
`// error: cannot redefine the built-in operator for ints`  
`int operator+(int, int);`  
This restriction means that we cannot change the meaning of an operator when applied to operands of built-in type.

###### Operators That May Be Overloaded

|     |     |       |          |          |             |
| --- | --- | ----- | -------- | -------- | ----------- |
| +   | -   | *     | /        | %        | ^           |
| &   | \|  | ~     | !        | ,        | =           |
| <   | >   | <=    | >=       | ++       | --          |
| <<  | >>  | ==    | !=       | &&       | \|\|        |
| +=  | -=  | /=    | %=       | ^=       | &=          |
| \|= | *=  | <<=   | >>=      | []       | ()          |
| ->  | ->* | `new` | `new []` | `delete` | `delete []` |

###### Operators That Cannot Be Overloaded

|     |     |     |     |
| --- | --- | --- | --- |
| ::  | .*  | .   | ?:  |

###### The `.*` Operator (by CB Bailey@SOF)

```cpp
struct A
{
    int a;
    int b;
};

int main()
{
    A obj;
    int A::* ptr_to_memb = &A::b;

    obj.*ptr_to_memb = 5;

    ptr_to_memb = &A::a;

    obj.*ptr_to_memb = 7;

    // Both members of obj are now assigned

    return 0;
}
```

##### 1) Calling an Overloaded Operator Function Directly

```cs
// equivalent calls to a nonmember operator function
data1 + data2;           // normal expression
operator+(data1, data2); // equivalent function call

// member function
data1 += data2;          // expression-based ''call''
data1.operator+=(data2); // equivalent call to a member operatorfunction
```

##### 2) Some Operators Shouldn’t Be Overloaded

Because the overloaded versions of some operators do not preserve order of
evaluation and/or short-circuit evaluation, it is usually a bad idea to overload them.

> ##### Best Practices
> Ordinarily, the comma, address-of, logical `AND`, and logical `OR` operatorsshould not be overloaded.

##### 3) Use Definitions That Are Consistent with the Built-in Meaning

- If the class does IO, define the shift operators to be consistent with how IO is done for the built-in types.
- If the class has an operation to test for equality, define `operator==`. If the class has `operator==`, it should usually have `operator!=` as well.
- If the class has a single, natural ordering operation, define `operator<`. If the class has `operator<`, it should probably have all of the relational operators.
- The return type of an overloaded operator usually should be compatible with the return from the built-in version of the operator: The logical and relational operators should return `bool`, the arithmetic operators should return a value of the class type, and assignment and compound assignment should return a reference to the left-hand operand.

##### 4) Assignment and Compound Assignment Operators

> ##### Caution: Use Operator Overloading Judiciously
> Each operator has an associated meaning from its use on the built-in types.   
> Binary +, for example, is strongly identified with addition.  
> Mapping binary + to an analogous operation for a class type can provide a convenient notational shorthand.  
> For example, the library `string` type, following aconvention common to many programming languages, uses + to represent concatenation—“adding” one `string` to the other.
> 
> Operator overloading is most useful when there is a logical mapping of abuilt-in operator to an operation on our type.  
> Using overloaded operatorsrather than inventing named operations can make our programs more naturaland intuitive.  
> Overuse or outright abuse of operator overloading can makeour classes incomprehensible.
> 
> Obvious abuses of operator overloading rarely happen in practice.  
> As an example, no responsible programmer would define operator+ to perform subtraction.  
> More common, but still inadvisable, are uses that contort anoperator’s “normal” meaning to force a fit to a given type.  
> Operators shouldbe used only for operations that are likely to be unambiguous to users.  
> Anoperator has an ambiguous meaning if it plausibly has more than one interpretation.

##### 5) Choosing Member or Nonmember Implementation

The following guidelines can be of help in deciding whether to make an operator a member or an ordinary nonmember function:

- The assignment (`=`), subscript (`[]`), call (`()`), and member access arrow (`->`) operators *must* be defined as members
- The compound-assignment operators ordinarily *ought* to be members. However, unlike assignment, they are not required to be members
- Operators that change the state of their object or that are closely tied to their given type—such as increment, decrement, and dereference—usually should be members
- Symmetric operators—those that might convert either operand, such as the arithmetic, equality, relational, and bitwise operators—usually should be defined as ordinary nonmember functions

--------------------------------------------------------------------------------

### 14.2 Input and Output Operators

#### 14.2.1 Overloading the Output Operator `<<`

Ordinarily, the first parameter of an output operator is a reference to a non`const` `ostream` object.  
The `ostream` is non`const` because writing to the stream changes its state. The parameter is a reference because we cannot copy an ostream object.

The second parameter ordinarily should be a reference to `const` of the class type we want to print.  
The parameter is a reference to avoid copying the argument.  
It can be const because (ordinarily) printing an object does not change that object.

To be consistent with other output operators, `operator<<` normally returns its `ostream` parameter.

##### 1) The `Sales_data` Output Operator

##### 2) Output Operators Usually Do Minimal Formatting

> ##### Best Practices
> Generally, output operators should print the contents of the object, with minimal formatting.  
> They should not print a newline.

##### 3) IO Operators Must Be Nonmember Functions

#### 14.2.2 Overloading the Input Operator `>>`

##### 1) The `Sales_data` Input Operator

> ##### Note
> Input operators must deal with the possibility that the input might fail; outputoperators generally don’t bother.

##### 2) Errors during Input

The kinds of errors that might happen in an input operator include the following:
- A read operation might fail because the stream contains data of an incorrect type. For example, after reading bookNo, the input operator assumes that the next two items will be numeric data. If nonnumeric data is input, that read and any subsequent use of the stream will fail.
- Any of the reads could hit end-of-file or some other error on the input stream.

Rather than checking each read, we check once after reading all the data and before using those data.

```cs
if (is) // check that the inputs succeeded
    item.revenue = item.units_sold *price;
else
    item = Sales_data(); // input failed: give the object the default state
```

> ##### Best Practices
> Input operators should decide what, if anything, to do about error recovery.

##### 3) Indicating Errors

--------------------------------------------------------------------------------

### 14.3 Arithmetic and Relational Operators

Ordinarily, we define the arithmetic and relational operators as nonmember functions in order to allow conversions for either the left- or right-hand operand.  
These operators shouldn’t need to change the state of either operand, so the parameters are ordinarily references to `const`.

Classes that define an arithmetic operator generally define the corresponding compound assignment operator as well.  
When a class has both operators, it is usuallymore efficient to define the arithmetic operator to use compound assignment:

```cs
//assumes that both objects refer to the same book
Sales_data operator+(const Sales_data &lhs, const Sales_data &rhs)
{
    Sales_data sum = lhs; // copy data members from lhs into sum
    sum += rhs;           // add rhs into sum
    return sum;
}
```

> ##### Tip
> Classes that define both an arithmetic operator and the related compound assignment ordinarily ought to implement the arithmetic operator by **using the compound assignment**.

#### 14.3.1 Equality Operators

Ordinarily, classes in C++ define the equality operator to test whether two objects areequivalent.  
That is, they usually compare every data member and treat two objects asequal if and only if all the corresponding members are equal.

In line with this designphilosophy, our Sales_data equality operator should compare the bookNo as well asthe sales figures:Click here to view code imagebool operator==(const Sales_data &lhs, const Sales_data &rhs){return lhs.isbn() == rhs.isbn() &&lhs.units_sold == rhs.units_sold &&lhs.revenue == rhs.revenue;}bool operator!=(const Sales_data &lhs, const Sales_data &rhs){return !(lhs == rhs);}

The definition of these functions is trivial.  
More important are the design principlesthat these functions embody:

- If a class has an operation to determine whether two objects are equal, it should define that function as `operator==` rather than as a named function:  
  Users will expect to be able to compare objects using `==`; providing `==` means they won’t need to learn and remember a new name for the operation; and it is easier to use the library containers and algorithms with classes that define the== operator.
- If a class defines `operator==`, that operator ordinarily should determine whether the given objects contain equivalent data.
- Ordinarily, the equality operator should be transitive, meaning that if `a == b` and `b == c` are both true, then `a == c` should also be true.
- If a class defines `operator==`, it should also define `operator!=`. Users willexpect that if they can use == then they can also use !=, and vice versa.
- One of the equality or inequality operators should delegate the work to the other. That is, one of these operators should do the real work to compare objects. The other should call the one that does the real work.

> ##### Best Practices
> Classes for which there is a logical meaning for equality normally should define `operator==`.  
> Classes that define == make it easier for users to usethe class with the library algorithms.

#### 14.3.2 Relational Operators

Ordinarily the relational operators should

1. Define an ordering relation that is consistent with the requirements for use as a key to an associative container; and
2. Define a relation that is consistent with == if the class has both operators. Inparticular, if two objects are !=, then one object should be < the other.

> ##### Best Practices
> If a single logical definition for `<` exists, classes usually should define the `<` operator.  
> However, if the class also has `==`, define `<` only if the definitions of `<` and `==` yield consistent results.

--------------------------------------------------------------------------------

### 14.4 Assignment Operators

> ##### Note
> Assignment operators can be overloaded. Assignment operators, regardless of parameter type, must be defined as member functions.

##### Compound-Assignment Operators

> ##### Best Practices
> Assignment operators must, and ordinarily compound-assignment operators should, be defined as members.  
> These operators should return a reference to the left-hand operand.

--------------------------------------------------------------------------------

### 14.5 Subscript Operator

> ##### Note
> The subscript operator must be a member function.

> ##### Best Practices
> If a class has a subscript operator, it usually should define two versions:  
> one that returns a plain reference and the other that is a const member and returns a reference to const.

--------------------------------------------------------------------------------

### 14.6 Increment and Decrement Operators

The increment (++) and decrement (--) operators are most often implemented foriterator classes.

> ##### Best Practices
> Classes that define increment or decrement operators should define both the prefix and postfix versions.  
> These operators usually should be defined as members.

##### 1) Defining Prefix Increment/Decrement Operators

```cs
class StrBlobPtr
{
public:
    // increment and decrement
    StrBlobPtr& operator++(); // prefix operators
    StrBlobPtr& operator--();
    // other members as before
};
```

> ##### Best Practices
> To be consistent with the built-in operators, the prefix operators should return a reference to the incremented or decremented object.

```cs
//prefix: return a reference to the incremented/decremented object
StrBlobPtr& StrBlobPtr::operator++()
{
    // if curr already points past the end of the container, canot increment it
    check(curr, "increment past end of StrBlobPtr");
    ++curr; // advance the current state
    return *this;
}

StrBlobPtr& StrBlobPtr::operator--()
{
    // if curr is zero, decrementing it will yield an invalid subscript
    --curr; // move the current state back one element
    check(-1, "decrement past begin of StrBlobPtr");
    return *this;
}
```

The decrement operator decrements curr before calling check. That way, if curr(which is an unsigned number) is already zero, the value that we pass to check willbe a large positive value representing an invalid subscrip.

##### 2) Differentiating Prefix and Postfix Operators

The prefix and postfix versions use the same symbol, meaning that the overloaded versions of these operators have the same name.  
They also have the same number and type of operands.
 
To solve this problem, the postfix versions take an extra (unused) parameter of type `int`.  
When we use a postfix operator, the compiler supplies 0 as the argument for this parameter.  
Although the postfix function can use this extra parameter, it usually should not.  
That parameter is not needed for the work normally performed by a postfix operator.  
Its sole purpose is to distinguish a postfix function from the prefix version.

```cs
class StrBlobPtr
{
public:
    // increment and decrement
    StrBlobPtr operator++(int); // postfix operators
    StrBlobPtr operator--(int);
    // other members as before
};
```

> ##### Best Practices
> To be consistent with the built-in operators, the postfix operators should return the old (unincremented or undecremented) value.  
> That value is returned as a value, not a reference.

The postfix versions have to remember the current state of the object before incrementing the object:

```cs
//postfix: increment/decrement the object but return the unchanged value
StrBlobPtr StrBlobPtr::operator++(int)
{
    // no check needed here; the call to prefix increment will do the check
    StrBlobPtr ret = *this; // save the current value
    ++*this;    // advance one element; prefix ++ checks the increment
    return ret; // return the saved state
}

StrBlobPtr StrBlobPtr::operator--(int)
{
    // no check needed here; the call to prefix decrement will do the check
    StrBlobPtr ret = *this; // save the current value
    --*this;    //move backward one element; prefix -- checks the decrement
    return ret; // return the saved state
}
```

> ##### Note
> The `int` parameter is not used, so we do not give it a name.

##### 3) Calling the Postfix Operators Explicitly

--------------------------------------------------------------------------------

### 14.7 Member Access Operators

> ##### Note
> Operator arrow must be a member.  
> The dereference operator is not required to be a member but usually should be a member as well.

It is worth noting that we’ve defined these operators as const members.  
Unlike the increment and decrment operators, fetching an element doesn’t change the state of a `StrBlobPtr`.  
Also note that these operators return a reference or pointer to non`const` string.  
They do so because we know that a `StrBlobPtr` can only be bound to a non`const StrBlob`.

##### 1) Constraints on the Return from Operator Arrow

The arrow operator never loses its fundamental meaning of member access.  
When we overload arrow, we change the object from which arrow fetches the specified member.  
We cannot change the fact that arrow fetches a member.

When we write `point->mem`, point must be a pointer to a class object or it mustbe an object of a class with an overloaded `operator->`.  
Depending on the type of point, writing `point->mem` is equivalent to  
`(*point).mem; // point is a built-in pointer typepoint.`  
`operator()->mem; // pointis an object of class type`

Otherwise the code is in error.  
That is, `point->mem` executes as follows:

1. If point is a pointer, then the built-in arrow operator is applied, which means this expression is a synonym for `(*point).mem`.  
   The pointer is dereferenced and the indicated member is fetched from the resulting object.  
   If the type pointed to by `point` does not have a member named `mem`, then the code is in error.
2. If `point` is an object of a class that defines `operator->`, then the result of `point.operator->()` is used to fetch `mem`.  
   If that result is a pointer, then step 1 is executed on that pointer.  
   If the result is an object that itself has anoverloaded `operator->()`, then this step is repeated on that object.  
   This process continues until either a pointer to an object with the indicated memberis returned or some other value is returned, in which case the code is in error.

> ##### Note
> The overloaded arrow operator must return either a pointer to a class type or an object of a class type that defines its own operator arrow.

--------------------------------------------------------------------------------

### 14.8 Function-Call Operator

Classes that overload the call operator allow objects of its type to be used as if they were a function.
Because such classes can also store state, they can be more flexible than ordinary functions.

> ##### Note
> The function-call operator must be a member function.  
> A class may define multiple versions of the call operator, each of which must differ as to the number or types of their parameters.

Objects of classes that define the call operator are referred to as **function objects**.  
Such objects “act like functions” because we can call them.

##### 1) Function-Object Classes with State

#### 14.8.1 Lambdas Are Function Objects

When we write a lambda, the compiler translates that expression into an unnamed object of an unnamed class.  
The classes generated from a lambda contain an overloaded function-call operator.  
For example, the lambda that we passed as the last argument to `stable_sort`:

```cs
// sort words by size, but maintain alphabetical order for words of the same size
stable_sort(words.begin(), words.end(),
            [](const string &a, const string &b)
            { return a.size() < b.size(); });
```

acts like an unnamed object of a class that would look something like

```cs
class ShorterString
{
public:
    bool operator()(const string &s1, const string &s2) const
    { return s1.size() < s2.size(); }
};
```

By default, lambdas may not change their captured variables.  
As a result, by default, the function-call operator in aclass generated from a lambda is a const member function.  
If the lambda is declaredas `mutable`, then the call operator is not const.

##### 1) Classes Representing Lambdas with Captures

When a lambda captures a variable by reference, it is up to the program to ensure that the variable to which the reference refers exists when the lambda is executed.  
Therefore, the compiler is permitted to use the reference directly without storing that reference as a data member in the generated class.

In contrast, variables that are captured by value are copied into the lambda.  
As a result, classes generated from lambdas that capture variables by value have data members corresponding to each such variable.  
These classes also have a constructor to initialize these data members from the value of the captured variables.  
As an example, in § 10.3.2 (p. 390), the lambda that we used to find the first string whose length was greater than or equal to a given bound:

```cs
//get an iterator to the first element whose size() is >= sz
auto wc = find_if(words.begin(), words.end(),
                  [sz] (const string &a) { return a.size() >= sz; });
```

would generate a class that looks something like

```cs
class SizeComp
{
    SizeComp(size_t n): sz(n) {} // parameter for each captured variable
    // call operator with the same return type, parameters, and body as the lambda
    bool operator()(const string &s) const
    { return s.size() >= sz; }

private:
    size_t sz; // a data member for each variable captured by value
};
```

#### 14.8.2 Library-Defined Function Objects

###### Library Function Objects `<functional>`

| Arithmetic    | Relational       | Logical        |
| ------------- | ---------------- | -------------- |
| plus<T>       | equal_to<T>      | logical_and<T> |
| minus<T>      | not_equal_to<T>  | logical_or<T>  |
| multiplies<T> | greater<T>       | logical_not<T> |
| divides<T>    | greater_equal<T> |
| modulus<T>    | less<T>          |
| negate<T>     | less_than<T>     |

##### 1) Using a Library Function Object with the Algorithms

If svec is a `vector<string>`,  
`// passes a temporary function object that applies the < operator to two strings`  
`sort(svec.begin(), svec.end(), greater<string>());`  
sorts the vector in descending order.

One important aspect of these library function objects is that the library guarantees that they will work for pointers.  
Recall that comparing two unrelated pointers is undefined.  
However, we might want to sort a vector of pointers based on their addresses in memory.  
Although it would be undefined for us to do so directly, we can do so through one of the library function objects:

```cs
vector<string *> nameTable; // vectorof pointers
// error: the pointers in nameTableare unrelated, so < is undefined
sort(nameTable.begin(), nameTable.end(),
     [](string *a, string *b) { return a < b; });
// ok: library guarantees that less on pointer types is well defined
sort(nameTable.begin(), nameTable.end(), less<string*>());
```

It is also worth noting that the associative containers use `less<key_type>` to order their elements.  
As a result, we can define a set of pointers or use a pointer as the key in a map without specifying less directly.

#### 14.8.3 Callable Objects and `function`

C++ has several kinds of callable objects:
- functions
- pointers to functions
- lambdas
- objects created by `bind`
- classes that overload the function-call operator

However, two callable objects with different types may share the same **call signature**.  
The call signature specifies the type returned by a call to the object and the argument type(s) that must be passed in the call.  
A call signature corresponds to a function type.  
For example:  
`int(int, int)`  
is a function type that takes two ints and returns an int.

##### 1) Different Types Can Have the Same Call Signature

Sometimes we want to treat several callable objects that share a call signature as if they had the same type.  
For example:

```cs
//ordinary functionint
add(int i, int j) { return i + j; }

// lambda, which generates an unnamed function-object class
auto mod = [](int i, int j) { return i % j; };

// function-object class
struct div
{
    int operator()(int denominator, int divisor) { return denominator / divisor; }
};
```

Even though each has a distinct type, they all share the same call signature:  
`int(int, int)`

We might want to use these callables to build a simple desk calculator.  
To do so, we’d want to define a **function table** to store “pointers” to these callables.  
When the program needs to execute a particular operation, it will look in the table to find which function to call.

In C++, function tables are easy to implement using a `map`.  
In this case, we’ll use a string corresponding to an operator symbol as the key;  
the value will be the function that implements that operator.  
When we want to evaluate a given operator, we’ll index the map with that operator and call the resulting element.

If all our functions were freestanding functions, and assuming we were handling only binary operators for type `int`, we could define the `map` as  
`// maps an operator to a pointer to a function taking two ints and returning an int`  
`map<string, int(*)(int,int)> binops;`

We could put a pointer to add into binops as follows:  
`// ok:add is a pointer to function of the appropriate type`  
`binops.insert({"+", add}); // {"+", add} is a pair`

However, we can’t store mod or div in binops:  
`binops.insert({"%", mod}); // error: mod is not a pointer to function`

The problem is that mod is a lambda, and each lambda has its own class type.  
That type does not match the type of the values stored in `binops`.

##### 2) The Library `function` Type

We can solve this problem using a new library type named `function` that is defined in the `functional` header.

###### Operations on `function`

|                           |                                                                      |
| ------------------------- | -------------------------------------------------------------------- |
| `function<T> f;`          | `f` is a null `function` object can store callable objects           |
|                           | with a call signature equivalent to the function type T              |
|                           | (i.e., T is *retType(args)*).                                        |
| `function<T> f(nullptr);` | Explicitly construct a null `function`                               |
| `function<T> f(obj);`     | Stores a copy of the callable object `obj` in `f`.                   |
| `f(args)`                 | Calls the object in `f` passing *args*.                              |
| >>>>>>>>>>>>>>>>>>        | **Types defined as memebers of `function<T>`**                       |
| `result_type`             | The type returned by this `function` type's callable object.         |
| `argument_type`           | Types defined when T has exactly one or two arguments.               |
| `first_argument_type`     | If `T` has one argument, `argument_type` is a synonym for that type. |
| `second_argument_type`    | If `T` has two arguments, `first_argument_type` and                  |
|                           | `second_argument_type` are synonyms for those argument types.        |

`C++11` function is a template.  
We must specify the call signature of the objects that this particular function type can represent.  
`function<int(int, int)>`  
We can use that type to represent any of our desk calculator types:

```cs
function<int(int, int)> f1 = add; // function pointer
function<int(int, int)> f2 = div(); //object of a function-object class
function<int(int, int)> f3 = [](inti, int j) // lambda { return i * j; };
cout << f1(4,2) << endl; // prints 6
cout << f2(4,2) << endl; // prints 2
cout << f3(4,2) << endl; // prints 8
```

We can now redefine our `map` using this function type:

```cs
// table of callable objects corresponding to each binary operator
// all the callables must take twoints and return an int
// an element can be a function pointer, function object, or lambda
map<string, function<int(int, int)>> binops;
```

We can add each of our callable objects, be they function pointers, lambdas, or function objects, to this map:

```cs
map<string, function<int(int, int)>> binops =
{
    {"+", add},                                 // function pointer
    {"-", std::minus<int>()},                   // library function object
    {"/", div()},                               // user-defined function object
    {"*", [](int i, int j) { return i * j; }},  // unnamed lambda
    {"%", mod}                                  // named lambda object
};
```

As usual, when we index a map, we get a reference to the associated value.  
When we index binops, we get a reference to an object of type function.  
The `function` type overloads the call operator.  
That call operator takes its own arguments and passes them along to its stored callable object:  
`binops["+"](10, 5); // calls add(10, 5)`  
`binops["/"](10, 5); // uses the call operator of the div object`

##### 3) Overloaded Functions and `function`

We cannot (directly) store the name of an overloaded function in an object of type `function`:

```cs
int add(int i, int j) { return i + j; }
Sales_data add(const Sales_data&, const Sales_data&);
map<string, function<int(int, int)>> binops;
binops.insert({"+", add}); // error: which add?
```

One way to resolve the ambiguity is to store a function pointer instead of the name of the function:  
`int (*fp)(int,int) = add; // pointer to the version of add that takes two ints`  
`binops.insert({"+", fp}); // ok: fp points to the right version of add`

Alternatively, we can use a lambda to disambiguate:  
`// ok: use a lambda to disambiguate which version of add we want to use`  
`binops.insert({"+", [](int a, int b) {return add(a, b);}});`

The call inside the lambda body passes two ints.  
That call can match only the version of add that takes two ints, and so that is the function that is called when the lambda is executed.

> ##### Note
> The `function` class in the new library is not related to classes `namedunary_function` and `binary_function` that were part of earlier versions of the library.  
> These classes have been deprecated by the more general `bind` function.

--------------------------------------------------------------------------------

### 14.9 Overloading, Conversions, and Operators

A non`explicit` constructor that can be called with one argument defines an implicit conversion.  
Such constructors convert an object fromthe argument’s type to the class type.  
We can also define conversions *from* the class type. We define a conversion from a class type by defining a conversion operator.  
Converting constructors and conversion operators define **class-type conversions**.  
Such conversions are also referred to as **user-defined conversions**.

#### 14.9.1 Conversion Operators

A **conversion operator** is a special kind of member function that converts a value of a class type to a value of some other type.  
A conversion function typically has the general form  
`operator type() const;`

Conversion operators can be defined for any type (other than void) that can be a function return type.  
Conversions to pointer types—both data and function pointers—and to reference types are allowed.

Conversion operators have no explicitly stated return type and no parameters, and they must be defined as member functions.  
Conversion operations ordinarily should not change the object they are converting. As a result, conversion operators usually should be defined as const members.

> ##### Note
> A conversion function must be a member function, may not specify a return type, and must have an empty parameter list.  
> The function usually should be `const`.

##### 1) Defining a Class with a Conversion Operator

As an example, we’ll define a small class that represents an integer in the range of 0 to 255:

```cs
class SmallInt
{
public:
    SmallInt(int i = 0) : val(i)
    {
        if (i < 0 || i > 255)
            throw std::out_of_range("Bad SmallInt value");
    }
    
    operator int() const { return val; }

private:
    std::size_t val;
};
```

Our `SmallInt` class defines conversions *to* and *from* its type:

```cs
SmallInt si;
si = 4; // implicitly converts 4 to SmallInt then calls SmallInt::operator=
si + 3; // implicitly converts si to int followed by integer addition
```

Although a conversion function does not specify a return type, each conversion function must return a value of its corresponding type:

```cs
class SmallInt;
operator int(SmallInt&);                    // error: nonmember
class SmallInt
{
public:
    int operator int() const;               // error: return type
    operator int(int = 0) const;            // error: parameter list
    operator int*() const { return 42; }    // error: 42 is not a  pointer
};
```

> ##### Caution: Avoid Overuse of Conversion Functions
> As with using overloaded operators, judicious use of conversion operators can greatly simplify the job of a class designer and make using a class easier.  
> However, some conversions can be misleading.  
> Conversion operators are misleading when there is no obvious single mapping between the class type and the conversion type.
> 
> For example, consider a class that represents a `Date`.  
> We might think it would be a good idea to provide a conversion from Date to int.  
> However, what value should the conversion function return?  
> The function might returna decimal representation of the year, month, and day.  
> For example, July 30, 1989 might be represented as the int value 19800730.  
> Alternatively, the conversion operator might return an int representing the number of days that have elapsed since some epoch point, such as January 1, 1970.  
> Both these conversions have the desirable property that later dates correspond to larger integers, and so either might be useful.
> 
> The problem is that there is no single one-to-one mapping between an object of type Date and a value of type int.  
> In such cases, it is better not to define the conversion operator.  
> Instead, the class ought to define one or more ordinary members to extract the information in these various forms.

##### 2) Conversion Operators Can Yield Suprising Results

In practice, classes rarely provide conversion operators.  
However, there is one important exception to this rule of thumb:  
It is not uncommon for classes to define conversions to `bool`.

Under earlier versions of the standard, classes that wanted to define a conversion tobool faced a problem:  
Because bool is an arithmetic type, a class-type object that is converted to bool can be used in any context where an arithmetic type is expected.  
Such conversions can happen in surprising ways.  
In particular, if `istream` had a conversion to bool, the following code would compile:  
`int i = 42;`  
`cin << i; // this code would be legal if the conversion to bool were not explicit!`

This program attempts to use the output operator on an input stream. There is no `<<` defined for istream, so the code is almost surely in error.  
However, this code could use the bool conversion operator to convert `cin` to `bool`.  
The resulting bool value would then be promoted to int and used as the left-hand operand to the built-inversion of the left-shift operator.  
The promoted bool value (either 1 or 0) would beshifted left 42 positions.

##### 3) `explicit` Conversion Operators

`C++11` To prevent such problems, the new standard introduced **`explicit` conversion operators**:

```cs
class SmallInt
{
public:
    // the compiler won't automatically apply this conversion
    explicit operator int() const { return val; }
    // other members as before
};
```

As with an explicit constructor, the compiler won’t (generally) use an explicit conversion operator for implicit conversions:  
`SmallInt si = 3; // ok: the SmallInt constructor is not explicit`  
`si + 3; // error: implicit is conversion required, but operator int is explicit`  
`static_cast<int>(si) + 3; // ok: explicitly request the conversion`

If the conversion operator is `explicit`, we can still do the conversion.  
However, with one exception, we must do so explicitly through a cast.

The exception is that the compiler will apply an `explicit` conversion to an expression used as a condition.  
That is, an `explicit` conversion will be used implicitly to convert an expression used as

- The condition of an `if`, `while`, or `do` statement
- The condition expression in a `for` statement header
- An operand to the logical NOT (`!`), OR (`||`), or AND (`&&`) operators
- The condition expression in a conditional (`?:`) operator

##### 4) Conversion to `bool`

In earlier versions of the library, the IO types defined a conversion to void*.  
They did so to avoid the kinds of problems illustrated above.  
Under the new standard, the IO library instead defines an `explicit` conversion to `bool`.

Whenever we use a stream object in a condition, we use the operator bool thatis defined for the IO types.  
For example,  
`while (std::cin >> value)`

The condition in the `while` executes the input operator, which reads into `value` and returns `cin`.  
To evaluate the condition, `cin` is implicitly converted by the `istream operator bool` conversion function.  
That function returns `true` if the condition state of cin is good, and false otherwise.

> ##### Best Practices
> Conversion to `bool` is usually intended for use in conditions.  
> As a result, `operator bool` ordinarily should be defined as `explicit`.

#### 14.9.2 Avoiding Ambiguous Conversions

If a class has one or more conversions, it is important to ensure that there is only oneway to convert from the class type to the target type.  
There are two ways that multiple conversion paths can occur:

- The first happens when two classes provide mutual conversions.  
  For example, mutual conversions exist when a class `A` defines a converting constructor that takes an object of class `B` and `B` itself defines a conversion operator to type `A`.
- The second way to generate multiple conversion paths is to define multiple conversions from or to types that are themselves related by conversions.  
  The most obvious instance is the built-in arithmetic types.  
  A given class ordinarily ought to define at most one conversion to or from an arithmetic type.

> ##### Warning
> Ordinarily, it is a bad idea to define classes with mutual conversions or to define conversions to or from two arithmetic types.

##### 1) Argument Matching and Mutual Conversions

In the following example, we’ve defined two ways to obtain an A from a B: either byusing B’s conversion operator or by using the A constructor that takes a B:

```cs
//usually a bad idea to have mutual conversions between two class types
struct B;
struct A
{
    A() = default;
    A(const B&); // converts a B to an A
    // other members
};

struct B
{
    operator A() const; // also converts a B to an A
    // other members
};

A f(const A&);
B b;
A a = f(b); // error ambiguous: f(B::operator A()) or f(A::A(const B&))
```

If we want to make this call, we have to explicitly call the conversion operator or the constructor:  
`A a1 = f(b.operator A()); // ok: use B's conversion operator`  
`A a2 = f(A(b));           // ok: use A's constructor`

Note that we can’t resolve the ambiguity by using a cast—the cast itself would havethe same ambiguity.

##### 2) Ambiguities and Multiple Conversions to Built-in Types

Ambiguities also occur when a class defines multiple conversions to (or from) typesthat are themselves related by conversions.  
The easiest case to illustrate—and one that is particularly problematic—is when a class defines constructors from or conversions to more than one arithmetic type:

```cs
struct A
{
    A(int = 0); // usually a bad idea to have two
    A(double);  // conversions from arithmetic types
    operator int() const;       // usually a bad idea to have two
    operator double() const;    // conversions to arithmetic types
    //other members
};

void f2(long double);
A a;
f2(a);      // error ambiguous: f(A::operator int()) or f(A::operator double())
long lg;
A a2(lg);   // error ambiguous: A::A(int) or A::A(double)
```

In the call to f2, neither conversion is an exact match to long double.  
However,either conversion can be used, followed by a standard conversion to get to long double.  
Hence, neither conversion is better than the other;  
the call is ambiguous.

We encounter the same problem when we try to initialize a2 from a long.  
Neither constructor is an exact match for long.  
Each would require that the argument be converted before using the constructor:

- Standard long to double conversion followed by A(double)
- Standard long to int conversion followed by A(int)

These conversion sequences are indistinguishable, so the call is ambiguous.

The call to f2, and the initialization of a2, are ambiguous because the standard conversions that were needed had the same rank. When a user-defined conversion is used, the rank of the standard conversion, if any, is used to select the best match:

```cs
short s = 42;
// promoting short to int is better than converting short to double
A a3(s); // usesA::A(int)
```

> ##### Note
> When two user-defined conversions are used, the rank of the standard conversion, if any, *preceding* or *following* the conversion function is used to select the best match.

> ##### Caution: Conversions and Operators
> Correctly designing the overloaded operators, conversion constructors, and conversion functions for a class requires some care.  
> In particular, ambiguities are easy to generate if a class defines both conversion operators and overloaded operators.  
> A few rules of thumb can be helpful:
> 
> - Don’t define mutually converting classes—if class `Foo` has a constructor that takes an object of class `Bar`, do not give `Bar` a conversion operator to type `Foo`.
> - Avoid conversions to the built-in arithmetic types. In particular, if you do define a conversion to an arithmetic type, then
>   - Do not define overloaded versions of the operators that take arithmetic types.  
>     If users need to use these operators, the conversion operation will convert objects of your type, and then the built-in operators can be used.
>   - Do not define a conversion to more than one arithmetic type.  
>     Let the standard conversions provide conversions to the other arithmetic types.
> 
> **The easiest rule of all**: With the exception of an `explicit` conversion to `bool`, avoid defining conversion functions and limit non`explicit` constructors to those that are “obviously right.”

##### 3) Overloaded Functions and Converting Constructors

Choosing among multiple conversions is further complicated when we call anoverloaded function.  
If two or more conversions provide a viable match, then theconversions are considered equally good.

As one example, ambiguity problems can arise when overloaded functions take parameters that differ by class types that define the same converting constructors:

```cs
struct C
{
    C(int);
    // other members
};

struct D
{
    D(int);
    // other members
};

void manip(const C&);
void manip(const D&);
manip(10); // error ambiguous: manip(C(10)) or manip(D(10))
```

The caller can disambiguate by explicitly constructing the correct type:  
`manip(C(10)); // ok: calls manip(const C&)`

> ##### Warning
> Needing to use a constructor or a cast to convert an argument in a call to anoverloaded function frequently is a sign of bad design.

##### 4) Overloaded Functions and User-Defined Conversion

In a call to an overloaded function, if two (or more) user-defined conversions providea viable match, the conversions are considered equally good.  
The rank of anystandard conversions that might or might not be required is not considered.  
Whether a built-in conversion is also needed is considered only if the overload set can be matched using the same conversion function.

For example, our call to manip would be ambiguous even if one of the classes defined a constructor that required a standard conversion for the argument:

```cs
struct E
{
    E(double);
    // other members
};

void manip2(const C&);
void manip2(const E&); // error ambiguous: two different user-defined conversions could be used
manip2(10); // manip2(C(10)) or manip2(E(double(10)))
```

In this case, C has a conversion from int and E has a conversion from double.  
For the call `manip2(10)`, both manip2 functions are viable:

- manip2(const C&) is viable because C has a converting constructor that takes an int. That constructor is an exact match for the argument.
- manip2(const E&) is viable because E has a converting constructor thattakes a double and we can use a standard conversion to convert the int argument in order to use that converting constructor.

Because calls to the overloaded functions require *different* user-defined conversions from one another, this call is ambiguous.  
In particular, even though one of the callsrequires a standard conversion and the other is an exact match, the compiler will still flag this call as an error.

> ##### Note
> In a call to an overloaded function, the rank of an additional standard conversion (if any) matters only if the viable functions require the same user-defined conversion.  
> If different user-defined conversions are needed, then thecall is ambiguous.

#### 14.9.3 Function Matching and Overloading Operators

Overloaded operators are overloaded functions.  
Normal function matching is used to determine which operator—built-in or overloaded—to apply to a given expression.  
However, when an operator function is used in an expression, the set of candidate functions is broader than when we call a function using the call operator.  
If `a` has a class type, the expression `a sym b` might be  
`a.operatorsym (b); // a has operator sym as a member function`  
`operatorsym(a, b); // operator sym is an ordinary function`

Unlike ordinary function calls, we cannot use the form of the call to distinquish whether we’re calling a nonmember or a member function.

When we use an overloaded operator with an operand of class type, the candidate functions include ordinary nonmember versions of that operator, as well as the built-inversions of the operator.  
Moreover, if the left-hand operand has class type, the overloaded versions of the operator, if any, defined by that class are also included.

When we call a named function, member and nonmember functions with the same name do not overload one another.  
There is no overloading because the syntax we use to call a named function distinguishes between member and nonmember functions.  
When a call is through an object of a class type (or through a reference orpointer to such an object), then only the member functions of that class are considered.  
When we use an overloaded operator in an expression, there is nothing to indicate whether we’re using a member or nonmember function.  
Therefore, both member and nonmember versions must be considered.

> ##### Note
> The set of candidate functions for an operator used in an expression cancontain both nonmember and member functions.

As an example, we’ll define an addition operator for our SmallInt class:

```cs
class SmallInt
{
    friend SmallInt operator+(const SmallInt&, const SmallInt&);

public:
    SmallInt(int = 0); // conversion from int
    operator int() const { return val; } // conversion to int

private:
    std::size_t val;
};
```

We can use this class to add two SmallInts, but we will run into ambiguity problems if we attempt to perform mixed-mode arithmetic:

```cs
SmallInt s1, s2;
SmallInt s3 = s1 + s2;  // uses overloaded operator+
int i = s3 + 0;         // error: ambiguous
```

The first addition uses the overloaded version of + that takes two SmallInt values.  
The second addition is ambiguous, because we can convert 0 to a SmallInt and use the SmallInt version of +, or convert s3 to int and use the built-in addition operator on ints.

> ##### Warning
> Providing both conversion functions to an arithmetic type and overloaded operators for the same class type may lead to ambiguities between the overloaded operators and the built-in operators.

--------------------------------------------------------------------------------

### Chapter Summary

An overloaded operator must either be a member of a class or have at least oneoperand of class type.  
Overloaded operators have the same number of operands, associativity, and precedence as the corresponding operator when applied to the built-in types.  
When an operator is defined as a member, its implicit `this` pointer is bound to the first operand.  
The
- assignment
- subscript
- function-call
- arrow

operators must be class members.

Objects of classes that overload the function-call operator, `operator()`, are known as “function objects.”  
Such objects are often used in combination with the standard algorithms.  
Lambda expressions are succinct ways to define simple function-object classes.

A class can define conversions to or from its type that are used automatically.  
Non`explicit` constructors that can be called with a single argument define conversions from the parameter type to the class type;  
non`explicit` conversion operators define conversions from the class type to other types.

--------------------------------------------------------------------------------

EOF
