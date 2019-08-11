//  Exercise1.16.cpp
//  Ad
//  Write you own version of a program that prints the sum of a set of integers read from cin.

#include <iostream>

int main()
{
    int sum = 0, i = 0;
    while (std::cin >> i)   //  end-of-file in Windows is Ctrl-Z
    {
        sum += i;
    }
    std::cout << "The sum is " << sum << std::endl;
    
    //  Pause
    system("pause");
    return 0;
}