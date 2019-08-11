// Exercise11.22.cpp
// Ad
// Given a map<string, vector<int>>, write the types used as an argument and as the return value for the version of insert that inserts one element.

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <utility>

// main ------------------------------------------------------------------------

int main(int argc, char *argv[])
{
    std::map<std::string, std::vector<int>> svmap;
    std::pair<std::map<std::string, std::vector<int>>::iterator, bool>
        ibpair = {svmap.insert(std::pair<std::string, std::vector<int>>())};

    // pause
    system("pause");
    return 0;
}