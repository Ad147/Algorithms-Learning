CppPrimerCh12.md

C++ Primer Notes
================================================================================

Ad  
init: May20.2018

Chapter12 Dynamic Memory
--------------------------------------------------------------------------------

### 12.1 Dynamic Memory and Smart Pointers

- `new` : allocates, and optionally initializes, returns a pointer
- `delete` : takes a pointer to a dynamic object, destroys that object, and frees

`C++11` `smart pointer` `<memory>` (template):
- `shared_ptr` : allows multiple pointers to refer to the same object
- `unique_ptr` : owns the object it points
- `weak_ptr` : managed by a shared_ptr

#### 12.1.1 The `shared_ptr` Class

|| Operations Common to `shared_ptr` and `unique_ptr`
-|---------------------------------------------------
shared_ptr<T> sp    | null smart pointer that can point to objects of type T
unique_ptr<T> up    | 
p                   | use p as a condition; true if p points to an object
*p                  | Dereference p to get the object to which p points
p->mem              | 
p.get()             | returns the built-in pointer in p. use with caution
swap(p, q)          | swaps the pointers in p and q
p.swap(q)           | 


|| Operations Specific to `shared_ptr`
-|------------------------------------
make_shared<T>(args)    | returns a shared_ptr pointing to a dynamically allocated object of type T. Uses args to initialize that object
shared_ptr<T> p(q)      | copy q to p. increments the count in q. 
p = q                   | p and q are shared_ptrs holding pointers that can be converted. 
||decrement p's reference count and increments q's; delete p if counts 0
p.unique()              | returns true if p.use_count() is one; false otherwise
p.use_count()           | returns the number of objects sharing with p; a slow operation

##### The `make_shared` function (the safest way)
`shared_ptr<int> p = make_shared<int>(42);`

Once a shared_ptr counter goes to zero, the ptr automatically frees the memory

> If you put shared_ptrs in a container, and you subsequently need to use some, but not all, of the elements, remember to erase the elements you no longer need.

##### Classes with resources that have dynamic lifetime

Programs tend to use dynamic memory for one of three purposes:
1. They do not know how many objects they'll need
2. dont know the precise type needed
3. want to share data between several objects

Container classes are an example of classes that use dynamic memory.

#### 12.1.2 Managing Memory Directly

`int *pi = new int();` (value defined to 0)  
`vector<int> *pv = new vector<int>{1,2,3};`

##### Dynamic allocated const objects
`const int *pci = new const int(201);`

##### Memory exhaustion
if `new` is unable to allocate the requested storage, it throws an exception of type `bad_alloc`  
prevent new from throwing an exception by using a different form (`<new>`):
- `int *p = new (nothrow) int;` : if allocation fails, returns a null pointer

##### Pointer value and delete
Deleting a ptr not allocated by new  
or deleting the same ptr value, is undefined

##### Dynamically allocated objects exist until they are freed

> #### Caution: managing dynamic memory is error-prone
> There are three common problems with using new and delete to manage dynamic memory:
> 1. Forgetting to delete memory. Neglecting to delete dynamic memory is known as a "memory leak", because the memory is never returned to the free store.  
> Testing for memory leaks is defficult bacouse they usually cannot be detected.
> 2. Using an object after it has been deleted.
> 3. Deleting the same memory twice
>
> Avoiding all of these problems by using smart pointers.

#### 12.1.3 Using shared_ptrs with new

`shared_ptr<int> p(new int(42));`

|| Other Ways to Define and Change shared_ptrd
-|--------------------------------------------
shared_ptr<T> p(q)  | p manages the object to which the built-in pointer q points;
|| q must point to memory allocated by new and convertible T*
shared_ptr<T> p(u)  | p assumes ownership from the unique_ptr u; makes u null
shared_ptr<T> p(q, d) | p assumes ownership for the object to which the built-in pointer q points. q must convertable
|| p will use the callable object d in place of delete to free q.
shared_ptr<T> p(p2, d) | p is a copy of the shared_ptr p2 as described in table 12.2 except p uses d in place of delete
p.reset()               | if p is the only shared_ptr pointing at its object, reset frees the object.
p.reset(q)              | if the optional built-in pointer q is passed, makes p point to q, otherwise null.
p.reset(q, d)           | if d is supplied, call d to free q otherwise delete

Cannot implicily convert a butlt-in pointer to a smart pointer.

##### Dont mix ordinary pointers and smart pointers 

Once give shared_ptr responsibility for a pointer, should no longer use a built-in pointer to access the memory.

##### and dont use `get` to initialize or assign another smart pointer

#### 12.1.4 Smart Pointers and Exceptions

If an exceptiong happens between the new and the delete, and is not caught inside function, then this memory can never be freed.

