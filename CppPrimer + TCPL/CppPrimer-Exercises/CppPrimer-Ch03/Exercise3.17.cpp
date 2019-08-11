//  Exercise3.17.cpp
//  Ad
//  Read a sequence of words from cin and store the values in a vector. Change each word to uppercase then print.

#include <iostream>
#include <vector>
#include <string>
#include <cctype>
using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;

int main()
{
    vector<string> svec{};
    string str;
    while (cin >> str)
        svec.push_back(str);
    for (auto &s : svec)
    {
        for (auto &c : s)
            c = toupper(c);
        cout << s << ' ';
    }
    cout << endl;

    //  Pause
    system("pause");
    return 0;
}