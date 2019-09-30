//  Exercise4.29.cpp
//  Ad
//  Predict the output of the following code and run the program.

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

int main()
{
    int x[10];
    int *p = x;
    cout << sizeof(x) / sizeof(*x) << endl;
    cout << sizeof(p) / sizeof(*p) << endl;

    //  pause
    cin.get();
    return 0;
}