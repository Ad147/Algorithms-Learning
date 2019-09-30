// Exercise10.01.cpp
// Ad
// The algorithm header defines a function named count that, like find, takes a pair of iterators and a value.
// count returns a count of how often that value appears.
// Read a sequence of ints into a vector and print the count of how many elements have a given value.

#include <iostream>
#include <vector>
#include <algorithm>

// -----------------------------------------------------------------------------

int main(int argc, char *argv[])
{
    std::vector<int> ivec{0, 1, 2, 7, 3, 4, 7, 5, 7, 8, 9, 7};
    std::cout << "number 7 appears " << count(ivec.begin(), ivec.end(), 7)
              << " times." << std::endl;

    // pause
    system("pause");
    return 0;
}