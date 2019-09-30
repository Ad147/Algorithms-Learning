//  Exercise6.04.cpp
//  Ad
//  Write a function that asks for a number and generates the factorial.

int factorial();

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

int main()
{
    cout << factorial() << endl;

    //  pause
    system("pause");
    return 0;
}

int factorial()
{
    cout << "Enter a number: " << endl;
    int value = {1};
    cin >> value;
    int sum = {1};
    for (int i = {1}; i <= value; ++i)
    {
        sum *= i;
    }
    return sum;
}