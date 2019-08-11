//  Exercise6.10.cpp
//  Ad
//  Using pointers, write a function to swap the values of two ints.

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

void swap(int *p1, int *p2);

int main()
{
    int i1 = {1}, i2 = {2};
    cout << i1 << ' ' << i2 << endl;
    swap(&i1, &i2);
    cout << i1 << ' ' << i2 << endl;

    //  pause
    cin.get();
    return 0;
}

void swap(int *p1, int *p2)
{
    int temp = {*p1};
    *p1 = *p2;
    *p2 = temp;
}