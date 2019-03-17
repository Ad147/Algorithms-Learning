DSAA-Ch04-Trees.md


Notes of Data Structures and Algorithm Analysis in C++
================================================================================

Ad  
<ar><r>

Init: 19Mar13


Chapter 4 Trees
--------------------------------------------------------------------------------


**Binary search tree** is the basis for the implementation of two library collections classes, `set` and `map`.  
For a binary search tree, the average running time of most operations is O(logN).

*Trees* in general are very useful abstractions in computer science, so we will discuss their use in other, more general applications.

In this chapter:

- See how trees are used to implement the file system of several popular operationg systems.
- See how trees can be used to evaluate arithmetic expressions.
- Show how to use trees to support searching operations in O(logN) average time and how to refine these ideas to obtain O(logN) worst-case bounds.  
  We will also see how to implement these operations when the data are stored on a disk.
- Discuss and use the `set` and `map` classes.


--------------------------------------------------------------------------------


- [Chapter 4 Trees](#chapter-4-trees)
  - [4.1 Preliminaries](#41-preliminaries)
    - [4.1.1 Implementation of Trees](#411-implementation-of-trees)
    - [4.1.2 Tree Traversals with an Application](#412-tree-traversals-with-an-application)
  - [4.2 Binary Trees](#42-binary-trees)
    - [4.2.1 Implementation](#421-implementation)
    - [4.2.2 An Example: Expression Trees](#422-an-example-expression-trees)
  - [4.3 The Search Tree ADT - Binary Search Trees](#43-the-search-tree-adt---binary-search-trees)
    - [4.3.1 `contains`](#431-contains)
    - [4.3.2 `findMin` and `findMax`](#432-findmin-and-findmax)
    - [4.3.3 `insert`](#433-insert)
    - [4.3.4 `remove`](#434-remove)
    - [4.3.5 Destructor and Copy Constructor](#435-destructor-and-copy-constructor)
    - [4.3.6 Average-Case Analysis](#436-average-case-analysis)
  - [4.4 AVL Trees](#44-avl-trees)


--------------------------------------------------------------------------------


### 4.1 Preliminaries

Recursive definition of a **tree**:  
A tree is a collections fo nodes.  
The collection can be empty;  
otherwise, a tree consists of a distinguished node, *r*, called the **root**, and zero or more nonempty (sub)trees T1, T2, ..., Tk, each of whose roots are connected by a directed **edge** from r.

The root of each subtree is a **child** of r, and r is the **parent** of each subtree root.

From the recursive definition, a tree is a collection of N nodes, one of which is the root, and N-1 edges.  
That there are N-1 edges follows from the fact that each edge connects some node to its parent, and every node except the root has one parent.

Each node may have an arbitrary number of children, possibly zero.  
Nodes with no children are **leaves**.  
Nodes with the same parent are **siblings**;  
**Grandparent** and **grandchild** relations can be defined in a similar manner.

A **path** from node n1 to nk is defined as a sequence of nodes n1, n2, ..., nk such that ni is the parent of ni+1 for 1<=i<k.  
The **length** of this path is the number of edges on the path, namely, k-1.  
There is a path of length zero from every node to itself.  
Notice that in a tree there is exactly one path from the root to each node.

For any node ni, the **depth** of ni is the length of the unique path from the root to ni.  
Thus, the root is at depth 0.  
The **height** of ni is the length of the longest path from ni to a leaf.  
Thus all leaves are at height 0.  
The height of a tree is equal to the height of the root.  
The depth of a tree is equal to the depth of the deepest leaf;  
this is always equal to the height of the tree.

If there is a path from n1 to n2, then n1 is an ancestor of n2 and n2 is a descendant of n1.  
If n1 != n2, then n1 is a proper ancestor of n2 and n2 is a proper descendant of n1.


#### 4.1.1 Implementation of Trees

One way is to have a link to each child for each node.  
However, since the number of chiledren per node can vary greatly and is not known in advance, there would be too much wasted space.

The solution:  
Keep the children of each node in a linked list of tree nodes:

```cs
struct TreeNode
{
    Object element;
    TreeNode *firstChild;
    TreeNode *nextSibling;
};
```


#### 4.1.2 Tree Traversals with an Application

One of the popular applications is the directory structure in many common operating syustem including UNIX and DOS.

The root of the directory is `/usr`.  
The filename  `/usr/mark/book/ch1.r` is obtained by following the left most child three times.  
Each `/` after the first indicated an edge;  
the result is the full **pathname**.  
This hierarchical file system is very popular because it allows users to organize their data logically.  
Furthermore, two files in different directories can share the same name, they have diffrent pathnames.

A directory in the UNIX file system is just a file with a list of all its children, so the directories are structured almost exactly in accordance with the type declaration above.  
Indeed, on some versions of UNIX, if the normal command to print a file is applied to a directory, then the names of the files in the directory can be seen in the output (along with other non-ASCII information).

Suppose we would like to list the names of all the files in the directory.  
The output format will be that files that are depth di will have their names indented by di tabs.  
The algorithm is given in Figure 4.6 as pseudocode.


###### Figure 4.6 Pseudocode to list a directory in a hierachical file system

```cs
void FileSystem::listAll(int depth = 0) const
{
    printName(depth); // Print the name of the object
    if (isDirectory())
        for each file c in this directory (for each child)
            c.listAll(depth + 1);
}
```

This traversal strategy is known as a **preorder traversal**.  
In a preorder traversal, work at a node is performed before (*pre*) its children are processed.  
The running time is O(N).

Another common method of traversing a tree is the **postorder traversal**.  
In a postorder traversal, the work at a node is performed after (*post*) its children are evaluated.

Suppose we would like to calculate the total number of disk blocks used by all the files in the tree.  
The most natural way to do this would be to find the number of blocks contained in the subdirectories.  
The pseudocode method `size` in Figure 4.9 implements this strategy.


###### Figure 4.9 Pseudocode to calculate the size of a directory

```cs
int FileSystem::size() const
{
    int totalSize = sizeOfThisFile();
    if (isDirectory())
        for each file c in this directory (for each child)
            totalSize += c.size();

    return totalSize;
}
```

If the current object is not a directory, then `size` merely returns the number of blocks it uses in the current object.  
Otherwise, the number of blocks used by the directory is added to the number of blocks (recursively) found in all the children.


--------------------------------------------------------------------------------


### 4.2 Binary Trees

A binary tree is a tree in which no node can have more than two children.

A property of a binary tree is that the depth of an average binary tree is smaller than N.  
An analysis shows that the average depth is O(√N), and that for a *binary search tree*, the average depth is O(logN).  
The worst case can be N-1.


#### 4.2.1 Implementation

As a binary tree node has at most two children, we can keep direct links to them:

```cs
struct BinaryNode
{
    Object element;     // The data in the node
    BinaryNode *left;   // Left child
    BinaryNode *right;  // Right child
}
```

We could draw the binary trees using the rectangular boxes that are customary fro linked lists, but trees are generally drawn as circles connected by lines, because they are actually *graphs*.  
Every binary tree with N nodes would require N+1 nullptr links.

Binary trees have many important uses not associated with searching.  
One of the principal uses of binary trees is in the area of compliler design, which we will now explore.


#### 4.2.2 An Example: Expression Trees

An **expression tree** presents an expression.  
The leaves of an expression tree are **operands**, and other nodes contain **operators**.  
This particular tree happens to be binary, because all the operators are binary.  
It is also possible for a node to have only one child, like **unary minus** operator.

We can evaluate an expression tree T, by applying the operator at the root to the values obtained by recursively evaluating the left and right subtrees.

We can produce an (overly parenthesized) infix expression by recusively producing a parenthesized left expression, then printing out the operator at the root, and finally recursively producing a parenthesized right expression.  
This general strategy (left, node, right) is an **inorder traversal**.

An alternate traversal strategy is to recursively print out the left subtree, the right subtree, and then the operator.  
The output is a postfix expression.  
This traversal strategy is generally known as a *postorder* traversal.

A third traversal strategy is to print out the operator frist and then recursively print out the left and right subtree.  
The resulting expression is the less useful prefix notation, and the traversal strategy is a *preorder* traversal.


##### Constructing an Expression Tree

We now give an algorithm to convert a postfix into an expression tree.  
The method strongly resembles the postfix eveluation algorithm of Section 3.6.3.

We read our expression one symbol at a time.

- If the symbol is an operand, we create a one-node tree and push a pointer to it onto a stack.
- If the symbol is an operator, we pop (pointers) to two trees T1 and T2 from the stack (T1 is popped first) and form a new tree whose root is the operator and whose left and right children point to T2 and T1, respectively.  
  A pointer to the new tree is then pushed onto the stack.


--------------------------------------------------------------------------------


### 4.3 The Search Tree ADT - Binary Search Trees

An important application of binary trees is in searching.

Assuming that all the items are distinct, and duplicates will bu dealt later.

For every node X in a BST, the values of all the items in its left subtree are smaller than the item in X, and the values of all the items in its right subtree are larger than the item in X.  
Notice that this implies that all the elements in the tree can be ordered in some consistent manner.


##### Operations That are Usually Performed on BST

Because of the recursive definition of trees, it is common to write these routines recursively.  
Because the average depth of a BST turns out to be O(logN), we generally do not need to woory about running out of stack space.

Figure 4.16 show the interface.  
There are serveral things worth noticing.  
Searching is based on the `<` operator that must be defined for the particular `Comparable` type.  
Specifically, item x matches y if both `x<y` and `y<x` are false.  
THis allows `Comparable` to be a complex type (such as the social security number data member or salary).


###### Figure 4.16 Binary search tree class skeleton

```cs
template <typename Comparable>
class BinarySearchTree
{
  public:
    BinarySearchTree();
    BinarySearchTree(const BinarySearchTree &rhs);
    BinarySearchTree(BinarySearchTree &&rhs);
    ~BinarySearchTree();

    const Comparable &findMin() const;
    const Comparable &findMax() const;
    bool contains(const Comparable &x) const;
    bool isEmpty() const;
    void printTree(ostream *out = cout) const;

    void makeEmpty();
    void insert(const Comparable &x);
    void insert(Comparable &&x);
    void remove(const Comparable &x);

    BinarySearchTree &operator=(const BinarySearchTree &rhs);
    BinarySearchTree &operator=(BinarySearchTree &&rhs);

  private:
    struct BinaryNode
    {
        Comparable element;
        BinaryNode *left;
        BinaryNode *right;

        BinaryNode(const Comparable &theElement, BinaryNode *lt, BinaryNode *rt)
            : element{theElement}, left{lt}, right{rt} { }
        
        BinaryNode(Comparable &&theElement, BinaryNode *lt, BinaryNode *rt)
            : element{theElement}, left{lt}, right{rt} { }
    }

    BinaryNode *root;

    void insert(const Comparable &x, BinaryNode *&t);
    void insert(Comparable &&x, BinaryNode *&t);
    void remove(const Comparable &x, BinaryNode *&t);
    BinaryNode *findMin(BinaryNode *t) const;
    BinaryNode *findMax(BinaryNode *t) const;
    bool contains(const Comparable &x, BinaryNode *t) const;
    void makeEmpty(BinaryNode *&t);
    void printTree(BinaryTreeNode *t, ostream &out) const;
    BinaryNode *clone(BinaryNode *t) const;
}
```

The data member is a pointer to the root node;  
this pointer is nullptr for empty trees.  
The public member functions use the general technique of calling private recursive functions.  
An example of how this is done for contains, insert and remove is shown in Figure 4.17.


###### Figure 4.17 Illustration of public member functions calling private recursive member function

```cs
// Returns true if x is found in the tree.
bool contains(const Comparable &x) const
{
    return constains(x, root);
}

// Insert x into the tree; duplicates are ignored.
void insert(const Comparable &x)
{
    insert(x, root);
}

// Remove x from the tree. Nothing is done if x is not found.
void remove(const Comparable &x)
{
    remove(x, root);
}
```

Serveral of the private member functions use the technique of passing a pointer variable using call-by-reference.  
This allows the public member functions to pass a pointer to the root to the private recursive member functions.  
The recursive functions can then change the value of the root so that the root points to another node.


#### 4.3.1 `contains`

This operation requires returning `true` if there is a node in tree T that has item X, of `false` is there is no such node.  

- If T is empty, return false.
- Otherwise, if the item stored at T is X, return true.
- Otherwise, make a recursive call on a subtree of T, either left or right, depending on the relationship of X to the item stored in T.


###### Figure 4.18 `contains` operation for binary search trees

```cs
// Internal method to test if an item is in a subtree.
// x is item to search for.
// t is the node that roots the subtree.
bool contains(const Comparable &x, BinaryNode *t) const
{
    if (t == nullptr)
        return false;
    else if (x < t->element)
        return constains(x, t->left);
    else if (t->element < x)
        return contains(x, t->right);
    else
        return true; // Match
}
```

Notice the order of the tests.  
It is crucial that the empth test be performed first, since otherwise, a run time error attempting to access a data member through a nullptr would be generated.  
The remaining tests are arranged with the **least likely case last**.  
Also note that both recusive calls are tail recursions and can be easily removed with a while loop.  
The use of tail recursion is justifiable here because **the simplicity of algorithm expression** compensates for the decrease in speed, and the amount of stack space used is expected to be only O(logN).

Figure 4.19 shows the trivial changes required to use a function object rather than requiring that the items be Comparable.


###### Figure 4.19 Illustrates use of a function object to implement binary search tree

```cs
template <typename Object, typename Comparator=less<Object>>
class BinarySearchTree
{
  public:

    // Same methods, with Object replacing Comparable

  private:
    BinaryNode *root;
    Comparator isLessThan;

    // Same methods, with Object replacing Comparable

    // Internal method to test if an item is in a subtree.
    // x is item to search for.
    // t is the node that roots the subtree.
    bool contains(const Object &x, BinaryNode *t) const
    {
        if (t == nullptr)
            return false;
        else if (isLessThan(x, t->element))
            return contains(x, t->left);
        else if (isLessThan(t->element, x))
            return contains(x, t->right);
        else
            return true; // Match
    }
};
```


#### 4.3.2 `findMin` and `findMax`

These private routines return a pointer to the node containing the smallest and largest elements in the tree, respectively.  
To perform a findMin, start at the root and go left as long as there is a left child.  
The stopping point is the smallest element.

Many programmers do not bother using recursion.  
We will code the routines both ways by doing findMin recursively and findMax nonrecursively.


###### Figure 4.20 Recusive implementation of findMin for binary search trees

```cs
// Internal method to find the smallest item in a subtree t.
// Return node containing the smallest item.
BinaryNode *findMin(BinaryNode *t) const
{
    if (t == nullptr)
        return nullptr;
    if (t->left == nullptr)
        return t;
    return findMin(t->left);
}
```


###### Figure 4.21 Nonrecursive implementation of findMax for binary search trees

```cs
// Interal method to find the largest item in a subtree t.
// Return node containing the largest item.
BinaryNode *findMax(Binary *t) const
{
    if (t != nullptr)
        while (t->right != nullptr)
            t = t->right;
    return t;
}
```

Notice how we carefully handle the degenerate case of an empty tree.  
Although this is always important to do, it is especially crucial in recursive programs.  
Also notice thst it is safe to change t in finMax, since we are only working with a copy of a pointer.  
Always be extremly careful, however, bacause a statement such as t->right = t->right->right will make changes.


#### 4.3.3 `insert`

To insert X into T, proceed down the tree as you would with a contains.

- If X is found, do nothing.
- Otherwise, insert X at the last spot on the path traversed.

Duplicates can be handled by keeping an extra field in the node record indicating the frequency of occurence.  
This adds some extra space to the entire tree but is better thatn putting duplicates in the tree (which tends to make the tree very deep).  
Of course, this strategy does not work if the key that guides the < operator is only part of a larger structure.  
If that is the case, then we can keep all of the structures that have the same key in an auxiliary data structure, such as a list of another search tree.


###### Figure 4.23  Insertion into a binary search tree

```cs
// Internal method to insert into a subtree.
// x is the item to insert.
// t is the node that roots the subtree.
// Set the new root of the subtree.
void insert(const Comparable &x, BinaryNode *&t)
{
    if (t == nullprt)
        t = new BinaryNode{x, nullptr, nullptr};
    else if (x < t->element)
        insert(x, t->left);     // Line 12
    else if (t->element, x)
        insert(x, t->right);    // Line 14
    else
        ; // Duplicate; do nothing
}

// There is a move version of insert.
```

Line 12 and 14 recursively insert and attach x into the appropriate subtree.  
Notice that in the recursive routine, the only time that t changes is when a new leaf is created.  
When this happens, it means that the recursive routine has been called from some other node p, which is to be the leaf's parent.  
The call will be `insert(x, p->left)` or `insert(x, p->right)`.  
Either way, t is now a reference to either p->left or p->right, meaning that p->left or p->right will be changed to point at the new node.  
All in all, a slick maneuver.


#### 4.3.4 `remove`

As is common with many data structures, the hardest operation is deletion.  
Once we have found the node to be deleted:

- If the node is a leaf, it can be deleted immediately.
- If the node has one child, the node can be deleted after its parent  adjusts a link to bypass the node.
- Has two children: general strategy is to replace the data of this node with the smallest data of the right subtree and recursively delete that node.

The code in Figure 4.26 performs deletion.  
It is inefficient because it makes two passes down the tree to find and delete the smallest node in the right subtree.  
It is easy  to remove this inefficieny by writing a special `removeMin` method, and we have left it in only for simplicity.


###### Figure 4.26 Deletion routine for binary search trees

```cs
// Interal method to remove from a subtree.
// x is the item to remove.
// t is the node that roots the subtree.
// Set the new root of the subtree.
void remove(const Comparable &x, BinaryNode *&t)
{
    if (t == nullptr)
        return; // Item not found; do nothing
    if (x < t->element)
        remove(x, t->left);
    else if (t->element < x)
        remove(x, t->right);
    else if (t->left != nullptr && t->right != nullptr) // Two children
    {
        t->element = findMin(t->right)->element;
        remove(t->element, t->right);
    }
    else
    {
        BinaryNode *oldNode = t;
        t = (t->left != nullptr) ? t->left : t->right;
        delete oldNode;
    }
}
```

If the number of deletions is expected to be small, then a popular strategy to use is **lazy deletion**:  
When an element is to be deleted, it is left in the tree and merely *marked* as being deleted.  
This is especially popular if duplicate items are present, because then the data member that keeps count of the frequency of appearance can be decremented.  
If the number of real nodes in the tree is the same as the number of “deleted” nodes, then the depth of the tree is only expected to go up by a small constant (why?), so there is a very small time penalty associated with lazy deletion.  
Also, if a deleted item is reinserted, the overhead of allocating a new cell is avoided.


#### 4.3.5 Destructor and Copy Constructor

As usual, the destructor calls `makeEmpty`.  
Notice that at the end, t, and thus root, is changed to point at nullptr.


###### Figure 4.27 Destructor and recusive makeEmpty member function

```cs
// Destrucotr for the tree
~BinarySearchTree()
{
    makeEmpty();
}

// Internal method to make subtree empty.
void makeEmpty(BinaryNode *&t)
{
    if (t != nullptr)
    {
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
    }
    t = nullptr;
}
```

The copy constructor, first initializing root to nullptr and then making a copy of rhs.  
We use a very slick recursive function named clone to do all the dirty work.


###### Figure 4.28 Copy constructor and recusive clone member function

```cs
// Copy constructor
BinarySearchTree(const BinarySearchTree &rhs) : root{nullptr}
{
    root = clone(rhs.root);
}

// Internal method to clone subtrees.
BinaryNode *clone(BinaryNode *t) const
{
    if (t === nullptr)
        return nullptr;
    else
        return new BinaryNode{t->element, clone(t->left), clone(t->right)};
}
```


#### 4.3.6 Average-Case Analysis

Indeed, the running time of all of the operations (except makeEmpty and copying)is O(d), where d is the depth of the node containing the accessed item.

We prove that the average depth over all nodes is O(logN) on the assumption that all insertion sequences are equally likely.

The sum of the depth of all nodes in a tree is known as the **internal path length**.


##### Calculation of average internal path length

Let D(N) be the internal path length for some tree T of N nodes.  
D(1) = 0.  
An N-node tree consists of an i-node left subtree and an (N-i-1)-node right subtree, plus a root at depth zero for 0 <= i < N.  
D(i) is the interal path length of the left subtree with respect to its root.  
We get the recurrence

$$ D(N) = D(i) + D(n-i-1) + N - 1 $$

If all subtree sizes are equally likely, which is true for binary search trees (since the subtree size depends only on the relative rank oof the first element inserted into the tree), but not binary trees, then the average value of both D(i) and D(N-i-1) is $(1/N)\sum^{N-1}_{j=0} D(j)$.  
This yields

$$ D(N) = \frac2 N \sum^{N-1}_{j=0} D(j) + N - 1 $$

This recurrence will be encountered and solved in Chapter 7, obtaining an average value of D(N) = O(NlogN).  
Thus expected depth of any node is O(logN).

It is not entirely true that the average running time of all the operations discussed in the previous section if O(logN).  
That is because of deletions, the deletion algorithm favors making the left subtree deeper than the right.  
The exact effect of this strategy is still unknown, but it seems only to be a theoretical novelty.  
It has shown that if we alternate insertions and deletions Θ(N^2) times, then the tree will have an expected depth of Θ(√N).

One solution is to insist on an extra structual condition called *balance*:  
No node is allowed to get too deep.

There are quite a few general algorithms to implement balanced trees.  
Most are quite a bit more complicated than a standard binary search tree, and all take longer on average for updates.  
However, providing protection against the embarrasingly simple cases.

A second method is to forgo the balance condition and allow the tree to be arbitrarily deep, but after every operation, a resturcturing rule is applied that tend to make future operations efficient.  
These types of data structures are generally classifiedf as **self-adjusting**.  
In the case, we can no longer guarantee an O(logN) bound on any single operation but can show that any sequence of M operations takes total time O(MlogN) in the worst case.  
The data structure is known as a splay tree; its analysis is fairly intricate and is discussed in Chapter 11.


--------------------------------------------------------------------------------


### 4.4 AVL Trees

