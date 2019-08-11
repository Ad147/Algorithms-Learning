//  Exercise3.19.cpp
//  Ad
//  List 3 ways to difine a vector and give it 10 elements with 42.

#include <iostream>
#include <vector>
using std::cin;
using std::cout;
using std::endl;

int main()
{
    std::vector<int> ivec1(10, 42);
    std::vector<int> ivec2{ivec1};
    std::vector<int> ivec3{42, 42, 42, 42, 42, 42, 42, 42, 42, 42};

    //  Pause
    cin.get();
    return 0;
}