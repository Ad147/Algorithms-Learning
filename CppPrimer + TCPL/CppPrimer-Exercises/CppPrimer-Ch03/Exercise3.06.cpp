//  Exercise3.6.cpp
//  Ad
//  Use a range for to change all the chatacters in a string to X.

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
    for (auto &c : s1)
        c = 'X';
    cout << s1 << endl;

    //  Pause
    cin.get();
    return 0;
}