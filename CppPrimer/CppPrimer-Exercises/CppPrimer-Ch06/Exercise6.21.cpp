//  Exercise6.21.cpp
//  Ad
//  Write a function that takes an int and a pointer to an int and returns the larger of the int value or the value to which the pointer points.

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

int larger(int i, const int *p);

int main()
{
    int i1 = {1}, i2 = {2}, i3 = {3};
    int *p = {&i2};
    cout << larger(i1, p) << endl
         << larger(i3, p) << endl;

    //  pause
    cin.get();
    return 0;
}

int larger(int i, const int *p)
{
    return i > *p ? i : *p;
}