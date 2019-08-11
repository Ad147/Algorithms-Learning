//  Exercise3.35.cpp
//  Ad
//  Write a program to set the elements of an array to zero using pointers.

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

int main()
{
    int arr[10];
    for (int *pa{arr}; pa != &arr[9]; ++pa)
    {
        *pa = 0;
    }
    for (auto i : arr)
    {
        cout << i << ' ';
    }
    cout << endl;

    //  pause
    cin.get();
    return 0;
}