// Exercise7.22.cpp
// Ad
// Update your Person class to hdie its implementation.

#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::endl;

// class declaration -----------------------------------------------------------

class Person
{
  public:
    // constructors
    Person() = default;
    Person(const std::string &n, const std::string &a) : name(n), address(a) { }
    Person(std::istream &is) { is >> name >> address; }

    // member functions
    std::string getName() const { return name; }
    std::string getAddress() const { return address; }
    std::ostream &print(std::ostream &os) const;
    std::istream &read(std::istream &is);

  private:
    // member variables
    std::string name;
    std::string address;
};

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