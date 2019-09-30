// Exercise11.09.cpp
// Ad
// Define a map that asscociates words with a list of line numbers on which the word might occur.

#include <iostream>
#include <string>
#include <list>
#include <map>

// -----------------------------------------------------------------------------

int main(int argc, char *argv[])
{
    std::map<std::string, std::list<size_t>> linenum{{"word", {2, 5}}};
    for (const auto &w : linenum)
    {
        std::cout << w.first << std::endl;
        for (const auto &n : w.second)
            std::cout << n << ' ';
        std::cout << std::endl;
    }

    // pause
    system("pause");
    return 0;
}