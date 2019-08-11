//  Exercise6.06.cpp
//  Ad
//  Give an example of a function in which the parameter, the local variable and the static variable are all useful.

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

int summation(int n);

int main()
{
    cout << summation(10) << endl;

    //  pause
    cin.get();
    return 0;
}

//  generating the sum of the numbers from 1 through n
//  and counting how many times the function is called
int summation(int n)
{
    static unsigned cnt = {0};
    ++cnt;
    int sum = {0};
    while (n > 0)
    {
        sum += n--;
    }
    return sum;
}