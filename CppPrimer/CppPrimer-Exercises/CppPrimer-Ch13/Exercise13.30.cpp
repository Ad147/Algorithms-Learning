// Exercise13.30.cpp
// Ad
// Write and test a swap function for your valuelike version of HasPtr.
// Give your swap a print statement that notes when it is excuted.

#include <iostream>
#include <string>

// class =========================================

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

  private:
    std::string *ps;
    int i;

    friend void swap(HasPtr &, HasPtr &);
};

// function ======================================

inline void swap(HasPtr &lhs, HasPtr &rhs)
{
    std::cout << "Function swap(" << *lhs.ps << ", " << *rhs.ps << ") Executing..." << std::endl;

    using std::swap;
    swap(lhs.ps, rhs.ps);
    swap(lhs.i, rhs.i);

    std::cout << "Function swap(" << *lhs.ps << ", " << *rhs.ps << ") Executed" << std::endl;
}

// main ==========================================

int main(int argc, char *argv[])
{
    HasPtr hp1 = {"hp1"};
    HasPtr hp2 = {"hp2"};

    std::cout << "call swap" << std::endl;
    swap(hp1, hp2);

    system("pause");
    return 0;
}
