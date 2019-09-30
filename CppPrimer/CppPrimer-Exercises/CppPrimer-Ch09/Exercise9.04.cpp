// Exercise9.04.cpp
// Ad
// Write a function that takes a pair of iterators to a vector<int> and an int value.
// Look for that value in the range and return a bool indicating whether it was found.

#include <iostream>
#include <vector>

// function --------------------------------------------------------------------

bool function(std::vector<int>::const_iterator iter1,
              std::vector<int>::const_iterator iter2, int i)
{
    while (iter1 != iter2)
    {
        if (*iter1 == i)
            return 1;
        ++iter1;
    }
    return 0;
}

// test ------------------------------------------------------------------------

int main(int argc, char *argv[])
{
    std::vector<int> ivec{1, 2, 3};
    std::cout << function(ivec.begin(), ivec.end(), 2) << std::endl
              << function(ivec.begin(), ivec.end(), 4) << std::endl;

    // pause
    system("pause");
    return 0;
}