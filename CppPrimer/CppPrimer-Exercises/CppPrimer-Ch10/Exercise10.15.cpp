// Exercise10.15.cpp
// Ad
// Write a lambda that captures an int from its enclosing function and takes an int parameter.
// The lambda should return the sum of the captured int and the int parameter.

#include <iostream>

// function --------------------------------------------------------------------

int function(int i)
{
    int temp{7};
    auto f{[temp](int i) { return i + temp; }};
    return f(i);
}

// test ------------------------------------------------------------------------

int main(int argc, char *argv[])
{
    std::cout << function(9) << std::endl;

    // pause
    system("pause");
    return 0;
}