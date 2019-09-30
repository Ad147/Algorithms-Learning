//  Exercise2.31.cpp
//  Ad
//  Given the declarations in the previous exercise determine whether the following assignments are legal.

#include <iostream>

int main()
{
    const int v2 = 0;
    int v1 = v2;
    int *p1 = &v1, &r1 = v1;
    const int *p2 = &v2, *const p3 = &v2, &r2 = v2;

    r1 = v2;
    p1 = p2;    //  p1 is not const
    p1 = p3;    //  p1 is not const
    p2 = p1;
    p2 = p3;

    //  Pause
    std::cin.get();
    return 0;
}