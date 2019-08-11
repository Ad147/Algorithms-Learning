//  Exercise2.20.cpp
//  Ad
//  What does the following program do?

#include <iostream>

int main()
{
    int i = 42;
    int *p = &i;
    *p = *p * *p;
    std::cout << *p << std::endl;

    //  Pause
    std::cin.get();
    return 0;
}