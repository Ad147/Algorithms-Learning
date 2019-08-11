// Exercise13.31.cpp
// Ad
// Give your class a < operator and define a vector of HasPtrs.
// Give that vector some elements and then sort the vector.
// Note when swap is called.

// an exception unresolved

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

// class =======================================================================

class HasPtr
{
  public:
    HasPtr(const std::string &s = std::string())
        : ps(new std::string(s)), i(0) {}
    HasPtr(const HasPtr &hp) : ps(new std::string(*hp.ps)), i(hp.i) {}
    ~HasPtr() { delete ps; }
    HasPtr &operator=(const HasPtr &rhs)
    {
        auto newp = new std::string(*rhs.ps);
        delete ps;
        ps = newp;
        i = rhs.i;
        return *this;
    }
    // a < operator for sort
    bool operator<(const HasPtr &rhs)
    {
        std::cout << "<<<" << std::endl;
        return (ps < rhs.ps);
    }

  private:
    std::string *ps;
    int i;

    friend void swap(HasPtr &, HasPtr &);
};

// function ====================================================================

inline void swap(HasPtr &lhs, HasPtr &rhs)
{
    std::cout << "Function swap(" << *lhs.ps << ", " << *rhs.ps << ") Executing..." << std::endl;

    using std::swap;
    swap(lhs.ps, rhs.ps);
    swap(lhs.i, rhs.i);

    std::cout << "Function swap(" << *lhs.ps << ", " << *rhs.ps << ") Executed" << std::endl;
}

// main ========================================================================

int main(int argc, char *argv[])
{
    std::vector<HasPtr> hpv = {std::string("hp2"), std::string("hp3"), std::string("hp1")};
    std::sort(hpv.begin(), hpv.end()); // an exception unresolved

    system("pause");
    return 0;
}
