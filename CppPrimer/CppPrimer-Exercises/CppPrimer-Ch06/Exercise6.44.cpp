//  Exercise6.44.cpp
//  Ad
//  Rewrite the isShorter function to be inline.

#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::endl;

inline bool isShorter(const std::string &s1, const std::string &s2)
{
    return s1.size() < s2.size();
}

    int main(int argc, char *argv[])
{

    //  pause
    cin.get();
    return 0;
}