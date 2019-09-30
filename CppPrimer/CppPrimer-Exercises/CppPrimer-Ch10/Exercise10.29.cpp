// Exercise10.29.cpp
// Ad
// Write a program using stream iterators to read a text file into a vector of strings.

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iterator>

// -----------------------------------------------------------------------------

int main(int argc, char *argv[])
{
    std::ifstream finput{"testfile"};
    std::istream_iterator<std::string> input{finput}, end;
    std::vector<std::string> svec{input, end};
    for (const auto &s : svec)
        std::cout << s << " ";
    std::cout << std::endl;

    // pause
    system("pause");
    return 0;
}