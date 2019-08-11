// Exercise11.31.cpp
// Ad
// Write a program that defines a multimap of authors and their works.
// Use find to find an element in the multimap and erase that element.
// Be sure your program works correctly if the element you look for is not in the map.

#include <iostream>
#include <string>
#include <map>

// main ------------------------------------------------------------------------

int main(int argc, char *argv[])
{
    std::multimap<std::string, std::string> authors = {{"Tolkien", "The Lord of the Rings"}, {"Tolkien", "The Hobbit"}};

    std::string author = {"Aragorn"};
    if (authors.find(author) != authors.end())
        authors.erase(author);

    for (const auto &p : authors)
        std::cout << p.first << ": " << p.second << std::endl;

    // pause
    system("pause");
    return 0;
}