//  Exercise4.7.cpp
//  Ad
//  Show three expressions that will overflow.

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

int main()
{
    char c{};
    short s{};
    unsigned u{};
    c = 256;
    s = 40000;
    u = -1;
    cout << c << ' ' << s << ' ' << u << endl;

    //  pause
    cin.get();
    return 0;
}