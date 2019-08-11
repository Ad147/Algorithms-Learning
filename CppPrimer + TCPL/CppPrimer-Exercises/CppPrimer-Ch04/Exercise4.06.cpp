//  Exercise4.6.cpp
//  Ad
//  Write a expression to determine whether a int value is even or odd.

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

int main()
{
    int i{0};
    cin >> i;
    if (i % 2 == 0)
        cout << "i is a even number." << endl;
    else
        cout << "i is an odd number." << endl;

    //  pause
    system("pause");
    return 0;
}