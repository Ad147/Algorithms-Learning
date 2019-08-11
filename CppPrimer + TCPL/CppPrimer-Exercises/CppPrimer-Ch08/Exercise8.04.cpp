// Exercise8.04.cpp
// Ad
// Writes a function to open a file for input and read its contents into a vector of strings, storing each line as a aeparate element in the vector.

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

std::vector<std::string> read(std::string file)
{
    std::ifstream in(file);
    std::vector<std::string> svec;
    std::string s;
    while (getline(in, s))
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