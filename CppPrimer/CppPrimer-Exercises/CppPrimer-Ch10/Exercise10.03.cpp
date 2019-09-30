// Exercise10.03.cpp
// Ad
// Use accumulate to sum the elements in a vector<int>.

#include <iostream>
#include <vector>
#include <numeric>

// -----------------------------------------------------------------------------

int main(int argc, char *argv[])
{
    std::vector<int> ivec{0, 1, 2, 34, 5, 6, 7, 9};
    std::cout << accumulate(ivec.begin(), ivec.end(), 0) << std::endl;

    // pause
    system("pause");
    return 0;
}