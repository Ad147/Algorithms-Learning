//  Exercise2.38.cpp
//  Ad
//  Give examples of expressions where auto and decltype deduce the same and different types.

#include <iostream>
#include <typeinfo>

int main()
{
    int i{17};
    int &r{i};
    //  deduce the same type
    auto a1{i};
    decltype(i) d1;
    std::cout << "a1" << " type: " << typeid(a1).name() << "\tvalue: " << a1 << std::endl;
    std::cout << "d1" << " type: " << typeid(d1).name() << "\tvalue: " << d1 << std::endl;
    //  deduce different types
    auto a2{r};
    decltype(r) d2;
    std::cout << "a2" << " type: " << typeid(a2).name() << "\tvalue: " << a2 << std::endl;
    std::cout << "d2" << " type: " << typeid(d2).name() << "\tvalue: " << d2 << std::endl;

    //  Pause
    std::cin.get();
    return 0;
}