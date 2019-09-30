// Exercise9.24.cpp
// Ad
// Write a program that fetches the first element in a vector using at, the subscript operator, front and begin.
// Test your program on an empty vector.

#include <iostream>
#include <vector>

// -----------------------------------------------------------------------------

int main(int argc, char *argv[])
{
    std::vector<int> ivec;
    std::cout << ivec.at(0) << std::endl;    // throws an exception
    std::cout << ivec[0] << std::endl;       // error
    std::cout << ivec.front() << std::endl;  // error
    std::cout << *ivec.begin() << std::endl; // error

    // pause
    system("pause");
    return 0;
}