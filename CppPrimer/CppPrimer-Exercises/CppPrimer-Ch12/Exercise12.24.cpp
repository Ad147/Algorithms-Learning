// Exercise12.24.cpp
// Ad
// Write a program that reads a string from the standard input into a dynamically allocated character array.
// Describe how your program handles varying size inputs.
// Test your program by giving it a string of data that is longer than the array size you've allocated.

#include <iostream>

// main ========================================================================

int main(int argc, char *argv[])
{
    std::cout << "Input length of the string:" << std::endl;
    int n = {0};
    std::cin >> n;
    char *pc = new char[n]();
    std::cout << "Input the string:" << std::endl;
    auto q = pc;
    while (std::cin >> *q && q != pc + n)
        ++q;

    for (auto q = pc; q != pc + n; ++q)
        std::cout << *q;
    std::cout << std::endl;

    delete[] pc;

    // pause
    system("pause");
    return 0;
}