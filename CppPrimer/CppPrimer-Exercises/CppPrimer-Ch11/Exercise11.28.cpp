// Exercise11.28.cpp
// Ad
// Define and initialize a variable to hold the result of calling find on a map from string to vector of int.

#include <iostream>
#include <vector>
#include <string>
#include <map>

// main ------------------------------------------------------------------------

int main(int argc, char *argv[])
{
    std::map<std::string, std::vector<int>> svmap;

    std::map<std::string, std::vector<int>>::iterator var = {svmap.find("A")};

    // pause
    system("pause");
    return 0;
}