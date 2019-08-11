//  Exercise1.19.cpp
//  Ad
//  Revise the program for exercise 1.11 so that it handles input in which the first number is smaller/bigger than the second.

#include <iostream>

int main()
{
    int v1 = 0, v2 = 0;
    int i = 0;
    std::cout << "Enter two integers:" << std::endl;
    std::cin >> v1 >> v2;
    i = v1;
    if (v1 > v2)
    {
        v1 = v2;
        v2 = i;
        i = v1;
    }
    while (i <= v2)
    {
        std::cout << i << std::endl;
        ++i;
    }

    //  Pause 
    system("pause");
    return 0;
}