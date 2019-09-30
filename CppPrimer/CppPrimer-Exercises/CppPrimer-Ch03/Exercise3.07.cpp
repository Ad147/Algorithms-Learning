//  Exercise3.7.cpp
//  Ad
//  Use type char as the loop control variable type.

#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::endl;
using std::string;

int main()
{
    string s1{"Hello"};
    cout << s1 << endl;
    for (char c : s1)
        c = 'X';
    cout << s1 << endl;

    //  Pause
    cin.get();
    return 0;
}