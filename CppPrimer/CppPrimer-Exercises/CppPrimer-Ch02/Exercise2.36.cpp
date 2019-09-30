//  Exercise2.36.cpp
//  Ad
//  Determine the type and variable when code finishes.

#include <iostream>

int main()
{
    int a = 3, b = 4;
    decltype(a) c = a;
    decltype((b)) d = a;
    ++c;
    ++d;
    std::cout << a << '\t' << b << '\t' << c << '\t' << d << '\t' << std::endl;

    //  Pause
    std::cin.get();
    return 0;
}