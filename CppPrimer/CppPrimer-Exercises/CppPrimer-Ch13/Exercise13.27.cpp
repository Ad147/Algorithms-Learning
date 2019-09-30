// Exercise13.27.cpp
// Ad
// Define your own reference-counted version of HasPtr.

#include <iostream>
#include <string>

// class =======================================================================

class HasPtr
{
  public:
    // constructor allocates a new string and a new counter set to 1
    HasPtr(const std::string &s = std::string())
        : ps(new std::string(s)), i(0), use(new std::size_t(1)) {}
    // copy constructor copies data members and imcrement the counter
    HasPtr(const HasPtr &hp) : ps(hp.ps), i(hp.i), use(hp.use) { ++*use; }
    ~HasPtr();
    HasPtr &operator=(const HasPtr &hp);

  private:
    std::string *ps;
    int i;
    std::size_t *use; // member to keep track of how many objs share *ps
};

HasPtr::~HasPtr()
{
    if (--*use == 0)
    {
        delete ps;
        delete use;
    }
}

HasPtr &HasPtr::operator=(const HasPtr &hp)
{
    ++*hp.use;
    if (--*use == 0)
    {
        delete ps;
        delete use;
    }
    ps = hp.ps;
    i = hp.i;
    use = hp.use;
    return *this;
}

// main ========================================================================

int main(int argc, char *argv[])
{

    // pause
    system("pause");
    return 0;
}
