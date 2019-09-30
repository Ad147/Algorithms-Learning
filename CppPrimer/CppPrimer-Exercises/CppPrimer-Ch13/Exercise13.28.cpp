// Exercise13.28.cpp
// Ad
// Given the following classes, implement a default constructor and the necessary copy-control members.

#include <iostream>

// class-TreeNode ================================

class TreeNode
{
public:
  // default constructor
  TreeNode(const std::string &v = std::string(), int cnt = 1) : value(v), count(cnt), left(nullptr), right(nullptr) {}
  // copy constructor
  TreeNode(const TreeNode &tn) : value(tn.value), count(tn.count), left(nullptr), right(nullptr) {}
  // destructor
  ~TreeNode()
  {
    delete left;
    delete right;
  }
  // assignment
  TreeNode &operator=(const TreeNode &tn)
  {
    value = tn.value;
    count = tn.count;
  }

private:
  std::string value;
  int count;
  TreeNode *left;
  TreeNode *right;
};

// class-BinStrTree ==============================

class BinStrTree
{
public:
  // default constructor
  BinStrTree(const TreeNode &tn = TreeNode()) : root(new TreeNode(tn)) {}
  // copy construcor (unable to copy)
  BinStrTree(const BinStrTree &bnt) = delete;
  // destructor
  ~BinStrTree() { delete root; }
  // assignment (unable)
  BinStrTree &operator=(const BinStrTree &bnt) = delete;

private:
  TreeNode *root;
};

// main ==========================================

int main(int argc, char *argv[])
{

  system("pause");
  return 0;
}
