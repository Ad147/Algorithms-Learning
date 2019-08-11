//  Exercise5.19.cpp
//  Ad
//  Use a do while loop to repetitively request two string form user and report which is less.

#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::endl;

int main()
{
    std::string str1 = {}, str2 = {};
    cin >> str1 >> str2;
    do
    {
        if (str1 == str2)
        {
            cout << "Equal." << endl;
        }
        else
        {
            cout << (str1 < str2 ? str1 : str2) << " is less." << endl;
        }
    } while (cin >> str1 >> str2);

    //  pause
    system("pause");
    return 0;
}