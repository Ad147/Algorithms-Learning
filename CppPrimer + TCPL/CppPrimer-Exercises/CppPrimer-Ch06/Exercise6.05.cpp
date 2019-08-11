//  Exercise6.05.cpp
//  Ad
//  Write a function to return the absolute value of its argument.

int absolute(int value);

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

int main()
{
    cout << absolute(5) << endl
         << absolute(0) << endl
         << absolute(-10) << endl;

    //  pause
    cin.get();
    return 0;
}

int absolute(int value)
{
    return value < 0 ? -value : value;
}