//  Exercise3.14.cpp
//  Ad
//  Write a program to read a sequence of ints from cin and store those values in a vector

#include <iostream>
#include <vector>
using std::cin;
using std::cout;
using std::endl;
using std::vector;

int main()
{
    vector<int> ivec{};
    int value{0};
    while (cin >> value)
        ivec.push_back(value);

    //  Pause
    cin.get();
    return 0;
}