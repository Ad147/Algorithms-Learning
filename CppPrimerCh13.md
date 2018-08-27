CppPrimerCh13.md

C++ Primer Notes
================================================================================

Ad  
init: 2018Jun08

Chapter13 Copy Control
--------------------------------------------------------------------------------

### 13.1 Copy, Assign and Destroy

#### 13.1.1 The Copy Constructor (the first parameter is a reference to the class and any additional parameters have default values)

`class Foo { Foo(const Foo &); };`

Copy initialization ordinarily uses the copy constructor. But maybe use move constructor.

Copy initialization happens not only defining variables using `=`, but also

 - pass an obj as an argument to a parameter of nonreference type
 - return an obj from a function that has a nonreference return type
 - brace initialize the elements in an array or the members of an aggregate class

##### The compiler can bypass the copy constructor

#### 13.1.2 The Copy-Assignment Operator

`Foo& operator=(const Foo &);`

> Assignment operators ordinarily should return a reference to their left-hand operand.

##### The synthesized copy-assignment operator

It assigns each nonstatic member of the right-hand operand to the corresponding member of the left-hand obj **using the copy-assignment operator for the type of that member**  
and returns a reference to its left-hand obj

#### 13.1.3 The Destructor

In a constructor, members initialized before function body executed, and members initialized in the same order as they appear in the class  
In a destructor, the function body executed before members destroyed in the reverse order from initilazation.

> The implicit destruction of a member of built-in pointer type does not delete the object to which it points.

##### When a destructor is called

The destructor is used automatically whenever an object of its type is destroyed:

 - variables are destroyed when they go out of scope
 - members of an object are destroyed when the obj destroyed
 - elements in a container (whether a library container or an array) are destroyed when the container is destroyed
 - dynamically allocated objs are destroyed when the delete applied
 - temprary objs are destroyed at the end of the full expression in which the temporary was created

> The destructor is not run when a reference or a pointer to an object goes out of range.

#### 13.1.4 The Rule of Three/Five

##### Classes that need destructors need copy and assignment (like with pointer members)

##### Classes that need copy need assignment and vice versa

#### 13.1.5 Using `= default`

#### 13.1.6 Preventing Copies

##### Defining a function as delete `C++11`

`NoCopy(const NoCopy &) = delete;`  
`NoCopy &operator=(const NoCopy &) = delete;`

##### The destructor should not be a deleted member

> In essence, the copy-control members are synthesized as deleted when it is impossible to copy, assign or destroy a member of the class.

Prior to `C++11`, classes prevented copies by declaring members as private, and did not define them.

--------------------------------------------------------------------------------

### 13.2 Copy Control and Resource Management

#### 13.2.1 Classes That Act Like Values

```cpp
class HasPtr
{
public:
    HasPtr(const std::string &s = std::string())
        : ps(new std::string(s)), i(0) {}
    // copy constructor that copies the string
    HasPtr(const HasPtr &p)
        : ps(new std::string(*p.ps)), i(p.i) {}
    // destructor to free the string
    ~HasPtr() { delete ps; }
    // copy-assignment operator to free current string and copy
    HasPtr &operator=(const HasPtr &rhs)
    {
        auto newp = new string(*rhs.ps);
        delete ps;
        ps = newp;
        i = rhs.i;
        return *this;
    }

private:
    std::string *ps;
    int i;
};
```

> Key Concept: Assignment Operators
> two points to keep in mind:
>  - assignment operators must work correctly if an obj is assigned to itself
>  - most assignment operators share work with the destructor and copy constructor

#### 13.2.2 Defining Classes That Act Like Pointers

```cpp
class HasPtr
{
  public:
    // constructor allocates a new string and a new counter set to 1
    HasPtr(const std::string &s = std::string())
        : ps(new std::string(s)), i(0), use(new std::size_t(1)) {}
    // copy constructor copies data members and imcrement the counter
    HasPtr(const HasPtr &hp) : ps(hp.ps), i(hp.i), use(hp.use) { ++*use; }
    ~HasPtr();
    HasPtr &operator=(const HasPtr &hp);

  private:
    std::string *ps;
    int i;
    std::size_t *use; // member to keep track of how many objs share *ps
};

HasPtr::~HasPtr()
{
    if (--*use == 0)
    {
        delete ps;
        delete use;
    }
}

HasPtr &HasPtr::operator=(const HasPtr &hp)
{
    ++*hp.use;
    if (--*use == 0)
    {
        delete ps;
        delete use;
    }
    ps = hp.ps;
    i = hp.i;
    use = hp.use;
    return *this;
}
```

--------------------------------------------------------------------------------

### 13.3 Swap

Swapping two objects involves a copy and 2 assignments,  
Swap pointers rather than copy data.

```cpp
class HasPtr
{
    friend void swap(HasPtr &, HasPtr &);
};

inline void swap(HasPtr &lhs, HasPtr &rhs)
{
    using std::swap; // IMPORTANT to use using
    swap(lhs.ps, rhs.ps); // swap pointers instead of data
    swap(lhs.i, rhs.i);
}
```

> Unlike the copy-control members, `swap` is never necessary.  
> However, defining swap can be an important optimization for classes that allocate resources.

##### `swap` functions should call `swap`, not `std::swap`

If one of the member of the class has its own version of swap (i.e. a member of type Foo), call `std::swap` will override the type-specific one.  
About why the `using` declaration does not hide the member version of `swap`, will cover in 18.2.3.

##### Using `swap` in assignment operators

Classes that define `swap` often use `swap` to define assignment operator.  
This technique known as **copy and swap**.

```cpp
// note the parameter rhs is passed by value, which means the HasPtr copy constructor copies the data in right-hand operand into rhs
HasPtr &HasPtr::operator=(HasPtr rhs)
{
    // swap the contents of the left-hand operand with the local variable rhs
    swap(*this, rhs); // rhs now points to the memory this had used
    return *this;     // rhs is destroyed, deletes the pointer in rhs
}
```

> Assignment operators that use copy and swap are automaticlly exception safe and correctly handle self-assignment.

--------------------------------------------------------------------------------

### 13.4 A Copy-Control Example

### 13.5 Classes That Manage Dynamic Memory

### 13.6 Moving Objects

#### 13.6.1 Rvalue References

#### 13.6.2 Move Constructor and Move Assignment

#### 13.6.3 Rvalue References and Member Functions
