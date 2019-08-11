//  Exercise4.22.cpp
//  Ad
//  Extend the program that assigned high pass, pass, and fail grades to also assign low pass for grades between 60 and 75 inclusive.

#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::endl;

int main()
{
    unsigned grade{0};
    cin >> grade;
    std::string finalGrade{};
    //  using only conditional operators
    finalGrade = (grade > 90) ? "high pass"
                              : (grade < 60) ? "fail"
                                             : (grade > 75) ? "pass" : "low pass";
    cout << finalGrade << endl;
    //  using only ifs
    if (grade > 90)
    {
        finalGrade = "high pass";
    }
    else if (grade < 60)
    {
        finalGrade = "fail";
    }
    else if (grade > 75)
    {
        finalGrade = "pass";
    }
    else
    {
        finalGrade = "low pass";
    }
    cout << finalGrade << endl;
    //  using conditional operators and if
    if (grade > 75)
    {
        finalGrade = (grade > 90) ? "high pass" : "pass";
    }
    else
    {
        finalGrade = (grade < 60) ? "fail" : "low pass";
    }
    cout << finalGrade << endl;

    //  pause
    system("pause");
    return 0;
}