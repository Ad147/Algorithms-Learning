//  Exercise3.8.cpp
//  Ad
//  Use while and traditional for loop to rewrite the first program.

#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::endl;
using std::string;

int main()
{
    //  Using range for
    string s1{"Hello"};
    cout << "Range for:" << endl
         << s1 << endl;
    for (auto &c : s1)
        c = 'X';
    cout << s1 << endl;
    //  Using while
    string s2{"World"};
    cout << "While:" << endl
         << s2 << endl;
    decltype(s2.size()) cnt{0};
    while (cnt < s2.size())
    {
        s2[cnt] = 'X';
        ++cnt;
    }
    cout << s2 << endl;
    //  Using traditional for
    string s3{"String"};
    cout << "Traditional for:" << endl
         << s3 << endl;
    for (decltype(s3.size()) cnt{0}; cnt < s3.size(); ++cnt)
        s3[cnt] = 'X';
    cout << s3 << endl;

    //  Pause
    cin.get();
    return 0;
}