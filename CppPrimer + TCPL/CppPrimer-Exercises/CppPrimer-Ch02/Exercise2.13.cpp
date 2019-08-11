//  Exercise2.13.cpp
//  Ad
//  What is the value of j in the following program?

#include <iostream>

int i = 42;

int main()
{
    int i = 100;
    int j = i;
    std::cout << i << std::endl
              << j << std::endl;

    //  Pause
    std::cin.get();
    return 0;
}