> #### Caution: Smart Pointer Pitfalls
> To use smart pointers correctlly, must adhere to a set of conventions:
> - Do not use the same built-in pointer value to initialize (or reset) more than one smart pointer.
> - Do not delete the pointer returned from get().
> - Do not use get() to initialize or reset another smart pointer.
> - If you use a pointer returned by get(), remember that the pointer will become invalid when the last corresponding smart pointer goes away.
> - If you use a smart pointer to manage a resource other than memory allocated by new, remember to pass a deleter.

#### 12.1.5 `unique_ptr`

|| `unique_ptr` Operations (see also table 12.1)
-|----------------------------------------------
unique_ptr<T> u1    | null pointer. use delete to free
unique_ptr<T, D> u2 | use callable obejct of type D to free
unique_ptr<T, D> u(d) | null pointer used d which is type D to free
u = nullptr         | deletes the object. makes null
u.release()         | relinquishes control of the pointer u had held; returns pointer u had held and null u
u.reset()           | deletes the object u points
u.reset(q)          | if the built-in pointer q is supplied, makes u point to that object.
u.reset(nullptr)    | Ohterwise makes u null.

cannot copy or assign unique_ptr, can transfer ownership from one unique_ptr to another:  
- `unique_ptr<int> p2(p1.release());`  
- `p2.reset(p3.release());`

##### Passing and Returning `unique_ptr`s
One exception that can copy a unique_ptr:  
copy or assign a unique_ptr that is about to be destroyed. (returning)

#### 12.1.6 `weak_ptr`

A weak_ptr does not control the lifetime of the object it points to.  
Instead, points to an object that managed by a shared_ptr.  
Binding a weak_ptr to a shared_ptr does not change the reference count.  
Once last shared_ptr goes away, the object deleted.

cannot use a weak_ptr to access its object directly. To access using lock()

|| `weak_ptr`s
-|---------------------------------
weak_ptr<T> w   | null weak_ptr that can point at objects of type T
weak_ptr<T> w(sp) | points to the same object as the shared_ptr sp.
w = p           | p can be a shared_ptr or a weak_ptr. w shares ownership with p
w.reset()       | null w
w.use_count()   | the numer of shared_ptr that shares ownership with w
w.expired()     | returns true if w.use_count() is zero
w.lock()        | if expired is true, returns a null shared_ptr. otherwise returns a shared_ptr

--------------------------------------------------------------------------------

### 12.2 Dynamic Arrays

`allocator` separates allocation from initialization.  
Using an allocator generally provides better performance and more flexible memory management.

#### 12.2.1 `new` and Arrays

`int *pia = new int[get_size()]; // points to the first of ints`

> It is important to remember that what we call a dynamic array does not have an array type.

##### It is legal to dynamically allocate an empty array

##### Freeing dynamic arrays
`delete [] pa;`

##### Smart pointers and dynamic arrays

`unique_ptr<int[]> u(new int[10]);`

|| `unique_ptr` to Arrays
-|-----------------------------------
|| member access operators (dot and arrow) are not supported for unique_ptrs to arrays
unique_ptr<T[]> u   | u can point to a dynamically array of type T
unique_ptr<T[]> u(p)| u points to the dynamically allocated array to which the built-in pointer p points. 
u[i]    | returns the object at position i in the array. u must point to an array

shared_ptr provides no direct support for managing a dynamic array.  
if use shared_ptr to manage dynamic array, must provide own deleter

#### 12.2.2 The `allocator` Class (decouple the allocation and construction)

|| Standard `allocator` Class and Customized Algorithms
-|-----------------------------------------------------
allocator<T> a      | defines an allocator object named a that can allocate memory for type T
a.allocate(n)       | allocates raw, unconstructed memory to hold n objects
a.deallocate(p, n)  | deallocates memory held n objs starting at p.
|| p must be returned from allocate, n must be the size with p created
|| the user must run destroy on any objs that were constructed in this memory before calling deallocate
a.construct(p, args)| p must point to raw memory
a.destroy(p)        | runs the destructor on the object pointed to by p

##### allocators allocate unconstructed memory

> must construct objs in order to use memory returned by allocate.

[allocate] -> [construct] -> [destroy] -> [deallocate]

##### Algorithms to copy and fill uninitialized memory

|| `allocator` Algorithms
-|--------------------------------------------
|| These functions construct elements in the destination, rather than assigning to them
uninitialized_copy(b, e, b2)    | copies elements from  range denoted by iterators b and e into unconstructed, raw memory denoted by b2.
|| the memory must be large enough
uninitialized_copy_n(b, n, b2)  | copies n elements starting at b into memory b2
uninitialized_fill(b, e, t)     | constructs objs in the range of raw memory denoted by b, e as a copy of t
uninitialized_fill_n(b, n, t)   | constructs an unsigned number n objs starting at b

--------------------------------------------------------------------------------

### 12.3 Using the Library: A Text-Query Program

#### 12.3.1 Design of the Query Progaram

#### 12.3.2 Defining the Query Program Classes

--------------------------------------------------------------------------------

EOF
