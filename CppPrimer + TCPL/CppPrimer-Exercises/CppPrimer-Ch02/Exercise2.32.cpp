//  Exercise2.32.cpp
//  Ad
//  Is the following code legal?

#include <iostream>

int main()
{
    // int null = 0, *p = null;
    //  Solution1: make p points to nothing
    int null1 = 0, *p1{nullptr};
    //  Solution2: make p points to the integer null
    int null2 = 0, *p2{&null2};

    //  Pause
    std::cin.get();
    return 0;
}