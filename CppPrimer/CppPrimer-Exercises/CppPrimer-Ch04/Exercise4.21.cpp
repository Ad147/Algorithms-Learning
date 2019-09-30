//  Exercise4.21.cpp
//  Ad
//  Write a program to use a conditional operator to find the elements in a vector<int> that have odd value and double the value of each such element.

#include <iostream>
#include <vector>
using std::cin;
using std::cout;
using std::endl;

int main()
{
    std::vector<int> vecInt = {1, 2, 3, 4, 5};
    for (auto &i : vecInt)
    {
        (i % 2 == 1) ? i *= 2 : 1;
    }
    for (auto i : vecInt)
        cout << i << endl;

    //  pause
    cin.get();
    return 0;
}