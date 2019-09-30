// Exercise9.05.cpp
// Ad
// Rewrite the previous program to return an iterator to the requested element.
// Note that the program must handle the case where the element is not found.

#include <iostream>
#include <vector>

// function --------------------------------------------------------------------

std::vector<int>::iterator function(std::vector<int>::iterator iter1,
                                    std::vector<int>::iterator iter2,
                                    int i)
{
    while (iter1 != iter2)
    {
        if (*iter1 == i)
            return iter1;
        ++iter1;
    }
    return iter2;
}

// test ------------------------------------------------------------------------

int main(int argc, char *argv[])
{
    std::vector<int> ivec{1, 2, 3};
    std::cout << *function(ivec.begin(), ivec.end(), 2) << std::endl
              << *function(ivec.begin(), ivec.end(), 4) << std::endl;

    // pause
    system("pause");
    return 0;
}