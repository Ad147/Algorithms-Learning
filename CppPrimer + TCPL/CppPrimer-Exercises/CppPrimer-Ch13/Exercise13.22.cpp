// Exercise13.22.cpp
// Ad
// Assume that we want HasPtr to behave like a value.
// That is, each object should have its own copy of the string to which the object point.
// Write the HasPtr copy constructor and copy-assignment operator before reading on.

#include <iostream>
#include <string>

// class =======================================================================

class HasPtr
{
  public:
    HasPtr(const std::string &s = std::string())
        : ps(new std::string(s)), i(0) {}
    HasPtr(const HasPtr &hp) : i(hp.i), ps(new std::string(*hp.ps)) {}
    ~HasPtr() { delete ps; }
    HasPtr &operator=(const HasPtr &hp)
    {
        auto newp = new std::string(*hp.ps);
        delete ps;
        ps = newp;
        i = hp.i;
        return *this;
    }

  private:
    int i;
    std::string *ps;
};

// main ========================================================================

int main(int argc, char *argv[])
{

    // pause
    system("pause");
    return 0;
}