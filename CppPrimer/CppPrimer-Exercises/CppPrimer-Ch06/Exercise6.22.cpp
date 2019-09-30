//  Exercise6.22.cpp
//  Ad
//  Write a function to swap two int pointers.

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

//  parameters are references to pointers to ints
void swap(int *&r1, int *&r2);

int main()
{
    int i1 = {1}, i2 = {2};
    int *p1 = {&i1}, *p2 = {&i2};
    cout << "p1: " << p1 << " *p1: " << *p1 << endl
         << "p2: " << p2 << " *p2: " << *p2 << endl;
    swap(p1, p2);
    cout << "p1: " << p1 << " *p1: " << *p1 << endl
         << "p2: " << p2 << " *p2: " << *p2 << endl;

    //  pause
    cin.get();
    return 0;
}

void swap(int *&r1, int *&r2)
{
    int *pTemp = {r1};
    r1 = r2;
    r2 = pTemp;
}