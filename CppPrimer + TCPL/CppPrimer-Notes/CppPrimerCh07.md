CppPrimerCh07.md

C++ Primer Notes
================================================================================

Ad  
init: May01.2018

Chapter7 Classes
--------------------------------------------------------------------------------

### 7.1 Defining Abstract Data Types

#### 7.1.1 Designing the Sales_data Class

#### 7.1.2 Defining the Rivised Sales_data Class

Member functions access the class object through a extra, implicit parameter `this`
 - `this` is initialized with the adress of the class object
 - `return *this;` : when need returning the class object

Member functions can refer directly to the member of the class object, no need for `this ->`

##### Introduing `const` member functions

`int funcion() const {}` : the `const` is to modify the type of the implicit `this` pointer  
if no changes are done to member object, define a const member function

##### Define a member function ouside the class (using name: `Class::function`)

#### 7.1.3 Defining nonmember class-related functions

Some auxiliary functions conceptually part of the interface of the class, they are not part of the class itself.
 - the functions always declared in the same header as the class
 - the IO class types cannot be copied, only be referred

#### 7.1.4 Constructors

##### The synthesized default constructor

If no constructors defined explicitly, the compiler will generate a constructor
 - if there is a in-class initializer, the constructor uses it to init
 - otherwise, default init

For the variables in class without init can be undefined, and some classes that hold member classes without default constructors cannot rely on synthesized constructor  
To define constructors is necessary

##### `C++11` `Class() = default;`

##### Constructor Initializer

`Class(T1 para1, T2 para2) : mem1(para1), mem2(para2) {}`

##### Define a constructor outside the class body

`Class::Class(T para) { read(para, *this); }`

#### 7.1.5 Copy, Assignment and Destruction

If no these operations defined, the compiler will synthesize them.

`~Class();`

--------------------------------------------------------------------------------

### 7.2 Access Control and Encapsulation

Access specifiers:
 - `public`
 - `protected`
 - `private` : the private sections encapsulate the implementation

##### Using the `class` or `struct` Keyword

The only difference is the default access level:
 - `class` : private
 - `struct` : public

#### 7.2.1 Friends (another class or function to access nonpublic members)

Making friends by including a declaration for the function preceded by the keyword `friend`
 - the declaration can appear anywhere inside the class body
 - and is not affected by the access control
 - friend declaration only specifies access (need to declare outside if using)

> Encapsulation provides two important advantages:
>  - User code cannot inadvertently corrupt the state of an encapsulated object.
>  - The implementation of an ancapsulated class can change over time without requiring changes in user-level code.

--------------------------------------------------------------------------------

### 7.3 Additional Class Features

#### 7.3.1 Class Member Revisited

##### Defining a Type member

`(public:) typedef originalType newName;` / `(public:) using newName = originalType;`
 - must appear before they are used, so usually at beginning

##### Making Members inline

 - member functions **defined** inside the class is implicitly inline
 - functions defined outside can be declared as inline explicitly, the inline declaration can be inside or outside the class, or both

##### Overloading Member Functions

##### `mutable` Data Members (are nerver const, can be changed by const functions)

##### Initializers for data members of class type

`C++11` The best way to specify this default value is as an in-class initializer:  
`private: std::vector<Screen> screens{Screen(24, 90, ' ')};`

#### 7.3.2 Functions That Return *this

Returned references are lvalues: `myScreen.move(4, 0).set('#');`

##### Returning *this from a const Member Function

> A const member function that returns *this as a reference should have a return type that is a reference to const.  
(const function -> const `this` parameter -> const `*this` objetct -> const return type)

##### Overloading Based on const:

 - define a const and a nonconst versions for a function that returns *this
 - define a `private` member function `do_display` to do the actual work of print
 - then each of the overloaded `display` function will call `do_display`

#### 7.3.3 Class Type

Every class defines a unique type.

`myClass item;` == `class myClass item;`

##### Class declarations: `class Screen;` (forward declaration)

The class is just declared is imcomplete type, which can be used in only limited ways:
 - define pointers or references to the class
 - declare (but not define) functions that use it as a parameter
 - declare vector holds that class type

#### 7.3.4 Friendship Revisited

A class can make friend with:
 - another class: `friend class aClass;`
 - specific member funtions of another class (previously defined):  
   `friend void aClass::clear();`
 - a external function

 - friendship is not transitive.

When making a member function a friend, be careful with the order if definition and declaration:
 1. define `class ClassHoldFriend` which **declares but not** define `friendFunction()`
 2. define `class ClassMakeFriend` including a friend declaration for `friend friendFunction()`
 3. define `friendFunction()` which can now refer to private members

##### Overloaded functions should be declared as friends once each

##### Friend declaration and scope

