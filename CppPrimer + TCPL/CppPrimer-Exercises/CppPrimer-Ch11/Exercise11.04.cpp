// Exercise11.04.cpp
// Ad
// Extend your program to ignore case and punctuation.
// For example, "example." "example," and "Example" should all increment the same counter.

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
        {
            if (isupper(word[0]))
                word[0] = tolower(word[0]);
            if (ispunct(*word.crbegin()))
                word.erase(word.end() - 1);
            ++wordCount[word];
        }
    }

    for (const auto &w : wordCount)
        std::cout << w.first << " occurs " << w.second << " time(s)" << std::endl;

    // pause
    system("pause");
    return 0;
}