// Exercise7.15.cpp
// Ad
// Add appropriate constructors to your Person class.

#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::endl;

// class declaration -----------------------------------------------------------

struct Person
{
    // constructors
    Person() = default;
    Person(const std::string &n, const std::string &a) : name(n), address(a) { }
    Person(std::istream &is) { is >> name >> address; }

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
    Person adam(cin);
    adam.print(cout);
    adam.read(cin);
    cout << adam.getName() << ' ' << adam.getAddress() << endl;

    // pause
    system("pause");
    return 0;
}

// member functions ------------------------------------------------------------

std::ostream &Person::print(std::ostream &os) const
{
    std::cerr << ">>> Calling: [" << __func__ << "] <<<" << endl;
    os << "Name: " << name << endl
       << "Address: " << address << endl;
    return os;
}

std::istream &Person::read(std::istream &is)
{
    std::cerr << ">>> Calling: [" << __func__ << "] <<<" << endl;
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