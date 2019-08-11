//  Exercise3.42.cpp
//  Ad
//  Write a program to copy a vector of ints into an array  of ints.

#include <iostream>
#include <vector>
using std::cin;
using std::cout;
using std::endl;

int main()
{
    std::vector<int> vecInt(10, 7);
    int arrInt[10]{};
    int *pi{arrInt};
    for (auto i : vecInt)
    {
        *pi = i;
        ++pi;
    }
    for (auto i : arrInt)
    {
        cout << i << ' ';
    }
    cout << endl;


    //  pause
    cin.get();
    return 0;
}