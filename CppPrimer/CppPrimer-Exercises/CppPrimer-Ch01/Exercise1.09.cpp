//  Exercise1.9.cpp
//  Ad
//  Write a program that uses a while to sum the numbers from 50 to 100.

#include <iostream>

int main()
{
    int sum = 0, i = 50;
    while (i < 101)
    {
        sum += i;
        ++i;
    }
    std::cout << "Sum of 50 to 100 is " << sum << std::endl;

    //  Pause
    std::cin.get();
    return 0;
}