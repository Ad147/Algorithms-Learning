//  Exercise2.29.cpp
//  Ad
//  Using the variables in the previous exercise, which of the following assignments are legal?

#include <iostream>

int main()
{
    int i, *const cp{nullptr};
    int *p1, *const p2{nullptr};
    const int ic{0}, &r = ic;
    const int *const p3{nullptr};
    const int *p;

    i = ic;
    p1 = p3;    //  p1 is not a pointer to const
    p1 = &ic;   //  p1 is not a pointer to const
    p3 = &ic;   //  p3 is const
    p2 = p1;    //  p2 is const
    ic = *p3;   //  ic is const

    //  Pause
    std::cin.get();
    return 0;
}