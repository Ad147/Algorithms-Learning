//  Exercise3.45.cpp
//  Ad
//  Rewrite the previous program using auto.

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

int main()
{
    int ia[3][4]{
        {0, 1, 2, 3},
        {4, 5, 6, 7},
        {8, 9, 10, 11}};
    //  using range for
    for (auto &i : ia)
    {
        for (auto j : i)
            cout << j << ' ';
        cout << endl;
    }
    //  using for and subscripts
    for (auto i{0}; i != 3; ++i)
    {
        for (auto j{0}; j != 4; ++j)
            cout << ia[i][j] << ' ';
        cout << endl;
    }
    //  using for and pointers
    for (auto p{ia}; p != ia + 3; ++p)
    {
        for (auto q{*p}; q != *p + 4; ++q)
            cout << *q << ' ';
        cout << endl;
    }

        //  pause
        cin.get();
    return 0;
}