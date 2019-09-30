// Exercise11.23.cpp
// Ad
// Rewrite the map that stored vectors of children's names with a key that is the family last name for the exercise in page 424 to use a multimap.

#include <iostream>
#include <vector>
#include <string>
#include <map>
// -----------------------------------------------------------------------------

int main(int argc, char *argv[])
{
    std::multimap<std::string, std::string> family;

    family.insert({"Stark", "Robb"});
    family.insert({"Stark", "Arya"});

    for (const auto &f : family)
        std::cout << f.first << ' ' << f.second << std::endl;

    // pause
    system("pause");
    return 0;
}