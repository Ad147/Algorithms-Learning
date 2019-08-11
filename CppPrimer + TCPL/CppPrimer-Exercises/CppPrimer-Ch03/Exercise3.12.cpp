//  Exercise3.12.cpp
//  Ad
//  Which of the following vector definitions are in error?

#include <iostream>
#include <vector>
using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;

int main()
{
    vector<vector<int>> ivec;
    vector<string> svec1 = ivec;
    vector<string> svec2(10, "null");

    //  Pause
    cin.get();
    return 0;
}