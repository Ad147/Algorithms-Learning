// Exercise13.05.cpp
// Ad
// Given the following sketch of a class, write a copy constructor that copies all the members.
// Your constructor should dynamically allocate a new string and copy the object to which ps points, rather than copying ps itself.

#include <iostream>
#include <string>

// class =======================================================================

class HasPtr
{
  public:
    HasPtr(const std::string &s = std::string())
        : ps(new std::string(s)), i(0) {}
    // copy constructor
    HasPtr(const HasPtr &hp) : ps(new std::string(*hp.ps)), i(hp.i) {}

  private:
    std::string *ps;
    int i;
};

// main ========================================================================

int main(int argc, char *argv[])
{

    // pause
    system("pause");
    return 0;
}