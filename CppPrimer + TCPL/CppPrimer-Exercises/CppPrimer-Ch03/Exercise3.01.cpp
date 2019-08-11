//  Exercise3.1.cpp
//  Ad
//  Rewrite the exercises from 1.4.1 with using declaration.

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

int main()
{
    int v1{0}, v2{0};
    int i{0};
    cout << "Enter two integers:" << endl;
    cin >> v1 >> v2;
    i = v1;
    while (i <= v2)
    {
        cout << i << endl;
        ++i;
    }

    //  Pause 
    system("pause");
    return 0;
}