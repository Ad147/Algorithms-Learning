// Exercise10.31.cpp
// Ad
// Update the program from the previous exercise so that it prints only the unique elements.
// Your program should use unique_copy.

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

// -----------------------------------------------------------------------------

int main(int argc, char *argv[])
{
    std::istream_iterator<int> input{std::cin}, end;
    std::vector<int> ivec{input, end};

    std::sort(ivec.begin(), ivec.end());

    std::ostream_iterator<int> output{std::cout, " "};
    std::unique_copy(ivec.begin(), ivec.end(), output);
    std::cout << std::endl;

    // pause
    system("pause");
    return 0;
}