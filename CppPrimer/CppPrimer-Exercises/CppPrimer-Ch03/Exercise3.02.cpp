//  Exercise3.2.cpp
//  Ad
//  Write a program to read one line/one word at a time.

#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::endl;
using std::string;

int main()
{
    string s1{}, s2{};
    getline(cin, s1);
    cin >> s2;
    cout << s1 << endl
         << s2 << endl;
    
    //  Pause
    system("pause");
    return 0;
}