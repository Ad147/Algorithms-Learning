//  Exercise6.17.cpp
//  Ad
//  Write a function to determine whether a string contains any capital letters.
//  Write a function to change a string to all lowercase.

#include <iostream>
#include <string>
#include <cctype>
using std::cin;
using std::cout;
using std::endl;

int conCap(const std::string &str);
void allLow(std::string &str);

int main()
{
    std::string str1 = {"string contains a Capital letter"};
    std::string str2 = {"STRING TO BE CHANGED TO LOWERCASE"};
    cout << conCap(str1) << endl;
    cout << str2 << endl;
    allLow(str2);
    cout << str2 << endl;

    //  pause
    cin.get();
    return 0;
}

int conCap(const std::string &str)
{
    int flag = {0};
    for (char c : str)
    {
        if (c == std::toupper(c))
        {
            flag = 1;
            break;
        }
    }
    return flag;
}

void allLow(std::string &str)
{
    for (char &c : str)
    {
        c = std::tolower(c);
    }
}