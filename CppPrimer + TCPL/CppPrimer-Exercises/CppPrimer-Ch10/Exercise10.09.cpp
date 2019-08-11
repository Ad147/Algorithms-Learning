// Exercise10.09.cpp
// Ad
// Implement your own version of elimDups.
// Test your program by printing the vector after you read the input, after the call to unique, and after the call to erase.

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

// function --------------------------------------------------------------------

void elimDups(std::vector<std::string> &svec)
{
    for (const auto &s : svec)
        std::cerr << s << ' ';
    std::cerr << std::endl;

    sort(svec.begin(), svec.end());
    for (const auto &s : svec)
        std::cerr << s << ' ';
    std::cerr << std::endl;

    auto era{unique(svec.begin(), svec.end())};
    for (const auto &s : svec)
        std::cerr << s << ' ';
    std::cerr << std::endl;

    svec.erase(era, svec.end());
    for (const auto &s : svec)
        std::cerr << s << ' ';
    std::cerr << std::endl;
}

// test ------------------------------------------------------------------------

int main(int argc, char *argv[])
{
    std::vector<std::string> svec{"beta", "alpha", "gama", "beta", "alpha"};
    elimDups(svec);

    // pause
    system("pause");
    return 0;
}