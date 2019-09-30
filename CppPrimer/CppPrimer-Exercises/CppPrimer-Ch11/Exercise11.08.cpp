// Exercise11.08.cpp
// Ad
// Write a program that stores the excluded words i a vector instead of in a set.
// What are the advantages to using a set?

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>

// -----------------------------------------------------------------------------

int main(int argc, char *argv[])
{
    std::map<std::string, size_t> countWord;
    std::vector<std::string> exclude{"the", "but", "a", "an", "and", "or"};

    std::string word;
    while (std::cin >> word)
        if (find(exclude.cbegin(), exclude.cend(), word) == exclude.cend())
            ++countWord[word];
    for (const auto &w : countWord)
        std::cout << w.first << " occurs " << w.second << " time(s)"
                  << std::endl;

    // pause
    system("pause");
    return 0;
}