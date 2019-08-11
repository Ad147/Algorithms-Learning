//  Exercise3.23.cpp
//  Ad
//  Write a program to create a vector with ten int elements. Using an iterator, assign each element a value that is twice ist current value.

#include <iostream>
#include <vector>
using std::cin;
using std::cout;
using std::endl;

int main()
{
    std::vector<int> ivec(10, 42);
    for (auto vit{ivec.begin()}; vit != ivec.end(); ++vit)
    {
        *vit *= 2;
        cout << *vit << ' ';
    }
    cout << endl;

    //  pause
    cin.get();
    return 0;
}