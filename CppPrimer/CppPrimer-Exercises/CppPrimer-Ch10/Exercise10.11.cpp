// Exercise10.11.cpp
// Ad
// Write a program that uses stable_sort and isShorter to sort a vector passed to your version of emilDups.
// Print the vector to verify that your program is correct.

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

// function --------------------------------------------------------------------

bool isShorter(const std::string &s1, const std::string &s2)
{
    return s1.size() < s2.size();
}

void elimDups(std::vector<std::string> &svec)
{
    for (const auto &s : svec)
        std::cerr << s << ' ';
    std::cerr << std::endl;

    stable_sort(svec.begin(), svec.end(), isShorter);
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
    std::vector<std::string> svec{"beta", "alpha", "aaaa", "beta", "alpha"};
    sort(svec.begin(), svec.end());
    elimDups(svec);

    // pause
    system("pause");
    return 0;
}