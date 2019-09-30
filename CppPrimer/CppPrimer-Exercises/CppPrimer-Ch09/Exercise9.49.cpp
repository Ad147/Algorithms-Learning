// Exercise9.49.cpp
// Ad
// Write a program that reads a file containing words and reports the longest word that contains neither ascender nor descender.

#include <iostream>
#include <fstream>
#include <string>

// -----------------------------------------------------------------------------

int main(int argc, char *argv[])
{
    std::string asc{"bdfhklt"};
    std::string des{"gjpqy"};
    std::ifstream f("test");
    std::string str; // to store the output
    size_t size{0};  // to store the size
    std::string s;
    while (f >> s)
    {
        if ((s.find_first_of(asc) == std::string::npos) &&
            (s.find_first_of(des) == std::string::npos))
            if (s.size() > size)
            {
                str = s;
                size = s.size();
            }
    }
    std::cout << str << std::endl;

    // pause
    system("pause");
    return 0;
}