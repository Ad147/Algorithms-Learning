// Exercise10.27.cpp
// Ad
// Write a program that uses unique_copy to copy the unique elements from a vector into an initially empty list.

#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <iterator>

// -----------------------------------------------------------------------------

int main(int argc, char *argv[])
{
    std::vector<int> ivec{1, 1, 2, 3, 4, 4, 4, 5};
    std::list<int> ilst;
    std::unique_copy(ivec.begin(), ivec.end(), std::back_inserter(ilst));
    for (const auto &i : ivec)
        std::cout << i << ' ';
    std::cout << std::endl;
    for (const auto &i : ilst)
        std::cout << i << ' ';
    std::cout << std::endl;

    // pause
    system("pause");
    return 0;
}