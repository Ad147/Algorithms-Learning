// Exercise9.14.cpp
// Ad
// Write a program to assign the elements from a list of char* pointers to C-style character strings to a vector of strings.

#include <iostream>
#include <vector>
#include <list>
#include <string>

// main ------------------------------------------------------------------------

int main(int argc, char *argv[])
{
    std::list<char *> clst{"str0", "str1"};
    std::vector<std::string> svec;
    svec.assign(clst.begin(), clst.end());
    std::cout << svec[0] << ' ' << svec[1] << std::endl;

    // pause
    system("pause");
    return 0;
}