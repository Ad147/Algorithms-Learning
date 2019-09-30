// Exercise9.38.cpp
// Ad
// Write a program to explore how vectors grow in the library you use.

#include <iostream>
#include <vector>

// -----------------------------------------------------------------------------

int main(int argc, char *argv[])
{
    std::vector<int> ivec;
    std::cout << "size: " << ivec.size() << std::endl
              << "capacity: " << ivec.capacity() << std::endl;
    ivec.insert(ivec.end(), 10, 1);
    std::cout << "size: " << ivec.size() << std::endl
              << "capacity: " << ivec.capacity() << std::endl;
    ivec.reserve(50);
    std::cout << "size: " << ivec.size() << std::endl
              << "capacity: " << ivec.capacity() << std::endl;
    ivec.insert(ivec.end(), 41, 1);
    std::cout << "size: " << ivec.size() << std::endl
              << "capacity: " << ivec.capacity() << std::endl;

    // pause
    system("pause");
    return 0;
}