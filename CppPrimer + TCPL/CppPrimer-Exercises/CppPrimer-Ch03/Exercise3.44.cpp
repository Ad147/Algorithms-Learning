//  Exercise3.44.cpp
//  Ad
//  Rewrite the previous program using a type alias.

#include <iostream>
#include <cstddef>
using std::cin;
using std::cout;
using std::endl;

//  define a type alias
using int_arr = int[4];

int main()
{
    int ia[3][4]{
        {0, 1, 2, 3},
        {4, 5, 6, 7},
        {8, 9, 10, 11}};
    //  using range for
    for (int_arr &i : ia)
    {
        for (int j : i)
            cout << j << ' ';
        cout << endl;
    }
    //  using for and subscripts
    for (size_t i{0}; i != 3; ++i)
    {
        for (size_t j{0}; j != 4; ++j)
            cout << ia[i][j] << ' ';
        cout << endl;
    }
    //  using for and pointers
    for (int_arr *p{ia}; p != ia + 3; ++p)
    {
        for (int *q{*p}; q != *p + 4; ++q)
            cout << *q << ' ';
        cout << endl;
    }

        //  pause
        cin.get();
    return 0;
}