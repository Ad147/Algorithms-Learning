//  Exercise2.37.cpp
//  Ad
//  Determine the type and value of each variable.

#include <iostream>

int main()
{
    int a = 3, b = 4;
    decltype(a) c = a;
    decltype(a = b) d = a;
    // ++d;
    std::cout << a << '\t' << b << '\t' << c << '\t' << d << '\t' << std::endl;


    //  Pause
    std::cin.get();
    return 0;
}