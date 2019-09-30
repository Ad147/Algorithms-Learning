CppPrimer-Ch15-OOP.md

C++ Primer Notes
================================================================================

Ad147  
<ar><r>

Init: 18Nov04

Chapter 15 Object-Oriented Programming
--------------------------------------------------------------------------------

- [Chapter 15 Object-Oriented Programming](#chapter-15-object-oriented-programming)
    - [15.1 OOP: An Overview](#151-oop-an-overview)
    - [15.2 Defining Base and Derived Classes](#152-defining-base-and-derived-classes)
        - [15.2.1 Defining a Base Class](#1521-defining-a-base-class)
        - [15.2.2 Defining a Derived Class](#1522-defining-a-derived-class)
        - [15.2.3. Conversions and Inheritance](#1523-conversions-and-inheritance)
    - [15.3 Virtual Functions](#153-virtual-functions)
    - [15.4 Abstract Base Classes](#154-abstract-base-classes)
    - [15.5 Access Control and Inheritance](#155-access-control-and-inheritance)
    - [15.6 Class Scope under Inheritance](#156-class-scope-under-inheritance)
    - [15.7 Constructors and Copy Control](#157-constructors-and-copy-control)
        - [15.7.1 Virtual Destructors](#1571-virtual-destructors)
        - [15.7.2 Synthesized Copy Control and Inheritance](#1572-synthesized-copy-control-and-inheritance)
        - [15.7.3 Derived-Class Copy-Control Members](#1573-derived-class-copy-control-members)
        - [15.7.4 Inherited Constructors](#1574-inherited-constructors)
    - [15.8 Containers and Inheritance](#158-containers-and-inheritance)
        - [15.8.1 Writing a `Basket` Class](#1581-writing-a-basket-class)
    - [15.9 Text Queries Revisited (TODO)](#159-text-queries-revisited-todo)
    - [Chapter Summary](#chapter-summary)

--------------------------------------------------------------------------------

Object-oriented programming is based on three fundamental concepts:

- data abstraction
- inheritance
- dynamic binding

Inheritance and dynamic binding affect how we write our programs in two ways:

- they make it easier to define new classes that are similar, but not identical, to other classes
- they make it easier for us to write programs that can ignore the details of how those similar types differ

### 15.1 OOP: An Overview

- Using data abstraction, we can define classes that separate interface from implementation.
- Through inheritance, we can define classes that model the relationships among similar types.
- Through dynamic binding, we can use objects of these types while ignoring the details of how they differ.

##### 1) Inheritance

Classes related by inheritance form a hierarchy.  
Typically there is a **base class** at the root of the hierarchy, from which the **derived classes** inherit, directly or indirectly.  
The base class defines those members that are common to the types in the hierarchy.  
Each derived class defines those members that are specific to the derived class itself.

We’ll define a class named `Quote`, which will be the base class of our hierarchy.  
A `Quote` object will represent undiscounted books.  
From `Quote` we will inherit `Bulk_quote`, to represent books that can be sold with a quantity discount.

These classes will have the following two member functions:
- `isbn()`, which will return the ISBN. This operation does not depend on the specifics of the inherited class(es); it will be defined only in class `Quote`
- `net_price(size_t)`, which will return the price for purchasing a specified number of copies of a book. This operation is type specific; both `Quote` and `Bulk_quote` will define their own version of this function

In C++, a base class distinguishes functions that are type dependent from those that it expects its derived classes to inherit without change.  
The base class defines as `virtual` those functions it expects its derived classes to define for themselves.

```cs
class Quote
{
public:
    std::string isbn() const;
    virtual double net_price(std::size_t n) const;
};
```

A derived class must specify the class(es) from which it intends to inherit in a **class derivation list** (a colon followed by a comma-separated list of base classes each of which may have an optional access specifier):

```cs
class Bulk_quote : public Quote // Bulk_quote inherits from Quote
{
public:
    double net_price(std::size_t) const override;
};
```

Because Bulk_quote uses `public` in its derivation list, we can use objects of type Bulk_quote *as if* they were Quote objects.

A derived class must include in its own class body a declaration of all the virtual functions it intends to define for itself.  
A derived class may include the `virtual` keyword on these functions but is not required to do so.  
the new standard lets a derived class explicitly note that it intends a member function to **override** a virtual that it inherits. It does so by specifying `override` after its parameter list.

##### 2) Dynamic Binding

Through dynamic binding, we can use the same code to process objects of either type `Quote` or `Bulk_quote` interchangeably.

```cs
// calculate and print the price for the given number of copies, applying any discounts
double print_total(ostream &os, const Quote &item, size_t n)
{
    // depending on the type of the object bound to the item parameter
    // calls either Quote::net_price or Bulk_quote::net_price
    double ret = item.net_price(n);
    os << "ISBN: " << item.isbn() // calls Quote::isbn
       << " # sold: " << n << " total due: " << ret << endl;
    return ret;
}
```

- because the item parameter is a reference to Quote, we can call this function on either a Quote object or a Bulk_quote object
- because net_price is a virtual function, and because print_total calls net_price through a reference, the version of net_price that is run will depend on the type of the object that we pass to print_total

```cs
// basic has type Quote; bulk has type Bulk_quote
print_total(cout, basic, 20); //  calls Quote version of net_price
print_total(cout, bulk, 20);  //  calls Bulk_quote version of net_price
```

Because the decision as to which version to run depends on the type of the argument, that decision can’t be made until run time. Therefore, dynamic binding is sometimes known as **run-time binding**.

> ##### Note
> In C++, dynamic binding happens when a virtual function is called through a reference (or a pointer) to a base class.

--------------------------------------------------------------------------------

### 15.2 Defining Base and Derived Classes

#### 15.2.1 Defining a Base Class

```cs
class Quote
{
public:
    Quote() = default;
    Quote(const std::string &book, double sales_price)
          : bookNo(book), price(sales_price) {}
    std::string isbn() const { return bookNo; }
    // returns the total sales price for the specified number of items
    // derived classes will override and apply different discount algorithms
    virtual double net_price(std::size_t n) const{ return n * price; }
    virtual ~Quote() = default; // dynamic binding for the destructor

private:
    std::string bookNo; // ISBN number of this item

protected:
    double price = 0.0; // normal, undiscounted price
};
```

For now it is worth noting that classes used as the root of an inheritance hierarchy almost always define a *virtual destructor*.

> ##### Note
> Base classes ordinarily should define a virtual destructor. Virtual destructors are needed even if they do no work.

##### 1) Member Functions and Inheritance

In C++, a base class must distinguish

- the functions it expects its derived classes to *override*
- those that it expects its derived classes to *inherit without change*

The base class defines as **virtual** those functions it expects its derived classes to override.  
When we call a virtual function **through a pointer or reference**, the call will be dynamically bound.  
Depending on the type of the object to which the reference orpointer is bound, the version in the base class or in one of its derived classes will be executed.

A base class specifies that a member function should be dynamically bound by preceding its declaration with the keyword `virtual`.  
Any non`static` member function, other than a constructor, may be `virtual`.  
The `virtual` keyword appears only on the declaration inside the class and may not be used on a function definition that appears outside the class body.  
A function that is declared as `virtual` in the base class is implicitly `virtual` in the derived classes as well.

Member functions that are not declared as virtual are resolved at compile time, not run time.

##### 2) Access Control and Inheritance

Sometimes a base class has members that it wants to let its derived classes use while still prohibiting access to those same members by other users.  
We specify such members after a `protected` access specifier.

#### 15.2.2 Defining a Derived Class

A derived class must specify from which class(es) it inherits in its class derivation list:  
`class DerivedClass : specifier BaseClass...`

A derived class must declare each inherited member function it intends to override.

Therefore, our `Bulk_quote` class must include a `net_price` member:

```cs
class Bulk_quote : public Quote // Bulk_quote inherits from Quote
{
    Bulk_quote() = default;
    Bulk_quote(const std::string&, double, std::size_t, double);
    // overrides the base version in order to implement the bulk purchase  discount policy
    double net_price(std::size_t) const override;

private:
    std::size_t min_qty = 0; // minimum purchase for the discount  to apply
    double discount = 0.0; // fractional discount to apply
};
```

Our `Bulk_quote` class inherits the `isbn` function and the `bookNo` and `price` data members of its `Quote` base class.  

About the access specifier, for now, what’s useful to know is that the access specifier determines whether users of a derived class are allowed to know that the derived class inherits from its base class.

When the derivation is `public`, the `public` members of the base class become part of the interface of the derived class as well.  
In addition, we can bind an object of a publicly derived type to a pointer or reference to the base type.  

Most classes inherit directly from only one base class. This form of inheritance, known as “single inheritance,” forms the topic of this chapter.

##### 1) Virtual Functions in the Derived Class

Derived classes frequently, *but not always*, override the virtual functions that they inherit.  
If a derived class does not override a virtual from its base, then, like any other member, the derived class inherits the version defined in its base class.

A derived class may include the `virtual` keyword on the functions it overrides, butit is not required to do so.  
The new standard lets a derived class explicitly note that it intends a member function to override a virtual that it inherits by specifying `override` after the parameter list, or after the `const` or reference qualifier(s) if the member is a const or reference function.

##### 2) Derived-Class Objects and the Derived-to-Base Conversion

Although the standard does not specify how derived objects are laid out in memory,we can think of a `Bulk_quote` object as consisting of two parts as represented in Figure.

###### Figure Conceptual Structure of a Bulk_quote Object

```figure
                                  Bulk_quote object
                                    +----------+
members inherited from Quote -----> | BookNo   |
                                    | price    |
                                    +----------+
members defined by Bulk_quote ----> | min_qty  |
                                    | discount |
                                    +----------+
```

The base and derived parts of an object are **not guaranteed** to be stored contiguously.  
Figure 15.1 is a conceptual, not physical, representation of how classes work.

Because a derived object contains subparts corresponding to its base class(es), we can use an object of a derived type as if it were an object of its base type(s).  
In particular, we can bind a base-class reference or pointer to the base-class part of aderived object.

This conversion is often referred to as the **derived-to-base** conversion.  
As with any other conversion, the compiler will apply the derived-to-base conversion implicitly.  
The fact that the derived-to-base conversion is implicit means that we can use an object of derived type or a reference to a derived type when a reference to the basetype is required.  
Similarly, we can use a pointer to a derived type where a pointer tothe base type is required.

> ##### Note
> The fact that a derived object **contains subobjects** for its base classes is key to how inheritance works.

##### 3) Derived-Class Constructors

Although a derived object contains members that it inherits from its base, it **cannot directly initialize** those members.  
Like any other code that creates an object of thebase-class type, a derived class must use a base-class constructor to initialize its base-class part.

> ##### Note
> Each class controls how its members are initialized.

Analogously to how we initialize a member, a derived-class constructor uses its constructor initializer list to pass arguments to a base-class constructor.

> ##### Note
> The base class is initialized first, and then the members of the derived classare initialized in the order in which they are declared in the class.

##### 4) Using Members of the Base Class from the Derived Class

We’ll have more to say about scope in §15.6 (p. 617), but for now it’s worth knowing that the scope of a derived class is **nested inside** the scope of its base class.  
As a result, there is no distinction between how a member of the derived class uses members defined in its own class (e.g., min_qty and discount) and how it uses members defined in its base (e.g., price).

> ##### Key Concept: Respecting the Base-Class Interface
> It is essential to understand that each class defines its own interface.  
> Interactions with an object of a class-type should use the interface of that class, even if that object is the base-class part of a derived object.  
> As a result, derived-class constructors may not directly initialize the members of its base class.  
> The constructor body of a derived constructor can assign values to its public or protected base-class members.  
> Although it can assign to those members, it generally should not do so.  
> Like any other user of the base class, a derived class should respect the interface of its baseclass by using a constructor to initialize its inherited members.

##### 5) Inheritance and `static` Members

If a base class defines a static member, there is **only one** such member defined for the entire hierarchy.  
Regardless of the number of classes derived from a base class, there exists a single instance of each static member.

##### 6) Declarations of Derived Classes

A derived class is declared like any other class.  
The declarationcontains the class name but does not include its derivation list.

##### 7) Classes Used as a Base Class

A class must be defined, not just declared, before we can use it as a base class.

The reason for this restriction should be easy to see:  
Each derived class contains, andmay use, the members it inherits from its base class.  
To use those members, the derived class must know what they are.  
One implication of this rule is that it is impossible to derive a class from itself.

A base class can itself be a derived class:  
`class Base { /* ... */ };`  
`class D1: public Base { /* ... */ };`  
`class D2: public D1 { /* ... */ };`

In this hierarchy, Base is a direct base to D1 and an indirect base to D2.  
A direct base class is named in the derivation list.  
An indirect base is one that a derived class inherits through its direct base class.

Each class inherits all the members of its direct base class.  
The most derived class inherits the members of its direct base.  
The members in the direct base include those it inherits from its base class, and so on up the inheritance chain.  
Effectively, the most derived object contains a subobject for its direct base and for each of its indirectbases.

##### 8) Preventing Inheritance

`C++11` We can prevent a class from being used as abase by following the class name with `final`.

#### 15.2.3. Conversions and Inheritance

> ##### Warning
> Understanding conversions between base and derived classes is essential to understanding how object-oriented programming works in C++.

We can bind a pointer or reference to a base-class type to an object of a type derived from that base class.

The fact that we can bind a reference (or pointer) to a base-class type to a derived object has a crucially important implication:  
When we use a reference (or pointer) to a base-class type, we don’t know the actual type of the object to which the pointer or reference is bound.  
That object can be an object of the base class or it can be an object of a derived class.

> ##### Note
> Like built-in pointers, the smart pointer classes support the derived-to-base conversion—we can store a pointer to a derived object in a smart pointer to the base type.

##### 1) Static Type and Dynamic Type

When we use types related by inheritance, we often need to distinguish between the static type of a variable or other expression and the dynamic type of the objectthat expression represents.

- **static type**: always known at compile time—it is the type with which a variable is declared or that an expression yields
- **dynamic type**: the type of the object in memory that the variable or expression represents  
   The dynamic type may not be known until run time

For example, when `print_total` calls `net_price`:  
`double ret = item.net_price(n);`

we know that the static type of item is `Quote&`.  
The dynamic type depends on the type of the argument to which item is bound.  
That type cannot be known until a call is executed at run time.  
If we pass a Bulk_quote object to print_total, then the static type of item will differ from its dynamic type.  
As we’ve seen, the static type of item is Quote&, but in this case the dynamic type is Bulk_quote.

The dynamic type of an expression that is neither a reference nor a pointer isalways the same as that expression’s static type.  
For example, a variable of typeQuote is always a Quote object; there is nothing we can do that will change the typeof the object to which that variable corresponds.

> ##### Note
> It is crucial to understand that the static type of a pointer or reference to a base class may differ from its dynamic type.

##### 2) There Is No Implicit Conversion from Base to Derived ...

The conversion from derived to base exists because every derived object contains abase-class part to which a pointer or reference of the base-class type can be bound.  
There is no similar guarantee for base-class objects.  
A base-class object can exist either as an independent object or as part of a derived object.  
A base object that is not part of a derived object has only the members defined by the base class; it doesn’t have the members defined by the derived class.

Because a base object might or might not be part of a derived object, there is no automatic conversion from the base class to its derived class(s).

What is sometimes a bit surprising is that we cannot convert from base to derived even when a base pointer or reference is bound to a derived object:  

```cs
Bulk_quote bulk;
Quote *itemP = &bulk;       // ok: dynamic type is Bulk_quote
Bulk_quote *bulkP = itemP;  // error: can't convert base to derived
```

The compiler has no way to know (at compile time) that a specific conversion will besafe at run time.  
The compiler looks only at the static types of the pointer orreference to determine whether a conversion is legal.  
If the base class has one or more virtual functions, we can use a `dynamic_cast` (which we’ll cover in §19.2.1 (p.825)) to request a conversion that is checked at run time.  
Alternatively, in those cases when we know that the conversion from base to derived is safe, we can use a `static_cast` to override the compiler.

##### 3) ...and No Conversion between Objects

The automatic derived-to-base conversion applies only for conversions to a referenceor pointer type.  
There is no such conversion from a derived-class type to the base-class type.  
Nevertheless, it is often possible to convert an object of a derived class to its base-class type.  
However, such conversions may not behave as we might want.

Remember that when we initialize or assign an object of a class type, we are actually calling a function.  
When we initialize, we’re calling a constructor;  
when we assign, we’re calling an assignment operator.  
These members normally have a parameter that is a reference to the const version of the class type.

Because these members take references, the derived-to-base conversion lets us pass a derived object to a base-class copy/move operation.  
These operations are not virtual.  
When we pass a derived object to a base-class constructor, the constructor that is run is defined in the base class.  
That constructor knows only about the members of the base class itself.  
Similarly, if we assign a derived object to a base object, the assignment operator that is run is the one defined in the base class.  
That operator also knows only about the members of the base class itself.

For example, our bookstore classes use the synthesized versions of copy and assignment.  
We’ll have more to say about copycontrol and inheritance in §15.7.2 (p. 623), but for now what’s useful to know is that the synthesized versions memberwise copy or assign the data members of the class the same way as for any other class:

```cs
Bulk_quote bulk;    // object of derived type
Quote item(bulk);   // uses the Quote::Quote(const Quote&) constructor
item = bulk;        // calls Quote::operator=(const Quote&)
```

When item is constructed, the Quote copy constructor is run.  
That constructor knows only about the bookNo and price members.  
It copies those members from the Quote part of bulk and ignores the members that are part of the Bulk_quote portion of bulk.  
Similarly for the assignment of bulk to item;  
only the Quote partof bulk is assigned to item.

Because the Bulk_quote part is ignored, we say that the Bulk_quote portion ofbulk is **sliced down**.

> ##### Warning
> When we initialize or assign an object of a base type from an object of a derived type, only the base-class part of the derived object is copied, moved, or assigned. The derived part of the object is ignored.

> ##### Key Concept: Conversions among Types Related by Inheritance
> 
> There are three things that are important to understand about conversions among classes related by inheritance:
> 
> - The conversion from derived to base applies only to pointer or reference types.
> - There is no implicit conversion from the base-class type to the derivedtype.
> - Like any member, the derived-to-base conversion may be inaccessible due to access controls. We’ll cover accessibility in §15.5 (p. 613).
> 
> Although the automatic conversion applies only to pointers and references, most classes in an inheritance hierarchy (implicitly or explicitly) define the copy-control members (Chapter 13).  
> As a result, we can often copy, move, or assign an object of derived type to a base-type object.  
> However, copying, moving, or assigning a derived-type object to a base-type object copies, moves, or assigns *only* the members in the base-class part of the object.

--------------------------------------------------------------------------------

### 15.3 Virtual Functions

As we’ve seen, in C++ dynamic binding happens when a **virtual member function** is called **through a reference or a pointer** to a base-class type.  
Becausewe don’t know which version of a function is called until run time, virtual functions must always be defined.  
Ordinarily, if we do not use a function, we don’t need tosupply a definition for that function.  
However, we must define every virtual function, regardless of whether it is used, because the compiler has no way to determine whether a virtual function is used.  

##### 1) Calls to Virtual Functions *May Be* Resolved at Run Time

When a virtual function is called through a reference or pointer, the compiler generates code to *decide at run time* which function to call.

It is crucial to understand that dynamic binding happens only when a virtual function is called through a pointer or a reference.

> ##### Key Concept: Polymorphism in C++
>
> The key idea behind OOP is polymorphism.  
> Polymorphism is derived from a Greek word meaning “many forms.”  
> We speak of types related by inheritance as polymorphic types, because we can use the “many forms” of these types while ignoring the differences among them.  
> The fact that the static and dynamic types of references and pointers can differ is the cornerstone of how C++ supports polymorphism.
>
> When we call a function defined in a base class through a reference or pointer to the base class, we do not know the type of the object on which that member is executed.  
> The object can be a base-class object or an object of a derived class.  
> If the function is virtual, then the decision as to which function to run is delayed until run time.  
> The version of the virtual function that is run is the one defined by the type of the object to which the reference is bound or to which the pointer points.
>
> On the other hand, calls to nonvirtual functions are bound at compile time.  
> Similarly, calls to any function (virtual or not) on an object are also bound at compile time.  
> The type of an object is fixed and unvarying—there is nothing we can do to make the dynamic type of an object differ from its static type.  
> Therefore, calls made on an object are bound at compile time to the version defined by the type of the object.

> ##### Note
> Virtuals are resolved at run time only if the call is made through a reference or pointer.  
> Only in these cases is it possible for an object’s dynamic type to differ from its static type.

##### 2) Virtual Functions in a Derived Class

When a derived class overrides a virtual function, it may, but is not required to, repeatthe `virtual` keyword.  
Once a function is declared as virtual, it remains virtualin all the derived classes.

A derived-class function that overrides an inherited virtual function must have exactly the same parameter type(s) as the base-class function that it overrides.

With one exception, the return type of a virtual in the derived class also must match the return type of the function from the base class.  
The exception applies to virtuals that return a reference (or pointer) to types that are themselves related by inheritance.  
That is, if D is derived from B, then a base class virtual can return a B* and the version in the derived can return a D*.  
However, such return types require that the derived-to-base conversion from D to B is accessible.  

> ##### Note
> A function that is virtual in a base class is implicitly virtual in its derived classes.  
> When a derived class overrides a virtual, the parameters in the base and derived classes must match exactly.

##### 3) The `final` and `override` Specifiers

It is legal for a derived class to define a function with the same name as a virtual in its base class but with a different parameter list.  
The compiler considers such a function to be independent from the base-class function.  
In such cases, the derived version does not override the version in the base class.  
In practice, such declarations often are a mistake—the class author intended to override a virtual from the base class but made a mistake in specifying the parameter list.

`C++11` Finding such bugs can be surprisingly hard.  
Under the new standard we can specify `override` on a virtual function in a derived class.  
Doing so makes our intention clear and (more importantly) enlists the compiler in finding such problems for us.

```cs
struct B
{
    virtual void f1(int) const;
    virtual void f2();
    void f3();
};

struct D1 : B
{
    void f1(int) const override;    // ok:f1 matches f1 in the base
    void f2(int) override;          // error: B has no f2(int) function
    void f3() override;             // error: f3 not virtual
    void f4() override;             // error: B doesn't have a function named f4
};
```

We can also designate a function as `final`. Any attempt to override a function that has been defined as final will be flagged as an error.

`final` and `override` specifiers appear after the parameter list (including any const or reference qualifiers) and after a trailing return.

##### 4) Virtual Functions and Default Arguments

If a call uses a default argument, the value that is used is the one defined by the static type through which the function is called.

That is, when a call is made through a reference or pointer to base, the default argument(s) will be those defined in the base class.  
The base-class arguments will be used even when the derived version of the function is run.

> ##### Best Practices
> Virtual functions that have default arguments should use the same argument values in the base and derived classes.

##### 5) Circumventing the Virtual Mechanism

We can force the call to use a particular version of that virtual by using the scope operator.  
`//  calls the version from the base class regardless of the dynamic type of baseP`  
`double undiscounted = baseP->Quote::net_price(42);`

This call will be resolved at compile time.

> ##### Note
> Ordinarily, only code inside member functions (or friends) should need to use the scope operator to circumvent the virtual mechanism.

Why might we wish to circumvent the virtual mechanism?  
The most common reason is when a derived-class virtual function calls the version from the base class.  
In such cases, the base-class version might do work common to all types in the hierarchy.  
The versions defined in the derived classes would do whatever additional work is particularto their own type.

> ##### Warning
> If a derived virtual function that intended to call its base-class version omits the scope operator, the call will be resolved at run time as a call to the derived version itself, resulting in an infinite recursion.

--------------------------------------------------------------------------------

### 15.4 Abstract Base Classes

##### 1) Pure Virtual Functions

Unlike ordinary virtuals, a pure virtual function does not have to be defined.

We specify that a virtual function is a pure virtual by writing `= 0` in place of a function body.  
The = 0 may appear only on the declaration of a virtual function in the class body.

```cs
//class to hold the discount rate and quantity
// derived classes will implement pricing strategies using these data
class Disc_quote : public Quote
{
public:
    Disc_quote() = default;
    Disc_quote(const std::string& book, double price, std::size_t qty, double disc)
              :Quote(book, price), quantity(qty), discount(disc) {}
    double net_price(std::size_t) const = 0;

protected:
    std::size_t quantity = 0;   // purchase size for the discount to apply
    double discount = 0.0;      // fractional discount to apply
};
```

Although we cannot define objects of this type directly, constructors in classes derived from Disc_quote will use the Disc_quote constructors to construct the Disc_quote part of their objects.  
The constructor that has four parameters passes its first two to the Quote constructor and directly initializes its own members, discount and quantity.  
The default constructordefault initializes those members.

It is worth noting that we can provide a definition for a pure virtual.  
However, thefunction body must be defined outside the class.  
That is, we cannot provide a function body inside the class for a function that is = 0.

##### 2) Classes with Pure Virtuals Are Abstract Base Classes

A class containing (or inheriting without overridding) a pure virtual function is an **abstract base class**.  
An abstract base class defines an interface for subsequentclasses to override.

> ##### Note
> We may not create objects of a type that is an abstract base class.

##### 3) A Derived Class Constructor Initializes Its Direct Base Class Only

Now we can reimplement Bulk_quote to inherit from Disc_quote rather than inheriting directly from Quote:

```cs
// the discount kicks in when a specified number of copies of the same book are sold
// the discount is expressed as a fraction to use to reduce the normal price
class Bulk_quote : public Disc_quote
{
public:
    Bulk_quote() = default;
    Bulk_quote(const std::string& book, double price, std::size_t qty, double disc
              : Disc_quote(book, price, qty, disc) {}
    // overrides the base version to implement the bulk purchase discount policy
    double net_price(std::size_t) const override;
};
```

This version of Bulk_quote has a direct base class, Disc_quote, and an indirectbase class, Quote.  
Each Bulk_quote object has three subobjects:

- an (empty)Bulk_quote part
- a Disc_quote subobject
- a Quote subobject

As we’ve seen, each class controls the initialization of objects of its type.  
Therefore, even though Bulk_quote has no data members of its own, it provides the same four-argument constructor as in our original class.  
Our new constructor passes its arguments to the Disc_quote constructor.  
That constructor in turn runs the Quote constructor.  
The Quote constructor initializes the bookNo and price members of bulk.  
When the Quote constructor ends, the Disc_quote constructor runs andinitializes the quantity and discount members.  
At this point, the Bulk_quote constructor resumes. That constructor has no further initializations or any other work to do.

> ##### Key Concept: Refactoring
> Adding Disc_quote to the Quote hierarchy is an example of **refactoring**.  
> Refactoring involves redesigning a class hierarchy to move operations and/or data from one class to another.  
> Refactoring is common in object-oriented applications.
>
> It is noteworthy that even though we changed the inheritance hierarchy, code that uses Bulk_quote or Quote would not need to change.  
> However, when classes are refactored (or changed in any other way) we must recompile any code that uses those classes.

--------------------------------------------------------------------------------

### 15.5 Access Control and Inheritance

##### 1) `protected` Members

A class uses protected for those members that it is willing to share with its derived classes but wants to protect from general access.  
The `protected` specifier can be thought of as a blend of private and public:

- Like private, protected members are inaccessible to users of the class
- Like public, protected members are accessible to members and friends of classes derived from this class

In addition, protected has another important property:

- A derived class member or friend may access the protected members of the base class only through a derived object. The derived class has no special access to the protected members of base-class objects.

To understand this last rule, consider the following example:

```cs
class Base
{
protected:
    int prot_mem;   // protectedmember
};

class Sneaky : public Base
{
    friend void clobber(Sneaky&);   // can access Sneaky::prot_mem
    friend void clobber(Base&);     // can't access Base::prot_mem
    int j;                          // j is private by default
};
// ok: clobber can access the private and protected members in Sneaky objects
void clobber(Sneaky &s) { s.j = s.prot_mem = 0; }
// error: clobber can't access the protected members in Base
void clobber(Base &b) { b.prot_mem = 0; }
```

##### 2) `public`, `private`, and `protected` Inheritance

Access to a member that a class inherits is controlled by a combination of the access specifier for that member in the base class, and the access specifier in the derivation list of the derived class.  
As an example, consider the following hierarchy:

```cs
class Base
{
public:
    void pub_mem(); // public member
protected:
    int prot_mem;   // protected member
private:
    char priv_mem;  // private member
};

struct Pub_Derv : public Base
{
    // ok: derived classes can access protected members
    int f() { return prot_mem; }
    // error: private members are inaccessible to derived classes
    char g() { return priv_mem; }
};

struct Priv_Derv : private Base
{
    // private derivation doesn't affect access in the derived class
    int f1() const { return prot_mem; }
};
```

The derivation access specifier has no effect on whether members (and friends) of a derived class may access the members of its own direct base class.  
Access to the members of a base class is controlled by the access specifiers in the base class itself.  
Both Pub_Derv and Priv_Derv may access the protected member prot_mem.  
Neither may access the private member priv_mem.

The purpose of the derivation access specifier is to control the access that users of the derived class—including other classes derived from the derived class—have to the members inherited from Base:

```cs
Pub_Derv d1;    // members inherited from Base are public
Priv_Derv d2;   // members inherited from Base are private
d1.pub_mem();   // ok: pub_mem is public in the derived class
d2.pub_mem();   // error: pub_mem is private in the derived class
```

BothPub_Derv and Priv_Derv inherit the pub_mem function.  
When the inheritance is public, members retain their access specification.  
Thus, d1 can call pub_mem.  
InPriv_Derv, the members of Base are private; users of that class may not call pub_mem.

The derivation access specifier used by a derived class also controls access from classes that inherit from that derived class:

```cs
struct Derived_from_Public : public Pub_Derv
{
    // ok: Base::prot_mem remains protected in Pub_Derv
    int use_base() { return prot_mem; }
};

struct Derived_from_Private : public Priv_Derv
{
    // error: Base::prot_mem is private in Priv_Derv
    int use_base() { return prot_mem; }
};
```

Classes derived from Pub_Derv may access prot_mem from Base because that member remains a protected member in Pub_Derv.  
In contrast, classes derived from Priv_Derv have no such access.  
To them, all the members that Priv_Derv inherited from Base are private.

Had we defined another class, say, Prot_Derv, that used protected inheritance, the public members of Base would be protected members in that class.  
Users of Prot_Derv would have no access to pub_mem, but the members and friends of Prot_Derv could access that inherited member.

##### 3) Accessibility of Derived-to-Base Conversion

Whether the derived-to-base conversion is accessible depends on which code is trying to use the conversion and may depend on the access specifier used in the derived class’ derivation.  
Assuming D inherits from B:

- User code may use the derived-to-base conversion only if D inherits publicly  from B.  
  User code may not use the conversion if D inherits from B using either protected or private.
- Member functions and friends of D can use the conversion to B regardless of how D inherits from B.  
  The derived-to-base conversion to a direct base class isalways accessible to members and friends of a derived class.
- Member functions and friends of classes derived from D may use the derived-to-base conversion if D inherits from B using either public or protected.  
  Such code may not use the conversion if D inherits privately from B.

> ##### Tip
> For any given point in your code, if a public member of the base class would be accessible, then the derived-to-base conversion is also accessible, and not otherwise.

> ##### Key Concept: Class Design and `protected` Members
> In the absence of inheritance, we can think of a class as having two different kinds of users: ordinary users and implementors.  
> Ordinary users write code that uses objects of the class type; such code can access only the public (interface) members of the class.  
> Implementors write the code contained in the members and friends of the class.  
> The members and friends of the class can access both the public and private (implementation) sections.
>
> Under inheritance, there is a third kind of user, namely, derived classes.  
> A base class makes protected those parts of its implementation that it is willing to let its derived classes use.  
> The protected members remain inaccessible to ordinary user code; private members remain inaccessible to derived classes and their friends.
>
> Like any other class, a class that is used as a base class makes its interface members public.  
> A class that is used as a base class may divide its implementation into those members that are accessible to derived classes and those that remain accessible only to the base class and its friends.  
> An implementation member should be protected if it provides an operation or data that a derived class will need to use in its own implementation.  
> Otherwise, implementation members should be private.

##### 4) Friendship and Inheritance

Just as friendship is not transitive, friendship is also not inherited.

Friends of the base have no special access to members of its derived classes, and friends of a derived class have no special access to the base class:

```cs
class Base
{
    // added friend declaration; other members as before
    friend class Pal; // Pal has no access to classes derived from Base
};

class Pal
{
public:
    int f(Base b) { return b.prot_mem; }    // ok: Pal is a friend of Base
    int f2(Sneaky s) { return s.j; }        // error: Pal not friend of Sneaky
    // access to a base class is controlled by the base class, even inside a derived object
    int f3(Sneaky s) { return s.prot_mem; } // ok: Pal is a friend
};
```

The fact that f3 is legal may seem surprising, but it follows directly from the notion that each **class controls access to its own members**.  
Pal is a friend of Base, so Pal can access the members of Base objects.  
That access includes access to Base objects that are embedded in an object of a type derived from Base.

When a class makes another class a friend, it is only that class to which friendship is granted.  
The base classes of, and classes derived from, the friend have no special access to the befriending class:

```cs
// D2 has no access to protected or private members in Base
class D2 : public Pal
{
public:
    int mem(Base b) { return b.prot_mem; } // error: friendship doesn't inherit
};
```

> ##### Note
> Friendship is not inherited; each class controls access to its members.

##### 5) Exempting Individual Members

Sometimes we need to change the access level of a name that a derived class inherits. We can do so by providing a `using` declaration.

```cs
class Base
{
public:
    std::size_t size() const { return n; }
protected:
    std::size_t n;
};

class Derived : private Base
{
    // note: private inheritance
public:
    // maintain access levels for members related to the size of the object
    using Base::size;
protected:
    using Base::n;
};
```

Because Derived uses private inheritance, the inherited members, size and n, are (by default) private members of Derived.  
The using declarations adjust the accessibility of these members.  
Users of Derived can access the size member, and classes subsequently derived from Derived can access n.

A `using` declaration inside a class can name any accessible (e.g., not private) member of a direct or indirect base class.  
Access to a name specified in a using declaration depends on the access specifier preceding the using declaration.  
That is,

- If a using declaration appears in a private part of the class, that name is accessible to members and friends only.  
- If the declaration is in a public section, the name is available to all users of the class.  
- If the declaration is in a protected section, the name is accessible to the members, friends, and derived classes.

> ##### Note
> A derived class may provide a `using` declaration only for names it is permitted to access.

##### 6) Default Inheritance Protection Levels

By default, a derivedclass defined with the class keyword has private inheritance.  
a derived classdefined with struct has public inheritance.

It is a common misconception to think that there are deeper differences between classes defined using the struct keyword and those defined using class.  
The only differences are the default access specifier for members and the default derivation access specifier.  
There are no other distinctions.

> ##### Best Practices
> A privately derived class should specify private explicitly rather than rely on the default.  
> Being explicit makes it clear that private inheritance is intendedand not an oversight.

--------------------------------------------------------------------------------

### 15.6 Class Scope under Inheritance

Each class defines its own scope within which its members are defined.  
Under inheritance, the scope of a derived class is **nested inside** the scope of its base classes.  
If a name is unresolved within the scope of the derived class, the enclosing base-class scopes are searched for a definition of that name.

It is this hierarchical nesting of class scopes that allows the members of a derived class to use members of its base class as if those members were part of the derived class.

##### 1) Name Lookup Happens at Compile Time

The static type of an object, reference, or pointer determines which members of that object are visible.  
Even when the static and dynamic types might differ (as can happen when a reference or pointer to a base class is used), the static type determines what members can be used.

##### 2) Name Collisions and Inheritance

Like any other scope, a derived class can reuse a name defined in one of its direct orindirect base classes. As usual, names defined in an inner scope (e.g., a derived class)hide uses of that name in the outer scope (e.g., a base class).

> ##### Note
> A derived-class member with the same name as a member of the base classhides direct use of the base-class member.

##### 3) Using the Scope Operator to Use Hidden Members

> ##### Best Practices
> Aside from overriding inherited virtual functions, a derived class usually should not reuse names defined in its base class.

> ##### Key Concept: Name Lookup and Inheritance
> 
> Understanding how function calls are resolved is crucial to understanding inheritance in C++.  
> Given the call `p->mem()` (or `obj.mem()`), the following four steps happen:
> 
> - First determine the static type of `p` (or `obj`). 
>   Because we’re calling a member, that type must be a class type.
> - Look for `mem` in the class that corresponds to the static type of p (or obj).  
>   If mem is not found, look in the direct base class and continue up the chain of classes until mem is found or the last class is searched.  
>   If mem is not found in the class or its enclosing base classes, then the call will not compile.
> - Once mem is found, do normal type checking to see if this call is legal given the definition that was found.
> - Assuming the call is legal, the compiler generates code, which varies depending on whether the call is virtual or not:
>   - If mem is virtual and the call is made through a reference or pointer, then the compiler generates code to determine at run time which version to run based on the dynamic type of the object
>   - Otherwise, if the function is nonvirtual, or if the call is on an object (not a reference or pointer), the compiler generates a normal function call

##### 4) As Usual, Name Lookup Happens before Type Checking

As we’ve seen, *functions declared in an inner scope do not overload* functions declared in an outer scope.  
As a result, functions defined in a derived class do not overload members defined in its base class(es).  
As in any other scope, if a member in a derived class (i.e., in an inner scope) has the same name as a base-class member (i.e., a name defined in an outer scope), then the derived member hides the base-class member within the scope of the derived class.  
The base member is hidden even if the functions have different parameter lists.

##### 5) Virtual Functions and Scope

We can now understand why virtual functions must have the same parameter list in the base and derived classes.  
If the base and derived members took arguments that differed from one another, there would be no way to call the derived version through a reference or pointer to the base class.

##### 6) Calling a Hidden Virtual through the Base Class

##### 7) Overriding Overloaded Functions

As with any other function, a member function (virtual or otherwise) can beoverloaded.  
A derived class can override zero or more instances of the overloaded functions it inherits.  
If a derived class wants to make all the overloaded versions available through its type, then it must override all of them or none of them.

Sometimes a class needs to override some, but not all, of the functions in an overloaded set.  
It would be tedious in such cases to have to override every base-classversion in order to override the ones that the class needs to specialize.

Instead of overriding every base-class version that it inherits, a derived class canprovide a `using` declaration for the overloaded member.  
A using declaration specifies only a name; it may not specify a parameter list.  
Thus, a usingdeclaration for a base-class member function adds all the overloaded instances of thatfunction to the scope of the derived class.  
Having brought all the names into its scope,the derived class needs to define only those functions that truly depend on its type.  
It can use the inherited definitions for the others.

The normal rules for a using declaration inside a class apply to names of overloaded functions; every overloaded instance of the function in thebase class must be accessible to the derived class.  
The access to the overloadedversions that are not otherwise redefined by the derived class will be the access ineffect at the point of the using declaration.

--------------------------------------------------------------------------------

### 15.7 Constructors and Copy Control

Like any other class, a class in an inheritance hierarchy controls what happens whenobjects of its type are *created, copied, moved, assigned, or destroyed*.

#### 15.7.1 Virtual Destructors

The primary direct impact that inheritance has on copy control for a base class is that a base class generally should define a virtual destructor.  
The destructor needs to be virtual to allow objects in the inheritance hierarchy to be dynamically allocated.

```cs
class Quote
{
public:
    // virtual destructor needed if a base pointer pointing to a derived object is deleted
    virtual ~Quote() = default; // dynamic binding for the destructor
};
```

> ##### Warning
> Executing `delete` on a pointer to base that points to a derived object has undefined behavior if the base’s destructor is not virtual.

Destructors for base classes are an important **exception** to the rule of thumb that ifa class needs a destructor, it also needs copy and assignment.  
A base class almost always needs a destructor, so that it can make the destructorvirtual.  
If a base class has an empty destructor in order to make it virtual, then thefact that the class has a destructor does not indicate that the assignment operator orcopy constructor is also needed.

##### 1) Virtual Destructors Turn Off Synthesized Move

The fact that a base class needs a virtual destructor has an important indirect impacton the definition of base and derived classes: If a class defines a destructor—even ifit uses `= default` to use the synthesized version—the compiler will not synthesize amove operation for that class.

#### 15.7.2 Synthesized Copy Control and Inheritance

The synthesized copy-control members in a base or a derived class execute like anyother synthesized constructor, assignment operator, or destructor:  
They memberwiseinitialize, assign, or destroy the members of the class itself.  
In addition, these synthesized members initialize, assign, or destroy the direct base part of an object byusing the corresponding operation from the base class.

- The synthesized Bulk_quote default constructor runs the Disc_Quote defaultconstructor, which in turn runs the Quote default constructor.
- The Quote default constructor default initializes the bookNo member to theempty string and uses the in-class initializer to initialize price to zero.
- When the Quote constructor finishes, the Disc_Quote constructor continues,which uses the in-class initializers to initialize qty and discount.
- When the Disc_quote constructor finishes, the Bulk_quote constructor continues but has no other work to do.

It is worth noting that it doesn’t matter whether the base-class member is itself synthesized (as is the case in our Quote hierarchy) or has a an user-provided definition.  
All that matters is that the corresponding member is accessible and that it is not a deleted function.

Each of our Quote classes use the synthesized destructor.  
The derived classes do so implicitly, whereas the Quote class does so explicitly by defining its (virtual) destructor as `= default`.  
The synthesized destructor is (as usual) empty and itsimplicit destruction part destroys the members of the class.  
In addition to destroying its own members, the destruction phase of a destructor in aderived class also destroys its direct base.  
That destructor in turn invokes the destructor for its own direct base, if any.  
And, so on up to the root of the hierarchy.

As we’ve seen, Quote does not have synthesized move operations because itdefines a destructor.  
The (synthesized) copy operations will be used whenever wemove a Quote object.  
As we’re about to see, the fact that Quotedoes not have move operations means that its derived classes don’t either.

##### 1) Base Classes and Deleted Copy Control in the Derived

The synthesized default constructor, or any of the copy-control members of either abase or a derived class, may be defined as deleted for the same reasons as in anyother class.  
In addition, the way in which abase class is defined can cause a derived-class member to be defined as deleted:

- If the default constructor, copy constructor, copy-assignment operator, or destructor in the base class is deleted or inaccessible, then the corresponding member in the derived class is defined as deleted, because the compiler can’t use the base-class member to construct, assign, or destroy thebase-class part of the object.
- If the base class has an inaccessible or deleted destructor, then the synthesized default and copy constructors in the derived classes are defined as deleted, because there is no way to destroy the base part of the derived object.
- As usual, the compiler will not synthesize a deleted move operation. If we use `= default` to request a move operation, it will be a deleted function in the derived if the corresponding operation in the base is deleted or inaccessible,because the base class part cannot be moved. The move constructor will also be deleted if the base class destructor is deleted or inaccessible.

```cs
class B
{
public:
    B();
    B(const B&) = delete;   // other members, not including a move constructor
};

class D : public B
{
    // no constructors
};

D d;                // ok:D's synthesized default constructor usesB's default constructor
D d2(d);            // error:D's synthesized copy constructor isdeleted
D d3(std::move(d)); // error: implicitly usesD's deleted copy constructor
```

Because the copy constructor is defined, the compiler will not synthesize a move constructor for class B.  
As a result, we can neither move nor copyobjects of type B.  
If a class derived from B wanted to allow its objects to be copied ormoved, that derived class would have to define its own versions of these constructors.  
Of course, that class would have to decide how to copy or move the members in itbase-class part.

In practice, if a base class does not have a default, copy, or moveconstructor, then its derived classes usually don’t either.

##### 2) Move Operations and Inheritance

Most base classes define a virtual destructor.  
As a result, by default, base classes generally do not get synthesized move operations.  
Moreover, by default, classes derived from a base class that doesn’t have move operations don’t get synthesized move operations either.

Because lack of a move operation in a base class suppresses synthesized move forits derived classes, base classes ordinarily should define the move operations if it issensible to do so.  
Our Quote class can use the synthesized versions.  
However, Quote must define these members explicitly.  
Once it defines its move operations, it must alsoexplicitly define the copy versions as well:

```cs
class Quote
{
public:
    Quote() = default;                          // memberwise default initialize
    Quote(const Quote&) = default;              // memberwise copy
    Quote(Quote&&) = default;                   // memberwise copy
    Quote& operator=(const Quote&) = default;   // copy assign
    Quote& operator=(Quote&&) = default;        // move assign
    virtual ~Quote() = default;
    // other members as before};
};
```

Now, Quote objects will be memberwise copied, moved, assigned, and destroyed.  
Moreover, classes derived from Quote will automatically obtain synthesized moveoperations as well, unless they have members that otherwise preclude move.

#### 15.7.3 Derived-Class Copy-Control Members

The copy and move constructors for a derived class must copy/move the members of its base part as well as the members in the derived.  
Similarly, a derived-class assignment operator must assign the members in the basepart of the derived object.

Unlike the constructors and assignment operators, the destructor is responsible only for destroying the resources allocated by the derived class.  
Recall that the members ofan object are implicitly destroyed.  
Similarly, the base-class part of aderived object is destroyed automatically.

> ##### Warning 
> When a derived class defines a copy or move operation, that operation is responsible for copying or moving the entire object, including base-class members.

##### 1) Defining a Derived Copy or Move Constructor

```cs
class Base { /* ...*/ };

class D: public Base
{
public:
    // by default, the base class default constructor initializes the base part of an object
    // to use the copy or move constructor, we must explicitly call that
    // constructor in the constructor initializer list
    D(const D& d): Base(d)          // copy the base members /* initializers for members of D */ { /* ...*/ }
    D(D&& d): Base(std::move(d))    // move the base members /* initializers for members of D */ { /* ...*/ }
};
```

The initializer Base(d) passes a D object to a base-class constructor.  
Although in principle, Base could have a constructor that has a parameter of type D, in practice, that is very unlikely.  
Instead, Base(d) will (ordinarily) match the Base copy constructor.  
The D object, d, will be bound to the Base& parameter in that constructor. The Base copy constructor will copy the base part of d into the objectthat is being created. 

> ##### Warning
> By default, the base-class default constructor initializes the base-class part of a derived object.  
> If we want copy (or move) the base-class part, we must explicitly use the copy (or move) constructor for the base class in thederived’s constructor initializer list.

##### 2) Derived-Class Assignment Operator

```cs
// Base::operator=(const Base&) is not invoked automatically
D &D::operator=(const D &rhs)
{
    Base::operator=(rhs); // assigns the base part
    // assign the members in the derived class, as usual,
    // handling self-assignment and freeing existing resources as appropriate
    return *this;
}
```

This operator starts by explicitly calling the base-class assignment operator to assignthe members of the base part of the derived object.  
The base-class operator will (presumably) correctly handle self-assignment and, if appropriate, will free the old value in the base part of the left-hand operand and assign the new values from rhs.  
Once that operator finishes, we continue doing whatever is needed to assign themembers in the derived class.

It is worth noting that a derived constructor or assignment operator can use its corresponding base class operation regardless of whether the base defined its own version of that operator or uses the synthesized version.  
For example, the call to Base::operator= executes the copy-assignment operator in class Base.  
It is immaterial whether that operator is defined explicitly by the Base class or is synthesized by the compiler.

##### 3) Derived-Class Destructor

Unlike the constructors and assignment operators, a derived destructor is responsible only for destroying the resources allocated by the derived class:

```cs
class D: public Base
{
public:
    // Base::~Base invoked automatically
    ~D() { /* do what it takes to clean up derived members   */ }
};
```

Objects are destroyed in the opposite order from which they are constructed:  
The derived destructor is run first, and then the base-class destructors are invoked, back up through the inheritance hierarchy.

##### 4) Calls to Virtuals in Constructors and Destructors

As we’ve seen, the base-class part of a derived object is constructed first.  
While the base-class constructor is executing, the derived part of the object is uninitialized.  
Similarly, derived objects are destroyed in reverse order, so that when a base class destructor runs, the derived part has already been destroyed.  
As a result, while these base-class members are executing, the object is incomplete.

To accommodate this incompleteness, the compiler treats the object as if its type changes during construction or destruction.  
That is, while an object is beingconstructed it is treated as if it has the same class as the constructor; calls to virtual functions will be bound as if the object has the same type as the constructor itself.  
Similarly, for destructors.  
This binding applies to virtuals called directly or that are called indirectly from a function that the constructor (or destructor) calls.

To understand this behavior, consider what would happen if the derived-class version of a virtual was called from a base-class constructor.  
This virtual probablyaccesses members of the derived object.  
After all, if the virtual didn’t need to usemembers of the derived object, the derived class probably could use the version in itsbase class.  
However, those members are uninitialized while a base constructor isrunning. If such access were allowed, the program would probably crash.

> ##### Note
> If a constructor or destructor calls a virtual, the version that is run is the one corresponding to the type of the constructor or destructor itself.

#### 15.7.4 Inherited Constructors

`C++11` A derived class can reuse the constructors defined by its direct base class.  
Although, as we’ll see, such constructors are not inherited in the normal sense of that term, it is nonetheless common to refer to such constructors as “inherited.”  
For the same reasons that a class may initialize only its direct base class, a class may inherit constructors only from its direct base.  
A class cannot inherit thedefault, copy, and move constructors.  
If the derived class does not directly define these constructors, the compiler synthesizes them as usual.

A derived class inherits its base-class constructors by providing a `using` declarationthat names its (direct) base class.  
As an example, we can redefine our Bulk_quote class to inherit its constructors from Disc_quote:

```cs
class Bulk_quote : public Disc_quote
{
public:
    using Disc_quote::Disc_quote; // inherit Disc_quote's constructors
    double net_price(std::size_t) const;
};
```

Ordinarily, a using declaration only makes a name visible in the current scope.  
When applied to a constructor, a using declaration causes the compiler to generate code.  
The compiler generates a derived constructor corresponding to each constructor in thebase.  
That is, for each constructor in the base class, the compiler generates a constructor in the derived class that has the same parameter list.

These compiler-generated constructors have the form  
`derived(parms) : base(args) { }`  
where derived is the name of the derived class, base is the name of the base class, parms is the parameter list of the constructor, and args pass the parameters from the derived constructor to the base constructor.

##### 1) Characteristics of an Inherited Constructor

Unlike using declarations for ordinary members, a constructor using declarationdoes not change the access level of the inherited constructor(s).  
For example, regardless of where the using declaration appears, a private constructor in thebase is a private constructor in the derived; similarly for protected and public constructors.

Moreover, a using declaration can’t specify explicit or constexpr.  
If aconstructor in the base is explicit or constexpr, the inherited constructor has the same property.

If a base-class constructor has default arguments, those argumentsare not inherited.  
Instead, the derived class gets multiple inherited constructors inwhich each parameter with a default argument is successively omitted.  
For example, if the base has a constructor with two parameters, the second of which has a default, the derived class will obtain two constructors: one with both parameters (and nodefault argument) and a second constructor with a single parameter corresponding to the left-most, non-defaulted parameter in the base class.

If a base class has several constructors, then with two exceptions, the derived class inherits each of the constructors from its base class.

The first exception is that aderived class can inherit some constructors and define its own versions of otherconstructors.  
If the derived class defines a constructor with the same parameters as aconstructor in the base, then that constructor is not inherited.  
The one defined in thederived class is used in place of the inherited constructor.

The second exception is that the default, copy, and move constructors are notinherited.  
These constructors are synthesized using the normal rules.  
An inherited constructor is not treated as a user-defined constructor.  
Therefore, a class thatcontains only inherited constructors will have a synthesized default constructor.

--------------------------------------------------------------------------------

### 15.8 Containers and Inheritance

When we use a container to store objects from an inheritance hierarchy, we generally must store those objects **indirectly**.  
We cannot put objects of types related by inheritance directly into a container, because there is no way to define a container that holds elements of differing types.

As an example, assume we want to define a vector to hold several books that a customer wants to buy.  
It should be easy to see that we can’t use a vector that holds Bulk_quote objects.  
We can’t convert Quote objects to Bulk_quote so we wouldn’t be able to put Quote objects into that vector.

It may be somewhat less obvious that we also can’t use a vector that holds objects of type Quote.  
In this case, we can put Bulk_quote objects into the container.  
However, those objects would no longer be Bulk_quote objects.  
When we add a Bulk_quote object tothe vector its derived part is ignored.

> ##### Warning
> Because derived objects are “sliced down” when assigned to a base-type object, containers and types related by inheritance do not mix well.

##### 1) Put (Smart) Pointers, Not Objects, in Containers

When we need a container that holds objects related by inheritance, we typically define the container to hold pointers (preferably smart pointers) to thebase class.  
As usual, the dynamic type of the object to which those pointers point might be the base-class type or a type derived from that base:

```cs
vector<shared_ptr<Quote>> basket;
basket.push_back(make_shared<Quote>("0-201-82470-1", 50));
basket.push_back(make_shared<Bulk_quote>("0-201-54848-8", 50, 10, .25));
// calls the version defined byQuote;prints562.5,i.e., 15 * $50 less the discount
cout << basket.back()->net_price(15) << endl;
```

#### 15.8.1 Writing a `Basket` Class

One of the ironies of object-oriented programming in C++ is that we cannot useobjects directly to support it.  
Instead, we must use pointers and references.  
Because pointers impose complexity on our programs, we often define auxiliary classes to help manage that complexity.  
We’ll start by defining a class to represent a basket:

```cs
class Basket
{
public:
    // Basket uses synthesized default constructor and copy-control members
    void add_item(const std::shared_ptr<Quote> &sale)
        { items.insert(sale); }
    // prints the total price for each book and the overall  total for all items in the basket
    double total_receipt(std::ostream&) const;

private:
    // function to compare shared_ptrs needed by the multiset member
    static bool compare(const std::shared_ptr<Quote> &lhs,
                        const std::shared_ptr<Quote> &rhs)
        { return lhs->isbn() < rhs->isbn(); }
    
    // multiset to hold multiple quotes, ordered by the compare member
    std::multiset<std::shared_ptr<Quote>, decltype(compare)*> items{compare};
};
```

Our class uses a multiset to hold the transactions, so that we can store multiple transactions for the same book, and so that all the transactions for a given book will be kept together.

The elements in our multiset are shared_ptrs and there is no less-than operator for shared_ptr.  
As a result, we must provide our own comparison operation to order the elements.  
Here, we define a private static member, named compare, that compares the isbns of the objects to whichthe shared_ptrs point.  
We initialize our multiset to use this comparison function through an in-class initializer.  
This declaration can be hard to read, but reading from left to right, we see that we are defining a multiset of shared_ptrs to Quote objects.  
The multiset will usea function with the same type as our compare member to order the elements. The multiset member is named items, and we’re initializing items to use ourcompare function.

##### 1) Defining the Members of Basket

The `Basket` class defines only two operations.  
We defined the add_item memberinside the class.  
That member takes a shared_ptr to a dynamically allocated Quote and puts that shared_ptr into the multiset.  
The second member,total_receipt, prints an itemized bill for the contents of the basket and returnsthe price for all the items in the basket:

```cs
double Basket::total_receipt(ostream &os) const
{
    double sum = 0.0;   // holds the running total
    // iter refers to the first element in a batch of elements with the same ISBN
    // upper_bound returns an iterator to the element just past the end of that batch
    for (auto iter = items.cbegin();
              iter != items.cend();
              iter = items.upper_bound(*iter))
    {
        // we know there's at least one element with this key in the Basket
        // print the line item for this book
        sum += print_total(os, **iter, items.count(*iter));
    }
    os << "Total Sale: " << sum << endl; // print  the  final  overall total
    return sum;
}
```

Our for loop starts by defining and initializing iter to refer to the first element in the multiset.  
The condition checks whether iter is equal to items.cend().  
If so,we’ve processed all the purchases and we drop out of the for.  
Otherwise, we process the next book.

The interesting bit is the “increment” expression in the for.  
Rather than the usual loop that reads each element, we advance iter to refer to the next key.  
We skip over all the elements that match the current key by calling upper_bound.  
The call to upper_bound returns the iterator that refers to the element just past the last one with the same key as in iter.  
The iterator we get back denotes either the end of the set or the next book.

Inside the for loop, we call print_total to print the details for each book in the basket:  
`sum += print_total(os, **iter, items.count(*iter));`

The arguments to print_total are an ostream on which to write, a Quote object to process, and a count.  
When we dereference iter, we get a shared_ptr that points to the object we want to print.  
To get that object, we must dereference that shared_ptr.  
Thus, **iter is a Quote object (or an object of a type derived from Quote).  
We use the multiset count member to determine howmany elements in the multiset have the same key (i.e., the same ISBN).

As we’ve seen, print_total makes a virtual call to net_price, so the resulting price depends on the dynamic type of **iter.  
The print_total function prints the total for the given book and returns the total price that it calculated.  
We add that result into sum, which we print after we complete the for loop.

##### 2) Hiding the Pointers

Users of Basket still have to deal with dynamic memory, because add_item takes a shared_ptr.  
As a result, users have to write code such as

```cs
Basket bsk;
bsk.add_item(make_shared<Quote>("123", 45));
bsk.add_item(make_shared<Bulk_quote>("345", 45, 3, .15));
```

Our next step will be to redefine add_item so that it takes a Quote object instead of a shared_ptr.  
This new version of add_item will handle the memory allocation so that our users no longer need to do so.  
We’ll define two versions, one that will copy its given object and the other that will move from it:

```cs
void add_item(const Quote& sale);   // copy the given object
void add_item(Quote&& sale);        // move the given object
```

The only problem is that add_item doesn’t know what type to allocate.  
When it does its memory allocation, add_item will copy (or move) its sale parameter.  
Somewhere there will be a new expression such as:  
`new Quote(sale)`  
Unfortunately, this expression won’t do the right thing: new allocates an object of the type we request.  
This expression allocates an object of type Quote and copies theQuote portion of sale. However, sale might refer to a Bulk_quote object, inwhich case, that object will be sliced d own.

##### 3) Simulating Virtual Copy

We’ll solve this problem by giving our Quote classes a virtual member that allocates a copy of itself.

```cs
class Quote
{
public:
    // virtual function to return a dynamically allocated copy of itself
    // these members use reference qualifiers
    virtual Quote* clone() const & { return new Quote(*this); }
    virtual Quote* clone() && { return new Quote(std::move(*this)); }
    // other members as before
};

class Bulk_quote : public Quote
{
    Bulk_quote* clone() const & { return new Bulk_quote(*this); }
    Bulk_quote* clone() && { return new Bulk_quote(std::move(*this)); }
    // other members as before
};
```

Because we have a copy and a move version of add_item, we defined lvalue and rvalue versions of clone.  
Each clone function allocates a new object of its own type.  
The const lvalue reference member copies itself into that newly allocated object; the rvalue reference member moves its own data.

Using clone, it is easy to write our new versions of add_item:

```cs
class Basket
{
public:
    void add_item(const Quote& sale)    // copy the given object
        { items.insert(std::shared_ptr<Quote>(sale.clone())); }
    void add_item(Quote&& sale)         // move the given object
        { items.insert(std::shared_ptr<Quote>(std::move(sale).clone())); }
        // other members as before
};
```

Like add_item itself, clone is overloaded based on whether it is called on an lvalue or an rvalue.  
Thus, the first version of add_item calls the const lvalue version of clone, and the second version calls the rvalue reference version.  
Note that in the rvalue version, although the type of `sale` is an rvalue reference type, `sale` (like any other variable) is an lvalue.  
Therefore, we call move to bind an rvalue reference to `sale`.

Our clone function is also virtual.  
Whether the Quote or Bulk_quote function is run, depends (as usual) on the dynamic type of sale.  
Regardless of whether we copy or move the data, clone returns a pointer to a newly allocated object, of its owntype.  
We bind a shared_ptr to that object and call insert to add this newly allocated object to items.  
Note that because shared_ptr supports the derived-to-base conversion, we can bind a shared_ptr<Quote> to a Bulk_quote*.

--------------------------------------------------------------------------------

### 15.9 Text Queries Revisited (TODO)

--------------------------------------------------------------------------------

### Chapter Summary

Inheritance lets us write new classes that share behavior with their base class(es) but override or add to that behavior as needed. Dynamic binding lets us ignore type differences by choosing, at run time, which version of a function to run based on an object’s dynamic type. The combination of inheritance and dynamic binding lets us **write type-independent, programs that have type-specific behavior**.

In C++, dynamic binding applies only to functions declared as `virtual` and called through a *reference* or *pointer*.

A derived-class object contains a subobject corresponding to each of its base classes. Because every derived object contains a base part, we can convert a reference or pointer to a derived-class type to a reference or pointer to an accessible base class.

Inherited objects are constructed, copied, moved, and assigned by constructing, copying, moving, and assigning the base part(s) of the object before handling the derived part. Destructors execute in the opposite order; the derived type is destroyed first, followed by destructors for the base-class subobjects. Base classes usually should define a virtual destructor even if the class otherwise has no need for a destructor. The destructor must be virtual if a pointer to a base is ever deleted when it actually addresses a derived-class object.

A derived class specifies a protection level for each of its base class(es). Members of a public base are part of the interface of the derived class; members of a private base are inaccessible; members of a protected base are accessible to classes that derive from the derived class but not to users of the derived class.

--------------------------------------------------------------------------------

EOF
