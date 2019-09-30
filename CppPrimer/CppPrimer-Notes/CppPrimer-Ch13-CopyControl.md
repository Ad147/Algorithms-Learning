CppPrimer-Ch13-CopyControl.md

C++ Primer Notes
================================================================================

Ad147  
<ar><r>

Init: 18Jun08

Chapter13 Copy Control
--------------------------------------------------------------------------------

- [Chapter13 Copy Control](#chapter13-copy-control)
    - [13.1 Copy, Assign and Destroy](#131-copy-assign-and-destroy)
        - [13.1.1 The Copy Constructor](#1311-the-copy-constructor)
        - [13.1.2 The Copy-Assignment Operator](#1312-the-copy-assignment-operator)
        - [13.1.3 The Destructor](#1313-the-destructor)
        - [13.1.4 The Rule of Three/Five](#1314-the-rule-of-threefive)
        - [13.1.5 Using `= default`](#1315-using--default)
        - [13.1.6 Preventing Copies](#1316-preventing-copies)
    - [13.2 Copy Control and Resource Management](#132-copy-control-and-resource-management)
        - [13.2.1 Classes That Act Like Values](#1321-classes-that-act-like-values)
        - [13.2.2 Defining Classes That Act Like Pointers](#1322-defining-classes-that-act-like-pointers)
    - [13.3 Swap](#133-swap)
    - [13.4 A Copy-Control Example](#134-a-copy-control-example)
    - [13.5 Classes That Manage Dynamic Memory](#135-classes-that-manage-dynamic-memory)
    - [13.6 `C++11` Moving Objects](#136-c11-moving-objects)
        - [13.6.1 Rvalue References](#1361-rvalue-references)
        - [13.6.2 Move Constructor and Move Assignment](#1362-move-constructor-and-move-assignment)
        - [13.6.3 Rvalue References and Member Functions](#1363-rvalue-references-and-member-functions)
    - [Chapter Summary](#chapter-summary)

--------------------------------------------------------------------------------

### 13.1 Copy, Assign and Destroy

#### 13.1.1 The Copy Constructor

**Copy constructor**: the first parameter is a reference to the class and any additional parameters have default values

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

 - copy constructor
 - copy-assignment operator
 - destructor
 - move constructor
 - move-assignment operator

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

```cs
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

```cs
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

```cs
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

```cs
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

Two classes used in a mail-handling application: `Message` and `Folder`.  
Each `Message` will store a `set` of pointers to `Folder`s.  
Each `Folder` contains a set of pointers to its `Message`s.

> **Best Practices**  
> The copy-assignment operator often does the same work as is needed in the copy constructor and destructor.  
> In such cases, the common work should beput in private utility functions.

 - `Message`: `save()` `remove()`
 - `Folder`: `addMsg()` `remMsg()`

##### The `Message` Class

```cs
class Message
{
    friend class Folder;

  public:
    // folders is implicitly initialized to the empty set
    explicit Message(const std::string &str = "") : contents(str) {}

    // copy control to manage pointers to this Message
    Message(const Message &);            // copy constructor
    Message &operator=(const Message &); // copy assignment
    ~Message();                          // destructor

    // add/remove this Message from the specified Folder's set of messages
    void save(Folder &);
    void remove(Folder &);

  private:
    std::string contents;       // actual message text
    std::set<Folder *> folders; // Folders that have this Message

    // utility functions used by copy constructor, assignment, and destructor
    // add this Message to the Folders that point to the parameter
    void add_to_Folders(const Message &);
    // remove this Message from every Folder in folders
    void remove_from_Folders();
};
```

##### The `save` and `remove`  Members

```cs
void Message::save(Folder &f)
{
    folders.insert(&f); // add the given Folder to our list
    f.addMsg(this);     // add this Message to f's set
}

void Message::remove(Folder &f)
{
    folders.erase(&f); // take the given Folder to our list
    f.remMsg(this);    // remove this Message to f's set
}
```

##### Copy Control for the `Message` Class

```cs
// add this Message to Folders that point to m
void Message::add_to_Folders(const Message &m)
{
    for (auto f : m.folders) // for each Folder that holds m
        f->addMsg(this);     // add a pointers to this Message to that Folder
}

Message::Message(const Message &m) : contents(m.contents), folders(m.folders)
{
    add_to_Folders(m); // add this Message to the Folders that point to m
}
```

##### The `Message` Destructor

```cs
// remove this Message from the cooresponding Folders
void Message::remove_from_Folders()
{
    for (auto f : folders) // for each pointer in the folders
        f->remMsg(this);   // remove this Message from that Foler
}

Message::~Message()
{
    remove_from_Folders();
    // the compiler automatically invokes the string destructor to free contents and the set destructor to clean up the memory used by thos members
}
```

##### `Message` Copy-Assignment Operator

```cs
Message &Message::operator=(const Message &rhs)
{
    // handle self-assignment by removing pointers before inserting them
    remove_from_Folders();   // update existing Folders
    contents = rhs.contents; // copy message contents from rhs
    folders = rhs.folders;   // copy Folder pointers from rhs
    add_to_Folders(this);    // add this Message to those Folders
    return *this;
}
```

##### A `swap` Function for `Message`

```cs
void swap(Message &lhs, Message &rhs)
{
    using std::swap; // not strictly needed in this case, but good habit
    // remove pointers to each Message from their (original) respective Folders
    for (auto f : lhs.folders)
        f->remMsg(&lhs);
    for (auto f : rhs.folders)
        f->remMsg(&rhs);

    // swap the contents and Folder pointer sets
    swap(lhs.folders, rhs.folders);   // uses swap(set&, set&)
    swap(lhs.contents, rhs.contents); // swap(string&, string&)

    // add pointers to each Message to their (new) respective Folders
    for (auto f : lhs.folders)
        f->addMsg(&lhs);
    for (auto f : rhs.folders)
        f->addMsg(&rhs);
}
```

--------------------------------------------------------------------------------

### 13.5 Classes That Manage Dynamic Memory

Some classes need to define their own copy-control  members to manage the memory they allocate.

##### `StrVec` Class Design

Implementation of a simplification of library `vector` contains `string`

Each `StrVec` will have 3 ptrs:
- `elements` points to the `st element in the allocated memory
- `first_free` points just after the last actual element
- `cap` points to the just past the end of the allocated memory

Will have a `alloc` which is an `allocator<string>`  to allocate the memory

4 utility functions:
- `alloc_n_copy` will allocate space and copy a range of elements
- `free` will destroy elements and deallocate the space
- `chk_n_alloc` will ensure that there is room to add at least one more element
- `reallocate` will reallocate the `StrVerc` when it runs out of space

##### `StrVec` Class Definition

```cs
// simplified implementation of the memory allocationg strategy for a vector-like class
class StrVec
{
  public:
    StrVec() : elements(nullptr), first_free(nullptr), cap(nullptr) {}
    // the allocator member is default initialized

    StrVec(const StrVec &);            // copy constructor
    StrVec &operator=(const StrVec &); //copy assignment
    ~StrVec();                         // destructor

    void push_back(const std::string &); // copy the element
    size_t size() const { return first_free - elements; }
    size_t capacity() const { return cap - elements; }
    std::string *begin() const { return elements; }
    std::string *end() const { return first_free; }
    // ...

  private:
    std::allocator<std::string> alloc; // allocates the elements
    // used by the functions that add elements to the StrVec
    void chk_n_alloc()
    {
        if (size() == capacity())
            reallocate();
    }
    // ultilities used by the copy constructor, assignment operator, and destructor
    std::pair<std::string *, std::string *> alloc_n_copy(const std::string *, const std::string *);
    void free();             // destroy the elements and free the space
    void reallocate();       // get more space and copy the existing elements
    std::string *elements;   // pointer to the first element in the array
    std::string *first_free; // pointer to the first free element in the array
    std::string *cap;        // pointer to one past the end of the array
}
```

##### Using `construct`

```cs
void StrVec::push_back(const std::string &s)
{
    chk_n_alloc(); //ensure that there is room for another element
    // construct a copy of s in the element to which first_free points
    alloc.construct(first_free++, s);
}
```

When we use an `allocator` to allocate memory, we must remember that the memory is unconstructed. To use this raw memory we must call construct, which will `construct` an object in that memory.

##### The `alloc_n_copy` Member

```cs
std::pair<std::string *, std::string *> StrVec::alloc_n_copy(const std::string *b, const std::string *e)
{
    // allocate space to hold as many elements as are in the range
    auto data = alloc.allocate(e - b);
    // initialize and return a pair constructed from data and the value returned by uninitialized_copy
    return {data, uninitialized_copy(b, e, data)};
}
```

The first member of the returned `pair` points to the start of theallocated memory;  
the second is the value returned from `uninitialized_copy`. That value will be pointer positioned one element past the last constructed element.

##### The `free` Member

```cs
void StrVec::free()
{
    // may not pass deallocate a 0 pointer; if elements is 0, there's no work to do
    if (elements)
    {
        // destroy the old elements in reverse order
        for (auto p = first_free; p != elements; /* empty */)
            alloc.destroy(--p);
        alloc.deallocate(elements, cap - elements);
    }
}
```

The `destroy` function runs the `string` destructor. The `string` destructor freeswhatever storage was allocated by the `string`s themselves.

##### Copy-Control Members

```cs
StrVec::StrVec(const StrVec &s)
{
    // call alloc_n_copy to allocate exactly as many elements as in s
    auto newdata = alloc_n_copy(s.begin(), s.end());
    elements = newdata.first;
    first_free = cap = newdata.second;
}

StrVec::~StrVec() { free(); }

// The copy-assignment operator calls alloc_n_copy before freeing its existing elements. By doing so it protects against self-assignment
StrVec &StrVec::operator=(const StrVec &rhs)
{
    // call alloc_n_copy to allocate exactly as many elements as in rhs
    auto data = alloc_n_copy(rhs.begin(), rhs.end());
    free();
    elements = data.first;
    first_free = cap = data.second;
    return *this;
}
```

##### Moving, Not Copying, Elements during Reallocation

The `reallocate` member will
- Allocate memory for a new, larger array of strings
- Construct the first part of that space to hold the existing elements
- Destroy the elements in the existing memory and deallocate that memory

Copying the data in these `string`s is unnecessary. Our `StrVec`'s performance will be *much* better if we can avoid the overhead of allocating and deallocating the `string`s themselves each time we reallocate.

##### Move Constructors and `std::move`

`C++11`We can avoid copying the strings by using two facilities introduced by the newlibrary.

**First**, several of the library classes, including `string`, define so-called “move constructors.”  
*The details of how the string move constructor works—like any other detail about the implementation—are not disclosed.*(?)  
However, we do know that move constructors typically operate by “moving” resources from the given object to theobject being constructed.  
We also know that the library guarantees that the “moved-from” string remains in a valid, destructible state.  
For `string`, we can imagine that each string has a pointer to an array of char.  
Presumably the `string` move constructor copies the pointer rather than allocating space for and copying thecharacters themselves.

The **second** facility we’ll use is a library function named `move`, which is defined inthe `utility` header.  
For now, there are two important points to know about `move`.
- First, for reasons we’ll explain in § 13.6.1 (p. 532), when `reallocate` constructs the `string`s in the new memory it must call `move` to signal that it wants to use the `string` move constructor.  
  If it omits the call to move the string the copyconstructor will be used.
- Second, for reasons we’ll cover in § 18.2.3 (p. 798), weusually do not provide a `using` declaration for `move`. When we use `move`, we call `std::move`, not `move`.

##### The `reallocate` Member

```cs
void StrVec::reallocate()
{
    // we will allocate space fro twice as many as the current size
    auto newcapacity = size() ? 2 * size() : 1;
    //allocate new memory
    auto newdate = alloc.allocate(newcapacity);
    // move the data from the old memory to the new
    auto dest = newdata;  // points to the next free position in the new array
    auto elem = elements; // points to the next element in the old array
    for (size_t i = 0; i != size(); ++i)
        alloc.construct(dest++, std::move(*elem++));
    free(); // free the old space once we have moved the elements
    // updata the data structure to point to the new elements
    elements = newdata;
    first_free = dest;
    cap = elements + newcapacity;
}
```

The second argument in the call to `construct` (i.e., the one that determines whichconstructor to use) is the value returned by `move`.  
Calling `move` returns a result that causes `construct` to use the `string` move constructor.  
Because we’re using the move constructor, the memory managed by those stringswill not be copied.  
Instead, each string we construct will take over ownership of thememory from the string to which elem points.

--------------------------------------------------------------------------------

### 13.6 `C++11` Moving Objects

In some cases, an object is immediately destroyed after it is copied.  
In those cases, moving, rather than copying, the object can provide a significant performance boost.

> The library containers, `string`, and `shared_ptr` classes support move as well as copy. The IO and `unique_ptr` classes can be moved but not copied.

#### 13.6.1 Rvalue References

`C++11` An rvalue reference (using `&&` rather than `&`) is a reference that must be bound to an rvalue.

```cs
int i = 42;
int &r = i;             // ok: r refers to i
int &&rr = i;           // error: cannot bind an rvalue reference to an lvalue
int &r2 = i * 42;       // error: i * 42 is an rvalue const
int &r3 = i * 42;       // ok: we can bind a reference to const to an rvalue
int &&rr2 = i * 42;     // ok: bind rr2 to the result of the multiplication
```

##### Lvalues Persist; Rvalues Are Ephemeral

Because rvalue references can only be bound to temporaries:
- The referred-to object is about to be destroyed
- There can be no other users of that object

> **Note**  
> Rvalue references refer to objects that are about to be destroyed.  
> Hence, wecan “steal” state from an object bound to an rvalue reference.

##### Variables Are Lvalues

`int &&rr1 = 42;    // ok: literals are rvalues`  
`int &&rr2 = rr1;   // error: the expressionrr1is an lvalue!`

> **Note**  
> A variable is an lvalue; we cannot directly bind an rvalue reference to a variable *even if that variable was defined as an rvalue reference type*.

##### The Library `move` Function `<utility>`

`int &&rr3 = std::move(rr1); // ok`

> **Note**  
> We can *destroy* a moved-from object and can *assign* a new value to it, but we cannot *use* the value of a moved-from object.

> **Warning**  
> Code that uses `move` should use `std::move`, not `move`.  
> Doing so avoidspotential name collisions.

#### 13.6.2 Move Constructor and Move Assignment

Like the copy constructor, the move constructor has an initial parameter that is areference to the class type.  
Differently from the copy constructor, the referenceparameter in the move constructor is an rvalue reference.  
As in the copy constructor, any additional parameters must all have default arguments.  

In addition to moving resources, the move constructor must ensure that the moved-from object is left in a state such that destroying that object will be harmless. Inparticular, once its resources are moved, the original object must no longer point tothose moved resources—responsibility for those resources has been assumed by thenewly created object.

```cs
StrVec::StrVec(StrVec  &&s)  noexcept // move won't throw anyexceptions
    // member initializers take over the resources in s
    : elements(s.elements), first_free(s.first_free), cap(s.cap)
{
    // leaves in a state in which it is safe to run the destructor
    s.elements = s.first_free = s.cap = nullptr;
}
```

##### 1) Move Operations, Library Containers, and Exceptions

Because a move operation executes by “stealing” resources, it ordinarily does not itself allocate any resources.  
As a result, move operations ordinarily will not throw anyexceptions.  
When we write a move operation that cannot throw, we should inform the library of that fact.  
As we’ll see, unless the library knows that our move constructor won’t throw, it will do extra work to cater to the possibliity that moving an object of our class type might throw.

One way inform the library is to specify `noexcept` on our constructor.  
We’ll cover `noexcept`, which was introduced by the new standard, in more detail in § 18.1.4 (p.779).  
For now what’s important to know is that `noexcept` is a way for us to promise that a function does not throw any exceptions.  
We specify `noexcept` on a function after its parameter list.  
In a constructor, `noexcept` appears between the parameter list and the `:` that begins the constructor initializer list:

```cs
class StrVec
{
public:
    StrVec(StrVec&&) noexcept;     // move constructor
    // other members as before
};
StrVec::StrVec(StrVec &&s) noexcept : /* member initializers */
{ /* constructor body*/ }
```

We must specify `noexcept` on both the declaration in the class header and on thedefinition if that definition appears outside the class.

> ##### Note
> Move constructors and move assignment operators that cannot throw exceptions should be marked as `noexcept`.

Understanding why `noexcept` is needed can help deepen our understanding of howthe library interacts with objects of the types we write.  
We need to indicate that a move operation doesn’t throw because of two interrelated facts:
1. although move operations usually don’t throw exceptions, they are permitted to do so.
2. the library containers provide guarantees as to what they do if an exception happens.  
   As one example, `vector` guarantees that if an exception happens when we call `push_back`, the `vector` itself will be left unchanged.

Now let’s think about what happens inside `push_back`.  
Like the corresponding StrVec operation, `push_back` on a `vector` might require that the `vector` be reallocated.  
When a `vector` is reallocated, it moves the elements from its old space to new memory, just as we did in reallocate.

As we’ve just seen, moving an object generally changes the value of the moved-from object.  
If reallocation uses a move constructor and that constructor throws an exception after moving some but not all of the elements, there would be a problem.  
The moved-from elements in the old space would have been changed, and the unconstructed elements in the new space would not yet exist.  
In this case, `vector` would be unable to meet its requirement that the `vector` is left unchanged.

On the other hand, if `vector` uses the copy constructor and an exception happens,it can easily meet this requirement.  
In this case, while the elements are beingconstructed in the new memory, the old elements remain unchanged.  
If an exception happens, `vector` can free the space it allocated (but could not successfully construct)and return.  
The original `vector` elements still exist.

To avoid this potential problem, `vector` must use a copy constructor instead of a move constructor during reallocation unless it knows that the element type’s moveconstructor cannot throw an exception.  
If we want objects of our type to be moved rather than copied in circumstances such as `vector` reallocation, we must explicity tell the library that our move constructor is safe to use.  
We do so by marking the move constructor (and move-assignment operator) `noexcept`.

##### 2) Move-Assignment Operator

```cs
StrVec &StrVec::operator=(StrVec &&rhs) noexcept
{
    // direct test for self-assignment
    if (this != &rhs)
    {
        free();                  // free existing elements
        elements = rhs.elements; // take over resources from rhs
        first_free = rhs.first_free;
        cap = rhs.cap;
        // leave rhs in a destructible state
        rhs.elements = rhs.first_free = rhs.cap = nullptr;
    }
    return *this;
}
```

##### 3) A Moved-from Object Must Be Destructible

> ##### Warning
> After a move operation, the “moved-from” object must remain a valid, destructible object but users may make no assumptions about its value.

##### 4) The Synthesized Move Operations

Differently from the copy operations, for some classes the compiler does not synthesize the move operations *at all*.  
In particular, if a class defines its own copy constructor, copy-assignment operator, or destructor, the move constructor and move-assignment operator are not synthesized.  
As a result, some classes do not have a move constructor or a move-assignment operator.

The compiler will synthesize a move constructor or a move-assignment operator only if the class doesn’t define any of its own copy-control members and if every nonstatic data member of the class can be moved.  
The compiler can move members of built-in type.

```cs
// the compiler will synthesize the move operations for X and hasX
struct X
{
    int i;         // built-in types can be moved
    std::string s; // stringdefines its own move operations
};

struct hasX
{
    X mem; // X has synthesized move operations
};

X x, x2 = std::move(x);       // uses the synthesized move constructor
hasX hx, hx2 = std::move(hx); // uses the synthesized move constructor
```

> ##### Note
> The compiler synthesizes the move constructor and move assignment only if a class does not define any of its own copy-control members and only if all the data members can be moved constructed and move assigned,respectively.

- Unlike the copy constructor, the move constructor is defined as deleted if the class has a member that defines its own copy constructor but does not also define a move constructor, or if the class has a member that doesn’t define its own copy operations and for which the compiler is unable to synthesize a move constructor. Similarly for move-assignment.
- The move constructor or move-assignment operator is defined as deleted if the class has a member whose own move constructor or move-assignment operatoris deleted or inaccessible.
- Like the copy constructor, the move constructor is defined as deleted if the destructor is deleted or inaccessible.
- Like the copy-assignment operator, the move-assignment operator is defined as deleted if the class has a const or reference member.

```cs
//assume Y is a class that defines its own copy constructor but not a move constructor
struct hasY
{
    hasY() = default;
    hasY(hasY &&) = default;
    Y mem; // hasY will have a deleted move constructor
};

hasY hy, hy2 = std::move(hy); // error: move constructor is deleted
```

There is one final interaction between move operations and the synthesized copy-control members:  
Whether a class defines its own move operations has an impact on how the copy operations are synthesized.  
If the class defines either a move constructor and/or a move-assignment operator, then the synthesized copy constructor and copy-assignment operator for that class will be defined as deleted.

> ##### Note
> Classes that define a move constructor or move-assignment operator must also define their own copy operations.  
> Otherwise, those members are deleted by default.

##### 5) Rvalues Are Moved, Lvalues Are Copied ...

```cs
StrVec v1, v2;
v1 = v2;                  // v2 is an lvalue; copy assignment
StrVec getVec(istream &); // getVecreturns an rvalue
v2 = getVec(cin);         // getVec(cin) is an rvalue; move assignment
```

##### 6) ...But Rvalues Are Copied If There Is No Move Constructor

```cs
class Foo
{
public:
    Foo() = default;
    Foo(const Foo&); // copy constructor
    // other members, but Foo does not define a move constructor
};

Foo x;
Foo y(x);            // copy constructor; x is an lvalue
Foo z(std::move(x)); // copy constructor, because there is no move constructor T
```

> ##### Note
> If a class has a usable copy constructor and no move constructor, objects will be “moved” by the copy constructor.  
> Similarly for the copy-assignmentoperator and move-assignment.

##### 7) Copy-and-Swap Assignment Operators and Move

```cs
class HasPtr
{
public:
    // added move constructor
    HasPtr(HasPtr &&p) noexcept : ps(p.ps), i(p.i) { p.ps = 0; }
    // assignment operator is both the move- and copy-assignment operator
    HasPtr& operator=(HasPtr rhs) { swap(*this, rhs); return *this; }
    // other members as in § 13.2.1 (p. 511)
};
```

As aresult, this single assignment operator acts as both the copy-assignment and move-assignment operator.

> ##### Advice: Updating the Rule of Three
> All five copy-control members should be thought of as a unit: Ordinarily, if a class defines any of these operations, it usually should define them all.  
> As we’ve seen, some classes must define the copy constructor, copy-assignment operator, and destructor to work correctly. Such classes typically have a resource that the copy members must copy. Ordinarily, copying a resource entails some amount of overhead. Classes that define the move constructor and move-assignment operator can avoid this overhead in those circumstances where a copy isn’t necessary.

##### 8) Move Operations for the Message Class

##### 9) Move Iterators

> ##### Advice: Don’t Be Too Quick to Move
> Because a moved-from object has indeterminate state, calling `std::move` on an object is a dangerous operation.  
> When we call `move`, we must be absolutely certain that there can be no other users of the moved-from object.
> 
> Judiciously used inside class code, `move` can offer significant performance benefits. Casually used in ordinary user code (as opposed to class implementation code), moving an object is more likely to lead to mysterious and hard-to-find bugs than to any improvement in the performance of the application.

> ##### Best Practices
> Outside of class implementation code such as move constructors or move-assignment operators, use `std::move` only when you are certain that you need to do a move and that the move is guaranteed to be safe.

#### 13.6.3 Rvalue References and Member Functions

Member functions other than constructors and assignment can benefit from providing both copy and move versions.

Such move-enabled members typically use the same parameter pattern as the copy/move constructor and the assignment operators—one version takes an lvalue reference to const, and the second takes an rvalue reference to nonconst.

For example, the library containers that define `push_back` provide two versions: one that has an rvalue reference parameter and the other a const lvalue reference.

Assuming X is the element type, these containers define:  
`void push_back(const X&); // copy: binds to any kind of X`  
`void push_back(X&&);      // move: binds only to modifiable rvalues of typeX`

We can pass any object that can be converted to type X to the first version of `push_back`. This version copies data from its parameter.  
We can pass only an rvaluethat is not const to the second version.  
This version is an exact match (and a better match) for nonconst rvalues and will be run when we pass a modifiable rvalue.  
This version is free to steal resources from its parameter.

Ordinarily, there is no need to define versions of the operation that take a `const X&&` or a (plain) `X&`.

> ##### Note
> Overloaded functions that distinguish between moving and copying aparameter typically have one version that takes a `const T&` and one that takes a `T&&`.

##### 1) Rvalue and Lvalue Reference Member Functions

We place a **reference qualifier** after the parameter list:

```cs
class Foo
{
public:
    Foo &operator=(const Foo&) &; // may assign only to modifiable lvalues
    // other members of Foo
};
Foo &Foo::operator=(const Foo &rhs) &
{
    // do whatever is needed to assign rhs to this object
    return *this;
}
```

We may run a function qualified by `&` only on an lvalue and may run a function qualified by `&&` only on an rvalue:

```cs
Foo &retFoo(); // returns a reference; a call to retFoo is an lvalue
Foo retVal();  // returns by value; a call to retValis an rvalue
Foo i, j;      // i and j are lvalues
i = j;         // ok: i is an lvalue
retFoo() = j;  // ok: retFoo() returns an lvalue
retVal() = j;  // error: retVal() returns an rvalue
i = retVal();  // ok: we can pass an rvalue as the right-hand operand to assignment
```

##### 2) Overloading and Reference Functions

Just as we can overload a member function based on whether it is const, we can also overload a function based on its reference qualifier. Moreover, we may overload a function by its reference qualifier and by whether it is a const member.

> ##### Note
> If a member function has a reference qualifier, all the versions of that member with the same parameter list must have reference qualifiers.

### Chapter Summary

Each class controls what happens when we copy, move, assign, or destroy objects of its type. Special member functions—the copy constructor, move constructor, copyassignment operator, move-assignment operator, and destructor—define these operations. The move constructor and move-assignment operator take a (usually nonconst) rvalue reference; the copy versions take a (usually const) ordinary lvalue reference.

If a class declares none of these operations, the compiler will define them automatically. If not defined as deleted, these operations memberwise initialize, move, assign, or destroy the object: Taking each nonstatic data member in turn, the synthesized operation does whatever is appropriate to the member’s type to move, copy, assign, or destroy that member.

Classes that allocate memory or other resources almost always require that the class define the copy-control members to manage the allocated resource. If a class needs a destructor, then it almost surely needs to define the move and copy constructors and the move- and copy-assignment operators as well.

--------------------------------------------------------------------------------

EOF
