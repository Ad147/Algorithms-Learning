// Exercise9.32.cpp
// Ad
// In the final example in this section what would happen if we did not assign the result of insert to begin?
// Write a program that omits this assignment to see if your expectation was correct.

#include <iostream>
#include <vector>

// -----------------------------------------------------------------------------

int main(int argc, char *argv[])
{
    std::vector<int> v{0, 1, 2, 3, 4, 5};
    auto begin = v.begin();
    while (begin != v.end())
    {
        ++begin;
        /* begin =  */ v.insert(begin, 42);
        ++begin;
    }
    for (auto i : v)
        std::cout << i << ' ';
    std::cout << std::endl;

    // pause
    system("pause");
    return 0;
}