//  Exercise4.33.cpp
//  Ad
//  Explain what the following exprssion does.

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

int main()
{
    int x = {0}, y = {0};
    1 ? ++x, ++y : --x, --y;
    cout << x << ' ' << y << ' ' << endl;

    //  pause
    cin.get();
    return 0;
}