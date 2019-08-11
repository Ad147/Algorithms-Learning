//  Exercise3.31.cpp
//  Ad
//  Write a program to define an array of ten ints. Give each elemetns the same value as its position in the array.

#include <iostream>
#include <cstddef>
using std::cin;
using std::cout;
using std::endl;

int main()
{
    constexpr size_t sizeArr{10};
    int ia[sizeArr];
    for (size_t i{0}; i < sizeArr; ++i)
    {
        ia[i] = i + 1;
    }
    for (int i : ia)
    {
        cout << i << ' ';
    }
    cout << endl;

    //  pause
    cin.get();
    return 0;
}