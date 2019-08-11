//  Exercise5.22.cpp
//  Ad
//  Rewrite the last example in this section using a loop.

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

int get_size();

int main()
{
    int sz = get_size();
    while (sz <= 0)
    {
        sz = get_size();
    }

    //  pause
    cin.get();
    return 0;
}

int get_size()
{
    return -1;
}