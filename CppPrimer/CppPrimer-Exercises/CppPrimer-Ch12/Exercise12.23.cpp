// Exercise12.23.cpp
// Ad
// Write a program to concatenate two string literals, putting the result in a dynamically allocated array of char.
// Write a program to concatenate two library strings that have the same value as the literals used in the first program.

#include <iostream>
#include <string>

// main ========================================================================

int main(int argc, char *argv[])
{
    char sl1[] = {"Hello"};
    char sl2[] = {"World"};
    int n = (sizeof(sl1) + sizeof(sl2)) / sizeof(char) - 1;
    char *psa = new char[n]();

    // concatenating
    auto q = psa;
    int i = {0};
    while (q != psa + sizeof(sl1) / sizeof(char) - 1)
    {
        *q = sl1[i];
        ++q;
        ++i;
    }
    i = 0;
    while (q != psa + n)
    {
        *q = sl2[i];
        ++q;
        ++i;
    }
    for (auto q = psa; q != psa + n; ++q)
        std::cout << *q;
    std::cout << std::endl;

    delete[] psa;

    // using library string
    std::string s1 = {"Hello"};
    std::string s2 = {"World"};
    std::string s = s1 + s2;
    std::cout << s << std::endl;

    // pause
    system("pause");
    return 0;
}