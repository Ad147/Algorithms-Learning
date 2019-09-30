// Exercise11.07.cpp
// Ad
// Define a map for which the key is the family's last name and the value is a vector of the children's names.
// Write code to add new families and to add new children to an existing family.

#include <iostream>
#include <vector>
#include <string>
#include <map>
// -----------------------------------------------------------------------------

int main(int argc, char *argv[])
{
    std::map<std::string, std::vector<std::string>> family;
    family.insert({"Stark", std::vector<std::string>()});
    family["Stark"].push_back("Robb");
    family["Stark"].push_back("Sansa");
    for (const auto &f : family)
    {
        std::cout << f.first << std::endl;
        for (const auto &c : f.second)
            std::cout << c << ' ';
        std::cout << std::endl;
    }

    // pause
    system("pause");
    return 0;
}