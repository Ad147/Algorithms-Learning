// Exercise10.06.cpp
// Ad
// Using fill_n, write a program to set a sequence of int values to 0.

#include <iostream>
#include <vector>
#include <algorithm>

// -----------------------------------------------------------------------------

int main(int argc, char *argv[])
{
    std::vector<int> ivec(10, 1);
    fill_n(ivec.begin(), 10, 0);
    for (auto i : ivec)
        std::cout << i << ' ';
    std::cout << std::endl;

    // pause
    system("pause");
    return 0;
}