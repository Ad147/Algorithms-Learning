//  Exercise4.11.cpp
//  Ad
//  Write a expression that tests four values, a, b, c, d, and ensure that a > b > c > d.

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

int main()
{
    int a{4}, b{3}, c{2}, d{1};
    if (a > b && b > c && c > d)
        cout << "OK" << endl;

    //  pause
    cin.get();
    return 0;
}