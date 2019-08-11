//  Exercise3.36.cpp
//  Ad
//  Write a program to compare two arrays for equality, then write a similar to compare vectors.

#include <iostream>
#include <vector>
#include <iterator>
using std::cin;
using std::cout;
using std::endl;

int main()
{
    //  to compare two arrays
    int arr1[10]{}, arr2[10]{};
    int *pa1{arr1}, *pa2{arr2};
    for (; pa1 != std::end(arr1) && pa2 != std::end(arr2); ++pa1, ++pa2)
    {
        if (*pa1 != *pa2)
            break;
    }
    if (pa1 != std::end(arr1))
    {
        if (*pa1 > *pa2)
            cout << "arr1 > arr2" << endl;
        else
            cout << "arr1 < arr2" << endl;
    }
    else
    {
        cout << "arr1 == arr2" << endl;
    }
    //  to compare two vectors
    std::vector<int> vec1{}, vec2{};
    if (vec1 > vec2)
    {
        cout << "vec1 > vec2" << endl;
    }
    else if (vec1 < vec2)
    {
        cout << "vec1 < vec2" << endl;
    }
    else
    {
        cout << "vec1 == vec2" << endl;
    }

    //  pause
    cin.get();
    return 0;
}