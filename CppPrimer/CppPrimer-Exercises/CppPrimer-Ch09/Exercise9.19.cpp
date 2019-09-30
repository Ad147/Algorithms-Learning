// Exercise9.19.cpp
// Ad
// Rewrite the program from the previous exercise to use a list.
// List the changes you needed to make.

#include <iostream>
#include <list>
#include <string>

// main ------------------------------------------------------------------------

int main(int argc, char *argv[])
{
    std::list<std::string> sdeq; // change the container type only
    std::string s;
    while (std::cin >> s)
    {
        sdeq.push_back(s);
    }
    for (auto dit{sdeq.begin()}; dit != sdeq.end(); ++dit)
        std::cout << *dit << ' ';
    std::cout << std::endl;

    // pause
    system("pause");
    return 0;
}