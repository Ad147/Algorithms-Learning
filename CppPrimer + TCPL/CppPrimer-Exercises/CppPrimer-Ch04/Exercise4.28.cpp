//  Exercise4.28.cpp
//  Ad
//  Write a program to print the size of each of the butlt-in types.

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

int main()
{
    cout << "size of bool: \t\t" << sizeof(bool) << endl
         << "size of char: \t\t" << sizeof(char) << endl
         << "size of wchar_t: \t" << sizeof(wchar_t) << endl
         << "size of char16_t: \t" << sizeof(char16_t) << endl
         << "size of char32_t: \t" << sizeof(char32_t) << endl
         << "size of short: \t\t" << sizeof(short) << endl
         << "size of int: \t\t" << sizeof(int) << endl
         << "size of long: \t\t" << sizeof(long) << endl
         << "size of long long: \t" << sizeof(long long) << endl
         << "size of float: \t\t" << sizeof(float) << endl
         << "size of double: \t" << sizeof(double) << endl
         << "size of long double: \t" << sizeof(long double) << endl
         << "size of pointer to int: " << sizeof(int *) << endl;

    //  pause
    cin.get();
    return 0;
}