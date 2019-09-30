//  Exercise3.32.cpp
//  Ad
//  Copy the array in the previous exercise, then rewrite using vector.

#include <iostream>
#include <vector>
#include <cstddef>
using std::cin;
using std::cout;
using std::endl;

int main()
{
    //  define array
    constexpr size_t sizeArr{10};
    int ia[sizeArr]{};
    for (size_t i{0}; i < sizeArr; ++i)
        ia[i] = i + 1;
    //  copy to a new array
    int ia1[sizeArr]{};
    for (size_t i{0}; i < sizeArr; ++i)
        ia1[i] = ia[i];
    //  define vector
    std::vector<int> ivec{};
    for (int i{1}; i <= 10; ++i)
        ivec.push_back(i);
    //  copy to a new vector
    std::vector<int> ivec1{ivec};
    //  print the arrays
    for (int i : ia)
        cout << i << ' ';
    cout << endl;
    for (int i : ia1)
        cout << i << ' ';
    cout << endl;
    for( int i : ivec)
        cout << i << ' ';
    cout << endl;
    for( int i : ivec1)
        cout << i << ' ';
    cout << endl;

    //  pause
    cin.get();
    return 0;
}