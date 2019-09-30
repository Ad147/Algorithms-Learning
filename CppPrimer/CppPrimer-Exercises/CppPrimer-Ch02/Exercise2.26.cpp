//  Exercise2.26.cpp
//  Ad
//  Which of th following are legal?

#include <iostream>

int main()
{
    const int buf;
    int cnt = 0;
    const int sz = cnt;
    ++cnt;
    ++sz;

    //  Pause
    std::cin.get();
    return 0;
}