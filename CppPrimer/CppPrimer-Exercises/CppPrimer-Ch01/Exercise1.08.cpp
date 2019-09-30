//  Exercise1.8.cpp
//  Ad
//  Indicate which, if any, of the following output statements are legal.

#include <iostream>

int main()
{
    std::cout << "/*" << std::endl;
    std::cout << "*/" << std::endl;
    std::cout << /* "*/" */" << std::endl;
    std::cout << /* "*/" /* "/*" */ << std::endl;

    //  Pause
    std::cin.get();
    return 0;
}