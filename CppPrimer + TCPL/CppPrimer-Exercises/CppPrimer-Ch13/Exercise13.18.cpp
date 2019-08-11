// Exercise13.18.cpp
// Ad
// Define an Employee class that contains an employee name and a unique employee identifier.
//Give the class a default constructor and a constructor that takes a string representing the employee's name.
// Each constructor should generate a unique ID by incrementing a static data member.

#include <iostream>
#include <string>

// class =======================================================================

class Employee
{
  public:
    Employee() = default;
    Employee(const std::string &s) : name(s), id(idgen) { ++idgen; }

  private:
    static int idgen;

    std::string name;
    int id;
};

int Employee::idgen = {0};

// main ========================================================================

int main(int argc, char *argv[])
{

    // pause
    system("pause");
    return 0;
}