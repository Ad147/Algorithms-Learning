//  Exercise5.24.cpp
//  Ad
//  Revise the program to throw an exception if the second number is zero.

#include <iostream>
#include <stdexcept>
using std::cin;
using std::cout;
using std::endl;

int main()
{
    int i1 = {0}, i2 = {0};
    while (cin >> i1 >> i2)
    {
        if (i2 == 0)
        {
            throw std::runtime_error("The second number is zero.");
        }
        cout << i1 / i2 << endl;
    }

    //  pause
    system("pause");
    return 0;
}