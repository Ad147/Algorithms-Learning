DSAA-Ch02-StackQueue.md


Notes of Data Structures and Algorithm Analysis in C++
================================================================================

Ad  
<ar><r>

Init: 19Mar08


Chapter 3 Lists, Stacks, and Queues
--------------------------------------------------------------------------------

This chapter discusses three of the most simple and basic data structures.  
Virtually every significant program will use at least one of these structures explicitly, and a stack is alwaysimplicitly used in a program, whether or not you declare one.  
Among the highlights of thischapter, we will...

- Introduce the concept of Abstract Data Types (ADTs).
- Show how to efficiently perform operations on lists.
- Introduce the stack ADT and its use in implementing recursion.
- Introduce the queue ADT and its use in operating systems and algorithm design.

In this chapter, we provide code that implements a significant subset of two libraryclasses: `vector` and `list`.


--------------------------------------------------------------------------------


- [Chapter 3 Lists, Stacks, and Queues](#chapter-3-lists-stacks-and-queues)
  - [3.1 Abstract Data Types (ADTs)](#31-abstract-data-types-adts)
  - [3.2 The List ADT](#32-the-list-adt)
    - [3.2.1 Simple Array Implementation of Lists](#321-simple-array-implementation-of-lists)
    - [3.2.2 Simple Linked Lists](#322-simple-linked-lists)
  - [3.3 `vector` and `list` in the STL](#33-vector-and-list-in-the-stl)
    - [3.3.1 Iterators](#331-iterators)
    - [3.3.2 Example: Using `erase` on a List](#332-example-using-erase-on-a-list)
    - [3.3.3 `const_iterator`s](#333-constiterators)
  - [3.4 Implementation of `vector`](#34-implementation-of-vector)
  - [3.5 Implementation of `List`](#35-implementation-of-list)


--------------------------------------------------------------------------------


### 3.1 Abstract Data Types (ADTs)

An **abstract data type** (ADT) is a set of objects together with a set of operations.  
Abstractdata types are mathematical abstractions;  
nowhere in an ADT’s definition is there any men-tion ofhowthe set of operations is implemented.  
Objects such as lists, sets, and graphs,along with their operations, can be viewed as ADTs, just as integers, reals, and booleans aredata types.  
Integers, reals, and booleans have operations associated with them, and so doADTs.  

There is no rule telling us which operations must be supported for each ADT;  
this is a design decision.  
Error handling and tie breaking (where appropriate) are also generallyup to the program designer.


--------------------------------------------------------------------------------


### 3.2 The List ADT

We will deal with a general list of the form A0,A1,A2,...,AN−1.  
We say that the size ofthis list isN.  
We will call the special list of size 0 an **empty list**.

For any list except the empty list, we say that Ai follows (or succeeds) Ai−1(i<N)and that Ai−1 precedes Ai (i>0).  
The first element of the list isA0, and the last elementis AN−1.  
We will not define the predecessor ofA0or the successor ofAN−1.  
The **position** of elementAiin a list is i.  
Throughout this discussion, we will assume, to simplify matters,that the elements in the list are integers, but in general, arbitrarily complex elements areallowed (and easily handled by a class template).

Associated with these “definitions” is a set of operations that we would like to performon  the  List  ADT.  
Some  popular  operations  are `printList` and `makeEmpty`,  which  do  the obvious things;  
`find`, which returns the position of the first occurrence of an item;  
`insert` and `remove`, which generally insert and remove some element from some position in thelist;  
and `findKth`, which returns the element in some position (specified as an argument).


#### 3.2.1 Simple Array Implementation of Lists

All these instructions can be implemented just by using an array.  
Although arrays are cre-ated with a fixed capacity, thevectorclass, which internally stores an array, allows the arrayto grow by doubling its capacity when needed.  
This solves the most serious problem withusing an array—namely, that historically, to use an array, an estimate of the maximum sizeof the list was required.  
This estimate is no longer needed.

An array implementation allowsprintListto be carried out in linear time, and thefindKthoperation  takes  constant  time,  which  is  as  good  as  can  be  expected.  
However,insertion and deletion are potentially expensive, depending on where the insertions anddeletions occur.  
In the worst case, inserting into position 0 (in other words, at the frontof the list) requires pushing the entire array down one spot to make room, and deletingthe first element requires shifting all the elements in the list up one spot, so the worstcase for these operations isO(N).  
On average, half of the list needs to be moved for eitheroperation, so linear time is still required.  
On the other hand, if all the operations occur atthe high end of the list, then no elements need to be shifted, and then adding and deletingtakeO(1) time.

There  are  many  situations  where  the  list  is  built  up  by  insertions  at  the  high  end,and then only array accesses (i.e.,findKthoperations) occur.  
In such a case, the array isa suitable implementation.  
However, if insertions and deletions occur throughout the listand, in particular, at the front of the list, then the array is not a good option.  
The next section deals with the alternative: the *linked list*.


#### 3.2.2 Simple Linked Lists

In order to avoid the linear cost of insertion and deletion, we need to ensure that the listis not stored contiguously, since otherwise entire parts of the list will need to be moved.

The  linked  list  consists  of  a  series  of  nodes,  which  are  not  necessarily  adjacent  inmemory.  
Each node contains the element and a link to a node containing its successor.  
Wecall this the `next` link.  
The last cell’s `next` link points to `nullptr`.

To executeprintList()orfind(x),  we merely start at the first node in the list andthen traverse the list by following thenextlinks.  
This operation is clearly linear-time, asin the array implementation;  
although, the constant is likely to be larger than if an arrayimplementation  were  used.  
The `findKth` operation  is  no  longer  quite  as  efficient  as  anarray implementation;  
findKth(i)takesO(i) time and works by traversing down the list inthe obvious manner.  
In practice, this bound is pessimistic, because frequently the calls tofindKthare in sorted order (byi).  
As an example,findKth(2),findKth(3),findKth(4),andfindKth(6)can all be executed in one scan down the list.

The `remove` method can be executed in one `next` pointer change.  

The `insert` method requires obtaining a new node from the system by using a `new` call and then executing two `next` pointer maneuvers.  

As we can see, in principle, if we know where a change is to be made, inserting orremoving an item from a linked list does not require moving lots of items, and insteadinvolves only a constant number of changes to node links.

The special case of adding to the front or removing the first item is thus a constant-time operation, presuming of course that a link to the front of the linked list is maintained.

The special case of adding at the end (i.e., making the new item the last item) can be constant-time,  as  long  as  we  maintain  a  link  to  the  last  node.  
Thus,  a  typical  linkedlist keeps links to both ends  of  the  list.  
Removing  the  last item is trickier, because wehave to find the next-to-last item, change its next link to nullptr, and then update thelink  that  maintains  the  last  node.  
In  the  classic  linked  list,  where  each  node  stores  alink to its next node, having a link to the last node provides no information about the next-to-last node.

The obvious idea of maintaining a third link to the next-to-last node doesn’t work,because it too would need to be updated during a remove.  
Instead, we have every nodemaintain a link to its previous node in the list.  
This is knownas a **doubly linked list**.


--------------------------------------------------------------------------------


### 3.3 `vector` and `list` in the STL

The C++ language includes, in its library, an implementation of common data structures.  
This part of the language is popularly known as the **Standard Template Library** (STL).  
The List ADT is one of the data structures implemented in the STL.  
In  general,  these  data  structures  are  called **collections** or **containers**.

There are two popular implementations of the List ADT.  

The `vector` provides a growable array implementation of the List ADT.  
The advantage of using the `vector` is that it isindexable in constant time.  
The disadvantage is that insertion of new items and removal of existing items is expensive, unless the changes are made at the end of thevector.  

The `list` provides a doubly linked list implementation of the List ADT.  
The advantage of using the `list` is that insertion of new items and removal of existing items is cheap, provided that the position of the changes is known.  
The disadvantage is that the `list` is not easily indexable.

Both `vector` and `list` are inefficient for searches.

Throughout this discussion, `list` refers to the doubly linked list in the STL, whereas list (typeset without the monospace font) refers to the more general List ADT.

Both `vector` and `list` are class templates that are instantiated with the type of items that they store.  
Both have several methods in common.  
The first three methods shown are actually available for all the STL containers:

- `int size( ) const`: returns the number of elements in the container.
- `void clear( )`: removes all elements from the container.
- `bool empty( ) const`:  returns  true  if  the  container  contains  no  elements,  and  false otherwise.

Both `vector` and `list` support adding and removing from the end of the list in constant time.  
Both `vector` and `list` support accessing the front item in the list in constant time.  
The operations are:

- `void push_back( const Object & x )`: adds x to the end of the list.
- `void pop_back( )`: removes the object at the end of the list.
- `const Object & back( ) const:` returns the object at the end of the list (a mutator that returns a reference is also provided).
- `const Object & front( ) const`: returns the object at the front of the list (a mutator thatreturns a reference is also provided).

Because a doubly linked list allows efficient changes at the front, but a vector does not, the following two methods are available only for list:

- `void push_front( const Object & x )`: adds x to the front of thelist.
- `void pop_front( )`: removes the object at the front of thelist.

The vector has its own set of methods that are not part oflist.  
Two methods allowefficient indexing.  
The other two methods allow the programmer to view and change the internal capacity.  
These methods are:

- `Object & operator[] ( int idx )`: returns the object at index `idx` in the vector, with no bounds-checking (an accessor that returns a constant reference is also provided).
- `Object & at( int idx )`: returns the object at index idx in the vector, with bounds-checking (an accessor that returns a constant reference is also provided).
- `int capacity( ) const`: returns the internal capacity of the vector. (See Section 3.4 for more details.)
- `void reserve( int newCapacity )`: sets the new capacity. If a good estimate is available, it can be used to avoid expansion of thevector. (See Section 3.4 for more details.)


#### 3.3.1 Iterators

Some  operations  on  lists,  most  critically  those  to  insert  and  remove  from  the  middleof  the  list,  require  the  notion  of  a  position.  
In  the  STL,  a  position  is  represented  by  anested  type,iterator.  
In  particular,  for  a `list<string>`,  the  position  is  represented  bythe type `list<string>::iterator`;  
for a `vector<int>`, the position is represented by a class `vector<int>::iterator`, and so on.  
In describing some methods, we’ll simply useiteratoras a shorthand, but when writing code, we will use the actual nested class name.

Initially, there are three main issues to address:  

1. first, how one gets an iterator;
2. second, what operations the iterators themselves can perform;
3. third, which List ADT methodsrequire iterators as parameters.


##### Getting an Iterator

For the first issue, the STL lists (and all other STL containers) define a pair of methods:

- `iterator begin( )`:  returns  an  appropriate  iterator  representing  the  first  item  in  thecontainer.
- `iterator end( )`:  returns  an  appropriate  iterator  representing  the  endmarker  in  thecontainer (i.e., the position after the last item in the container).

The end method seems a little unusual, because it returns an iterator that is “out-of-bounds.”  
To see the idea, consider the following code typically used to print the items in a vector `v` prior to the introduction of range-based for loops in C++11:

```cs
for( int i = 0; i != v.size( ); ++i )
    cout << v[i] << endl;
```

If we were to rewrite this code using iterators, we would see a natural correspondence with the `begin` and `end` methods:

```cs
for( vector<int>::iterator itr = v.begin( ); itr != v.end( ); itr.???)
    cout << itr.??? << endl;
```

In the loop termination test, both `i!=v.size( )` and `itr!=v.end( )` are intended to test ifthe loop counter has become “out-of-bounds.”  
The code fragment also brings us to the second issue, which is that the iterator must have methods associated with it (these unknown methods are represented by???).


##### Iterator Methods

Based on the code fragment above, it is obvious that iterators can be compared with `!=` and `==`, and likely have copy constructors and `operator=` defined.  
Thus, iterators have methods, and many of the methods use operator overloading.  
Besides copying, the most commonly used operations on iterators include the following:

- `itr++` and `++itr`: advances the iterator `itr` to the next location. Both the prefix and postfix forms are allowable.
- `*itr`: returns a reference to the object stored at iterator itr’s location. The reference returned may or may not be modifiable (we discuss these details shortly).
- `itr1 == itr2`: returns true if iterators itr1 and itr2 refer to the same location and false otherwise.
- `itr1 != itr2`: returns true if iterators itr1 and itr2 refer to a different location and false otherwise.

With these operators, the code to print would be

```cs
for( vector<int>::iterator itr = v.begin( ); itr != v.end( ); ++itr )
    cout << *itr << endl;
```

The use of operator overloading allows one to access the current item, then advance tothe next item using `*itr++`.  
Thus, an alternative to the fragment above is

```cs
vector<int>::iterator itr = v.begin( );
while( itr !=v.end( ) )
    cout << *itr++ << endl;
```


##### Container Operations That Require Iterators

For the last issue, the three most popular methods that require iterators are those that addor remove from the list (either a vector or list) at a specified position:

- `iterator insert( iterator pos, const Object & x )`: adds x into the list, prior to the position given by the iterator pos. This is a constant-time operation for list, but not for vector. The return value is an iterator representing the position of the inserted item.
- `iterator erase( iterator pos )`: removes the object at the position given by the iterator. This is a constant-time operation forlist, but not forvector. The return value isthe position of the element that followed pos prior to the call. This operation invalidates pos, which is now stale, since the container item it was viewing has been removed.
- `iterator erase( iterator start, iterator end )`: removes all items beginning at posi-tionstart, up to, but not includingend. Observe that the entire list can be erased bythe call `c.erase( c.begin( ), c.end( ) )`.


#### 3.3.2 Example: Using `erase` on a List

As an example, we provide a routine that removes every other item in a list, starting withthe initial item.  
Thus if the list contains 6, 5, 1, 4, 2, then after the method is invoked itwill contain 5, 4.  
We do this by stepping through the list and using theerasemethod onevery second item.  
On a list, this will be a linear-time routine because each of the callstoerasetakes constant time, but in a vector the entire routine will take quadratic time because each of the calls to erase is inefficient, usingO(N) time.  
As a result, we wouldnormally write the code for a list only.  
However, for experimentation purposes, we writea general function template that will work with both a list or avector, and then provide timing information.  
The function template is shown in Figure 3.5.  
The use of `auto` at line 4 is a C++11 feature that allows us to avoid the longer type `Container::iterator`.  
If we run the code, passing a `list<int>`, it takes 0.039 sec for a 800,000-item list, and 0.073 secfor an 1,600,000-item list, and is clearly a linear-time routine, because the running time increases by the same factor as the input size.  
When we pass a `vector<int>`, the routine takes almost five minutes for an 800,000-item vector and about twenty minutes for an 1,600,000-item vector;  
the four fold increase in running time when the input increases by only a factor of two is consistent with quadratic behavior.


###### Figure 3.5 Using iterators to remove every other item in a List (either a vector or list). Efficient for a list, but not for a vector.

```cs
1template <typename Container>
2void removeEveryOtherItem( Container & lst )
3{
4   auto itr = lst.begin( );     // itr is a Container::iterator
5
6   while( itr != lst.end( ) )
7   {
8       itr = lst.erase( itr );
9       if( itr != lst.end( ) )
10          ++itr;
11  }
12}
```


#### 3.3.3 `const_iterator`s

The result of `*itr` is not just the value of the item that the iterator is viewing but also the item itself.  
This distinction makes the iterators very powerful but also introduces some complications.  
To see the benefit, suppose we want to change all the items in a collectionto a specified value.  
The following routine works for both vector and list and runs in linear time.  
It’s a wonderful example of writing generic, type-independent code.

```cs
template <typename Container, typename Object>
void change( Container & c, const Object & newValue )
{
    typename Container::iterator itr = c.begin( );
    while( itr != c.end( ) )
        *itr++ = newValue;
}
```

To see the potential problem, suppose the Container c was passed to a routine using call-by-constant reference.  
This means we would expect that no changes would be allowed toc, and the compiler would ensure this by not allowing calls to any ofc’s mutators.  
Consider the following code that prints a list of integers but also tries to sneak in a change to the list:

```cs
void print( const list<int> & lst, ostream & out = cout )
{
    typename Container::iterator itr = lst.begin( );
    while( itr != lst.end( ) )
    {
        out << *itr << endl;
        *itr = 0;   // This is fishy!!!
        ++itr;
    }
}
```

If this code were legal, then the const-ness of thelistwould be completely meaningless,because it would be so easily bypassed.  
The code is not legal and will not compile.  
The solution provided by the STL is that every collection contains not only an `iterator` nested type but also a `const_iterator` nested type.  
The main difference between an iterator and aconst_iterator is that `operator*` for `const_iterator` returns a constant reference, and thus `*itr` for a const_iterator cannot appear on the left-hand side of an assignment statement.

Further,  the  compiler  will  force  you  to  use  a const_iterator to  traverse  a  constant collection.  
It does so by providing two versions of begin and two versions of end, as follows:

- `iterator begin( )`
- `const_iterator begin( ) const`
- `iterator end( )`
- `const_iterator end( ) const`

The two versions ofbegincan be in the same class only because the const-ness of amethod (i.e., whether it is an accessor or mutator) is considered to be part of the signature.  
We saw this trick in Section 1.7.2 and we will see it again in Section 3.4, both in the context of overloading `operator[]`.

If begin is invoked on a nonconstant container, the “mutator” version that returns an iterator is invoked.  
However, if begin is invoked on a constant container, what is returned is a const_iterator, and the return value may not be assigned to an iterator.  
If you try to do so, a compiler error is generated.  
Once itr is a const_iterator, `*itr=0` is easily detectedas being illegal.

If you use `auto` to declare your iterators, the compiler will deduce for you whether an iterator or const_iterator is substituted;  
to a large extent, this relieves the programmer  from  having  to  keep  track  of  the  correct  iterator  type  and  is  precisely  one  of  theintended uses ofauto.  
Additionally, library classes such asvectorandlistthat provide iter-ators as described above are compatible with the range-basedforloop, as are user-definedclasses.

An  additional  feature  in  C++11  allows  one  to  write  code  that  works  even  if  theContainertype does not havebeginandendmember functions.  
Non-member free func-tionsbeginandendare defined that allow one to use `begin(c)` in any place where `c.begin()` is allowed.  
Writing generic code usingbegin(c)instead of `c.begin()` has the advantage thatit allows the generic code to work on containers that havebegin/endas members, as wellas those that do not havebegin/endbut which can later be augmented with appropriate non-member functions.  
The addition ofbeginandendas free functions in C++11 is made possible  by  the  addition  of  language  features auto and decltype,  as  shown  in  the  codebelow.

```cs
template<typename Container>
auto begin( Container & c ) -> decltype( c.begin( ) )
{
    return c.begin( );
}

template<typename Container>
auto begin( const Container&c)->decltype( c.begin( ) )
{
    return c.begin( );
}
```

In this code, the return type ofbeginis deduced to be the type ofc.begin().

The code in Figure 3.6 makes use ofautoto declare the iterator (as in Fig. 3.5) anduses non-member functionsbeginandend.


###### Figure 3.6 Printing any container

```cs
/*01*/  template <typename Container>
/*02*/  void print( const Container & c, ostream & out = cout )
/*03*/  {
/*04*/      if( c.empty( ) )
/*05*/          out << "(empty)";
/*06*/      else
/*07*/      {
/*08*/          auto itr = begin( c );   // itr is a Container::const_iterator
/*09*/  
/*10*/          out << "[ " << *itr++;   // Print first item
/*11*/  
/*12*/          while( itr != end( c ) )
/*13*/              out << ", " << *itr++;
/*14*/          out << " ]" << endl;
/*15*/      }
/*16*/  }
```


--------------------------------------------------------------------------------


### 3.4 Implementation of `vector`

The `vector` will be a first-class type, meaning that unlike the primitive array in C++, the `vector` can be copied, and the memory it uses can be automatically reclaimed (via its destructor).  
InSection 1.5.7, we described some important features of C++primitive arrays:

- The array is simply a pointer variable to a block of memory; the actual array size mustbe maintained separately by the programmer.
- The block of memory can be allocated vianew[]but then must be freed viadelete[].
- The block of memory cannot be resized (but a new, presumably larger block can beobtained and initialized with the old block, and then the old block can be freed).

To avoid ambiguities with the library class, we will name our class template `Vector`.  
Before examining the `Vector` code, we outline the main details:

1. The `Vector` will maintain the primitive array (via a pointer variable to the block ofallocated memory), the array capacity, and the current number of items stored in theVector.
2. The `Vector` will implement the Big-Five to provide deep-copy semantics for the copy constructor and `operator=`, and will provide a destructor to reclaim the primitive array.  
   It will also implement C++11 move semantics.
3. The `Vector` will provide are size routine that will change (generally to a larger number)the  size  of  theVectorand  areserveroutine  that  will  change  (generally  to  a  largernumber) the capacity of theVector.  
   The capacity is changed by obtaining a new blockof  memory  for  the  primitive  array,  copying  the  old  block  into  the  new  block,  andreclaiming the old block.
4. The `Vector` will   provide   an   implementation   ofoperator[](as   mentioned   inSection 1.7.2,operator[]is typically implemented with both an accessor and mutatorversion).
5. TheVectorwill provide basic routines, such assize,empty,clear(which are typicallyone-liners),back,pop_back,andpush_back.  
   Thepush_backroutine will callreserveif thesize and capacity are same.
6. TheVectorwill provide support for the nested typesiteratorandconst_iterator,and associated begin and end methods.

Figure 3.7 and Figure 3.8 show the `Vector` class.  
Like its STL counterpart, there islimited error checking.  
Later we will briefly discuss how error checking can be provided.


```cs
/*01*/  #include <algorithm>
/*02*/  
/*03*/  template <typename Object>
/*04*/  class Vector
/*05*/  {
/*06*/    public:
/*07*/      explicit Vector(int initSize = 0) : theSize{initSize},
/*08*/                                          theCapacity{initSize + SPARE_CAPACITY}
/*09*/      { objects = new Object[theCapacity]; }
/*10*/  
/*11*/      Vector(const Vector &rhs) : theSize{rhs.theSize},
/*12*/                                  theCapacity{rhs.theCapacity}, objects{nullptr}
/*13*/      {
/*14*/          objects = new Object[theCapacity];
/*15*/          for (int i = 0; i < theSize; ++i)
/*16*/              objects[i] = rhs.objects[i];
/*17*/      }
/*18*/  
/*19*/      Vector &operator=(const Vector &rhs)
/*20*/      {
/*21*/          Vector tmp = rhs;
/*22*/          std::swap(tmp, *this);
/*23*/          return *this
/*24*/      }
/*25*/  
/*26*/      ~Vector()
/*27*/      { delete[] objects; }
/*28*/  
/*29*/      Vector(Vector &&rhs) : theSize{rhs.theSize},
/*30*/                             theCapacity{rhs.theCapacity}, objects{rhs.objects}
/*31*/      {
/*32*/          rhs.objects = nullptr;
/*33*/          rhs.theSize = 0;
/*34*/          rhs.theCapacity = 0;
/*35*/      }
/*36*/  
/*37*/      Vector &operator=(Vector &&rhs)
/*38*/      {
/*39*/          std::swap(rhs, objects);
/*40*/          std::swap(rhs.theSize, theSize);
/*41*/          std::swap(rhs.theCapacity, theCapacity);
/*42*/          
/*43*/          return *this;
/*44*/      }
/*45*/  
/*46*/      void resize(int newSize)
/*47*/      {
/*48*/          if (newSize > theCapacity)
/*49*/              reserve(newSize * 2);
/*50*/          theSize = newSize;
/*51*/      }
/*52*/  
/*53*/      void reserve(int newCapacity)
/*54*/      {
/*55*/          if (newCapacity < theSize)
/*56*/              return;
/*57*/  
/*58*/          Object *tmp = new Object[newCapacity];
/*59*/          for (int i = 0; i < theSize; ++i)
/*60*/              tmp[i] = std::move(objects[i]);
/*61*/  
/*62*/          theCapacity = newCapacity;
/*63*/          std::swap(objects, tmp);
/*64*/          delete[] tmp;
/*65*/      }
/*66*/  
/*67*/      Object &operator[](int idx)
/*68*/      { return objects[idx]; }
/*69*/      const Object &operator[](int idx) const
/*70*/      { return objects[idx]; }
/*71*/  
/*72*/      bool empty() const
/*73*/      { return theSize == 0; }
/*74*/      int size() const
/*75*/      { return theSize; }
/*76*/      int capacity() const
/*77*/      { return theCapacity; }
/*78*/  
/*79*/      void push_back(const Object &x)
/*80*/      {
/*81*/          if (theSize == theCapacity)
/*82*/              reserve(2 * theCapacity + 1);
/*83*/          objects[theSize++] = x;
/*84*/      }
/*85*/  
/*86*/      void push_back(Object &&x)
/*87*/      {
/*88*/          if (theSize == theCapacity)
/*89*/              reserve(2 * theCapacity + 1);
/*90*/          objects[theSize++] = std::move(x);
/*91*/      }
/*92*/  
/*93*/      void pop_back()
/*94*/      {
/*95*/          --theSize;
/*96*/      }
/*97*/  
/*98*/      const Object &back() const
/*99*/      {
/*100*/         return objects[theSize - 1];
/*101*/     }
/*102*/ 
/*103*/     typedef Object *iterator;
/*104*/     typedef const Object *const_iterator;
/*105*/ 
/*106*/     iterator begin()
/*107*/     { return &objects[0]; }
/*108*/     const_iterator begin() const
/*109*/     { return &objects[0]; }
/*110*/     iterator end()
/*111*/     { return &object[theSize]; }
/*112*/     const_iterator end() const
/*113*/     { return &object[theSize]; }
/*114*/ 
/*115*/     static const int SPARE_CAPACITY = 16;
/*116*/ 
/*117*/   private:
/*118*/     int theSize;
/*119*/     int theCapacity;
/*120*/     Object *objects;
/*121*/ };
```

As shown on lines 118 to 120, the `Vector` stores the size, capacity, and primitive arrayas its data members.  
The constructor at lines 7 to 9 allows the user to specify an initialsize, which defaults to zero.  
It then initializes the data members, with the capacity slightlylarger than the size, so a few `push_back`s can be performed without changing the capacity.

The copy constructor, shown at lines 11 to 17, makes a newVectorand can then beused by a casual implementation of `operator=` that uses the standard idiom of swappingin a copy.  
This idiom works only if swapping is done by moving, which itself requiresthe implementation of the move constructor and move `operator=` shown at lines 29 to 44.  
Again, these use very standard idioms.  
Implementation of the copy assignment `operator=` using a copy constructor and swap, while simple, is certainly not the most efficient method,especially in the case where bothVectors have the same size.  
In that special case, whichcan be tested for, it can be more efficient to simply copy each element one by one using Object’s `operator=`.

The `resize` routine  is  shown  at  lines  46  to  51.  
The  code  simply  sets  the `theSize` data member, after possibly expanding the capacity.  
Expanding capacity is very expensive.  
So if the capacity is expanded, it is made twice as large as the size to avoid havingto change the capacity again unless the size increases dramatically (the+1is used in casethe size is 0).  
Expanding capacity is done by the reserve routine, shown at lines 53 to 65.  
It consists of allocation of a new array at line 58, moving the old contents at lines59  and  60,  and  the  reclaiming  of  the  old  array  at  line  64.  
As  shown  at  lines  55  and 56, the `reserve` routine can also be used to shrink the underlying array, but only if the specified  new  capacity  is  at  least  as  large  as  the  size.  
If  it  isn’t,  the `reserve` request  is ignored.

The two versions of `operator[]` are trivial (and in fact very similar to the implementations of `operator[]` in thematrixclass in Section 1.7.2) and are shown in lines 67 to 70.Error checking is easily added by making sure that `index` is in the range 0 to `size()-1`, inclusive, and throwing an exception if it is not.

A host of short routines, namely,empty,size,capacity,push_back,pop_back,andback,are implemented in lines 72 to 101.  
At lines 83 and 90, we see the use of the postfix `++` operator, which usestheSizeto index the array and then increasestheSize.  
We saw the same idiom when discussing iterators: `*itr++` usesitrto decide which item to view andthen  advances `itr`.  
The  positioning  of  the `++ `matters:  
In  the  prefix++operator, `*++itr` advances `itr` and  then  uses  the  new `itr` to  decide  which  item  to  view,  and  likewise, `objects[++theSize]` would increment theSize and use the new value to index the array(which  is  not  what  we  would  want).  
pop_backandbackcould  both  benefit  from  errorchecks in which an exception is thrown if the size is 0.

Finally, at lines 103 to 113 we see the declaration of the `iterator` and `const_iterator` nested types and the two `begin` and two `end` methods.  
This code makes use of the fact that in C++, a pointer variable has all the same operators that we expect for aniterator.  
Pointer variables can be copied and compared;  
the `*` operator yields the object being pointed at,and, most peculiarly, when++is applied to a pointer variable, the pointer variable thenpoints at the object that would be stored next sequentially:  
If the pointer is pointing insidean array, incrementing the pointer positions it at the next array element.  
These semanticsfor pointers date back to the early 70s with the C programming language, upon which C++is based.  
The STL iterator mechanism was designed in part to mimic pointer operations.

Consequently, at lines 103 and 104, we seetypedefstatements that state the `iterator` and `const_iterator` are simply other names for a pointer variable, and `begin` and `end` need to simply return the memory addresses representing the first array position and the first invalid array position, respectively.

The  correspondence  between  iterators  and  pointers  for  thevectortype  means  thatusing avectorinstead of the C++array is likely to carry little overhead.  
The disadvantageis  that,  as  written,  the  code  has  no  error  checks.  
If  the  iteratoritrgoes  crashing  pastthe end marker, neither `++itr` nor `*itr` will necessarily signal an error.  
To fix this problemwould require that theiteratorandconst_iteratorbe actual nested class types rather thansimply pointer variables.  
Using nested class types is much more common and is what wewill see in the `List` class in Section 3.5.


--------------------------------------------------------------------------------


### 3.5 Implementation of `List`