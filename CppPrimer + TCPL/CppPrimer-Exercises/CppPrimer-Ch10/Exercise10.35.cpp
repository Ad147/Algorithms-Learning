// Exercise10.35.cpp
// Ad
// Now print the elements in reverse using ordinary iterators.

#include <iostream>
#include <vector>
#include <iterator>

// -----------------------------------------------------------------------------

int main(int argc, char *argv[])
{
    std::vector<int> ivec{1, 2, 3, 4, 5};
    for (auto it{ivec.cend() - 1}; it != ivec.cbegin() - 1; --it)
        std::cout << *it << ' ';
    std::cout << std::endl;

    // pause
    system("pause");
    return 0;
}