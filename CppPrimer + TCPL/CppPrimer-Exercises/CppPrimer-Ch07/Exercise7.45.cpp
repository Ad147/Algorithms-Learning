// Exercise7.45.cpp
// Ad
// What if we defined the vector in the previous exercise to hold objects of C?

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
    std::vector<C> vec(10); // legal
}