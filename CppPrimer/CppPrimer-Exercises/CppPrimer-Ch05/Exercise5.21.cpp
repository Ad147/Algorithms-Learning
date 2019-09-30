//  Exercise5.21.cpp
//  Ad
//  Revise the previous program to look only for duplicated words that start with an uppercase letter.

#include <iostream>
#include <string>
#include <cctype>
using std::cin;
using std::cout;
using std::endl;

int main()
{
    std::string str = {}, strLast = {};
    bool flag = {0};    //  to flag repeat
    while (cin >> str)
    {
        if (str == strLast && std::isupper(*str.begin()))
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