// Exercise13.11.cpp
// Ad
// Add a destructor to your HasPtr class from the previous exercise.

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

    // destructor
    ~HasPtr() {}

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