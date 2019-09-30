//  Exercise2.28.cpp
//  Ad
//  Explain the following definitions.

#include <iostream>

int main()
{
    int i, *const cp;       //  cp uninitialized
    int *p1, *const p2;     //  p2 uninitialized
    const int ic, &r = ic;  //  ic uninitialized
    const int *const p3;    //  p3 uninitialized
    const int *p;

    //  Pause
    std::cin.get();
    return 0;
}