//  Exercise2.35.cpp
//  Ad
//  Determine the types deduced in each of the following definitions.

#include <iostream>

int main()
{
    const int i{17};
    auto j{i};          //  j is a int
    const auto &k{i};   //  k is a reference to const int
    auto *p{&i};        //  p is a pointer to const int
    const auto j2{i}, &k2{i};   //  j2 is a const int, k2 is a reference to const int
    std::cout << 'i' << '\t' << 'j' << '\t' << 'k' << '\t' << "p\t" << '\t' << "*p" << '\t' << "j2" << '\t' << "k2" << std::endl;
    std::cout << i << '\t' << j << '\t' << k << '\t' << p << '\t' << *p << '\t' << j2 << '\t' << k2 << std::endl;

    //  Pause
    std::cin.get();
    return 0;
}