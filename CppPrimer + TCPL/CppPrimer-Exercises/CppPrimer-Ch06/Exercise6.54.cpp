//  Exercise6.54.cpp
//  Ad
//  Write a declaration for a function that takes two int parameters and returns a int, and declare a vector whose elements have this function pointer type.

#include <iostream>
#include <vector>
using std::cin;
using std::cout;
using std::endl;

int function(int i1, int i2);
//  using type alias
using ptrFun = int(*)(int, int);

int main(int argc, char* argv[])
{
    std::vector<ptrFun> vecPtr = {};

    //  pause
    cin.get();
    return 0;
}