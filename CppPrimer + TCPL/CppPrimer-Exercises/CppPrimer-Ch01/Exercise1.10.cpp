//  Exercise1.10.cpp
//  Ad
//  Use the decrement operator to write a while that prints the numbers from ten down to zero.

#include <iostream>

int main()
{
    int i = 10;
    while (i > -1)
    {
        std::cout << i << std::endl;
        --i;
    }

    //  Pause
    std::cin.get();
    return 0;
}