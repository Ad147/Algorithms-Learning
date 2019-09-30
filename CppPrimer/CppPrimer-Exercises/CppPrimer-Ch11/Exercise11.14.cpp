// Exercise11.14.cpp
// Ad
// Extend the map of children to their family name that you wrote for the exercise in p.424 by having the vector store a pair that holds a child's name and birthday.

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <utility>

// -----------------------------------------------------------------------------

int main(int argc, char *argv[])
{
    std::map<std::string, std::vector<std::pair<std::string, size_t>>> family;

    family.insert({"Stark", std::vector<std::pair<std::string, size_t>>()});
    family["Stark"].push_back({"Robb", 19960101});
    family["Stark"].push_back({"Sansa", 19971010});
    for (const auto &f : family)
    {
        std::cout << f.first << std::endl;
        for (const auto &c : f.second)
            std::cout << c.first << ' ' << c.second << std::endl;
    }

    // pause
    system("pause");
    return 0;
}