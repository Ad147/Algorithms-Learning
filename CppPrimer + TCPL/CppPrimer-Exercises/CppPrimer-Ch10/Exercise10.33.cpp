// Exercise10.33.cpp
// Ad
// Write a program that takes the names of an input file and two output files.
// The input file should hold integers.
// Using an istream_iterator read the input file.
// Using ostream_iterators, write the odd numbers into the first output file.
// Each values should be followed by a space.
// Write the even numbers into the second file.
// Each of these values should be placed on a separate line.

#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <iterator>

// -----------------------------------------------------------------------------

int main(int argc, char *argv[])
{
    std::vector<int> ivec;
    std::ifstream fin{"infile"};
    std::istream_iterator<int> inIter{fin}, eof;
    std::ofstream foutOdd{"oddfile"}, foutEven{"evenfile"};
    std::ostream_iterator<int> outIter1{foutOdd, " "}, outIter2{foutEven, "\n"};

    std::copy(inIter, eof, std::back_inserter(ivec));
    for (auto i : ivec)
    {
        if (i % 2 == 0)
            outIter2 = i;
        else
            outIter1 = i;
    }

    // pause
    system("pause");
    return 0;
}