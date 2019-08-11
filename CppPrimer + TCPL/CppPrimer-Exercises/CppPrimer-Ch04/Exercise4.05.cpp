//  Exercise4.5.cpp
//  Ad
//  Determine the result of the following expressions.

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

int main()
{
    cout << -30 * 3 + 21 / 5 << endl    //  -86, -18, 0, -2
         << -30 + 3 * 21 / 5 << endl
         << 30 / 3 * 21 % 5 << endl
         << -30 / 3 * 21 % 4 << endl;

    //  pause
    cin.get();
    return 0;
}