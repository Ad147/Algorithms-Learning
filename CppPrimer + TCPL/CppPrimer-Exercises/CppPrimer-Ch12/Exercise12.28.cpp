// Exercise12.28.cpp
// Ad
// Write a program to implement text queries without defining classes to manage the data.
// Your program should take a file and interact with a user to query for words in that file.
// Use vector, map and set containers to hold the data for the file and to generate the results for the queries.

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <set>

// main ========================================================================

int main(int argc, char *argv[])
{
    // read file and store the contents
    std::ifstream infile("testfile1227");
    std::vector<std::string> text;
    std::string s;
    while (std::getline(infile, s))
        text.push_back(s);

    // build map
    std::map<std::string, std::set<int>> nums;
    for (int i = {0}; i != text.size(); ++i)
    {
        std::istringstream iss(text[i]);
        while (iss >> s)
            nums[s].insert(i + 1);
    }

    // interact with user
    while (true)
    {
        std::cout << "enter word to look for, or q to quit: ";
        std::string s;
        if (!(std::cin >> s) || s == "q")
            break;

        // do the querying
        std::cout << s << " occurs "
                  << nums[s].size() << " time(s)" << std::endl;
        for (const auto &i : nums[s])
            std::cout << "(line " << i << ") " << text[i - 1] << std::endl;
    }

    // pause
    system("pause");
    return 0;
}