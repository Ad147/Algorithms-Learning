// Exercise11.12.cpp
// Ad
// Write a progarm to read a sequence of strings and ints, storing each into a pair.
// Store the pairs in a vector.

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
    while (std::cin >> s >> i)
        pvec.push_back(make_pair(s, i));
    for (const auto &p : pvec)
        std::cout << p.first << ' ' << p.second << std::endl;
    // pause
    system("pause");
    return 0;
}