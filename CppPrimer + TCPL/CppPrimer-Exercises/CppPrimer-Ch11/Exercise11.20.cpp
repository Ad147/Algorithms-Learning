// Exercise11.20.cpp
// Ad
// Rewrite the word-counting program from page 421 to use insert instead of subscripting.
// Which program do you think is easier to write and read?
// Explain your reasoning.

#include <iostream>
#include <string>
#include <map>

// main ------------------------------------------------------------------------

int main(int argc, char *argv[])
{
    std::map<std::string, size_t> word_count;

    std::string word;
    while (std::cin >> word)
    {
        auto p = word_count.insert({word, 1});
        if (!p.second)
            ++p.first->second;
    }

    // pause
    system("pause");
    return 0;
}