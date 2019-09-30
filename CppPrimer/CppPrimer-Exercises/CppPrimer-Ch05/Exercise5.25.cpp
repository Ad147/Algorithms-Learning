//  Exercise5.25.cpp
//  Ad
//  Revise the program to use a try block to catch the exception.

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
        try
        {
            if (i2 == 0)
            {
                throw std::runtime_error("The second number is zero.");
            }
            cout << i1 / i2 << endl;
        }
        catch (std::runtime_error err)
        {
            cout << err.what() << endl << "Try again? Enter y or n: " << endl;
            char c;
            cin >> c;
            if (!cin || c == 'n')
            {
                break;
            }
        }
    }

    //  pause
    system("pause");
    return 0;
}