Even a friend function is defined inside the class, it still need to be declared outside the class.

--------------------------------------------------------------------------------

### 7.4 Class Scope

The fact that a class is a scope explains why we must provide the class name as well as the function name when we define a member name outside the class.
 - Outside the class, the names of the members are hidden.
 - Once the class name is seen, the parameter list and function body is in the scope of the class.
 - thr reutrn type is before the class name, so is should be used with class name

#### 7.4.1 Name Lookup and Class Scope

> Memer functions definitions **(The Body)** are processed after the compiler processes all of the declarations in the class.

##### Type names cannot be redefined if the type name has been used by the class member

##### Normal block-scope name lookup inside member definitions:

 1. look for the declaration of the name inside the member function. (before the use)
 2. look for a declaration inside the class
 3. look for a declaration that is in scope before the member function dedinition.

> Even though the class member is hidden, it is still possible to use that member by qualifying the member's name with the **name of its class (scope)** or by using the **this** pointer explicitly.

--------------------------------------------------------------------------------

### 7.5 Constructors Revisited

#### 7.5.1 Constructor Initializer List

If we do not explicitly initialize a member in the constructor initializer list, that member is default initialized **before the constructor body starts executing**.

const and reference must be initialized, and in class must using initializer list,  
the constructor body is actully assignments.

##### Order of member initialization: follow the order they appear in the class

##### Default arguments and constructors

`ClassOne(type par = val) : mem(par) { }` : to combine the default constructor and ordinary one

that is:
> A constructor that supplies default arguments for all its parameters also defines the default constructor.

#### 7.5.2 Delegating Constructors

`C++11` A delegating constructor can use another constructor from its own class to perform the initialization.

```cpp
class ClassOne
{
public:
    ClassOne(type par1, type par2) : mem1(par1), mem2(par2) {}
    ClassOne() : ClassOne(0, 0) {}
    ClassOne(type par1) : ClassOne(par1, 0) {}
    ClassOne(istream &is) : ClassOne() { input(is); }
}
```

 - the function body of the delegated-to constructor (the first one) is executed before the delegating constructor function body

#### 7.5.3 The Role of the Default Constructor

> Inpractice, it is almost always right to provide a default constructor if other constructors are being defined.

#### 7.5.4 Implicit Class-Type Conversions

> A constructor that can be called **with a single argument** defines an implicit conversion from the constructor's parameter type to the class type.

##### Only one class-type conversion is allowed (only once, not twice)

##### Suppressing implicit conversions defined by constructors:

 - `explicit`
 - the `explicit` declaration is only inside the class
 - `explicit` constructors can be used only for direct initialization (not copy init with `=`)
 - explicitly using constructors for conversions: like `a = int(b);`

##### Library classes with explicit constructors

 - `string` constructor that takes a single parameter of type `const char*` is not explicit
 - `vector` constructor that takes a size is explicit

#### 7.5.5 Aggregate Classes

An aggregate class gives users direct access to its members and has special initialization syntax:
 - all of the data members are public
 - does not define any constructors
 - has no in-class initializers
 - has no base classes or virtual functions

`struct Data { int i; string s; };` initialized as `Data val{ 0, "A" };`

#### 7.5.6 Literal Classes

##### constexpr constructors

--------------------------------------------------------------------------------

### 7.6 `static` Class Members

members **associated with the class**, rather than with individual objects of the class type:
 - no need for every object to store the member
 - if the value of the member changes, each object can use the new value

##### Declaring `static` members

 - static member functions are not bound to any object
 - static functions do not have a `this` (so that can not be declared as `const`)

##### Using `static` member:

 - directly through the scope operator: `ClassOne::staticFunction();`
 - using object to access: `obj.staticFunction();`
 - pointer and reference: `ptrObj->staticFunction();`

##### Defining `static` members (if outside, no `static` repeated)

 - `static` members are not defined by the constructors
 - moreover, may not initialize a `static` member outside the class body
 - initialized only once
 - like global objects

define and initialize:  
`type Class::staticMember = initStaticMember();`  
(static members are private)

> The best way to ensure that the object is defined exactly once is to put the definition of static data members in the same file that contains the definitions of the class noninline member functions.

###### In-class initialization of static data members

 - in-class init can be applied to static members have `const` integral type
 - and must used to init `constexpr` of literal type

> Even if a const static data member is initialized in the class body, that member ordinarily should be defined outside the class definition. (with no initializer)

##### `static` members can be used in ways ordinary members cannot

A static member can have imcomplete type (can have the type of its class)
A nonstatic member is restricted to being declared as a pointer or a reference to its class, but cannot be a object

 - a static member can be used as a default argument in the class

--------------------------------------------------------------------------------

EOF
