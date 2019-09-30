//  Exercise4.36.cpp
//  Ad
//  Write the expression i *= d so that it does integral, rather than floating-point, multiplication.

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

int main()
{
    int i = {2};
    double d = {3.3};
    i *= static_cast<int>(d);
    cout << i << ' ' << d << endl;

    //  pause
    cin.get();
    return 0;
}