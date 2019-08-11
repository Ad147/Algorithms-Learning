// Exercise9.13.cpp
// Ad
// How would you initialize a vector<double> from a list<int>?
// From a vector<int>?
// Write code to check your answers.

#include <iostream>
#include <vector>
#include <list>

// main ------------------------------------------------------------------------

int main(int argc, char *argv[])
{
    std::list<int> ilst{1, 2, 3};
    std::vector<double> dvec0{ilst.begin(), ilst.end()};
    std::vector<int> ivec{3, 2, 1};
    std::vector<double> dvec1{ivec.begin(), ivec.end()};

    // pause
    system("pause");
    return 0;
}