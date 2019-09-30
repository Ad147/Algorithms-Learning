// Exercise9.47.cpp
// Ad
// write a program that finds each numeric character and then each alphabetic character in the string "ab2c3d7R4E6".
// Write two versions of the program.
// The first should use find_first_of, and the second find_first_not_of.

#include <iostream>
#include <string>
using std::string;

// -----------------------------------------------------------------------------

int main(int argc, char *argv[])
{
    string str{"ab2c3d7R4E6"};
    string nums{"0123456789"};
    string alps{"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"};

    // version1: using find_first_of
    std::cout << "version1:" << std::endl;
    for (size_t i{0}; (i = str.find_first_of(nums, i)) != string::npos; ++i)
        std::cout << "found number at index: " << i
                  << " element is " << str[i] << std::endl;
    for (size_t i{0}; (i = str.find_first_of(alps, i)) != string::npos; ++i)
        std::cout << "found alphabet at index: " << i
                  << " element is " << str[i] << std::endl;

    // version2: using find_first_not_of
    std::cout << "version2:" << std::endl;
    for (size_t i{0}; (i = str.find_first_not_of(alps, i)) != string::npos; ++i)
        std::cout << "found number at index: " << i
                  << " element is " << str[i] << std::endl;
    for (size_t i{0}; (i = str.find_first_not_of(nums, i)) != string::npos; ++i)
        std::cout << "found alphabet at index: " << i
                  << " element is " << str[i] << std::endl;

    // pause
    system("pause");
    return 0;
}