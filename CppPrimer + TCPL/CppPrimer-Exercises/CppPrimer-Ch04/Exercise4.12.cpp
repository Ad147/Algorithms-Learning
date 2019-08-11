//  Exercise4.12.cpp
//  Ad
//  Explain what i != j < k means.

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

int main()
{
    int i{1}, j{0}, k{0};
    if (i != j < k)
        cout << "i != j < k means i != (j < k)" << endl;
    else
        cout << "i != j < k means (i != j) < k" << endl;

    //  pause
    cin.get();
    return 0;
}