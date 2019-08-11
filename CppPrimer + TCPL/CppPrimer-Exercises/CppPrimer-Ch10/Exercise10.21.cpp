// Exercise10.21.cpp
// Ad
// Write a lambda that captures a local int variable and decrements that variable until it reaches 0.
// Once the variable is 0 additional calls should no longer decrement the variable.
// The lambda should return a bool that indicates whether the captured variable is 0.

#include <iostream>

// -----------------------------------------------------------------------------

int main(int argc, char *argv[])
{
    int i{3};
    auto f{[&i]() mutable
           -> bool { if (i > 0) { --i; return true; } else return false; }};
    std::cout << i << ' ' << f() << std::endl;
    std::cout << i << ' ' << f() << std::endl;
    std::cout << i << ' ' << f() << std::endl;
    std::cout << i << ' ' << f() << std::endl;

    // pause
    system("pause");
    return 0;
}