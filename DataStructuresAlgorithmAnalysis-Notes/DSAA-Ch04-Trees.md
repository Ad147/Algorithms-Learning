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


--------------------------------------------------------------------------------


### 4.1 Preliminaries

