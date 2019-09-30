// Exercise9.31.cpp
// Ad
// The program on page 354 to remove even-valued elements and duplicate odd ones will not work on a list or forward_list. Why?
// Revise the program so that it works on these types as well.

#include <iostream>
#include <list>

// -----------------------------------------------------------------------------

int main(int argc, char *argv[])
{
    std::list<int> ilst{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto iter{ilst.begin()};
    while (iter != ilst.end())
    {
        if (*iter % 2)
        {
            iter = ilst.insert(iter, *iter);
            ++iter;
            ++iter;
        }
        else
            iter = ilst.erase(iter);
    }
    for (auto i : ilst)
        std::cout << i << ' ';
    std::cout << std::endl;

    // pause
    system("pause");
    return 0;
}