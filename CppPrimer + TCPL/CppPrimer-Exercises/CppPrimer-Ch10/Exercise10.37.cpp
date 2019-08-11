// Exercise10.37.cpp
// Ad
// Given a vector that has ten elements, copy the elements from positions 3 through 7 in reverse order to a list.

#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

// -----------------------------------------------------------------------------

int main(int argc, char *argv[])
{
    std::vector<int> ivec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::list<int> ilst;
    std::copy(ivec.crbegin() + 3, ivec.crend() - 2, std::back_inserter(ilst));
    for (auto i : ilst)
        std::cout << i << ' ';
    std::cout << std::endl;

    // pause
    system("pause");
    return 0;
}