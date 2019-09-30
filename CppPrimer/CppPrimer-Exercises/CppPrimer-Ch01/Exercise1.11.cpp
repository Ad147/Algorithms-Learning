//  Exercise1.11.cpp
//  Ad
//  Write a program that prompts the user for two integers. Print each number in the range specified by the two integers.

#include <iostream>

int main()
{
    int v1 = 0, v2 = 0;
    int i = 0;
    std::cout << "Enter two integers:" << std::endl;
    std::cin >> v1 >> v2;
    i = v1;
    //  the following part is for exercise 1.19
    // if (v1 > v2)
    // {
    //     v1 = v2;
    //     v2 = i;
    //     i = v1;
    // }
    while (i <= v2)
    {
        std::cout << i << std::endl;
        ++i;
    }

    //  Pause 
    system("pause");
    return 0;
}