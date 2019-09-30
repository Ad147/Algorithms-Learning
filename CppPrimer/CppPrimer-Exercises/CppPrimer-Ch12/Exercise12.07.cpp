// Exercise12.07.cpp
// Ad
// Redo the previous exercise, this time using shared_ptr.

#include <iostream>
#include <vector>
#include <memory>

// function ====================================================================

std::shared_ptr<std::vector<int>> newVector()
{
    return std::make_shared<std::vector<int>>();
}

std::shared_ptr<std::vector<int>>
inputVector(std::shared_ptr<std::vector<int>> pvi)
{
    int i = {0};
    while (std::cin >> i)
        pvi->push_back(i);

    return pvi;
}

void outputVector(std::shared_ptr<std::vector<int>> pvi)
{
    for (auto i : *pvi)
        std::cout << i << ' ';
    std::cout << std::endl;
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