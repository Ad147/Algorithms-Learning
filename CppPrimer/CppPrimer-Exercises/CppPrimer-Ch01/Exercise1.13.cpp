//  Exercise1.13.cpp
//  Ad
//  Rewrite the exercises from 1.4.1 using for loop.

#include <iostream>
void exercise_1_9();
void exercise_1_10();
void exercise_1_11();

int main()
{
    exercise_1_9();
    exercise_1_10();
    exercise_1_11();

    //  Pause
    system("pause");
    return 0;
}

void exercise_1_9()
{
    int sum = 0;
    for (int i = 50; i <= 100; ++i)
    {
        sum += i;
    }
    std::cout << "Sum of 50 to 100 is " << sum << std::endl;  
}

void exercise_1_10()
{
    for (int i = 10; i >= 0; --i)
    {
        std::cout << i << std::endl;
    }
}

void exercise_1_11()
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
    for (; i <= v2; ++i)
    {
        std::cout << i << std::endl;
    }
}