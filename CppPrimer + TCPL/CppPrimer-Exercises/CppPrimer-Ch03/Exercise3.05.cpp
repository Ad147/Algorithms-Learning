//  Exercise3.5.cpp
//  Ad
//  Write a program to read strings and concatenate them.

#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::endl;
using std::string;

int main()
{
    string sum{}, s1{};
    if (cin >> sum)
    {
        while (cin >> s1)
        {
            sum += ' ' + s1;
        }
        cout << sum << endl;
    }
    else
    {
        cout << "No input" << endl;
    }
    
    //  Pause
    system("pause");
    return 0;
}