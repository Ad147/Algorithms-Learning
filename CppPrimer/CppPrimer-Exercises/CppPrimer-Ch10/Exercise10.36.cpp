// Exercise10.36.cpp
// Ad
// Use find to find the last element in a list of ints with value 0.

#include <iostream>
#include <list>
#include <algorithm>

// -----------------------------------------------------------------------------

int main(int argc, char *argv[])
{
    std::list<int> ilst{1, 2, 0, 3, 4, 0, 5, 6, 0, 7, 8};
    auto it{std::find(ilst.crbegin(), ilst.crend(), 0)};
    std::cout << *it << ' ' << *(++it) << std::endl;

    // pause
    system("pause");
    return 0;
}