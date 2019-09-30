// Exercise10.28.cpp
// Ad
// Copy a vector that holds the values from 1 to 9 inclusive, into three other containers.
// Use an iserter, a back_inserter, and a front_inserter respectively to add elements to these containers.
// Predict how the output sequence varies by the kind of inserter and verify your predictions by running your programs.

#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <iterator>

// -----------------------------------------------------------------------------

int main(int argc, char *argv[])
{
    std::vector<int> ivec{1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::list<int> ilst1, ilst2, ilst3;

    std::copy(ivec.begin(), ivec.end(), std::inserter(ilst1, ilst1.begin()));
    std::copy(ivec.begin(), ivec.end(), std::back_inserter(ilst2));
    std::copy(ivec.begin(), ivec.end(), std::front_inserter(ilst3));

    std::cout << "inserter:" << std::endl;
    for (const auto &i : ilst1)
        std::cout << i << ' ';
    std::cout << std::endl;

    std::cout << "back_inserter:" << std::endl;
    for (const auto &i : ilst2)
        std::cout << i << ' ';
    std::cout << std::endl;

    std::cout << "front_inserter:" << std::endl;
    for (const auto &i : ilst3)
        std::cout << i << ' ';
    std::cout << std::endl;

    // pause
    system("pause");
    return 0;
}