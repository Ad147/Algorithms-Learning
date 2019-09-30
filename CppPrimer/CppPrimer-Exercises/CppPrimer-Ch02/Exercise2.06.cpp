//  Exercise2.6.cpp
//  Ad
//  What, if any, are the differences between the following definitions.

#include <iostream>

int main()
{
    int month1 = 9, day1 = 7;
    int month2 = 09, day2 = 07;
    std::cout << month1 << '.' << day1 << std::endl
              << month2 << '.' << day2 << std::endl;

    //  Pause
    std::cin.get();
    return 0;
}