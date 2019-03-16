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

