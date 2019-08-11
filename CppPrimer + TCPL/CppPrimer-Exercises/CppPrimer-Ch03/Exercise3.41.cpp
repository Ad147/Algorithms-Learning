//  Exercise3.41.cpp
//  Ad
//  Write a program to initialize a vector from an array of ints.

#include <iostream>
#include <vector>
#include <iterator>
using std::cin;
using std::cout;
using std::endl;

int main()
{
    int arrInt[10]{1, 2, 3};
    std::vector<int> vecInt(std::begin(arrInt), std::end(arrInt));
    for (auto i : vecInt)
    {
        cout << i << ' ';
    }
    cout << endl;

    //  pause
    cin.get();
    return 0;
}