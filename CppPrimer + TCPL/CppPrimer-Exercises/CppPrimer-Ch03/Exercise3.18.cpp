//  Exercise3.18.cpp
//  Ad
//  Is the following program legal?

#include <iostream>
#include <vector>
using std::cin;

int main()
{
    std::vector<int> ivec;
    ivec[0] = 42;   //  Illegal

    //  Pause
    cin.get();
    return 0;
}