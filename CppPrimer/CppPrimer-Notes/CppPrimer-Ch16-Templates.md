CppPrimer-Ch16-Templates.md

C++ Primer Notes
================================================================================

Ad  
<ar><r>

init: 18Nov05

Chapter16 Templates and Generic Programming
--------------------------------------------------------------------------------

- [Chapter16 Templates and Generic Programming](#chapter16-templates-and-generic-programming)
  - [16.1 Defining a Template](#161-defining-a-template)
    - [16.1.1 Function Templates](#1611-function-templates)
    - [16.1.2 Class Templates](#1612-class-templates)
    - [16.1.3 Template Parameters](#1613-template-parameters)
    - [16.1.4 Member Templates](#1614-member-templates)
    - [16.1.5 Controlling Instantiations](#1615-controlling-instantiations)
    - [16.1.6 Efficiency and Flexibility](#1616-efficiency-and-flexibility)
  - [16.2 Template Argument Deduction](#162-template-argument-deduction)
    - [16.2.1 Conversions and Template Type Parameters](#1621-conversions-and-template-type-parameters)
    - [16.2.2 Function-Template Explicit Arguments](#1622-function-template-explicit-arguments)
    - [16.2.3 Trailing Return Types and Type Transformation](#1623-trailing-return-types-and-type-transformation)
    - [16.2.4 Function Pointers and Argument Deduction](#1624-function-pointers-and-argument-deduction)
    - [16.2.5 Template Argument Deduction and References](#1625-template-argument-deduction-and-references)
    - [16.2.6 Understanding `std::move`](#1626-understanding-stdmove)
    - [16.2.7 Forwarding](#1627-forwarding)
  - [16.3 Overloading and Templates](#163-overloading-and-templates)
  - [16.4 Variadic Templates](#164-variadic-templates)
    - [16.4.1 Writing a Variadic Function Template](#1641-writing-a-variadic-function-template)
    - [16.4.2 Pack Expansion](#1642-pack-expansion)
    - [16.4.3 Forwarding Parameter Packs](#1643-forwarding-parameter-packs)
  - [16.5 Template Specializations](#165-template-specializations)
  - [Chapter Summary](#chapter-summary)

--------------------------------------------------------------------------------

Both object-oriented programming (OOP) and generic programming deal with typesthat are not known at the time the program is written. The distinction between thetwo is that OOP deals with types that are not known until run time, whereas ingeneric programming the types become known during compilation.

*Templates* are the foundation for generic programming in C++.  
A template is ablueprint or formula for creating classes or functions.  
When we use a generic type,such as `vector`, or a generic function, such as `find`, we supply the informationneeded to transform that blueprint into a specific class or function.  
Thattransformation happens during compilation.

### 16.1 Defining a Template

#### 16.1.1 Function Templates

```cpp
template <typename T>
int compare(const T &v1, const T &v2)
{
    if (v1 < v2) return -1;
    if (v2 < v1) return 1;
    return 0;
}
```

A template definition starts with the keyword  `template` followed by a **template parameter list**, which is a comma-separated list of one or more **template parameters** bracketed by the less-than (<) and greater-than (>) tokens.

> ##### Note
> In a template definition, the template parameter list cannot be empty.

##### 1) Instantiating a Function Template

When we call a function template, the compiler (ordinarily) uses the arguments of the call to deduce the template argument(s) for us.

The compiler uses the deduced template parameter(s) to **instantiate** a specificversion of the function for us.  
When the compiler instantiates a template, it creates anew “instance” of the template using the actual template argument(s) in place of the corresponding template parameter(s).

##### 2) Template Type Parameters

In general, we can use atype parameter as a type specifier in the same way that we use a built-in or classtype specifier.  
In particular, a type parameter can be used to name the return type ora function parameter type, and for variable declarations or casts inside the function body:

```cs
// ok: same type used for the return type and parameter
template <typename T> T foo(T* p)
{
    T tmp = *p; // tmp will have the type to which p points
    // ...
    return tmp;
}
```

Each type parameter must be preceded by the keyword `class` or `typename`:  

```cpp
// error: must precede U with either typename or class
template <typename T, U> T calc(const T&, const U&);

//ok: no distinction betweentypenameandclassin a template parameter list
template <typename T, class U> calc (const T&, const U&);
```

##### 3) Nontype Templates Parameters

A **nontype parameter** represents a value rather than a type.  
Nontype parameters are specified by using a specific type name instead of the class or typename keyword.

When the template is instantiated, nontype parameters are replaced with a value supplied by the user or deduced by the compiler.  
These values must be constant expressions, which allows the compiler to instantiate the templatesduring compile time.

```cpp
template<unsigned N, unsigned M>
int compare(const char (&p1)[N], const char (&p2)[M])
{
    return strcmp(p1, p2);
}
```

When we call this version of compare:  
`compare("hi", "mom");`  
the compiler will use the size of the literals to instantiate a version of the template with the sizes substituted for N and M.
Remembering that the compiler inserts a null terminator at the end of a string literal, the compiler will instantiate  
`int compare(const char (&p1)[3], const char (&p2)[4])`

A nontype parameter may be an integral type, or a pointer or (lvalue) reference to an object or to a function type.  
An argument bound to a nontype integral parametermust be a constant expression.  
Arguments bound to a pointer or reference nontype parameter must have static lifetime.  
We may not use an ordinary(nonstatic) local object or a dynamic object as a template argument for referenceor pointer nontype template parameters.  
A pointer parameter can also be instantiatedby nullptr or a zero-valued constant expression.

A template nontype parameter is a constant value inside the template definition.  
Anontype parameter can be used when constant expressions are required, for example,to specify the size of an array.

> ##### Note
> Template arguments used for nontype template parameters must be constant expressions.

##### 4) `inline` and `constexpr` Function Templates

A function template can be declared inline or constexpr in the same ways asnontemplate functions.  
The inline or constexpr specifier follows the templateparameter list and precedes the return type:

```cpp
// ok: inline specifier follows the template parameter list
template <typename T> inline T min(const T&, const T&);
// error: incorrect placement of theinlinespecifier
inline template <typename T> T min(const T&, const T&);
```

##### 5) Writing Type-Independent Code

Simple though it is, our initial compare function illustrates two important principles for writing generic code:

- The function parameters in the template are *references to const*. (for uncopyable and large objs)
- The tests in the body use only `<` comparisons (without `>`)

In fact, if we were truly concerned about type independence and portability, weprobably should have defined our function using the `less`.

```cpp
//version of compare that will be correct even if used on pointers;
template <typename T> int compare(const T &v1, const T &v2)
{
    if (less<T>()(v1, v2)) return -1;
    if (less<T>()(v2, v1)) return 1;
    return 0;
}
```

> ##### Best Practices
> Template programs should try to minimize the number of requirements placed on the argument types.

##### 6) Template Compilation

When the compiler sees the definition of a template, it does not generate code.  
It generates code only when we instantiate a specific instance of the template.

Ordinarily, when we call a function, the compiler needs to see only a declaration forthe function.  
Similarly, when we use objects of class type, the class definition must be available, but the definitions of the member functions need not be present.  
As aresult, we put class definitions and function declarations in header files and definitions of ordinary and class-member functions in source files.

Templates are different:  
To generate an instantiation, the compiler needs to have the code that defines a function template or class template member function.  
As aresult, unlike nontemplate code, headers for templates typically include definitions as well as declarations.

> ##### Note
> Definitions of function templates and member functions of class templates areordinarily put into header files.

> ##### Key Concept: Templates and Headers
> 
> Templates contain two kinds of names:
> 
> - Those that do not depend on a template parameter
> - Those that do depend on a template parameter
>
> It is up to the provider of a template to ensure that all names that do not depend on a template parameter are visible when the template is used.  
> Moreover, the template provider must ensure that the definition of thetemplate, including the definitions of the members of a class template, are visible when the template is instantiated.
>
> It is up to *users* of a template to ensure that declarations for all functions,types, and operators associated with the types used to instantiate the template are visible.
>
> Both of these requirements are easily satisfied by well-structured programs that make appropriate use of headers.  
> Authors of templates should provide a header that contains the template definition along with declarations for all the names used in the class template or in the definitions of its members.  
> Users of the template must include the header for the template and for any typesused to instantiate that template.

##### 7) Compilation Errors Are Mostly Reported during Instantiation

The fact that code is not generated until a template is instantiated affects when welearn about compilation errors in the code inside the template.  
In general, there are three stages during which the compiler might flag an error.

1. The first stage is when we compile the template itself.  
   The compiler generally can’t find many errors at this stage. The compiler can detect syntax errors—such as forgetting a semicolon or misspelling a variable name—but not much else.
2. The second error-detection time is when the compiler sees a use of the template.  
   At this stage, there is still not much the compiler can check.  
   For a call to a function template, the compiler typically will check that the number of the arguments is appropriate.  
   It can also detect whether two arguments that are supposed to have the same type do so.  
   For a class template, the compiler can check that the right numberof template arguments are provided but not much more.
3. The third time when errors are detected is during instantiation.  
   It is only then that type-related errors can be found.  
   Depending on how the compiler manages instantiation, these errors may be reported at link time.

> ##### Warning
> It is up to the caller to guarantee that the arguments passed to the template support any operations that template uses, and that those operations behave correctly in the context in which the template uses them.

#### 16.1.2 Class Templates

##### 1) Defining a Class Template

```cpp
template <typename T>
class Blob
{
public:
    typedef T value_type;
    typedef typename std::vector<T>::size_type size_type;
    // constructors
    Blob();
    Blob(std::initializer_list<T> il);
    // number of elements in the Blob
    size_type size() const { return data->size(); }
    bool empty() const { return data->empty(); }
    // add and remove elements
    void push_back(const T &t) { data->push_back(t); }
    // move version; see§ 13.6.3 (p. 548)
    void push_back(T &&t) { data->push_back(std::move(t)); }
    void pop_back();
    // element access
    T& back();
    T& operator[](size_type i); // defined in§ 14.5 (p. 566)

private:
    std::shared_ptr<std::vector<T>> data;
    // throws msg if data[i] isn't valid
    void check(size_type i, const std::string &msg) const;
};
```

##### 2) Instantiating a Class Template

As we’ve seen many times, when we use a class template, we must supply extra information.  
We can now see that that extra information is a list of **explicit template arguments** that are bound to the template’s parameters.  
The compiler uses these template arguments to instantiate a specific class from the template.

For providing the element type `int`  
`Blob<int> ia;`  
the compiler will instantiate a class that is equivalent to

```cpp
template <>
class Blob<int>
{
    typedef typename std::vector<int>::size_type size_type;
    Blob();
    Blob(std::initializer_list<int> il);
    // ...
    int& operator[](size_type i);
private:
    std::shared_ptr<std::vector<int>> data;
    void check(size_type i, const std::string &msg) const;
};
```

When the compiler instantiates a class from our Blob template, it rewrites the Blobtemplate, replacing each instance of the template parameter T by the given templateargument, which in this case is int.

> ##### Note
> Each instantiation of a class template constitutes an independent class.  
> The type `Blob<string>` has no relationship to, or any special access to, the members of any other `Blob` type.

##### 3) References to a Template Type in the Scope of the Template

In order to read template class code, it can be helpful to remember that the name of a class template is not the name of a type.  
A class template is used toinstantiate a type, and an instantiated type always includes template argument(s).

##### 4) Member Functions of Class Templates

A member function defined outside the class template body starts with the keyword `template` followed by the class’ template parameter list.

##### 5) The `check` and Element Access Members

```cpp
template <typename T>
void  Blob<T>::check(size_type i, const std::string &msg) const
{
    if (i >= data->size())
        throw std::out_of_range(msg);
}

template <typename T>
T& Blob<T>::back()
{
    check(0, "back on empty Blob");
    return data->back();
}

template <typename T>
T& Blob<T>::operator[](size_type i)
{
    // if i is too big, check will throw, preventing access to a nonexistent element
    check(i, "subscript out of range");
    return (*data)[i];
}

template <typename T>
void Blob<T>::pop_back()
{
    check(0, "pop_back on empty Blob");
    data->pop_back();
}
```

##### 6) `Blob` Constructors

```cpp
template <typename T>
Blob<T>::Blob(): data(std::make_shared<std::vector<T>>()) { }

template <typename T>
Blob<T>::Blob(std::initializer_list<T> il):
    data(std::make_shared<std::vector<T>>(il)) { }
```

##### 7) Instantiation of Class-Template Member Functions

> ##### Note
> By default, a member function of a class template is instantiated only if the program uses that member function.

If a member function isn’t used, it is not instantiated.  
The fact that members are instantiated only if we use them lets us instantiate a class with a type that may not meet the requirements for some of the template’s operations.

##### 8) Simplifying Use of a Template Class Name Inside Class Code

There is one exception to the rule that we must supply template arguments when weuse a class template type.  
Inside the scope of the class template itself, we may usethe name of the template without arguments.

##### 9) Using a Class Template Name outside the Class Template Body

When we define members outside the body of a class template, we must remember that we are not in the scope of the class until the class name is seen

```cpp
// postfix: increment/decrement the object but return the unchanged value
template <typename T>
BlobPtr<T> BlobPtr<T>::operator++(int)
{
    // no check needed here; the call to prefix increment will do the check
    BlobPtr ret = *this;    // save the current value
    ++*this;                // advance one element; prefix ++ checks the increment
    return ret;             // return the saved state
}
```

> ##### Note
> Inside the scope of a class template, we may refer to the template without specifying template argument(s).

##### 10) Class Templates and Friends

When a class contains a friend declaration, the class and the friend can independently be templates or not.  
A class template that has a nontemplate friend grants that friend access to all the instantiations of the template.  
When the friend is itself a template, the class granting friendship controls whether friendship includes all instantiations of the template or only specific instantiation(s).

##### 11) One-to-One Friendship

The most common form of friendship from a class template to another template (classor function) establishes friendship between corresponding instantiations of the classand its friend.

In order to refer to a specific instantiation of a template (class or function) we must first declare the template itself.  
A template declaration includes the template’stemplate parameter list:

```cpp
//forward declarations needed for friend declarations inBlob
template <typename> class BlobPtr;
template <typename> class Blob; // needed for parameters in operator==
template <typename T>
bool operator==(const Blob<T>&, const Blob<T>&);

template <typename T>
class Blob
{
    // each instantiation of Blob grants access to the version of
    // BlobPtr and the equality operator instantiated with the same type
    friend class BlobPtr<T>;
    friend bool operator==<T>(const Blob<T>&, const Blob<T>&);
    // other members as in§ 12.1.1 (p. 456)
};
```

We start by declaring that `Blob`, `BlobPtr`, and `operator==` are templates.  
These declarations are needed for the parameter declaration in the operator== function and the friend declarations in Blob.  
The friend declarations use Blob’s template parameter as their own template argument.  
Thus, the friendship is restricted to those instantiations of BlobPtr and the equality operator that are instantiated with the same type.

##### 12) General and Specific Template Friendship

A class can also make every instantiation of another template its friend, or it may limit friendship to a specific instantiation:

```cpp
// forward declaration necessary to befriend a specific instantiation of a template
template <typename T> class Pal;

class C // C is an ordinary, nontemplate class
{
    friend class Pal<C>;    // Pal instantiated with class C is a friend to C
    // all instances of Pal2 are friends to C;
    // no forward declaration required when we befriend all instantiations
    template <typename T> friend class Pal2;
};

template <typename T>
class C2 // C2 is itself a class template
{
    // each instantiation of C2 has the same instance of Palas a friend
    friend class Pal<T>;    // a template declaration for Pal must be in scope
    // all instances of Pal2 are friends of each instance of C2, prior  declaration needed
    template <typename X> friend class Pal2;
    // Pal3 is a nontemplate class that is a friend of every instance of C2
    friend class Pal3;  // prior declaration forPal3not needed
};
```

To allow all instantiations as friends, the friend declaration must use template parameter(s) that differ from those used by the class itself.

##### 13) Befriending the Template’s Own Type Parameter

`C++11` We can make a template type parameter a friend:

```cpp
template <typename Type>
class Bar
{
    friend Type; // grants access to the type used to instantiate Bar
    //...
};
```

##### 14) Template Type Aliases

An instantiation of a class template defines a class type, and as with any other class type, we can define a typedef that refers to that instantiated class:  
`typedef Blob<string> StrBlob;`  
Because a template is not a type,we cannot define a typedef that refers to a template.  
That is, there is no way to define a typedef that refers to Blob<T>.

`C++11` However, the new standard lets us define a type alias for a class template:

```cpp
template<typename T> using twin = pair<T, T>;
twin<string> authors;   // authors is a pair<string, string>
```

Here we’ve defined twin as a synonym for pairs in which the members have the same type.  

When we define a template type alias, we can fix one or more of the template parameters:

```cpp
template <typename T> using partNo = pair<T, unsigned>;
partNo<string> books;   // booksis apair<string, unsigned>
partNo<Vehicle> cars;   // carsis apair<Vehicle, unsigned>
partNo<Student> kids;   // kidsisapair<Student, unsigned>
```

##### 15) `static` Members of Class Templates

Like any other class, a class template can declare static members:

```cpp
template <typename T>
class Foo
{
public:
    static std::size_t count() { return ctr; }
    // other interface members

private:
    static std::size_t ctr;
    // other implementation members
};
```

Here `Foo` is a class template that has a `public static` member function named `count` and a `private static` data member named `ctr`.  
Each instantiation of Foo has its own instance of the static members.  
That is, for any given type `X`, there isone `Foo<X>::ctr` and one `Foo<X>::count` member.  
All objects of type `Foo<X>` share the same ctr object and count function.

#### 16.1.3 Template Parameters

##### 1) Template Parameters and Scope

Template parameters follow normal scoping rules.  
The name of a template parameter can be used after it has been declared and until the end of the template declaration ordefinition.  
As with any other name, a template parameter hides any declaration of thatname in an outer scope.  
Unlike most other contexts, however, a name used as a template parameter may not be reused within the template

```cpp
typedef double A;
template <typename A, typename B>
void f(A a, B b)
{
    A tmp = a;  // tmp has same type as the template parameter A, not double
    double B;   // error: redeclares template parameter B
}

// error: illegal reuse of template parameter name V
template <typename V, typename V> // ..
```

##### 2) Template Declarations

A template declaration must include the template parameters.

> ##### Best Practices
> For reasons we’ll explain in § 16.3 (p. 698), declarations for all the templates needed by a given file usually should appear together at the beginning of a file before any code that uses those names.

##### 3) Using Class Members That Are Types

Assuming T is a template type parameter, When the compiler sees code such as `T::mem` it won’t know until instantiation time whether mem is a type or a static data member.  
However, in order to process the template, the compiler must know whether a name represents a type.  

By default, the language assumes that a name accessed through the scope operatoris not a type.  
As a result, if we want to use a type member of a template type parameter, we must *explicitly* tell the compiler that the name is a type.  
We do so by using the keyword `typename`

```cpp
template <typename T>
typename T::value_type top(const T& c)
{
    if (!c.empty())
        return c.back();
    else
        return typename T::value_type();
}
```

> ##### Note
> When we want to inform the compiler that a name represents a type, wemust use the keyword typename, not class.

##### 4) Default Template Arguments

We can supply **default template arguments**.  
`C++11` We can supply default arguments for both function and class templates.

```cpp
// comparehas a default template argument, less<T>
// and a default function argument, F()
template <typename T, typename F = less<T>>
int compare(const T &v1, const T &v2, F f = F())
{
    if (f(v1, v2)) return -1;
    if (f(v2, v1)) return 1;
    return 0;
}
```

Here we’ve given our template a second type parameter, named F, that represents the type of a callable object and defined a new function parameter, f, that will be bound to a callable object.

We’ve also provided defaults for this template parameter and its corresponding function parameter.  
The default template argument specifies that compare will usethe library less function-object class, instantiated with the same type parameter as compare.  
The default function argument says that f will be a default-initialized object of type F.

When users call this version of compare, they may supply their own comparison operation but are not required to do so:

```cs
bool i = compare(0, 42); // usesless; i is -1
// result depends on the isbns in item1 and item2
Sales_data item1(cin), item2(cin);
bool j = compare(item1, item2, compareIsbn);
```

The first call uses the default function argument, which is a default-initialized object oftype less<T>.  
In this call, T is int so that object has type `less<int>`.  
This instantiation of compare will use `less<int>` to do its comparisons.

In the second call, we pass compareIsbn and two objects oftype Sales_data.  
When compare is called with three arguments, the type of the third argument must be a callable object that returns a type that is convertible tobool and takes arguments of a type compatible with the types of the first two arguments.  
As usual, the types of the template parameters are deduced from their corresponding function arguments.  
In this call, the type of T is deduced as Sales_data and F is deduced as the type of compareIsbn.

As with function default arguments, a template parameter may have a defaultargument only if all of the parameters to its right also have default arguments.

##### 5) Template Default Arguments and Class Templates

Whenever we use a class template, we must always follow the template’s name with brackets.  
The brackets indicate that a class must be instantiated from a template.  
In particular, if a class template provides default arguments for all of its template parameters, and we want to use those defaults, we must put an empty bracket pairfollowing the template’s name.

#### 16.1.4 Member Templates

A class—either an ordinary class or a class template—may have a member functionthat is itself a template.  
Such members are referred to as **member templates**.

Member templates may not be virtual.

##### 1) Member Templates of Ordianary (Nontemplate) Classes

```cs
// function-object class that calls delete on a given pointer
class DebugDelete
{
public:
    DebugDelete(std::ostream &s = std::cerr): os(s) { }
    // as with any function template, the type of T is deduced by the compiler
    template <typename T> void operator()(T *p) const
    {
        os << "deleting unique_ptr" << std::endl;
        delete p;
    }

private:
    std::ostream &os;
};

double* p = new double;
DebugDelete d;      // an object that can act like adelete expression
d(p);               // calls DebugDelete::operator()(double*), which deletes p
int* ip = new int;  // calls operator()(int*) on a emporary DebugDelete object
DebugDelete()(ip);
```

##### 2) Member Templates of Class Templates

Both the class and the member have their own, independent, template parameters.

```cpp
template <typename T> class Blob
{
    template <typename It> Blob(It b, It e);
    // ...
};
```

Unlike ordinary function members of class templates, member templates are function templates.

When we define a member template outside the body of a class template,we must provide the template parameter list for the class template and for thefunction template.

```cpp
template <typename T>   // type parameter for the class
template <typename It>  // type parameter for the constructor
Blob<T>::Blob(It b, I   t e): data(std::make_shared<std::vector<T>>(b, e)) {}
```

##### 3) Instantiation and Member Templates

To instantiate a member template of a class template, we must supply arguments for the template parameters for both the class and the function templates.  
As usual, argument(s) for the class template parameter(s) are determined by the type of the object through which we call the member template.  
Also as usual, the compiler typically deduces template argument(s) for the member template’s own parameter(s) from the arguments passed in the call

```cs
int ia[] = {0,1,2,3,4,5,6,7,8,9};
vector<long> vi = {0,1,2,3,4,5,6,7,8,9};
list<const char*> w = {"now", "is", "the", "time"};
// instantiates the Blob<int> class
// and the Blob<int> constructor that has two int* parameters
Blob<int> a1(begin(ia), end(ia));
// instantiates the Blob<int> constructor that has
// two vector<long>::iterator parameters
Blob<int> a2(vi.begin(), vi.end());
// instantiates the Blob<string> class and the Blob<string>
// constructor that has two(list<const char*>::iterator parameters
Blob<string> a3(w.begin(), w.end());
```

#### 16.1.5 Controlling Instantiations

The fact that instantiations are generated when a template is used means that the same instantiation may appear in multiple object files.  
When two ormore separately compiled source files use the same template with the same template arguments, there is an instantiation of that template in each of those files.

In large systems, the overhead of instantiating the same template in multiple filescan become significant.

`C++11` We can avoid this overhead through an **explicit instantiation**.  
An explicit instantiation has the form

```cpp
extern template declaration;    // instantiation declaration
template declaration;           // instantiation definition
```

where *declaration* is a class or function declaration in which all the template parameters are replaced by the template arguments.  
For example,

```cpp
// instantion declaration and definition
extern template class Blob<string>;             // declaration
template int compare(const int&, const int&);   // definition
```

When the compiler sees an extern template declaration, it will not generate code for that instantiation in that file.  
Declaring an instantiation as extern is a promise that there will be a nonextern use of that instantiation elsewhere in the program.  
There may be several extern declarations for a given instantiation but there must be exactly one definition for that instantiation.

Because the compiler automatically instantiates a template when we use it, the extern declaration must appear before any code that uses that instantiation:

```cs
// Application.cc
// these template types must be instantiated elsewhere in the program
extern template class Blob<string>;
extern template int compare(const int&, const int&);
Blob<string> sa1, sa2;          // instantiation will appear elsewhere
// Blob<int> and itsinitializer_listconstructor instantiated in this file
Blob<int> a1 = {0,1,2,3,4,5,6,7,8,9};
Blob<int> a2(a1);               // copy constructor instantiated in this file
int i = compare(a1[0], a2[0]);  // instantiation will appear elsewhere
```

The file Application.o will contain instantiations for `Blob<int>`, along with the initializer_list and copy constructors for that class.  
The `compare<int>` function and `Blob<string>` class will not be instantiated in that file.  
There must be definitions of these templates in some other file in the program:

```cs
// templateBuild.cc
// instantiation file must provide a (nonextern) definition for every
// type and function that other files declare as extern
template int compare(const int&, const int&);
template  class  Blob<string>;  // instantiates all members of the  class template
```

When the compiler sees an instantiation definition (as opposed to a declaration), it generates code.  
Thus, the file templateBuild.o will contain the definitions for compare instantiated with int and for the `Blob<string>` class.  
When we build theapplication, we must link templateBuild.o with the Application.o files.

> ##### Warning
> There must be an explicit instantiation definition somewhere in the programb for every instantiation declaration.

##### 1) Instantiation Definitions Instantiate All Members

An instantiation definition for a class template instantiates all the members of that template including inline member functions.  
When the compiler sees an instantiation definition it cannot know which member functions the program uses.  
Hence, unlike the way it handles ordinary class template instantiations, the compiler instantiates all themembers of that class.  
Even if we do not use a member, that member will beinstantiated.  
Consequently, we can use explicit instantiation only for types that can beused with all the members of that template.  

> ##### Note
> An instantiation definition can be used only for types that can be used withevery member function of a class template.

#### 16.1.6 Efficiency and Flexibility

The library smart pointer types offer a good illustration of design choices faced by designers of templates.

The obvious difference between `shared_ptr` and `unique_ptr` is the strategy they use in managing the pointer they hold—one class gives us shared ownership; the other owns the pointer that it holds.  
This difference is essential to what these classes do.

These classes also differ in how they let users override their default deleter.  
We can easily override the deleter of a shared_ptr by passing a callable object when we create or reset the pointer.  
In contrast, the type of the deleter is part of the type of a unique_ptr object.  
Users must supply that type as an explicit template argument when they define a unique_ptr.  
As a result, it is more complicated for users of unique_ptr to provide their own deleter.

The difference in how the deleter is handled is incidental to the functionality of these classes.  
However, as we’ll see, this difference in implementation strategy may have important performance impacts.

##### 1) Binding the Deleter at Run Time

Although we don’t know how the library types are implemented, we can infer that shared_ptr must access its deleter indirectly.  
That is, the deleter must be stored asa pointer or as a class (such as `function`) that encapsulates a pointer.

We can be certain that shared_ptr does not hold the deleter as a direct member, because the type of the deleter isn’t known until run time.  
Indeed, we can change the type of the deleter in a given shared_ptr during that shared_ptr’s lifetime.  
We can construct a shared_ptr using a deleter of one type, and subsequently use reset to give that same shared_ptr a different type of deleter.  
In general, we cannot have a member whose type changes at run time.  
Hence, the deleter must bestored indirectly.

To think about how the deleter must work, let’s assume that shared_ptr stores the pointer it manages in a member named p, and that the deleter is accessed through a member named del.  
The shared_ptr destructor must include astatement such as

```cpp
// value of delknown only at run time; call through a pointer
del ? del(p) : delete p; // del(p)requires run-time jump todel's location
```

Because the deleter is stored indirectly, the call del(p) requires a run-time jump tothe location stored in del to execute the code to which del points.

##### 2) Binding the Deleter at Compile Time

Now, let’s think about how unique_ptr might work.  
In this class, the type of the deleter is part of the type of the unique_ptr.  
That is, unique_ptr has two template parameters, one that represents the pointer that the unique_ptr managesand the other that represents the type of the deleter.  
Because the type of the deleter is part of the type of a unique_ptr, the type of the deleter member is known atcompile time.  
The deleter can be stored directly in each unique_ptr object.

The unique_ptr destructor operates similarly to its shared_ptr counterpart in that it calls a user-supplied deleter or executes delete on its stored pointer:

```cpp
// del bound at compile time; direct call to the deleter is instantiated
del(p); // no run-time overhead
```

The type of del is either the default deleter type or a user-supplied type.  
It doesn’t matter; either way the code that will be executed is known at compile time.  
Indeed, ifthe deleter is something like our DebugDelete class this call might even be inlined at compile time.

By binding the deleter at compile time, unique_ptr avoids the run-time cost of an indirect call to its deleter.  
By binding the deleter at run time, shared_ptr makes iteasier for users to override the deleter.

### 16.2 Template Argument Deduction

The process of determining thetemplate arguments from the function arguments is known as **template argument deduction**.  
During template argument deduction, the compiler uses types of thearguments in the call to find the template arguments that generate a version of thefunction that best matches the given call.

#### 16.2.1 Conversions and Template Type Parameters

As with a nontemplate function, the arguments we pass in a call to a function template are used to initialize that function’s parameters.  
Function parameters whose type uses a template type parameter have special initialization rules.  
Only a very limited number of conversions are automatically applied to such arguments.  
Rather than converting the arguments, the compiler generates a new instantiation.

As usual, top-level consts in either the parameter or the argumentare ignored.  
The only other conversions performed in a call to a function template are

- const conversions: A function parameter that is a reference (or pointer) to aconst can be passed a reference (or pointer) to a nonconst object.
- Array- or function-to-pointer conversions: If the function parameter is not areference type, then the normal pointer conversion will be applied to argumentsof array or function type.  
  An array argument will be converted to a pointer to itsfirst element.  
  Similarly, a function argument will be converted to a pointer to thefunction’s type.

Other conversions, such as the arithmetic conversions, derived-to-base, and user-defined conversions, are not performed.

As examples, consider calls to the functions `fobj` and `fref`.  
The fobj function copies its parameters, whereas fref’s parameters are references:

```cpp
template <typename T> T fobj(T, T); // arguments are copied
template <typename T> T fref(const T&, const T&);   // references
string s1("a value");
const string s2("another value");
fobj(s1, s2);   // calls fobj(string, string); constis ignored
fref(s1, s2);   // calls fref(const string&, const string&)
                // uses premissible conversion to const on s1
int a[10], b[42];
fobj(a, b); // calls f(int*, int*)
fref(a, b); // error: array types don't match
```

In the first pair of calls, we pass a string and a const string.  
Even though these types do not match exactly, both calls are legal.  
In the call to fobj, the argumentsare copied, so whether the original object is const doesn’t matter. In the call to fref, the parameter type is a reference to const.  
Conversion to const for areference parameter is a permitted conversion, so this call is legal.

In the next pair of calls, we pass array arguments in which the arrays are different sizes and hence have different types.  
In the call to fobj, the fact that the array types differ doesn’t matter.  
Both arrays are converted to pointers.  
The template parametertype in fobj is int*.  
The call to fref, however, is illegal.  
When the parameter is a reference, the arrays are not converted to pointers.  
The types of aand b don’t match, so the call is in error.

> ##### Note
> `const` conversions and array or function to pointer are the only automatic conversions for arguments to parameters with template types.

##### 1) Function Parameters That Use the Same Template Parameter Type

A template type parameter can be used as the type of more than one functionparameter.  
Because there are limited conversions, the arguments to such parameters must have essentially the same type.  
If the deduced types do not match, then the callis an error.  
For example, our compare function takes two constT& parameters.  
Its arguments must have essentially the same type:  
`long lng;`  
`compare(lng, 1024); // error: cannot instantiatecompare(long, int)`

If we want to allow normal conversions on the arguments, we can define the function with two type parameters:

```cpp
// argument types can differ but must be compatible
template <typename A, typename B>
int flexibleCompare(const A& v1, const B& v2)
{
    if (v1 < v2) return -1;
    if (v2 < v1) return 1;
    return 0;
}
```

##### 2) Normal Conversions Apply for Ordinary Arguments

A function template can have parameters that are defined using ordinary types—that is, types that do not involve a template type parameter.  
Such arguments have nospecial processing; they are converted as usual to the corresponding type of theparameter. 

> ##### Note
> Normal conversions are applied to arguments whose type is not a template parameter.

#### 16.2.2 Function-Template Explicit Arguments

In some situations, it is not possible for the compiler to deduce the types of thetemplate arguments.  
In others, we want to allow the user to control the template instantiation.  
Both cases arise most often when a function return type differs from anyof those used in the parameter list.

##### 1) Specifying an Explicit Template Argument

As an example in which we want to let the user specify which type to use, we’ll define a function template named sum that takes arguments of two different types.  
We’d like to let the user specify the type of the result.  
That way the user can choose whatever precision is appropriate.

We can let the user control the type of the return by defining a third template parameter to represent the return type:

```cpp
// T1 cannot be deduced: it doesn't appear in the function parameter list
template <typename T1, typename T2, typename T3>
T1 sum(T2, T3);
```

In this case, there is no argument whose type can be used to deduce the type of T1. 
The caller must provide an explicit template argument for this parameter on each call to sum.

We supply an explicit template argument to a call the same way that we define an instance of a class template.  
Explicit template arguments are specified inside angle brackets after the function name and before the argument list:

```cpp
// T1 is explicitly specified; T2 and T3 are inferred from the argument types
auto val3 = sum<long long>(i, lng); // long long sum(int, long)
```

This call explicitly specifies the type for T1.  
The compiler will deduce the types for T2 and T3 from the types of i and lng.

Explicit template argument(s) are matched to corresponding template parameter(s)from left to right; the first template argument is matched to the first template parameter, the second argument to the second parameter, and so on.  
An explicit template argument may be omitted only for the trailing (right-most) parameters, and then only if these can be deduced from the function parameters.  
If our sum functionhad been written as

```cpp
// poor design: users must explicitly specify all three template parameters
template <typename T1, typename T2, typename T3>
T3 alternative_sum(T2, T1);
```

then we would always have to specify arguments for all three parameters:

```cpp
// error: can't infer initial template parameters
auto val3 = alternative_sum<long long>(i, lng);
// ok: all three parameters are explicitly specified
auto val2 = alternative_sum<long long, int, long>(i, lng);
```

##### 2) Normal Conversions Apply for Explicitly Specified Arguments

For the same reasons that normal conversions are permitted for parameters that are defined using ordinary types, normal conversions also apply for arguments whose template type parameter is explicitly specified:

```cpp
long lng;
compare(lng, 1024);         // error: template parameters don't match
compare<long>(lng, 1024);   // ok: instantiates compare(long, long)
compare<int>(lng, 1024);    // ok: instantiates compare(int, int)
```

As we’ve seen, the first call is in error because the arguments to compare must have the same type.  
If we explicitly specify the template parameter type, normal conversions apply.  
Thus, the call to `compare<long>` is equivalent to calling afunction taking two const long& parameters.  
The int parameter is automatically converted to long.  
In the second call, T is explicitly specified as int, so lng isconverted to int.

#### 16.2.3 Trailing Return Types and Type Transformation

Using an explicit template argument to represent a template function’s return typeworks well when we want to let the user determine the return type.  
In other cases,requiring an explicit template argument imposes a burden on the user with nocompensating advantage.  
For example, we might want to write a function that takes apair of iterators denoting a sequence and returns a reference to an element in the sequence:

```cs
template <typename It>
??? &fcn(It beg, It end)
{
    // process the range
    return *beg; // return a reference to an element from the range
}
```

We don’t know the exact type we want to return, but we do know that we want that type to be a reference to the element type of the sequence we’re processing:

```cs
vector<int> vi = {1,2,3,4,5};
Blob<string> ca = { "hi", "bye" };
auto &i = fcn(vi.begin(), vi.end()); // fcnshould return int&
auto &s = fcn(ca.begin(), ca.end()); // fcnshould return string&
```

`C++11` Here, we know that our function will return `*beg`, and we know that we can use `decltype(*beg)` to obtain the type of that expression.  
However, beg doesn’t exist until the parameter list has been seen.  
To define this function, we must use a trailing return type.  
Because a trailing return appears after the parameterlist, it can use the function’s parameters:

```cs
// a trailing return lets us declare the return type after the parameter list is seen
template <typename It>
auto fcn(It beg, It end) -> decltype(*beg)
{
    // process the range
    return *beg;    // return a reference to an element from the range
}
```

Here we’ve told the compiler that fcn’s return type is the same as the type returned by dereferencing its beg parameter.  
The dereference operator returns an lvalue, so the type deduced by decltype is a reference to the type of the element that beg denotes.  
Thus, if fcn is called on a sequence of strings, the return type will be string&.  
If the sequence is int, the return will be int&.

##### 1) The Type Transformation Library Template Classes

Sometimes we do not have direct access to the type that we need.  
For example, we might want to write a function similar to fcn that returns an element by value, rather than a reference to an element.

The problem we face in writing this function is that we know almost nothing aboutthe types we’re passed.  
In this function, the only operations we know we can use areiterator operations, and there are no iterator operations that yield elements (asopposed to references to elements).

To obtain the element type, we can use a library **type transformation** template.  
These templates are defined in the type_traits header.  
In general the classes intype_traits are used for so-called template metaprogramming, a topic that isbeyond the scope of this Primer.  
However, the type transformation templates areuseful in ordinary programming as well.  
These templates are described in Table 16.1and we’ll see how they are implemented in § 16.5 (p. 710).

###### Standard Type Transformation Templates

| For `Mod<T>`, where `Mod` is | If `T` is               | `Mod<T>::type` is |
| ---------------------------- | ----------------------- | ----------------- |
| remove_reference             | X& or X&&               | X                 |
|                              | otherwise               | T                 |
| add_const                    | X&, const X or function | T                 |
|                              | otherwise               | const T           |
| add_lvalue_reference         | X&                      | T                 |
|                              | X&&                     | X&                |
|                              | otherwise               | T&                |
| add_rvalue_reference         | X& or X&&               | T                 |
|                              | otherwise               | T&&               |
| remove_pointer               | X*                      | X                 |
|                              | otherwise               | T                 |
| add_pointer                  | X& or X&&               | X*                |
|                              | otherwise               | T*                |
| make_signed                  | unsigned X              | X                 |
|                              | otherwise               | T                 |
| make_unsigned                | signed type             | unsigned T        |
|                              | otherwise               | T                 |
| remove_extent                | X[n]                    | X                 |
|                              | otherwise               | T                 |
| remove_all_extents           | X[n1][n2]...            | X                 |
|                              | otherwise               | T                 |

In this case, we can use remove_reference to obtain the element type.  
There move_reference template has one template type parameter and a (public)type member named type.  
If we instantiate remove_reference with a referencetype, then type will be the referred-to type.  
For example, if we instantiateremove_reference<int&>, the type member will be int.  
Similarly, if we instantiate remove_reference<string&>, type will be string, and so on.  
More generally, given that beg is an iterator:  
`remove_reference<decltype(*beg)>::type`  
will be the type of the element to which beg refers: decltype(*beg) returns thereference type of the element type.  
remove_reference::type strips off thereference, leaving the element type itself.

Usingremove_reference and a trailing return with decltype, we can write our function to return a copy of an element’s value:

```cpp
// must use typename to use a type member of a template parameter
template <typename It>
auto fcn2(It beg, It end) -> 
    typename remove_reference<decltype(*beg)>::type
{
    // process the range
    return *beg;    // return a copy of an element from the range
}
```

Note that type is member of a class that depends on a template parameter.  
As a result, we must use typename in the declaration of the return type to tell the compiler that type represents a type.

Each of the type transformation templates described in Table 16.1 works similarly toremove_reference.  
Each template has a public member named type thatrepresents a type.  
That type may be related to the template’s own template typeparameter in a way that is indicated by the template’s name.  
If it is not possible (ornot necessary) to transform the template’s parameter, the type member is thetemplate parameter type itself.  
For example, if T is a pointer type, thenremove_pointer<T>::type is the type to which T points.  
If T isn’t a pointer, thenno transformation is needed.  
In this case, type is the same type as T.

#### 16.2.4 Function Pointers and Argument Deduction

When we initialize or assign a function pointer from a functiontemplate, the compiler uses the type of the pointer to deduce the templateargument(s).

```cpp
template<typename T> int compare(const T&, const T&);
// pf1 points to the instantiation int compare(const T&, const T&)
int (*pf1)(const int&, const int&) = compare;
```

The type of the parameters in pf1 determines the type of the template argument forT.  
The template argument for T is int.  
The pointer pf1 points to the instantiation ofcompare with T bound to int.  
It is an error if the template arguments cannot bedetermined from the function pointer type:

```cpp
// overloaded versions of func; each takes a different function pointer type
void func(int(*)(const string&, const string&));
void func(int(*)(const int&, const int&));
func(compare); // error: which instantiation ofcompare?
```

The problem is that by looking at the type of func’s parameter, it is not possible todetermine a unique type for the template argument.  
The call to func could instantiatethe version of compare that takes ints or the version that takes strings.  
Becauseit is not possible to identify a unique instantiation for the argument to func, this callwon’t compile.

We can disambiguate the call to func by using explicit template arguments:

```cpp
// ok: explicitly specify which version ofcompareto instantiate
func(compare<int>); // passingcompare(const int&, const int&)
```

This expression calls the version of func that takes a function pointer with twoconst int& parameters.

> ##### Note
> When the address of a function-template instantiation is taken, the contextmust be such that it allows a unique type or value to be determined for eachtemplate parameter.

#### 16.2.5 Template Argument Deduction and References

In order to understand type deduction from a call to a function such as  
`template <typename T> void f(T &p);`  
in which the function’s parameter p is a reference to a template type parameter T, itis important to keep in mind two points:

1. Normal reference binding rules apply;
2. consts are low level, not top level.

##### 1) Type Deduction from Lvalue Reference Function Parameters

When a function parameter is an ordinary (lvalue) reference to a template typeparameter (i.e., that has the form T&), the binding rules say that we can pass only anlvalue (e.g., a variable or an expression that returns a reference type).  
That argumentmight or might not have a const type.  
If the argument is const, then T will bededuced as a const type:

```cs
template <typename T> void f1(T&);  // argument must be an lvalue
// calls tof1use the referred-to type of the argument as the template parameter type
f1(i);  //iis anint; template parameterTis int
f1(ci); //ciis aconst int; template parameterTisconst int
f1(5);  //error: argument to a&parameter must be an lvalue
```

If a function parameter has type const T&, normal binding rules say that we canpass any kind of argument—an object (const or otherwise), a temporary, or a literalvalue.  
When the function parameter is itself const, the type deduced for T will not bea const type.  
The const is already part of the function parameter type;  
therefore, itdoes not also become part of the template parameter type:

```cs
template <typename T> void f2(const T&);    // can take an rvalue
// parameter inf2isconst&;constin the argument is irrelevant
// in each of these three calls,f2's function parameter is inferred asconst int&
f2(i);  // iis anint; template parameterTisint
f2(ci); // ciis aconst int, but template parameterTisint
f2(5);  // aconst &parameter can be bound to an rvalue;Tisint
```

##### 2) Type Deduction from Rvalue Reference Function Parameters

When a function parameter is an rvalue reference (i.e., has theform T&&), normal binding rules say that we can pass an rvalue to this parameter.  
When we do so, type deduction behaves similarly to deduction for an ordinary lvaluereference function parameter.  
The deduced type for T is the type of the rvalue:

```cpp
template <typename T> void f3(T&&);
f3(42); // argument is an rvalue of typeint; template parameterTisint
```

##### 3) Reference Collapsing and Rvalue Reference Parameters

Assuming `i` is an int object, we might think that a call such as f3(i) would beillegal.  
After all, i is an lvalue, and normally we cannot bind an rvalue reference to anlvalue.  
However, the language defines two exceptions to normal binding rules thatallow this kind of usage.  
These exceptions are the foundation for how library facilitiessuch as move operate.

The first exception affects how type deduction is done for rvalue reference parameters.  
When we pass an lvalue (e.g., i) to a function parameter that is anrvalue reference to a template type parameter (e.g, T&&), the compiler deduces thetemplate type parameter as the argument’s lvalue reference type.  
So, when we callf3(i), the compiler deduces the type of T as int&, not int.

DeducingT as int& would seem to mean that f3’s function parameter would be anrvalue reference to the type int&.  
Ordinarily, we cannot (directly) define a referenceto a reference.  
However, it is possible to do so indirectly through atype alias or through a template type parameter.

In such contexts, we see the second exception to the normal binding rules: If weindirectly create a reference to a reference, then those references “collapse.”  
In all butone case, the references collapse to form an ordinary lvalue reference type.  
The newstandard, expanded the collapsing rules to include rvalue references.  
References collapse to form an rvalue reference only in the specific case of an rvalue reference toan rvalue reference.  
That is, for a given type X:

- X& &, X& &&, and X&& & all collapse to type X&
- The type X&& && collapses to X&&

> ##### Note
> Reference collapsing applies only when a reference to a reference is created indirectly, such as in a type alias or a template parameter.

The combination of the reference collapsing rule and the special rule for type deduction for rvalue reference parameters means that we can call f3 on an lvalue.  
When we pass an lvalue to f3’s (rvalue reference) function parameter, the compiler will deduce T as an lvalue reference type:

```cs
f3(i);  // argument is an lvalue; template parameterTisint&
f3(ci); // argument is an lvalue; template parameterTisconst int&
```

When a template parameter T is deduced as a reference type, the collapsing rule saysthat the function parameter T&& collapses to an lvalue reference type.  
For example,the resulting instantiation for f3(i) would be something like

```cs
// invalid code, for illustration purposes only
void f3<int&>(int& &&); // whenTisint&, function parameter isint& &&
```

The function parameter in f3 is T&& and T is int&, so T&& is int& &&, which collapses to int&.  
Thus, even though the form of the function parameter in f3 is anrvalue reference (i.e., T&&), this call instantiates f3 with an lvalue reference type(i.e., int&):  
`void  f3<int&>(int&);  //  whenTisint&,  function  parameter  collapses  toint&`  
There are two important consequences from these rules:

- A function parameter that is an rvalue reference to a template type parameter(e.g., T&&) can be bound to an lvalue; and
- If the argument is an lvalue, then the deduced template argument type will bean lvalue reference type and the function parameter will be instantiated as an(ordinary) lvalue reference parameter (T&)

It is also worth noting that by implication, we can pass any type of argument to aT&& function parameter.  
A parameter of such a type can (obviously) be used withrvalues, and as we’ve just seen, can be used by lvalues as well.

> ##### Note
> An argument of any type can be passed to a function parameter that is anrvalue reference to a template parameter type (i.e., T&&).  
> When an lvalue ispassed to such a parameter, the function parameter is instantiated as anordinary, lvalue reference (T&).

##### 4) Writing Template Functions with Rvalue Reference Parameters

The fact that the template parameter can be deduced to a reference type can have surprising impacts on the code inside the template:

```cpp
template <typename T> void f3(T&& val)
{
    T t = val;  // copy or binding a reference?
    t = fcn(t); // does the assignment change onlytorvalandt?
    if (val == t) { /* ... */ } // alwaystrueifTis a reference type
}
```

When we call f3 on an rvalue, such as the literal 42, T is int.  
In this case, the localvariable t has type int and is initialized by copying the value of the parameter val.  
When we assign to t, the parameter val remains unchanged.

On the other hand, when we call f3 on the lvalue i, then T is int&.  
When wedefine and initialize the local variable t, that variable has type int&.  
The initializationof t binds t to val. When we assign to t, we change val at the same time.  
In thisinstantiation of f3, the if test will always yield true.

It is surprisingly hard to write code that is correct when the types involved might beplain (nonreference) types or reference types (although the type transformationclasses such as remove_reference can help).

In practice, rvalue reference parameters are used in one of two contexts: Either thetemplate is forwarding its arguments, or the template is overloaded.  
We’ll look atforwarding in § 16.2.7 (p. 692) and at template overloading in § 16.3 (p. 694).

For now, it’s worth noting that function templates that use rvalue references oftenuse overloading in the same way as we saw in § 13.6.3 (p. 544):

```cpp
template <typename T> void f(T&&);          // binds to nonconst rvalues
template <typename T> void f(const  T&);    // lvalues and const rvalues
```

As with nontemplate functions, the first version will bind to modifiable rvalues and thesecond to lvalues or to const rvalues.

#### 16.2.6 Understanding `std::move`

The library move function is a good illustration of a template thatuses rvalue references.  
Fortunately, we can use move without understanding thetemplate mechanisms that it uses.  
However, looking at how move works can helpcement our general understanding, and use, of templates.

In § 13.6.2 (p. 534) we noted that although we cannot directly bind an rvaluereference to an lvalue, we can use move to obtain an rvalue reference bound to anlvalue.  
Because move can take arguments of essentially any type, it should not besurprising that move is a function template.

##### 1) How `std::move` Is Defined

The standard defines move as follows:

```cpp
//for the use of typename in the return type and the cast see§ 16.1.3 (p. 670)
// remove_reference is covered in§ 16.2.3 (p. 684)
template <typename T>typename remove_reference<T>::type&& move(T&& t)
{
    // static_castcovered in§ 4.11.3 (p. 163)
    return static_cast<typenameremove_reference<T>::type&&>(t);
}
```

This code is short but subtle.  
First, move’s function parameter, T&&, is an rvalue reference to a template parameter type.  
Through reference collapsing, this parametercan match arguments of any type.  
In particular, we can pass either an lvalue or anrvalue to move:

```cs
string s1("hi!"), s2;
s2 = std::move(string("bye!")); // ok: moving from an rvalue
s2 = std::move(s1); // ok:  but  after  the  assigments1has  indeterminate value
```

##### 2) How std::move Works

In the first assignment, the argument to move is the rvalue result of the string constructor, string("bye").  
As we’ve seen, when we pass an rvalue to an rvaluereference function parameter, the type deduced from that argument is the referred-totype.  
Thus, in std::move(string("bye!")):

- The deduced type of T is string.
- Therefore, remove_reference is instantiated with string.
- The type member of `remove_reference<string>` is string.
- The return type of move is string&&.
- move’s function parameter, t, has type string&&.

Accordingly, this call instantiates `move<string>`, which is the function  
`string&& move(string &&t)`  
The body of this function returns static_cast<string&&>(t).  
The type of t isalready string&&, so the cast does nothing.  
Therefore, the result of this call is thervalue reference it was given.

Now consider the second assignment, which calls std::move(s1).  
In this call, theargument to move is an lvalue. This time:

- The deduced type of T is string& (reference to string, not plain string).
- Therefore, remove_reference is instantiated with string&.
- The type member of remove_reference<string&> is string,
- The return type of move is still string&&.
- move’s function parameter, t, instantiates as string& &&, which collapses tostring&.

Thus, this call instantiates move<string&>, which is  
`string&& move(string &t)`  
and which is exactly what we’re after—we want to bind an rvalue reference to anlvalue.  
The body of this instantiation returns static_cast<string&&>(t).  
In thiscase, the type of t is string&, which the cast converts to string&&.

##### 3) `static_cast` from an Lvalue to an Rvalue Reference Is Permitted

Ordinarily, a static_cast can perform only otherwise legitimate conversions.  
However, there is again a special dispensation for rvalue references: Even though we cannot implicitly convert an lvalue to an rvalue reference, we canexplicitly cast an lvalue to an rvalue reference using static_cast.

Binding an rvalue reference to an lvalue gives code that operates on the rvaluereference permission to clobber the lvalue.  
There are times, such as in our StrVecreallocate function in § 13.6.1 (p. 533), when we know it is safe to clobber anlvalue.  
By *letting* us do the cast, the language allows this usage.  
By *forcing* us to usea cast, the language tries to prevent us from doing so accidentally.

Finally, although we can write such casts directly, it is much easier to use the librarymove function.  
Moreover, using std::move consistently makes it easy to find theplaces in our code that might potentially clobber lvalues.

#### 16.2.7 Forwarding

Some functions need to forward one or more of their arguments with their typesunchanged to another, forwarded-to, function.  
In such cases, we need to preserveeverything about the forwarded arguments, including whether or not the argumenttype is const, and whether the argument is an lvalue or an rvalue.

As an example, we’ll write a function that takes a callable expression and twoadditional arguments.  
Our function will call the given callable with the other two arguments in reverse order.  
The following is a first cut at our flip function:

```cpp
// template that takes a callable and two parameters
// and calls the given callable with the parameters ''flipped''
// flip1is an incomplete implementation: top-levelconstand references are lost
template <typename F, typename T1, typename T2>
void flip1(F f, T1 t1, T2 t2)
{
    f(t2, t1);
}
```

This template works fine until we want to use it to call a function that has a referenceparameter:

```cpp
void f(int v1, int &v2) // note v2 is a reference
{
    cout << v1 << " " << ++v2 << endl;
}
```

Here `f` changes the value of the argument bound to v2.  
However, if we call fthrough flip1, the changes made by f do not affect the original argument:

```cpp
f(42, i);           // f changes its argument i
flip1(f, j, 42);    // f called throughflip1leavesjunchanged
```

The problem is that j is passed to the t1 parameter in flip1.  
That parameter has isa plain, nonreference type, int, not an int&.  
That is, the instantiation of this call toflip1 is  
`void flip1(void(*fcn)(int, int&), int t1, int t2);`  
The value of j is copied into t1.  
The reference parameter in f is bound to t1, not toj.

##### 1) Defining Function Parameters That Retain Type Information

To pass a reference through our flip function, we need to rewrite our function so thatits parameters preserve the “lvalueness” of its given arguments.  
Thinking ahead a bit,we can imagine that we’d also like to preserve the constness of the arguments aswell.

We can preserve all the type information in an argument by defining its corresponding function parameter as an rvalue reference to a template typeparameter.  
Using a reference parameter (either lvalue or rvalue) lets us preserveconstness, because the const in a reference type is low-level.  
Through referencecollapsing, if we define the function parameters as T1&& and T2&&,we can preserve the lvalue/rvalue property of flip’s arguments:

```cpp
template <typename F, typename T1, typename T2>
void flip2(F f, T1 &&t1, T2 &&t2)
{
    f(t2, t1);
}
```

As in our earlier call, if we call `flip2(f, j, 42)`, the lvalue j is passed to the parameter t1.  
However, in flip2, the type deduced for T1 is int&, which means that the type of t1 collapses to int&.  
The reference t1 is bound to j.  
When `flip2` calls f, the reference parameter v2 in f is bound to t1, which in turn is bound to j.  
When f increments v2, it is changing the value of j.

> ##### Note
> A function parameter that is an rvalue reference to a template type parameter (i.e., `T&&`) preserves the `const`ness and lvalue/rvalue property ofits corresponding argument.

This version of flip2 solves one half of our problem.  
Our flip2 function worksfine for functions that take lvalue references but cannot be used to call a function thathas an rvalue reference parameter.  
For example:

```cpp
void g(int &&i, int& j)
{
    cout << i << " " << j << endl;
}
```

If we try to call g through flip2, we will be passing the parameter t2 to g’s rvaluereference parameter.  
Even if we pass an rvalue to flip2:  
`flip2(g, i, 42); // error: can't initialize int&& from an lvalue`  
what is passed to g will be the parameter named t2 inside flip2.  
A function parameter, like any other variable, is an lvalue expression.  
As aresult, the call to g in flip2 passes an lvalue to g’s rvalue reference parameter.

##### 2) Using `std::forward` to Preserve Type Information in a Call

We can use a new library facility named forward to pass flip2’s parameters in a way that preserves the types of the original arguments.  
Like move, forward isdefined in the utility header.  
Unlike move, forward must be called with an explicit template argument.  
forward returns an rvalue reference to that explicit argument type.  
That is, the return type of `forward<T>` is `T&&`.

`C++11` Ordinarily, we use forward to pass a function parameter that is defined as an rvalue reference to a template type parameter.  
Through reference collapsing on itsreturn type, forward preserves the lvalue/rvalue nature of its given argument:

```cpp
template <typename Type> intermediary(Type &&arg)
{
    finalFcn(std::forward<Type>(arg));
    // ...
}
```

Here we use Type—which is deduced from arg—as forward’s explicit template argument type.  
Because arg is an rvalue reference to a template type parameter, Type will represent all the type information in the argument passed to arg.  
If thatargument was an rvalue, then Type is an ordinary (nonreference) type and `forward<Type>` will return Type&&.  
If the argument was an lvalue, then—throughreference collapsing—Type itself is an lvalue reference type.  
In this case, the return type is an rvalue reference to an lvalue reference type.  
Again through referencecollapsing—this time on the return type—`forward<Type>` will return an lvalue reference type.

> ##### Note
> When used with a function parameter that is an rvalue reference to template type parameter (T&&), forward preserves all the details about anargument’s type.

Using forward, we’ll rewrite our flip function once more:

```cpp
template <typename F, typename T1, typename T2>
void flip(F f, T1 &&t1, T2 &&t2)
{
    f(std::forward<T2>(t2), std::forward<T1>(t1));
}
```

If we call `flip(g, i, 42)`, i will be passed to g as an int& and 42 will be passed as an int&&.

> ##### Note
> As with `std::move`, it’s a good idea not to provide a `using` declaration for `std::forward`.  
> § 18.2.3 (p. 798) will explain why.

--------------------------------------------------------------------------------

### 16.3 Overloading and Templates

Function templates can be overloaded by other templates or by ordinary, nontemplate functions.  
As usual, functions with the same name must differ either as to the numberor the type(s) of their parameters.

// TODO

--------------------------------------------------------------------------------

### 16.4 Variadic Templates

A **variadic template** is a template function or class that can take a varying numberof parameters.  
The varying parameters are known as a **parameter pack**.  
There aretwo kinds of parameter packs:

- a template parameter pack represents zero or more template parameters
- a function parameter pack represents zero or morefunction parameters

```cpp
// Args is a template parameter pack;restis a function parameter pack
// Args represents zero or more template type parameters
// rest represents zero or more function parameters
template <typename T, typename... Args>
void foo(const T &t, const Args& ... rest);

int i = 0;
double d = 3.14;
string s = "how now brown cow";
foo(i, s, 42, d);   // three parameters in the pack
foo(s, 42, "hi");   // two parameters in the pack
foo(d, s);          // one parameter in the pack
foo("hi");          // empty pack
```

the compiler will instantiate four different instances of foo:

```cpp
void foo(const int&, const string&, const int&, const double&);
void foo(const string&, const int&, const char[3]&);
void foo(const double&, const string&);
void foo(const char[3]&);
```

##### 1) The `sizeof...` Operator

`C++11` Use the `sizeof...` operator to know how many elements in a pack.  
Like `sizeof`, `sizeof...` returns a constant expression and does not evaluate its argument.

```cpp
template<typename ... Args> void g(Args ... args)
{
    cout << sizeof...(Args) << endl; // number of type parameters
    cout << sizeof...(args) << endl; // number of function parameters
}
```

#### 16.4.1 Writing a Variadic Function Template

In § 6.2.6 (p. 220) we saw that we can use an `initializer_list` to define a function that can take a varying number of arguments.  
However, the arguments musthave the same type (or types that are convertible to a common type).  
Variadic functions are used when we know neither the number nor the types of the argumentswe want to process.  
As an example, we’ll define a function like our earlier `error_msg` function, only this time we’ll allow the argument types to vary as well.  
We’ll start bydefining a variadic function named print that will print the contents of a given list ofarguments on a given stream.

Variadic functions are often recursive.  
The first call processes thefirst argument in the pack and calls itself on the remaining arguments.  
Our `print` function will execute this way—each call will print its second argument on the stream denoted by its first argument.  
To stop the recursion, we’ll also need to define anonvariadic print function that will take a stream and an object:

```cpp
// function to end the recursion and print the last element
// this function must be declared before the variadic version of print is defined
template<typename T>
ostream &print(ostream &os, const T &t)
{
    return os << t; // no separator after the last element in the pack
}

// this version of print will be called for all but the last element in the pack
template <typename T, typename... Args>
ostream &print(ostream &os, const T &t, const Args&... rest)
{
    os << t << ", ";            // print the first argument
    return print(os, rest...);  // recursive call; print the otherarguments
}
```

The first version of print stops the recursion and prints the last argument in the initial call to print.  
The second, variadic, version prints the argument bound to tand calls itself to print the remaining values in the function parameter pack.

The key part is the call to print inside the variadic function:  
`return print(os, rest...); // recursive call; print the other arguments`  
The variadic version of our print function takes three parameters:

- an ostream&
- a const T&
- a parameter pack

Yet this call passes only two arguments.  
What happens is that the first argument in rest gets bound to t.  
The remaining argumentsin rest form the parameter pack for the next call to print.  
Thus, on each call, the first argument in the pack is removed from the pack and becomes the argument bound to t.  
That is, given:  
`print(cout, i, s, 42); // two parameters in the pack`  
the recursion will execute as follows:

| Call                      |      t      | rest... |
| ------------------------- | :---------: | ------- |
| print(cout, i, s, 42)     |      i      | s, 42   |
| print(cout, s, 42)        |      s      | 42      |
| print(cout, 42) calls the | nonvariadic | version |

The first two calls can match only the variadic version of print because the nonvariadic version isn’t viable.  
These calls pass four and three arguments,respectively, and the nonvariadic print takes only two arguments.

For the last call in the recursion, print(cout, 42), both versions of print are viable.  
This call passes exactly two arguments, and the type of the first argument is `ostream&`.  
Thus, the nonvariadic version of print is viable.

The variadic version is also viable.  
Unlike an ordinary argument, a parameter pack can be empty.  
Hence, the variadic version of print can be instantiated with only two parameters:

- one for the `ostream&` parameter
- the other for the `const T&` parameter.

Both functions provide an equally good match for the call.  
However, a nonvariadic template is more specialized than a variadic template, so the nonvariadic version is chosen for this call.

> ##### Warning
> A declaration for the nonvariadic version of print must be in scope when the variadic version is defined.  
> Otherwise, the variadic function will recurse indefinitely.

#### 16.4.2 Pack Expansion

Aside from taking its size, the only other thing we can do with a parameter pack is to **expand** it.  
When we expand a pack, we also provide a **pattern** to be used on each expanded element.  
Expanding a pack separates the pack into its constituent elements, applying the pattern to each element as it does so.  
We trigger an expansion by putting an ellipsis (...) to the right of the pattern.

For example, our print function contains two expansions:

```cpp
template <typename T, typename... Args>
ostream &print(ostream  &os,  const  T  &t,  const  Args&...  rest) // expand Args
{
    os << t << ", ";
    return print(os, rest...);  // expand rest
}
```

The first expansion expands the template parameter pack and generates the function parameter list for print.  
The second expansion appears in the call to print.  
That pattern generates the argument list for the call to print.

The expansion of Args applies the pattern `const Args&` to each element in the template parameter pack Args.  
The expansion of this pattern is a comma-separated list of zero or more parameter types, each of which will have the form `const type&`.  
For example:  
`print(cout, i, s, 42); // two parameters in the pack`  
The types of the last two arguments along with the pattern determine the types of the trailing parameters.  
This call is instantiated as  
`ostream& print(ostream&, const int&, const string&, const int&);`  
The second expansion happens in the (recursive) call to print.  
In this case, the pattern is the name of the function parameter pack (i.e., rest).  
This pattern expands to a comma-separated list of the elements in the pack.  
Thus, this call is equivalent to  
`print(os, s, 42);`  

##### Understanding Pack Expansions

The expansion of the function parameter pack in print just expanded the pack into its constituent parts.  
More complicated patterns are also possible when we expand afunction parameter pack.  
For example, we might write a second variadic function that calls `debug_rep` on each of its arguments and then calls print to print the resulting strings:

```cpp
// call debug_repon each argument in the call to print
template <typename... Args>
ostream &errorMsg(ostream &os, const Args&... rest)
{
    // print(os, debug_rep(a1), debug_rep(a2), ..., debug_rep(an)
    return print(os, debug_rep(rest)...);
}
```

The call to print uses the pattern debug_rep(rest).  
That pattern says that we want to call debug_rep on each element in the function parameter pack rest.  
The resulting expanded pack will be a comma-separated list of calls to debug_rep.  
That is, a call such as  
`errorMsg(cerr, fcnName, code.num(), otherData, "other", item);`  
will execute as if we had written

```cpp
print(cerr, debug_rep(fcnName), debug_rep(code.num()),
            debug_rep(otherData), debug_rep("otherData"),
            debug_rep(item));
```

In contrast, the following pattern would fail to compile:

```cpp
// passes the pack todebug_rep; print(os, debug_rep(a1, a2, ..., an))
print(os, debug_rep(rest...)); // error: no matching function to call
```

The problem here is that we expanded rest in the call to debug_rep.  
This call would execute as if we had written  
`print(cerr, debug_rep(fcnName, code.num(), otherData, "otherData", item));`  
In this expansion, we attempted to call debug_rep with a list of five arguments.  
There is no version of debug_rep that matches this call.  
The debug_rep function isnot variadic and there is no version of debug_rep that has five parameters.

> ##### Note
> The pattern in an expansion applies separately to each element in the pack.

#### 16.4.3 Forwarding Parameter Packs

Under the new standard, we can use variadic templates together with forward to write functions that pass their arguments unchanged to some other function.  
To illustrate such functions, we’ll add an emplace_back member to our StrVec class.  
The emplace_back member of the library containers is a variadic member template that uses its arguments to construct an element directly in space managed by the container.

Our version of emplace_back for StrVec will also have to be variadic, because string has a number of constructors that differ in terms of their parameters. 
Because we’d like to be able to use the string move constructor, we’ll also need to preserve all the type information about the arguments passed to emplace_back.

As we’ve seen, preserving type information is a two-step process.  
First, to preserve type information in the arguments, we must define emplace_back’s function parameters as rvalue references to a template type parameter:

```cs
class StrVec
{
public:
    template <class... Args> void emplace_back(Args&&...);
    // remaining members as in§ 13.5 (p. 526)
};
```

The pattern in the expansion of the template parameter pack, `&&`, means that each function parameter will be an rvalue reference to its corresponding argument.

Second, we must use forward to preserve the arguments’ original types when emplace_back passes those arguments to construct:

```cpp
template <class... Args>
inline
void StrVec::emplace_back(Args&&... args)
{
    chk_n_alloc(); // reallocates theStrVecif necessary
    alloc.construct(first_free++, std::forward<Args>(args)...);
}
```

The body of emplace_back calls chk_n_alloc to ensure that there is enough room for an element and calls construct to create an element inthe first_free spot.  
The expansion in the call to construct:  
`std::forward<Args>(args)...`  
expands both the template parameter pack, Args, and the function parameter pack,args.  
This pattern generates elements with the form  
`std::forward<Ti>(ti)`  
where `Ti` represents the type of the *i*th element in the template parameter pack and `ti` represents the ith element in the function parameter pack.  
For example, assuming svec is a StrVec, if we call  
`svec.emplace_back(10, 'c'); // adds cccccccccc as a new last element`  
the pattern in the call to construct will expand to  
`std::forward<int>(10), std::forward<char>(c)`  
By using forward in this call, we guarantee that if emplace_back is called with an rvalue, then construct will also get an rvalue.  
For example, in this call:  
`svec.emplace_back(s1 + s2); // uses the move constructor`  
the argument to emplace_back is an rvalue, which is passed to construct as   `std::forward<string>(string("the end"))`  
The result type from `forward<string>` is `string&&`, so `construct` will be calledwith an rvalue reference.  
The construct function will, in turn, forward this argument to the string move constructor to build this element.

> ##### Advice: Forwarding and Variadic Templates
> 
> Variadic functions often forward their parameters to other functions.  
> Such functions typically have a form similar to our `emplace_back` function:
> 
> ```cpp
> // fun has zero or more parameters each of which is
> // an rvalue reference to a template parameter type
> template<typename... Args>
> void fun(Args&&... args) // expands Args as a list of rvalue references
> {
>     // the argument to work expands both Args and args
>     work(std::forward<Args>(args)...);
> }
> ```
> 
> Here we want to forward all of `fun`’s arguments to another function named `work` that presumably does the real work of the function.  
> Like our call to `construct` inside `emplace_back`, the expansion in the call to `work` expands both the template parameter pack and the function parameter pack.
> 
> Because the parameters to `fun` are rvalue references, we can pass arguments of any type to `fun`; because we use `std::forward` to pass those arguments, all type information about those arguments will bepreserved in the call to `work`.

--------------------------------------------------------------------------------

### 16.5 Template Specializations

It is not always possible to write a single template that is best suited for every possible template argument with which the template might be instantiated.  
In somecases, the general template definition is simply wrong for a type: The generaldefinition might not compile or might do the wrong thing.  
At other times, we may be able to take advantage of some specific knowledge to write more efficient code thanwould be instantiated from the template.  
When we can’t (or don’t want to) use thetemplate version, we can define a specialized version of the class or function template.

Our `compare` function is a good example of a function template for which thegeneral definition is not appropriate for a particular type, namely, character pointers.  
We’d like compare to compare character pointers by calling `strcmp` rather than by comparing the pointer values.  
Indeed, we have already overloaded the comparefunction to handle character string literals:

```cpp
// first version; can compare any two types
template <typename T> int compare(const T&, const T&);
// second version to handle string literals
template<size_t N, size_t M>
int compare(const char (&)[N], const char (&)[M]);
```

However, the version of compare that has two nontype template parameters will becalled only when we pass a string literal or an array.  
If we call compare with character pointers, the first version of the template will be called:

```cpp
const char *p1 = "hi", *p2 = "mom";
compare(p1, p2);        // calls the first template
compare("hi", "mom");   // calls the template with two nontype parameters
```

There is no way to convert a pointer to a reference to an array, so the second versionof compare is not viable when we pass p1 and p2 as arguments.

To handle character pointers (as opposed to arrays), we can define a **template specialization** of the first version of compare.  
A specialization is a separate definition of the template in which one or more template parameters are specified to have particular types.

##### Defining a Function Template Specialization

When we specialize a function template, we must supply arguments for every templateparameter in the original template.  
To indicate that we are specializing a template, weuse the keyword template followed by an empty pair of angle brackets (< >).  
The empty brackets indicate that arguments will be supplied for all the template parameters of the original template:

```cpp
// special version of compare to handle pointers to character arrays
template <>
int compare(const char* const &p1, const char* const &p2)
{
    return strcmp(p1, p2);
}
```

The hard part in understanding this specialization is the function parameter types.  
When we define a specialization, the function parameter type(s) must match the corresponding types in a previously declared template.  
Here we are specializing:  
`template <typename T> int compare(const T&, const T&);`  
in which the function parameters are references to a const type.  
As with type aliases,the interaction between template parameter types, pointers, and const can besurprising.

We want to define a specialization of this function with T as const char*.  
Our function requires a reference to the const version of this type.  
The const version ofa pointer type is a constant pointer as distinct from a pointer to const.  
The type we need to use in our specialization is const char* const &, whichis a reference to a const pointer to const char.

##### Function Overloading versus Template Specializations

When we define a function template specialization, we are essentially taking over the job of the compiler.  
That is, we are supplying the definition to use for a specificinstantiation of the original template.  
It is important to realize that a specialization isan instantiation; it is not an overloaded instance of the function name.

> ##### Note
> Specializations instantiate a template; they do not overload it.  
> As a result, specializations do not affect function matching.

Whether we define a particular function as a specialization or as an independent,nontemplate function can impact function matching.  
For example, we have definedtwo versions of our compare function template, one that takes references to array parameters and the other that takes const T&.  
The fact that we also have aspecialization for character pointers has no impact on function matching.  
When we callcompare on a string literal:  
`compare("hi", "mom")`  
both function templates are viable and provide an equally good (i.e., exact) match tothe call.  
However, the version with character array parameters is more specialized and is chosen for this call.

Had we defined the version of compare that takes character pointers as a plainnontemplate function (rather than as a specialization of the template), this call wouldresolve differently.  
In this case, there would be three viable functions: the twotemplates and the nontemplate character-pointer version.  
All three are also equallygood matches for this call.  
As we’ve seen, when a nontemplate provides an equallygood match as a function template, the nontemplate is selected.

> ##### Key Concept: Ordinary Scope Rules Apply to Specializations
> 
> In order to specialize a template, a declaration for the original template mustbe in scope.  
> Moreover, a declaration for a specialization must be in scopebefore any code uses that instantiation of the template.
> 
> With ordinary classes and functions, missing declarations are (usually) easyto find—the compiler won’t be able to process our code.  
> However, if aspecialization declaration is missing, the compiler will usually generate codeusing the original template.  
> Because the compiler can often instantiate theoriginal template when a specialization is missing, errors in declaration orderbetween a template and its specializations are easy to make but hard to find.
> 
> It is an error for a program to use a specialization and an instantiation of the original template with the same set of template arguments.  
> However, it isan error that the compiler is unlikely to detect.

> ##### Best Practices
> Templates and their specializations should be declared in the same header file.  
> Declarations for all the templates with a given name shouldappear first, followed by any specializations of those templates.

##### Class Template Specializations

We’ll define a specialization of the library `hash` template that we can use to store `Sales_data` objects in an unordered container.  
By default, the unordered containers use `hash<key_type>` to organize their elements.  
To use this default with our own data type, we must define a specializationof the hash template.  
A specialized hash class must define

- An overloaded call operator that returns a size_t and takes an object of the container’s key type

- Two type members, result_type and argument_type, which are the returnand argument types, respectively, of the call operator

- The default constructor and a copy-assignment operator (which can be implicitlydefined)

The only complication in defining this hash specialization is that when we specialize atemplate, we must do so in the same namespace in which the original template isdefined.  
We’ll have more to say about namespaces in § 18.2 (p. 785).  
For now, what we need to know is that we can add members to a namespace.  
To do so, we must first open the namespace:

```cpp
// open the std namespace so we can specialize std::hash
namespace std
{

}   // close the std namespace; note: no semicolon after the close curly
```

Any definitions that appear between the open and close curlies will be part of the std namespace.

The following defines a specialization of `hash` for `Sales_data`:

```cs
// open the std namespace so we can specialize std::hash
namespace std
{
template <>             // we're defining a specialization with
struct hash<Sales_data> // the template parameter of Sales_data
{
    // the type used to hash an unordered container must define these types
    typedef size_t result_type;
    typedef Sales_data argument_type; // by default, this type needs ==
    size_t operator()(const Sales_data& s) const;
    // our class uses synthesized copy control and default constructor
};

size_t
hash<Sales_data>::operator()(const Sales_data& s) const
{
    return hash<string>()(s.bookNo) ^
           hash<unsigned>()(s.units_sold) ^
           hash<double>()(s.revenue);
}
} // close thestdnamespace; note: no semicolon after the close curly
```

Our `hash<Sales_data>` definition starts with template<>, which indicates that we are defining a fully specialized template.  
The template we’re specializing is named hash and the specialized version is hash<Sales_data>.  
The members of the classfollow directly from the requirements for specializing hash.

As with any other class, we can define the members of a specialization inside the class or out of it, as we did here.  
The overloaded call operator must define a hashing function over the values of the given type.  
This function is required to return the same result every time it is called for a given value.  
A good hash function will (almost always) yield different results for objects that are not equal.

Here, we delegate the complexity of defining a good hash function to the library.  
The library defines specializations of the hash class for the built-in types and for many of the library types.  
We use an (unnamed) `hash<string>` object to generate a hashcode for bookNo, an object of type `hash<unsigned>` to generate a hash fromunits_sold, and an object of type `hash<double>` to generate a hash from revenue.  
We exclusive `OR` these results to form an overall hash codefor the given Sales_data object.

It is worth noting that we defined our hash function to hash all three data members so that our hash function will be compatible with our definition of operator== forSales_data.  
By default, the unordered containers use thespecialization of hash that corresponds to the key_type along with the equality operator on the key type.

Assuming our specialization is in scope, it will be used automatically when we use Sales_data as a key to one of these containers:

```cpp
// uses hash<Sales_data> and Sales_data operator== from § 14.3.1 (p. 561)
unordered_multiset<Sales_data> SDset;
```

Because hash<Sales_data> uses the private members of Sales_data, we must make this class a friend of Sales_data:

```cpp
template <class T> class std::hash; // needed for the friend declaration
class Sales_data
{
    friend class std::hash<Sales_data>;
    // other members as before
};
```

Here we say that the specific instantiation of hash<Sales_data> is a friend.  
Because that instantiation is defined in the std namespace, we must remember to that this hash type is defined in the std namespace.  
Hence, our friend declarationrefers to std::hash.

> ##### Note
> To enable users of Sales_data to use the specialization of hash, weshould define this specialization in the Sales_data header.

##### Class-Template Partial Specializations

Differently from function templates, a class template specialization does not have to supply an argument for every template parameter.  
We can specify some, but not all, of the template parameters or some, but not all, aspects of the parameters.  
A class template **partial specialization** is itself a template.  
Users must supply arguments for those template parameters that are not fixed by the specialization.

> ##### Note
> We can partially specialize only a class template.  
> We cannot partially specialize a function template.

In § 16.2.3 (p. 684) we introduced the library `remove_reference` type.  
That template works through a series of specializations:

```cpp
// original, most general template
template <class T> struct remove_reference
{
    typedef T type;
};

// partial specializations that will be used for lvalue and rvalue references
template <class T> struct remove_reference<T&>  // lvalue references
{
    typedef T type;
};

template <class T> struct remove_reference<T&&> // rvalue references
{
    typedef T type;
};
```

The first template defines the most general version.  
It can be instantiated with anytype; it uses its template argument as the type for its member named type.  
The next two classes are partial specializations of this original template.

Because a partial specialization is a template, we start, as usual, by defining the template parameters.  
Like any other specialization, a partial specialization has thesame name as the template it specializes.  
The specialization’s template parameter listincludes an entry for each template parameter whose type is not completely fixed by this partial specialization.  
After the class name, we specify arguments for the template parameters we are specializing.  
These arguments are listed inside angle brackets following the template name.  
The arguments correspond positionally to the parametersin the original template.

The template parameter list of a partial specialization is a subset of, or aspecialization of, the parameter list of the original template.  
In this case, the specializations have the same number of parameters as the original template.  
However, the parameter’s type in the specializations differ from the original template.  
The specializations will be used for lvalue and rvalue reference types, respectively:

```cs
int i;
// decltype(42) is int, uses the original template
remove_reference<decltype(42)>::type a;
// decltype(i) is int&, uses first (T&) partial pecialization
remove_reference<decltype(i)>::type b;
// decltype(std::move(i)) is int&&, uses second (i.e.,T&&) partial specialization
remove_reference<decltype(std::move(i))>::type c;
```

All three variables, a, b, and c, have type int.

##### Specializing Members but Not the Class

Rather than specializing the whole template, we can specialize just specific member function(s).  
For example, if Foo is a template class with a member Bar, we canspecialize just that member:

```cpp
template <typename T> struct Foo
{
    Foo(const T &t = T()): mem(t) { }
    void Bar() { /* ... */ }
    T mem;
    // other members of Foo
};

template<>              // we're specializing a template
void Foo<int>::Bar()    // we're specializing the Bar member of Foo<int>
{
    // do whatever specialized processing that applies toints
}
```

Here we are specializing just one member of the Foo<int> class.  
The other membersof Foo<int> will be supplied by the Foo template:

```cpp
Foo<string> fs; // instantiates Foo<string>::Foo()
fs.Bar();       // instantiates Foo<string>::Bar()
Foo<int> fi;    // instantiates Foo<int>::Foo()
fi.Bar();       // uses our specialization of Foo<int>::Bar()
```

When we use Foo with any type other than int, members are instantiated as usual.  
When we use Foo with int, members other than Bar are instantiated as usual.  
If we use the Bar member of `Foo<int>`, then we get our specialized definition.

--------------------------------------------------------------------------------

### Chapter Summary

Templates are a distinctive feature of C++ and are fundamental to the library.
A template is a blueprint that the compiler uses to generate specific class types or functions.
This process is called instantiation.
We write the template once, and the compiler instantiates the template for the type(s) or value(s) with which we use the template.

We can define both function templates and class templates.
The library algorithms are function templates and the library containers are class templates.

An explicit template argument lets us fix the type or value of one or more template parameters.
Normal conversions are applied to parameters that have an explicit template argument.

A template specialization is a user-provided instantiation of a template that binds one or more template parameters to specified types or values.
Specializations areuseful when there are types that we cannot use (or do not want to use) with thetemplate definition.

A major part of the latest release of the C++ standard is variadic templates.
A variadic template can take a varying number and types of parameters.
Variadictemplates let us write functions, such as the container `emplace` members and the library `make_shared` function, that pass arguments to an object’s constructor.

--------------------------------------------------------------------------------

EOF
