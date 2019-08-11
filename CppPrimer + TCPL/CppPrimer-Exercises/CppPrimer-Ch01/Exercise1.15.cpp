//  Exercise1.15.cpp
//  Ad
//  Write programs that contain the common errors discussed in the box on page 16.

#include <iostream>

int main()
{
    int v1 = 0, v2 = 0;
    std::cin >> v1 >> v2;
    //  error: cout and endl not defined; should be std::cout and std::endl
    cout << v1 + v2 << endl;

    //  error: missing ; on return statement
    return 0
}