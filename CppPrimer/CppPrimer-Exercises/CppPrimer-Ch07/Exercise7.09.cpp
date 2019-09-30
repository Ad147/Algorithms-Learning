// Exercise7.09.cpp
// Ad
// Add operations to read and print Person objects.

#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::endl;

// class declaration -----------------------------------------------------------

struct Person
{
    // member functions
    std::string getName() const { return name; }
    std::string getAddress() const { return address; }
    std::ostream &print(std::ostream &os) const;
    std::istream &read(std::istream &is);

    // member variables
    std::string name;
    std::string address;
};

// the following functions have been declared as member functions
// std::ostream &print(std::ostream &os, const Person &psn);
// std::istream &read(std::istream &is, Person &psn);

// main ------------------------------------------------------------------------

int main(int argc, char* argv[])
{
    Person adam;
    adam.read(cin);
    adam.print(cout);
    cout << adam.name << ' ' << adam.address << endl;

    // pause
    system("pause");
    return 0;
}

// member functions ------------------------------------------------------------

std::ostream &Person::print(std::ostream &os) const
{
    std::cerr << ">>> Function called: [" << __func__ << "] <<<" << endl;
    os << "Name: " << name << endl
       << "Address: " << address << endl;
    return os;
}

std::istream &Person::read(std::istream &is)
{
    std::cerr << ">>> Function called: [" << __func__ << "] <<<" << endl;
    is >> name >> address;
    return is;
}

// the following functions have been declared as member functions
// std::ostream &print(std::ostream &os, const Person &psn)
// {
//     std::cerr << ">>> Function called: [" << __func__ << "] <<<" << endl;
//     os << "Name: " << psn.name << endl
//        << "Sold: " << psn.address << endl;
//     return os;
// }

// std::istream &read(std::istream &is, Person &psn)
// {
//     std::cerr << ">>> Function called: [" << __func__ << "] <<<" << endl;
//     is >> psn.name >> psn.address;
//     return is;
// }