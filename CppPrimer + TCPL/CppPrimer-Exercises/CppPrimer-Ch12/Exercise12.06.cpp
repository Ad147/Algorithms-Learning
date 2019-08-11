// Exercise12.06.cpp
// Ad
// Write a function that returns a dynamically allocated vector of ints.
// Pass that vector to another function that reads the standard input to give values to the elements.
// Pass the vector to another function to print the calues that were read.
// Remember to delete the vector at the appropriate time.

#include <iostream>
#include <vector>
#include <memory>

// function ====================================================================

std::vector<int> *newVector()
{
    return new std::vector<int>;
}

std::vector<int> *inputVector(std::vector<int> *pvi)
{
    int i = {0};
    while (std::cin >> i)
        pvi->push_back(i);

    return pvi;
}

void outputVector(std::vector<int> *pvi)
{
    for (auto i : *pvi)
        std::cout << i << ' ';
    std::cout << std::endl;

    delete pvi;
}

// main ========================================================================

int main(int argc, char *argv[])
{
    auto intVector{newVector()};
    inputVector(intVector);
    outputVector(intVector);

    // pause
    system("pause");
    return 0;
}