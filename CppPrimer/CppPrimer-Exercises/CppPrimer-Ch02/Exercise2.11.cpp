//  Exercise2.11.cpp
//  Ad
//  Explain whether each of the following is a declaration or a definition.

#include <iostream>

int main()
{
    extern int ix = 1024;
    int iy;
    extern int iz;
    std::cout << ix << std::endl
              << iy << std::endl
              << iz << std::endl;

    //  Pause
    std::cin.get();
    return 0;
}