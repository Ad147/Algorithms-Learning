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

