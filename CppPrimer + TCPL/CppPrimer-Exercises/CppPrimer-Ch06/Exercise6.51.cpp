//  Exercise6.51.cpp
//  Ad
//  Write all four versions of f. Check your answers for the previous exercise.

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

void f();
void f(int);
void f(int, int);
void f(double, double = 3.14);

int main(int argc, char* argv[])
{
    f(2.56, 42);
    f(42);
    f(42, 0);
    f(2.56, 3.14);

    //  pause
    cin.get();
    return 0;
}

void f()
{
    cout << "Function f() called with no arguments." << endl;
}

void f(int i)
{
    cout << "Function f(int) called with arguments: " << i << endl;
}

void f(int i1, int i2)
{
    cout << "Function f(int, int) called with arguments: " << i1 << " and " << i2 << endl;
}

void f(double d1, double d2)
{
    cout << "Function f(double, double) called with arguments: " << d1 << " and " << d2 << endl;
}