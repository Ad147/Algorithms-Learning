//  Exercise2.14.cpp
//  Ad
//  What values are printed?

#include <iostream>

int main()
{
    int i = 100, sum = 0;
    for (int i = 0; i != 10; ++i)
    {
        sum += i;
    }
    std::cout << i << " " << sum << std::endl;

    //  Pause
    std::cin.get();
    return 0;
}