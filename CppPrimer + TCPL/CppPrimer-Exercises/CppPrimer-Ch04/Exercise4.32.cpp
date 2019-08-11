//  Exercise4.32.cpp
//  Ad
//  Explain the following loop.

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

int main()
{
    constexpr int size = 5;
    int ia[size] = {1, 2, 3, 4, 5};
    for (int *ptr = ia, ix = 0; ix != size && ptr != ia + size; ++ix, ++ptr)
    {
        cout << ix << ' ' << ptr << ' ' << *ptr << endl;
    }

    //  pause
    cin.get();
    return 0;
}