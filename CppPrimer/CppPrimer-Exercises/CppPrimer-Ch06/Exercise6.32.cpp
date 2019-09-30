//  Exercise6.32.cpp
//  Ad
//  Indicate whether the following function is legal.

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

int &get(int *arr, int index);

int main(int argc, char* argv[])
{
    int ia[10];
    for (auto i : ia)
    {
        cout << i << ' ';
    }
    cout << endl;
    for (int i = 0; i != 10; ++i)
    {
        get(ia, i) = i;
    }
    for (auto i : ia)
    {
        cout << i << ' ';
    }
    cout << endl;

    //  pause
    cin.get();
    return 0;
}

int  &get(int *arr, int index)
{
    return arr[index];
}