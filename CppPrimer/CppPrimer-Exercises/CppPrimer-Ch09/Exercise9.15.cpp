// Exercise9.15.cpp
// Ad
// Write a program to determine whether two vector<int>s are equal.

#include <iostream>
#include <vector>

// main ------------------------------------------------------------------------

int main(int argc, char *argv[])
{
    std::vector<int> ivec0{1, 2}, ivec1{2};
    bool b = ivec0 == ivec1;
    std::cout << b << std::endl;

    // pause
    system("pause");
    return 0;
}