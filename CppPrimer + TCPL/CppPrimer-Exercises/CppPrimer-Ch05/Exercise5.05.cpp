//  Exercise5.05.cpp
//  Ad
//  Using if-else statement, write your own version of the program to generate the letter grade from a numeric grade.

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
    //  using many if-elses
    while (cin >> grade)
    {
        if (grade < 80)
        {
            if (grade < 70)
            {
                if (grade < 60)
                {
                    graLet = 'F';
                }
                else
                {
                    graLet = 'D';
                }
            }
            else
            {
                graLet = 'C';
            }
        }
        else if (grade < 100)
        {
            if (grade < 90)
            {
                graLet = 'B';
            }
            else
            {
                graLet = 'A';
            }
        }
        else
        {
            graLet = "A++";
        }
        cout << grade << ':' << graLet << endl;
    }
    //  using no if-else
    std::vector<std::string> letter = {"F", "F", "F", "F", "F", "F", "D", "C", "B", "A", "A++"};
    while (cin >> grade)
    {
        graLet = letter[grade / 10];
        cout << grade << ':' << graLet << endl;
    }

    //  pause
    system("pause");
    return 0;
}