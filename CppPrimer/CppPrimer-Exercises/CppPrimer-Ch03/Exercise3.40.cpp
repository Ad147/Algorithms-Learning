//  Exercise3.40.cpp
//  Ad
//  Write a program to define an character array to hold the concatenation of two arrays.

#include <iostream>
#include <cstring>
using std::cin;
using std::cout;
using std::endl;

int main()
{
    char str1[10]{"Hello"}, str2[10]{"World"};
    char str3[20]{};
    strcpy(str3, str1);
    strcat(str3, str2);
    cout << str1 << endl
         << str2 << endl
         << str3 << endl;

    //  pause
    cin.get();
    return 0;
}