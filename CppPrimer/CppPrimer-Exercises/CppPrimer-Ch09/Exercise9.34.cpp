// Exercise9.34.cpp
// Ad
// Assuming vi is a container of ints that includes even and odd values, predict the bahavior of the following loop.
// After you have analyzed this loop, write a program to test whether your expectation were correct.

#include <iostream>
#include <vector>

// -----------------------------------------------------------------------------

int main(int argc, char *argv[])
{
    std::vector<int> vi{0, 1, 2};
    auto iter = vi.begin();
    while (iter != vi.end())
    {
        if (*iter % 2)
            iter = vi.insert(iter, *iter);
        ++iter;
        // to see what are in the vector
        for (auto i : vi)
            std::cout << i << ' ';
        std::cout << std::endl;
    }

    // pause
    system("pause");
    return 0;
}