//  Exercise3.15.cpp
//  Ad
//  Write a program to read a sequence of string from cin and store those values in a vector

#include <iostream>
#include <vector>
using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;

int main()
{
    vector<string> svec{};
    string value{};
    while (cin >> value)
        svec.push_back(value);

    //  Pause
    cin.get();
    return 0;
}