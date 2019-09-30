// Exercise13.19.cpp
// Ad
// Does your Employee class need to define its own versions of the copy-control members?
// If so, why?
// Implement whatever copy-control members you think Employee needs.

#include <iostream>
#include <string>

// class =======================================================================

class Employee
{
  public:
    // constructors
    Employee() = default;
    Employee(const std::string &s) : name(s), id(idgen) { ++idgen; }
    // copy-control members
    Employee(const Employee &) = delete;
    Employee &operator=(const Employee &) = delete;

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