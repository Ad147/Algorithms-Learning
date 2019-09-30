// Exercise10.34.cpp
// Ad
// Use reverse_iterators to print a vector in reverse order.

#include <iostream>
#include <vector>
#include <iterator>

// -----------------------------------------------------------------------------

int main(int argc, char *argv[])
{
    std::vector<int> ivec{1, 2, 3, 4, 5};
    for (auto it{ivec.crbegin()}; it != ivec.crend(); ++it)
        std::cout << *it << ' ';
    std::cout << std::endl;

    // pause
    system("pause");
    return 0;
}