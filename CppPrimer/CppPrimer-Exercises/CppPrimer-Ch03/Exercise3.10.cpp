//  Exercise3.10.cpp
//  Ad
//  Write a program to read a string including punctuation and print it without punctuation.

#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::endl;
using std::string;

int main()
{
    string s1{};
    cin >> s1;
    if (!s1.empty())
        for (auto c : s1)
            if (!ispunct(c))
                cout << c;
    cout << endl;

    //  Pause
    system("pause");
    return 0;
}