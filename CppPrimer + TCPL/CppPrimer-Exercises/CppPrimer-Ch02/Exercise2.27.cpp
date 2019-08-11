//  Exercise2.27.cpp
//  Ad
//  Which of the following are legal?

#include <iostream>

int main()
{
    int i = -1, &r = 0;         //  cannot refer to 0
    int i2{0};
    int *const p2 = &i2;
    const int ii = -1, &rr = 0;
    const int *const p3 = &i2;
    const int *p1 = &i2;
    const int &const r2;        //  no const references and not initialized
    const int i3 = i, &r3 = i;

    //  Pause
    std::cin.get();
    return 0;
}