// Exercise9.26.cpp
// Ad
// Using the following definition of ia, copy ia into a vector and into a list.
// Use the single-iterator form of erase to remove the elements with odd values from list and the even values from vector.

#include <iostream>
#include <vector>
#include <list>

// -----------------------------------------------------------------------------

int main(int argc, char *argv[])
{
    int ia[] = {0, 1, 1, 2, 3, 5, 8, 13, 21, 55, 89};
    std::vector<int> ivec{ia, ia + 11};
    std::list<int> ilst{ia, ia + 11};
    // remove even values from vector
    for (auto iter{ivec.begin()}; iter != ivec.end();)
    {
        if (*iter % 2)
            ++iter;
        else
            iter = ivec.erase(iter);
    }
    // remove odd values from list
    for (auto iter{ilst.begin()}; iter != ilst.end();)
    {
        if (*iter % 2)
            iter = ilst.erase(iter);
        else
            ++iter;
    }
    for (auto i : ivec)
        std::cout << i << ' ';
    std::cout << std::endl;
    for (auto i : ilst)
        std::cout << i << ' ';
    std::cout << std::endl;

    // pause
    system("pause");
    return 0;
}