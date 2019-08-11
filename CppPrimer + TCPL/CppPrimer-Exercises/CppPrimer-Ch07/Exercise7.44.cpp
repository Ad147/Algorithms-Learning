// Exercise7.44.cpp
// Ad
// Is the following declaration legal?

#include <vector>

// class -----------------------------------------------------------------------

class NoDefault
{
public:
  NoDefault(int i) {}
};

class C
{
public:
  C() : nd(0) {}

private:
  NoDefault nd;
};

// main ------------------------------------------------------------------------

int main()
{
    std::vector<NoDefault> vec(10); // illegal
}