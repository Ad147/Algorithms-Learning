// Exercise11.32.cpp
// Ad
// Using the multimap from the previous exercise, write a program to print the list of authors and their works alphabetically.

#include <iostream>
#include <string>
#include <map>

// main ------------------------------------------------------------------------

int main(int argc, char *argv[])
{
    std::multimap<std::string, std::string>
        authors = {{"Tolkien", "The Lord of the Rings"},
                   {"Tolkien", "The Hobbit"},
                   {"Martin", "A Song of Ice and Fire"}};

    for (const auto &p : authors)
        std::cout << p.first << ": " << p.second << std::endl;

    // pause
    system("pause");
    return 0;
}