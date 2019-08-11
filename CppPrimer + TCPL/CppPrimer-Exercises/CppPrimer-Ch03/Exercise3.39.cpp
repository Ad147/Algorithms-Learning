//  Exercise3.39.cpp
//  Ad
//  Write a program to campare two strings. And write one to compare two C-style character string.

#include <iostream>
#include <string>
#include <cstring>
using std::cin;
using std::cout;
using std::endl;

int main()
{
    //  compare two strings
    std::string str1{}, str2{};
    if (str1 > str2)
    {
        cout << "str1 > str2" << endl;
    }
    else if (str1 < str2)
    {
        cout << "str1 < str2" << endl;
    }
    else
    {
        cout << "str1 == str2" << endl;
    }
    //  compare two character string
    char cstr1[10]{}, cstr2[10]{};
    if (strcmp(cstr1, cstr2) > 0)
    {
        cout << "cstr1 > cstr2" << endl;
    }
    else if (strcmp(cstr1, cstr2) < 0)
    {
        cout << "cstr1 < cstr2" << endl;
    }
    else
    {
        cout << "cstr1 == cstr2" << endl;
    }
    
    //  pause
    cin.get();
    return 0;
}