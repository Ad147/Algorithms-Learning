// Exercise8.13.cpp
// Ad
// Rewrite the phone number program from this section to read from a named file rather than from cin.

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

// class -----------------------------------------------------------------------

struct PersonInfo
{
    std::string name;
    std::vector<std::string> phones;
};

// main ------------------------------------------------------------------------

int main(int argc, char *argv[])
{
    std::string line, word;
    std::vector<PersonInfo> people;
    std::ifstream fin("file1");
    while (getline(fin, line))
    {
        PersonInfo info;
        std::istringstream record(line);
        record >> info.name;
        while (record >> word)
            info.phones.push_back(word);
        people.push_back(info);
    }
    // output to see the result
    for (auto p : people)
    {
        std::cout << p.name << ":" << std::endl;
        for (auto s : p.phones)
            std::cout << s << std::endl;
    }

    // pause
    system("pause");
    return 0;
}