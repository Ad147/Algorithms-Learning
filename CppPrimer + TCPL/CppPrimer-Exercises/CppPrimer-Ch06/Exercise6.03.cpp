//  Exercise6.03.cpp
//  Ad
//  Write your own version of fact.

int fact(int value);

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

int main()
{
    cout << fact(5) << endl;

    //  pause
    cin.get();
    return 0;
}

int fact(int value)
{
    int sum = {1};
    for (int i = {1}; i <= value; ++i)
    {
        sum *= i;
    }
    return sum;
}