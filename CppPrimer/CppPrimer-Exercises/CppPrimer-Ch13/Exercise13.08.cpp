// Exercise13.08.cpp
// Ad
// Write the assignment operator for the HasPtr class from exercise 13.5.
// As with the copy constructor, your assignment operator should copy the object to which ps points.

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

    // assignment operator
    HasPtr &operator=(const HasPtr &hp)
    {
        ps = new std::string(*hp.ps);
        i = 0;
        return *this;
    }

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