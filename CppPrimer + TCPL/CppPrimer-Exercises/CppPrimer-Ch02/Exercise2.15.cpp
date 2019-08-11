//  Exercise2.15.cpp
//  Ad
//  Which of the following definitions are invalid?

#include <iostream>

int main()
{
    int ival = 1.01;
    int &rval1 = 1.01;  //  cannot refer to a literal
    int &rval2 = ival;
    int &rval3;         //  not defined

    //  Pause
    std::cin.get();
    return 0;
}