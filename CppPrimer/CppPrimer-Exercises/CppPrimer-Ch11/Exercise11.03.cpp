// Exercise11.03.cpp
// Ad
// Write your own version of the word-counting program.

#include <iostream>
#include <string>
#include <map>
#include <set>

// -----------------------------------------------------------------------------

int main(int argc, char *argv[])
{
    std::map<std::string, size_t> wordCount;
    std::set<std::string> exclude{"The", "the", "A", "a", "An", "an",
                                  "But", "but", "And", "and", "Or", "or"};

    std::string word;
    while (std::cin >> word)
    {
        if (exclude.find(word) == exclude.end())
            ++wordCount[word];
    }

    for (const auto &w : wordCount)
        std::cout << w.first << " occurs " << w.second << " time(s)" << std::endl;

    // pause
    system("pause");
    return 0;
}