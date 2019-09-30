//  Exercise6.25.cpp
//  Ad
//  Write a main function that takes two arguments and print the string.

#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::endl;

int main(int argc, char* argv[])
{
    std::string str = {};
    str = std::string(argv[0]);
    cout << str << endl;

    //  pause
    cin.get();
    return 0;
}