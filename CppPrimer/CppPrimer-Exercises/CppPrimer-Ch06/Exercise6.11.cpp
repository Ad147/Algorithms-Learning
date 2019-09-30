//  Exercise6.11.cpp
//  Ad
//  Write your own version of reset that takes a reference.

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

void reset(int &i);

int main()
{
    int i = {1};
    cout << i << endl;
    reset(i);
    cout << i << endl;

    //  pause
    cin.get();
    return 0;
}

void reset(int &i)
{
    i = 0;
}