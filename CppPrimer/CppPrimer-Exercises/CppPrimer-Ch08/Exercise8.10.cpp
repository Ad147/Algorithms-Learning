// Exercise8.10.cpp
// Ad
// Write a program to store each line from a file in a vector<string>.
// Now use an istringstream to read each element from the vector a word at a time.

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

// function --------------------------------------------------------------------

std::vector<std::string> read(std::string file)
{
    std::ifstream in(file);
    std::vector<std::string> svec;
    std::string s;
    while (getline(in, s))
        svec.push_back(s);
    return svec;
}

// main ------------------------------------------------------------------------

int main(int argc, char *argv[])
{
    std::vector<std::string> svec{read("file1")};
    for (auto s : svec)
    {
        std::istringstream iss(s);
        std::string str;
        while (iss >> str)
            std::cout << str << std::endl;
    }
    // pause
    system("pause");
    return 0;
}