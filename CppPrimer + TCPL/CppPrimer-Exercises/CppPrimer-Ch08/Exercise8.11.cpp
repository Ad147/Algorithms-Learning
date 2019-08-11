// Exercise8.11.cpp
// Ad
// The program in this section defined its istringstream object inside the outer while loop.
// What changes would you need to make if record were defined outside that loop?
// Rewrite the program, moving the definition of record outside the while, and see whether you thought of all the changes that are needed.

#include <iostream>
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
    std::istringstream record; // move the record definition outside
    while (getline(std::cin, line))
    {
        record.clear();   // clear the state
        record.str(line); // copy the string
        PersonInfo info;
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