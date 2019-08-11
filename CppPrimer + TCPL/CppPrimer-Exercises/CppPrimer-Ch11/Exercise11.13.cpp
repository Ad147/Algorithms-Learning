// Exercise11.13.cpp
// Ad
// There are at least three ways to create the pairs in the program for the previous exercise.
// Write three versions of that program, creating the pairs in each way.
// Explain which form you think is easiest to write and understand, and why.

#include <iostream>
#include <vector>
#include <string>
#include <utility>

// main ------------------------------------------------------------------------

int main(int argc, char *argv[])
{
    std::vector<std::pair<std::string, int>> pvec;

    std::string s;
    int i;

    // using make_pair
    while (std::cin >> s >> i)
    {
        auto p{make_pair(s, i)};
        pvec.push_back(p);
    }

    // using list initializers
    while (std::cin >> s >> i)
    {
        std::pair<std::string, int> p{s, i};
        pvec.push_back(p);
    }

    // using assignments
    while (std::cin >> s >> i)
    {
        std::pair<std::string, int> p;
        p.first = s;
        p.second = i;
        pvec.push_back(p);
    }

    for (const auto &p : pvec)
        std::cout << p.first << ' ' << p.second << std::endl;

    // pause
    system("pause");
    return 0;
}