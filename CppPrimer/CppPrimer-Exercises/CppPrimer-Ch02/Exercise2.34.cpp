//  Exercise2.34.cpp
//  Ad
//  Print the variables from previous exercise, check your predictions.

#include <iostream>

int main()
{
    int i{0}, &r{i};
    const int ci{i}, &cr{ci};
    auto a = r;
    auto b = ci;
    auto c = cr;
    auto d = &i;
    auto e = &ci;
    auto &g = ci;
    std::cout << a << ' ' << b << ' ' << c << ' ' << d << ' ' << e << ' ' << g << std::endl;
    a = 17;
    b = 17;
    c = 17;
    // d = 17;
    // e = 17;
    // g = 17;
    std::cout << a << ' ' << b << ' ' << c << ' ' << d << ' ' << e << ' ' << g << std::endl;

    //  Pause
    std::cin.get();
    return 0;
}