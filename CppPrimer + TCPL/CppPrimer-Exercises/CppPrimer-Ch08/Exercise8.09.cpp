// Exercise8.09.cpp
// Ad
// Use the function you wrote for the first exercise in p.314 to print the contents of an istringstream object.

#include <iostream>
#include <sstream>
#include <string>

// function --------------------------------------------------------------------

std::istream &function(std::istream &is)
{
    std::string s;
    while (is >> s)
    {
        std::cout << s << std::endl;
    }
    is.clear();
    return is;
}

// main ------------------------------------------------------------------------

int main(int argc, char *argv[])
{
    std::string str;
    getline(std::cin, str);
    std::istringstream sstrm(str);
    function(sstrm);

    // pause
    system("pause");
    return 0;
}