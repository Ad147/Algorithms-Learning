//  Exercise6.12.cpp
//  Ad
//  Using pointers, write a function to swap the values of two ints.

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

void swap(int &r1, int &r2);

int main()
{
    int i1 = {1}, i2 = {2};
    cout << i1 << ' ' << i2 << endl;
    swap(i1, i2);
    cout << i1 << ' ' << i2 << endl;

    //  pause
    cin.get();
    return 0;
}

void swap(int &r1, int &r2)
{
    int temp = {r1};
    r1 = r2;
    r2 = temp;
}