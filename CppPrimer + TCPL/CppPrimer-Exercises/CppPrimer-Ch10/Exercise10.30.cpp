// Exercise10.30.cpp
// Ad
// Use stream iterators, sort, and copy to read a sequence of integers from the standard input, sort them, and then write them back to the standard output.

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
    std::copy(ivec.begin(), ivec.end(), output);
    std::cout << std::endl;

    // pause
    system("pause");
    return 0;
}