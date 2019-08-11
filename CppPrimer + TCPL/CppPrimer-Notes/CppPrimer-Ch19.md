CppPrimer-Ch19.md

C++ Primer Notes
================================================================================

Ad  
init: 18Nov06 (Index)

Chapter 19 Specialized Tools and Techniques
--------------------------------------------------------------------------------

### 19.1 Controlling Memory Allocation

#### 19.1.1 Overloading `new` and `delete`

##### 1) The `operator new` and `operator delete` Interface

##### 2) The `malloc` and `free` Functions

#### 19.1.2 Placement `new` Expressions

##### 1) Explicit Destructor Invocation

--------------------------------------------------------------------------------

### 19.2 Run-Time Type Identification

#### 19.2.1 The `dynamic_cast` Operator

##### 1) Pointer-Type `dynamic_cast`s

##### 2) Reference-Type `dynamic_cast`s

#### 19.2.2 The `typeid` Operator

##### 1) Using the `typeid` Operator

#### 19.2.3 Using RTTI

##### 1) The Class Hierarchy

##### 2) A Type-Sensitive Equality Operator

##### 3) The Virtual `equal` Functions

##### 4) The Base-Class `equal` Function

#### 19.2.4 The `type_info` Class

--------------------------------------------------------------------------------

### 19.3 Enumerations

##### 1) Enumerators

##### 2) Like Classes, Enumerations Define New Types

##### 3) Specifying the Size of an `enum`

##### 4) Forward Declarations for Enumerations

##### 5) Parameter Matching and Enumerations

--------------------------------------------------------------------------------

### 19.4 Pointer to Class Member

#### 19.4.1 Pointers to Data Members

##### 1) Using a Pointer to Data Member

##### 2) A Function Returning a Pointer to Data Member

##### 3) Using a Pointer to Member Function

##### 4) Using Type Aliases for Member Pointers

##### 5) Pointer-to-Member Function Tables

#### 19.4.2 Pointers to Member Functions

#### 19.4.3 Using Member Functions as Callable Objects

##### 1) Using `mem_fn` to Generate a Callable

##### 2) Using `bind` to Generate a Callable

--------------------------------------------------------------------------------

### 19.5 Nested Classes

##### 1) Declaring a Nested Class

##### 2) Defining a Nested Class outside of the Enclosing Class

##### 3) Defining the Members of a Nested Class

##### 4) Nested-Class `static` Member Definitions

##### 5) Name Lookup in Nested Class Scope

##### 6) The Nested and Enclosing Classes Are Independent

--------------------------------------------------------------------------------

### 19.6 `union`: A Space-Saving Class

##### 1) Defining a `union`

##### 2) Using a `union` Type

##### 3) Anonymous `union`s

##### 4) `union`s with Members of Class Type

##### 5) Using a Class to Manage `union` Members

##### 6) Managing the Discriminant and Destroying the `string`

##### 7) Managing Union Members That Require Copy Control

--------------------------------------------------------------------------------

### 19.7 Local Classes

##### 1) Local Classes May Not Use Variables from the Function’s Scope

##### 2) Normal Protection Rules Apply to Local Classes

##### 3) Name Lookup within a Local Class

##### 4) Nested Local Classes

--------------------------------------------------------------------------------

### 19.8 Inherently Nonportable Features

#### 19.8.1 Bit-fields

##### 1) Using Bit-fields

#### 19.8.2 `volatile` Qualifier

##### 1) Synthesized Copy Does Not Apply to `volatile` Objects

#### 19.8.3 Linkage Directives: `extern "C"`

##### 1) Declaring a Non-C++ Function

##### 2) Linkage Directives and Headers

##### 3) Pointers to `extern "C"` Functions

##### 4) Linkage Directives Apply to the Entire Declaration

##### 5) Exporting Our C++ Functions to Other Languages

##### 6) Overloaded Functions and Linkage Directives

--------------------------------------------------------------------------------

### Chapter Summary

C++ provides several specialized facilities that are tailored to particular kinds of problems.

Some applications need to take control of how memory is allocated.
They can do so by defining their own versions—either class specific or global—of the library `operator new` and `operator delete` functions.
If the application defines its own versions of these functions, `new` and `delete` expressions will use the application-defined version.

Some programs need to directly interrogate the dynamic type of an object at runtime.
Run-time type identification (RTTI) provides language-level support for this kind of programming.
RTTI applies only to classes that define virtual functions;
type information for types that do not define virtual functions is available but reflects the static type.

When we define a pointer to a class member, the pointer type also encapsulates the type of the class containing the member to which the pointer points.
A pointer to member may be bound to any member of the class that has the appropriate type.
When we dereference a pointer to member, we must supply an object from which to fetch the member.

C++ defines several additional aggregate types:
 - Nested classes, which are classes defined in the scope of another class. Such classes are often defined as implementation classes of their enclosing class.
 - `unions` are a special kind of class that may define several data members, butat any point in time, only one member may have a value. unions are most often nested inside another class type.
 - Local classes, which are defined inside a function. All members of a local class must be defined in the class body. There are no static data members of a local class.

C++ also supports several inherently nonportable features, including bit-fields and `volatile`, which make it easier to interface to hardware, and linkage directives,which make it easier to interface to programs written in other languages.
