//  Exercise5.17.cpp
//  Ad
//  Given two vectors if ints, determine whether one vector id a prefix of the other.

#include <iostream>
#include <vector>
using std::cin;
using std::cout;
using std::endl;

int main()
{
    std::vector<int> ivec1 = {}, ivec2 = {};
    ivec1 = {0, 1, 1, 2};
    ivec2 = {0, 1, 1, 2, 3, 5, 8};
    bool flag = {0};
    for (std::vector<int>::size_type i = {0}; i < ivec1.size() && i < ivec2.size(); ++i)
    {
        if (ivec1[i] != ivec2[i])
        {
            cout << "False" << endl;
            flag = 1;
            break;
        }
    }
    if (flag == 0)
    {
        cout << "True" << endl;
    }

    //  pause
    cin.get();
    return 0;
}