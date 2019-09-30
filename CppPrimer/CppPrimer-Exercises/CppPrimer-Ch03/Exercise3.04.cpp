//  Exercise3.4.cpp
//  Ad
//  Write a program to read two strings and report whether the strings are equal or have the same length.

#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::endl;
using std::string;

int main()
{
    string s1{}, s2{};
    cin >> s1 >> s2;
    if (s1 == s2)
    {
        cout << s1 << " and " << s2 << " are equal" << endl;
    }
    else if (s1 > s2)
    {
        cout << s1 << " is larger" << endl;
    }
    else
    {
        cout << s2 << " is larger" << endl;
    }
    if (s1.size() == s2.size())
    {
        cout << s1 << " and " << s2 << " have the same length" << endl;
    }
    else if (s1.size() > s2.size())
    {
        cout << s1 << " is longer" << endl;
    }
    else
    {
        cout << s2 << " is  longer" << endl;
    }
    
    //  Pause
    system("pause");
    return 0;
}