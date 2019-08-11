//  Exercise2.10.cpp
//  Ad
//  What are the initial values, if any, of each of the following variables?

#include <iostream>

std::string globalStr;
int globalInt;

int main()
{
    int localInt;
    std::string localStr;
    std::cout << '|' << globalStr << '|' << std::endl
              << globalInt << std::endl
              << localInt << std::endl
              << '|' << localStr << '|' << std::endl;

    //  Pause
    std::cin.get();
    return 0;
}