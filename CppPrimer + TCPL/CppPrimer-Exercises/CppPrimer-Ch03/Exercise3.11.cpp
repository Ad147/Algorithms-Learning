//  Exercise3.11.cpp
//  Ad
//  Is the following range for legal?

#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::endl;
using std::string;

int main()
{
    const string s1{"Keep out!"};
    for (auto &c : s1) {}

    //  Pause
    cin.get();
    return 0;
}