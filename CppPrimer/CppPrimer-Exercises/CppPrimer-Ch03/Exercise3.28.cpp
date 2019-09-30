//  Exercise3.28.cpp
//  Ad
//  What are the values in the following arrays?

#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::endl;

std::string sa[10];
int ia[10];

int main()
{
    cout << sa[0] << ' ' << ia[0] << endl;
    std::string sa[10];
    int ia[10];
    cout << sa[0] << ' ' /* << ia[0] */ << endl;    

    //  pause
    cin.get();
    return 0;
}