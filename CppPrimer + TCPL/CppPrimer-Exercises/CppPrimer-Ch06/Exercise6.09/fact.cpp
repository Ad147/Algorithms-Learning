//  fact.cpp
//  Exercise6.09
//  Ad
//  Write your own version of fact and factMain files.

#include <iostream>
#include "Chapter6.h"

int fact(int value)
{
    int sum = {1};
    for (int i = {1}; i <= value; ++i)
    {
        sum *= i;
    }
    return sum;
}