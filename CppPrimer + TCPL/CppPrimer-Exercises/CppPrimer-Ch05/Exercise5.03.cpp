//  Exercise.5.03cpp
//  Ad
//  Use the comma operator to rewrite the while loop from p.11 so that i no longer requires a block.

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

int main()
{
    int sum = {0}, val = {0};
    while (++val, val <= 10)
        sum += val;
    cout << "Sum of 1 to 10 inclusive is " << sum << endl;

    //  pause
    cin.get();
    return 0;
}