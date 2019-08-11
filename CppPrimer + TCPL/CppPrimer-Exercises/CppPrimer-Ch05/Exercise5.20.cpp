//  Exercise5.20.cpp
//  Ad
//  Read a sequence of strings until either the same word occurs twice or all the words have been read.

#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::endl;

int main()
{
    std::string str = {}, strLast = {};
    bool flag = {0};    //  to flag repeat
    while (cin >> str)
    {
        if (str == strLast)
        {
            cout << str << " occurs twice." << endl;
            flag = 1;
            break;
        }
        strLast = str;
    }
    if (flag == 0)
    {
        cout << "No repeat." << endl;
    }

    //  pause
    system("pause");
    return 0;
}