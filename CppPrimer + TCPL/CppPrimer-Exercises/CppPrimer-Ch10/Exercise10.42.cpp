// Exercise10.42.cpp
// Ad
// Reimplement the progaram that eliminated duplicate words that we wrote to use a list instead of a list.

#include <iostream>
#include <list>
#include <string>
#include <algorithm>

// function --------------------------------------------------------------------

void elimDups(std::list<std::string> &slst)
{
    slst.reverse();
    slst.unique();
}

// test ------------------------------------------------------------------------

int main(int argc, char *argv[])
{
    std::list<std::string> slst{"beta", "alpha", "gama", "beta", "alpha"};
    elimDups(slst);
    for (auto s : slst)
        std::cout << s << ' ';
    std::cout << std::endl;

    // pause
    system("pause");
    return 0;
}