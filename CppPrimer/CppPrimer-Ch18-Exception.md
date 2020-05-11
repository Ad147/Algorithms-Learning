CppPrimer-Ch18-Exception.md

C++ Primer Notes
================================================================================

Ad147  
<ar><r>

Init: 18Nov06

Chapter 18 Tools for Large Programs
--------------------------------------------------------------------------------

- [Chapter 18 Tools for Large Programs](#chapter-18-tools-for-large-programs)
  - [18.1 Exception Handling](#181-exception-handling)
    - [18.1.1 Throwing an Exception](#1811-throwing-an-exception)
    - [18.1.2 Catching an Exception](#1812-catching-an-exception)
    - [18.1.3 Function `try` Blocks and Constructors](#1813-function-try-blocks-and-constructors)
    - [18.1.4 The `noexcept` Exception Specification](#1814-the-noexcept-exception-specification)
    - [18.1.5 Exception Class Hierachies](#1815-exception-class-hierachies)
  - [18.2 Namespace](#182-namespace)
    - [18.2.1 Namespace Definitions](#1821-namespace-definitions)
    - [18.2.2 Using Namespace Members](#1822-using-namespace-members)
    - [18.2.3 Classes, Namespaces, and Scope](#1823-classes-namespaces-and-scope)
    - [18.2.4 Overloading and Namespace](#1824-overloading-and-namespace)
  - [18.3 Multiple and Virtual Inheritance](#183-multiple-and-virtual-inheritance)
    - [18.3.1 Multiple Inheritance](#1831-multiple-inheritance)
    - [18.3.2 Conversions and Multiple Base Classes](#1832-conversions-and-multiple-base-classes)
    - [18.3.3 Class Scope under Multiple Inheritance](#1833-class-scope-under-multiple-inheritance)
    - [18.3.4 Virtual Inheritance](#1834-virtual-inheritance)
    - [18.3.5 Constructors and Virtual Inheritance](#1835-constructors-and-virtual-inheritance)
  - [Chapter Summary](#chapter-summary)

*Large-scale programming* places greater demands on programming languages than do the needs of systems that can be developed by small teams of programmers.  
Among the needs that distinguish large-scale applications are

- The ability to handle errors across independently developed subsystems
- The ability to use libraries developed more or less independently
- The ability to model more complicated application concepts

This chapter looks at three features in C++ that are aimed at these needs: exceptionhandling, namespaces, and multiple inheritance.

--------------------------------------------------------------------------------

### 18.1 Exception Handling

#### 18.1.1 Throwing an Exception

##### 1) Stack Unwinding

##### 2) Objects Are Automatically Destroyed during Stack Unwinding

##### 3) Destructors and Exceptions

##### 4) The Exception Object

#### 18.1.2 Catching an Exception

##### 1) Finding a Matching Handler

##### 2) Rethrow

##### 3) The Catch-All Handler

#### 18.1.3 Function `try` Blocks and Constructors

#### 18.1.4 The `noexcept` Exception Specification

##### 1) Violating the Exception Specification

##### 2) Arguments to the `noexcept` Specification

##### 3) The `noexcept` Operator

##### 4) Exception Specifications and Pointers, Virtuals, and Copy Control

#### 18.1.5 Exception Class Hierachies

##### 1) Exception Classes for a Bookstore Application

##### 2) Using Our Own Exception Types

--------------------------------------------------------------------------------

### 18.2 Namespace

#### 18.2.1 Namespace Definitions

##### 1) Each Namespace Is a Scope

##### 2) Namespaces Can Be Discontiguous

##### 3) Defining the Primer Namespace

##### 4) Defining Namespace Members

##### 5) Template Specializations

##### 6) The Global Namespace

##### 7) Nested Namespaces

##### 8) Inline Namespaces

##### 9) Unnamed Namespaces

#### 18.2.2 Using Namespace Members

##### 1) Namespace Aliases

##### 2) `using` Declarations: A Recap

##### 3) `using` Directives

##### 4) `using` Directives and Scope

##### 5) `using` Directives Example

##### 6) Headers and `using` Declarations or Directives

#### 18.2.3 Classes, Namespaces, and Scope

##### 1) Argument-Dependent Lookup and Parameters of Class Type

##### 2) Lookup and `std::move` and `std::forward`

##### 3) Friend Declarations and Argument-Dependent Lookup

#### 18.2.4 Overloading and Namespace

##### 1) Argument-Dependent Lookup and Overloading

##### 2) Overloading and `using` Declarations

##### 3) Overloading and `using` Directives

##### 4) Overloading across Multiple `using` Directives

--------------------------------------------------------------------------------

### 18.3 Multiple and Virtual Inheritance

#### 18.3.1 Multiple Inheritance

##### 1) Multiply Derived Classes Inherit State from Each Base Class

##### 2) Derived Constructors Initialize All Base Classes

##### 3) Inherited Constructors and Multiple Inheritance

##### 4) Destructors and Multiple Inheritance

##### 5) Copy and Move Operations for Multiply Derived Classes

#### 18.3.2 Conversions and Multiple Base Classes

##### 1) Lookup Based on Type of Pointer or Reference

#### 18.3.3 Class Scope under Multiple Inheritance

#### 18.3.4 Virtual Inheritance

##### 1) A Different `Panda` Class

##### 2) Using a Virtual Base Class

##### 3) Normal Conversions to Base Are Supported

##### 4) Visibility of Virtual Base-Class Members

#### 18.3.5 Constructors and Virtual Inheritance

##### 1) How a Virtually Inherited Object Is Constructed

##### 2) Constructor and Destructor Order

--------------------------------------------------------------------------------

### Chapter Summary

C++ is used to solve a wide range of problems—from those solvable in a few hours’ time to those that take years of development by large teams.
Some features in C++ are most applicable in the context of large-scale problems: exception handling, namespaces, and multiple or virtual inheritance.

Exception handling lets us separate the error-detection part of the program from the error-handling part.
When an exception is thrown, the current executing function is suspended and a search is started to find the nearest matching `catch` clause.
Local variables defined inside functions that are exited while searching for a `catch` clause are destroyed as part of handling the exception.

Namespaces are a mechanism for managing large, complicated applications built from code produced by independent suppliers.
A namespace is a scope in which objects, types, functions, templates, and other namespaces may be defined.
The standard library is defined inside the namespace named `std`.

Conceptually, multiple inheritance is a simple notion: A derived class may inherit from more than one direct base class.
The derived object consists of the derived part and a base part contributed by each of its base classes.
Although conceptually simple, the details can be more complicated.
In particular, inheriting from multiple base classes introduces new possibilities for name collisions and resulting ambiguous references to names from the base part of an object.

When a class inherits directly from more than one base class, it is possible that those classes may themselves share another base class.
In such cases, the intermediate classes can opt to make their inheritance virtual, which states a willingness to share their virtual base class with other classes in the hierarchy that inherit virtually from that same base class.
In this way there is only one copy of the shared virtual base in a subsequently derived class.

--------------------------------------------------------------------------------

EOF
