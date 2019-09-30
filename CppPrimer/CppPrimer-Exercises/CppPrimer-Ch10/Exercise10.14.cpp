// Exercise10.14.cpp
// Ad
// Write a lambda that takes two ints and returns their sum.

#include <iostream>

// -----------------------------------------------------------------------------

int main(int argc, char *argv[])
{
    auto f{[](int i1, int i2) { return i1 + i2; }};
    std::cout << f(1, 7) << std::endl;

    // pause
    system("pause");
    return 0;
}