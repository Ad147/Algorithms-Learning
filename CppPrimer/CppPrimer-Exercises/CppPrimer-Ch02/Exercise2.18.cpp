//  Exercise2.18.cpp
//  Ad
//  Write code to change the value of a pointer and the value to which the pointer points.

#include <iostream>

int main()
{
    int i{0};
    int *p = &i;
    std::cout << p << std::endl
              << *p << std::endl;
    //  change the value of pointer points
    *p = 17;
    std::cout << p << std::endl
              << *p << std::endl;
    //  change the value of pointer
    p = nullptr;
    std::cout << p << std::endl;
    //  std::cout << *p << std::endl;   //  p points to nothing

    //  Pause
    std::cin.get();
    return 0;
}