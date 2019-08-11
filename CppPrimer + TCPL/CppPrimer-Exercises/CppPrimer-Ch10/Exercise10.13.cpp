// Exercise10.13.cpp
// Ad
// Write a function that takes a string and returns a bool indicating whether the string has five characters or more.
// Use that function to partition words.
// Print the elements that have five or more characters.

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

// function --------------------------------------------------------------------

bool function(const std::string &s)
{
    return s.size() >= 5;
}

// test ------------------------------------------------------------------------

int main(int argc, char *argv[])
{
    std::vector<std::string> words{"the", "quick", "red", "fox", "jumps",
                                   "over", "the", "slow", "red", "turtle"};
    auto end{partition(words.begin(), words.end(), function)};
    for (auto beg{words.begin()}; beg != end; ++beg)
        std::cout << *beg << ' ';
    std::cout << std::endl;

    // pause
    system("pause");
    return 0;
}