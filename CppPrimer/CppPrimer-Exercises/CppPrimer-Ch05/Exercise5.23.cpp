//  Exercise5.23.cpp
//  Ad
//  Write a program that reads two integers and prints the result of dividing the first number by the second.

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

int main()
{
    int i1 = {0}, i2 = {0};
    while (cin >> i1 >> i2)
    {
        cout << i1 / i2 << endl;
    }

    //  pause
    system("pause");
    return 0;
}