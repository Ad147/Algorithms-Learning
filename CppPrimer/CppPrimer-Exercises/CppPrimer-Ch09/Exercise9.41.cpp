// Exercise9.41.cpp
// Ad
// Write a program that initializes a string from a vector<char>

#include <iostream>
#include <vector>
#include <string>

// -----------------------------------------------------------------------------

int main(int argc, char *argv[])
{
    std::vector<char> cvec{'a', 'b', 'c', 'd'};
    std::string str{cvec.begin(), cvec.end()};
    std::cout << str << std::endl;

    // pause
    system("pause");
    return 0;
}