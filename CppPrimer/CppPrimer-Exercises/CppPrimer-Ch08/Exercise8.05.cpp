// Exercise8.05.cpp
// Ad
// Rewrite the previous program to store each word in a separate element.

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

std::vector<std::string> read(std::string file)
{
    std::ifstream in(file);
    std::vector<std::string> svec;
    std::string s;
    while (in >> s)
        svec.push_back(s);
    return svec;
}

// -----------------------------------------------------------------------------

int main(int argc, char *argv[])
{
    std::vector<std::string> svec{read("file1")};
    for (auto s : svec)
        std::cout << s << std::endl;

    // pause
    system("pause");
    return 0;
}