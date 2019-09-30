// Exercise9.11.cpp
// Ad
// Show an example of each of the six ways to create and initialize a vector.
// Explain what values each vector contains.

#include <iostream>
#include <vector>

// main ------------------------------------------------------------------------

int main(int argc, char *argv[])
{
    std::vector<int> ivec0;                             // empty
    std::vector<int> ivec1{1, 2, 3};                    // holds 1, 2, 3
    std::vector<int> ivec2 = {4, 5, 6};                 // holds 4, 5, 6
    std::vector<int> ivec3(ivec1);                      // the same as ivec1
    std::vector<int> ivec4 = ivec2;                     // the same as ivec2
    std::vector<int> ivec5(ivec4.begin(), ivec4.end()); // the same as ivec4
    std::vector<int> ivec6(3);                          // holds 0, 0, 0
    std::vector<int> ivec7(3, 1);                       // holds 1, 1, 1

    // pause
    system("pause");
    return 0;
}