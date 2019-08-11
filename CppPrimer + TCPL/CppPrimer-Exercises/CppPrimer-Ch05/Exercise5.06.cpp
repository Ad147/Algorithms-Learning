//  Exercise5.06.cpp
//  Ad
//  Rewrite the program to use the conditional operator.

#include <iostream>
#include <vector>
#include <string>
using std::cin;
using std::cout;
using std::endl;

int main()
{
    unsigned grade = {0};
    std::string graLet = {};
    std::vector<std::string> letter = {"F", "D", "C", "B", "A", "A++"};
    while (cin >> grade)
    {
        graLet = grade < 60 ? letter[0] : letter[(grade - 50) / 10];
        cout << grade << ':' << graLet << endl;
    }

    //  pause
    system("pause");
    return 0;
}