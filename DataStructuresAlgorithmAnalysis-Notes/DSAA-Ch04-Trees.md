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
    - [4.4.1 Single Rotation](#441-single-rotation)
    - [4.4.2 Double Rotaion](#442-double-rotaion)
  - [4.5 Splay Trees](#45-splay-trees)
    - [4.5.1 A Simple Idea (That Does Not Work)](#451-a-simple-idea-that-does-not-work)
    - [4.5.2 Splaying](#452-splaying)
  - [4.6 Tree Traversal (Revisited)](#46-tree-traversal-revisited)
  - [4.7 B-Trees](#47-b-trees)
  - [4.8 Sets and Maps in the Standard Library](#48-sets-and-maps-in-the-standard-library)
    - [4.8.1 Sets](#481-sets)
    - [4.8.2 Maps](#482-maps)


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

An **AVL (Adelson-Velskii and Landis) tree** is identical to a binary search tree, except that for every node in the tree, the height of the left and right subtrees can differ by at most 1.  
(The height of an empty tree is defined to be -1.)

It can be shown that the height of an AVL tree is at most roughly $1.44log(N+2)-1.328$, but in practice it is only slightly more than logN.

Thus, all the operations can be performed in O(logN) time, except possibly insertion and deletion.  
When we do an insertion, we need to update all the balancing information for the nodes on the path back to the root, but the reason that insertion is potentially difficult is that inserting a node could violate the AVL tree property.  
Then the property has to be restored before the insertion step is considered over.  
It turns out that this can always be done with **rotation**.

After an insertion, only nodes that are on the path from the insertion point to the root might have their balance altered.  
As we follow the path up to the root and update the balancing information, we may find a node whose new balance violates the AVL condition.  
We will show how to rebalance the tree at the first (i.e. deepest) such node.  
This rebalancing guarantees that the entire tree satisfies the AVL property.

Assuming α is to be rebalanced.  
There are 4 cases:

1. An insertion into `α->left->left`
2. An insertion into `α->left->right`
3. An insertion into `α->right->left`
4. An insertion into `α->right->right`

Cases 1 and 4, 2 and 3 are mirror image symmetries with respect to α.  

- Consequently, as a matter of theory, there are two basic cases.  
- From a programming perspective, there are still four cases.

The first case, in which the insertion occurs on the "outside" (i.e., left-left or right-right), is fixed by a **single rotation** of the tree.  
The seconde case, in which the insertion occurs on the "inside" (i.e., left-right or right-left) is handled by the slightly more complex **double rotation**.


#### 4.4.1 Single Rotation

```
    k2             k1
   /  \           /  \
  k1       -->   X   k2
 /  \               /  \
X    
```

Node k2 violates the AVL balance property because its left subtree is two level deeper than its right subtree.  
The situation depicted is the **only** possible case 1 scenario that allows k2 to satisfy the AVL property before an insertion but violate it afterwards.

To ideally rebalance the tree, we would like to move X up a level and Z (`k2->right`) down a level.  
The result is that k1 will be the new root.  
Subtree Y (`k1->right`) which holds items that are between k1 and k2 in the original tree, can be placed as k2's left child in the new tree.

This work requires only a few pointer changes.  
k2 and k1 not only satisfy the AVL requirements, but they also have subtrees that are exactly the same height.  
Furthermore, the new height of the entire subtree is *exactly the same* as the height of the original subtree prior to the insertion that caused X to grow.  
Thus *no further rotations are needed*.


#### 4.4.2 Double Rotaion


###### Left-right double rotation to fix case 2

```
    k3               k2
   /  \             /  \
  k1       -->    k1    k3
 /  \            /  \  /  \
    k2
   /  \
```

To rebalace in this situation, we cannot leave k3 as the root, and a rotation between k3 and k1 do not work, so the only alternative is to place k2 as the new root.  
This force k1 to be k2's left child and k3 to be its right child, and it also completely determines the resulting location of the four subtrees (`k1->left`, `k2->left`, `k2->right`, `k3->right`).  
The resulting tree restores the height to what it was befor the insertion, thus guaranteeing that all rebalancing and height updating is complete.

The programming details are fairly straightforward except that there are several cases.  
To insert a new node with item X into an AVL tree T, we recursively insert X into the appropriate subtree of T (call this $T_{LR}$).  
If the height of TLR does not change, then we are done.  
Otherwise, if a height imbalance appears in T, we do the appropriate single or double rotation depending on X and the items in T and TLR, update the heights (making the connection from the rest of the tree above), and we are done.

Since one ratation always suffices, a carefully coded nonrecursive version generally turn out to be faster, but on modern compilers the difference is not as significant as in the past.  
However, nonrecursive versions are quite difficult to code correctly, whereas a casual recursive implementation is easily readable.

###### Figure 4.40 Node declaration for AVL trees

```cs
struct AvlNode
{
    Comparable element;
    AvlNode *left;
    AvlNode *right;
    int height;

    AvlNode(const Comparable &ele, AvlNode *lt, AvlNode *rt, int h = 0)
        : element{ele}, left{lt}, right{rt}, height{h} {}
    
    AvlNode(Comparable &&ele, AvlNode *lt, AvlNode *rt, int h = 0)
        : element{std::move(ele)}, left{lt}, right{rt}, height{h} {}
};
```


###### Figure 4.41 Function to compute height of an AVL node

```cs
// Return the height of node t or -1 if nullptr.
int height(AvlNode *t) const
{
    return t ? t->height : -1;
}
```


###### Figure 4.42 Insertion into an AVL tree

```cs
// Internal method to insert into a subtree.
// x is the item to insert.
// t is the node that roots the subtree.
// Set the new root of the subtree.
void insert(const Comparable &x, AvlNode *&t)
{
    if (!t)
        t = new AvlNode{x, nullptr, nullptr};
    else if (x < t->element)
        insert(x, t->left);
    else if (t->element < x)
        insert(x, t->right);
    
    balance(t);
}

static const int ALLOWED_IMBALANCE = 1;

// Assume t is balanced or within one of being balanced
void balance(AvlNode *&t)
{
    if (!t)
        return;
    
    if (height(t->left) - height(t->right) > ALLOWED_IMBALANCE)
        if (height(t->left->left) >= height(t->left->right))
            rotateWithLeftChild(t);
        else
            doubleWithLeftChild(t);
    else if (height(t->right) - height(t->left) > ALLOWED_IMBALANCE)
        if (height(t->right->right) >= height(t->right->left))
            rotateWithRightChild(t);
        else
            doubleWithRightChild(t);
    

    t->height = max(height(t->left), height(t->right) + 1;
}
```


###### Figure 4.44 Routine to perform single rotation

```cs
// Rotate binary tree node with left child.
// For AVL trees, this is a single rotation for case 1.
// Update heights, then set new root.
void rotateWithLeftChild(AvlNode *&k2)
{
    AvlNode *k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;
    k2->height = max(height(k2->left), height(k2->right)) + 1;
    k1->height = max(height(k1->left), k2->height) + 1;
    k2 = k1;
}
```


###### Figure 4.46 Routine to perform double rotation

```cs
// Double rotate binary tree node: first left child
// with its right child; then node k3 with new left chlid.
// For AVL trees, this is a double rotation for case 2.
// Update heights, then set new root.
void doubleWithLeftChild(AvlNode *&k3)
{
    rotateWithRightChild(k3->left);
    rotateWithLeftChild(k3);
}
```

A deletion could cause one side of the tree to become two levels shallower than the other side.  
The case-by-case analysis is similar to insertion, but not exactly the same.  
For instance, case 1 that reflect a deletion from tree Z (k2->right) (rather than an insertion into X), must be augmented with the possibility that tree Y could be as deep as tree X.  
Even so, it is easy to see that the rotation rebalances this case and the symmetric case 4.  
Thus the code in Figure 4.42 lines 28 and 34 uses >= instead of > specifically to ensure that single rotations are done in these cases rather than double rotations.


###### Figure 4.47 Deletion in an AVL tree

```cs
// Internal method to remove from a subtree.
// x is the item to remove.
// t is the node that roots the subtree.
// Set the new root of the subtree.
void remove(const Comparable &x, AvlNode *&t)
{
    if (!t)
        return;
    
    if (x < t->element)
        remove(x, t->left);
    else if (t->element < x)
        remove(x, t->right);
    else if (t->left && t->right)
    {
        t->element = findMin(t->right)->element;
        remove(t->element, t->right);
    }
    else
    {
        AvlNode *old = t;
        t = t->left ? t->left : t->right;
        delete old;
    }
    
    balance(t);
}
```


--------------------------------------------------------------------------------


### 4.5 Splay Trees

**Splay tree** guarantees that any M consecutive tree operations starting from an empty tree takes at most $O(MlogN)$ time.  
Although this guarantee does not preclude the possibility that any *single* operatio might take Θ(N) time, and thus the bound is not as strong as an O(logN) worst-case bound per operation, the net effect is the same:  
There are not bad input sequences.

Generally, when a sequence of M operations has total worst-case running time of $O(Mf(N))$, then the **amortized** running time is $O(f(N))$.  
Thus, a splay tree has an O(logN) amortized cost per operation.  
Over a long sequence of operations, some may take more, some less.

Splay trees are based on the fact that the O(N) worst-case time per operation for binary search trees is not bad, as long as it occurs relatively infrequently.  
Any one access, even if it takes Θ(N), is still likely to be extremely fast.  
The problem with binary search trees is that it is possible, and not uncommon, for a whole sequence of bad access to take palce.  
The cumulative running time then becomes noticeable.  
A search tree data structure with O(N) worst-case time, but a *guarantee* of at most O(MlogN) for any M consecutive operations, is certainly satisfactory, because there are no bad sequences.

If any particular operation is allowed to have an O(N) worst-case time bound, and we still want an O(logN) amortized time bound, then it is clear that whenever a node is accessed, it must be moved.  
Otherwise, once we find a deep node, we could keep performing accesses on it.  
If the node does not change location, and each access costs Θ(N), then a sequence of M accesses will cost Θ(M·N).

The basic idea of the splay trees is that after a node is accessed, it is pushed to the root by a series of AVL tree rotations.  
Notice that if a node is deep, there are many nodes on the path that are also relatively deep, and by restructing we can make future accesses cheaper on all these nodes.  
Thus, if the node is unduly deep, then we want this restructuring to have the side effect of balancing the tree (to some extent).  
Besides giving a good time bound in theory, this method is likely to have practical utility, because in many applications, when a node is accessed, it is likely to be accessed again in the near future.  
Studies have shown that this happens much more often then one would expect.  
Splay trees also do not require the maintenance of height or balance information, thus saving space and simplifying the code to some extent (especially when carefully implementations are written).


#### 4.5.1 A Simple Idea (That Does Not Work)

One way is to perform single rotations, bottom up.  
This means that we rotate evrery node on the access path with its parent.

These rotations push k1 (the accessed node) to the root, so that future accessses on k1 are easy (for a while).  
Unfortunately, it has pushed another node (k3) almost as deep as k1 used to be.  
An access on that node will then push another node deep, and so on.  
It is possible that there is a sequence of M operations requiring $Ω(M·N)$ time, so this idea is not quite good enough.


#### 4.5.2 Splaying

The splaying strategy is similar to the rotation idea above, except that we are a little more selective about how rotations are performed.  
We will still rotate bottom up along the access path.  
Let X be a (non-root) node on the access path at which we are rotating.

- If the parent of X is the root, we merely rotate X and the root.
- Otherwise, X has both a parent (P) and a grandparent (G), and there are 2 cases, plus symmetries, to consider.
    1. The **zig-zag** case: X is a right child and P is a left child (or vice versa).  
       Then perform a double rotation.
    2. The **zig-zig** case: X and P are both left children (or both right).
       Then transform the tree on the left of Figure 4.49 to the tree on the right.


###### Figure 4.48 Zig-zag

```
    G               X
   / \            /   \
  P   D          P     G
 / \      -->   / \   / \
A   X          A   B C   D
   / \
  B   C
```


###### Figure 4.49 Zig-zig

```
      G             X
     / \           / \
    P   D         A   P
   / \      -->      / \
  X   C             B   G
 / \                   / \
A   B                 C   D
```

Splaying not only moves the accessed node to the root but also has the effect of roughly *halving* the depth of most nodes on the access path (some shallow nodes are pushed down at most two levels).

We can perform deletion by accessing the node to be deleted.  
This puts the node at the root.  
If it is deleted, we get two subtrees TL and TR.  
If we find the largest element in TL (which is easy), then this element is rotated to the root of TL, and TL will now have a root with not right child.  
We can finish the deletion by making TR the right child.

The ananlysis of splay trees is difficult, because it must take into account the everchanging structure of the tree.  
On the other hand, splay trees are much simpler to program than most balanced trees, since there are fewer cases to consider and no balance information to maintain.


--------------------------------------------------------------------------------


### 4.6 Tree Traversal (Revisited)

It is simple to list all the items in sorted order.  
**inorder traversal**


###### Figure 4.60 Routine to print a binary search tree in order

```cs
// Print the tree contents in sorted order.
void printTree(ostream &out = cout) const
{
    if (isEmpty())
        out << "Empty tree" << endl;
    else
        printTree(root, out);
}

// Internal method to print a subtree rooted at t in sorted order.
void printTree(BinaryNode *t, ostream &out) const
{
    if (t != nullptr)
    {
        printTree(t->left, out);
        out << t->element << endl;
        printTree(t->right, out);
    }
}
```

The total running time is O(N), because there is contatn work being performed at every node in the tree.

When we need to compute the height of a node, we need **postorder traversal**.


###### Figure 4.61 Routine to compute the height of a tree using a postorder traversal

```cs
// Internal method to compute the height of a subtree rooted at t.
int height(BinaryNode *t)
{
    if (t == nullptr)
        return -1;
    else
        return 1 + max(height(t->left), height(t->right));
}
```

**Preorder traversal** is used, for example, to label each node with its depth.

These routines pass only the pointer to the node that roots the subtree, and do not declare or pass any extra variables.  
The more compact the code, the less likely that a silly bug will turn up.

A fourth, less often used, traversal (which we have not seen yet) is **level-order traversal**.  
In a level-order traversal, all nodes at depth d are processed before any node at depth d+1.  
Level-order traversal differs from the other traversals in that it is not done recursively;  
a queue is used, instead of the implied stack of recursion.


--------------------------------------------------------------------------------


### 4.7 B-Trees

So far, it is assumed that the entire data is stored in the main memory.  
Suppose there is more data than the memory can store, then must have data structure reside on disk.  
And the rules of the game change, because the Big-Oh model is no longer meaningful.

The problem is the a Big-Oh analysis assumes that all operations are equal.  
However, it is 9-11 ms for a disk IO while the processor deal billions instructions.  
SoiIt is the number of disk access that will dominate the running time.

We want to reduce the disk accesses to a very small constant, such as 3 or 4.  
A BST will not work.  
If we have more branching, we have less height.

An **M-ary search tree** allows M-way braching.  
A complete binary tree has height that is roughly $log_2 N$,  
a complete M-ary tree has height that is roughly $log_M N$.

We can create an M-ary tree in much the same way as a binary search tree.  
In a BST, we need one key to decide which of two branches to take.  
In an M-ary search tree, we need M-1 keys to decide.  
To make this scheme efficient in the worst case, we need to ensure that the M-ary search tree is balanced in some way.  
Otherwise, like a BST, it could degenerate into a linked list.  
Actually, we want an even more restrictive balancing condition.  
That is, we do not want an M-ary search tree to degenerate to even a binary search tree, because then we could be stuck with logN accesses.

One way to implement is to use a **B-tree*.  
The basic B-tree (popularly known as a B+ tree) is described here.  
In principle, a B-tree guarantees only a few disk accesses.

A B-tree of order M is an M-ary tree with the following properties:  
Rule 3 and 5 must be relaxed for the first L insertions.

1. The data item are stored at leaves.
2. The nonleaf nodes store up to M-1 keys to guide the searching; key i represents the smallest key in subtree i+1.
3. The root is either a leaf or has between two and M children.
4. All nonleaf nodes (except the root) have between ceil(M/2) and M children.
5. All leaves are at the same depth and have between ceil(L/2) and L data items, for some L (the determine of L is described shortly).

In the example, L and M are the same but this is not neccessary.

Each node represents a disk block, so we chooseMandLon the basis of the size of theitems that are being stored.  
As an example, suppose one block holds 8,192 bytes.  
In ourFlorida example, each key uses 32 bytes.  
In a B-tree of orderM, we would haveM−1 keys,for a total of 32M−32 bytes, plusMbranches.  
Since each branch is essentially a numberof another disk block, we can assume that a branch is 4 bytes.  
Thus the branches use 4Mbytes.  
The total memory requirement for a nonleaf node is thus 36M−32.  
The largest valueofMfor which this is no more than 8,192 is 228.  
Thus we would chooseM=228.  
Sinceeach data record is 256 bytes, we would be able to fit 32 records in a block.  
Thus we wouldchooseL=32.  
We are guaranteed that each leaf has between 16 and 32 data records andthat each internal node (except the root) branches in at least 114 ways.  
Since there are10,000,000 records, there are, at most, 625,000 leaves.  
Consequently, in the worst case,leaves would be on level 4.  
In more concrete terms, the worst-case number of accesses isgiven by approximately logM/2N, give or take 1.  
(For example, the root and the next levelcould be cached in main memory, so that over the long run, disk accesses would be neededonly for level 3 and deeper.)

If the leaf is full, split the leaf;  
if the parent is full, split the parent (update keys);  
if the root is full, split the root and create a new root, and the B-tree gains height.

There are other ways to handle the overflowing of children.  
One is to put a child up for adoption should a neighbor have a room.

When deleting, if the number of items is below the minimum, we can rectify this situaiton by adopting a neighboring item, if the nieghbor is not itself at its minimum.  
If it is, then we can combine with the neighbor to form a full leaf.  
After this, the parent has lost a child.  
If this causes the parent to fall below its minimum, then it follows the same strategy.  
The process could percolate all the way up to the root.  
The root cannot have just one child.  
If it is, we remove the root and make its child the new root.  
And this is the only way for a B-tree to lose height.


--------------------------------------------------------------------------------


### 4.8 Sets and Maps in the Standard Library

The STL provides two additional containers, `set` and `map`, that guarantee logarithmic cost for basic operations such as insertion, deletion, and searching.


#### 4.8.1 Sets

The `set` is an ordered container that does not allow duplicates.

The unique operations required by the `set` are the abilities to insert, remove, and perform a basic search (efficiently).

As a `set` does not allow duplicates, `insert` could fail.  
As a result, we want the return type to be able to indicate this with a Boolean variable.  
But `insert` also returns an iterator that represents where x is when insert returns.  
This iterator represents either the newly inserted item or the existing item that caused the insert to fail, and it is useful, because knowing the position of the item can make removing it more efficient by avoiding the search and getting directly to the node containing the item.

`insert` uses `pair` as its return type:

```cs
pair<iterator, bool> insert(const Object &x);
pair<iterator, bool> insert(iterator hint, const Object &x);
```

The two-parameter `insert` allows the sepcification of a hint, which represents the position where x should go.  
If the hint is accurate, the insertion is fast, often O(1).  
If not, the insertion is done using the normal insertion algorithm and performs comparably with the one-parameter insert.  
For instance, the following code might be faster using the two-parameter insert than the one-parameter insert:

```cs
set<int> s;
for (int i = 0; i < 1000000; ++i)
    s.insert(s.end(), i);
```

There are several versions of `erase`:

```cs
int erase(const Object &x);
iterator erase(iterator itr);
iterator erase(iterator start, iterator end);
```

- The first one-parameter erase removes x (if found) and returns the number of items actually removed, which is obviously 0 or 1.
- The seconde one-parameter erase behaves the same as in vector/list.  
  It removes the object at the iterator, returns an iterator representing the element that followed itr immediately prior to the call to erase, and invalidates itr, which becomes stale.
- The two-parameter erase behaves the same as in a vector/list, removing all between start and end.

For searching, rather than a contains routine, the set provides a `find`:

```cs
iterator find(const Object &x) const;
```


#### 4.8.2 Maps

A `map` is used to store a collection of ordered entries that consists of keys and their values.

For an iterator `itr`, `*itr` is of type `pair<KeyType, ValueType>`.  
For insert, one must provide a pair.  
`find` requires a key but returns itr to a pair.  
Using only these operations is often not worthwhile because the syntactic baggage can be expensive.

Fortunately, the `map` has an important extra operation that yields simple syntax:

```cs
ValueType &operator[](const KeyType &key);
```

The semantics of `operator[]`:

- If key is present, return a reference to the value.
- If key is not present, it is inserted with a default value into the map and then a reference to the inserted value is returned.

The code snippet in Figure 4.68 illustrates two techniques to access items in a map:


###### Figure 4.68 Accessing values in a map

```cs
map<string, double> salaries;

salaries["Pat"] = 75000.00;
cout << salaries["Pat"] << endl;
cout << salaries["Jan"] << endl;

map<string, double>::const_iterator itr;
itr = salaries.find("Chris");
if (itr == salaries.end())
    cout << "Not an employee of this company!" << endl;
else
    cout << itr->second << endl;
```
