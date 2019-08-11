// Exercise9.50.cpp
// Ad
// Write a program to process a vector<string> whose elements represent integral values.
// Prodece the sum of all the elements in that vector.
// Change the program so that it sums of strings that represent floating-point values.

#include <iostream>
#include <vector>
#include <string>

// -----------------------------------------------------------------------------

int main(int argc, char *argv[])
{
    std::vector<std::string> svec0{"123", "45", "6"};
    std::vector<std::string> svec1{"1.23", "4.5", "0.6"};

    // sum of integers
    int isum{0};
    for (auto s : svec0)
    {
        isum += stoi(s);
    }
    std::cout << "The sum is: " << isum << std::endl;

    // sum of doubles
    double dsum{0};
    for (auto s : svec1)
    {
        dsum += stod(s);
    }
    std::cout << "The sum is: " << dsum << std::endl;

    // pause
    system("pause");
    return 0;
}