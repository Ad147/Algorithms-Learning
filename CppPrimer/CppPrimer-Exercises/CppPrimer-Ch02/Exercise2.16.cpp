//  Exercise2.16.cpp
//  Ad
//  Which of the following assignments are invalid?

#include <iostream>

int main()
{
    int i = 0, &r1 = i;
    double d = 0, &r2 = d;
    r2 = 3.14159;
    std::cout << d << std::endl
              << r2 << std::endl;
    r2 = r1;
    std::cout << d << std::endl
              << r2 << std::endl;
    i = r2;
    std::cout << i << std::endl
              << r1 << std::endl;
    r1 = d;
    std::cout << i << std::endl
              << r1 << std::endl
              << d << std::endl
              << r2 << std::endl;

    //  Pause
    std::cin.get();
    return 0;
}