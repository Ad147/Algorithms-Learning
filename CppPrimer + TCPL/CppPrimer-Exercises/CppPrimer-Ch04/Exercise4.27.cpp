//  Exercise4.27.cpp
//  Ad
//  What is the result of each of these expressions?

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

int main()
{
    unsigned long ul1 = 3, ul2 = 7;
    cout << (ul1 & ul2) << endl     //  3
         << (ul1 | ul2) << endl     //  7
         << (ul1 && ul2) << endl    //  1
         << (ul1 || ul2) << endl;   //  1

    //  pause
    cin.get();
    return 0;
}