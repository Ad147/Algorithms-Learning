// Exercise7.05.cpp
// Ad
// Provide operations in your Person class to return the name and address.

#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::endl;

struct Person
{
    // member functions
    std::string getName() const { return name; }
    std::string getAddress() const { return address; }

    // member variables
    std::string name;
    std::string address;
};

int main(int argc, char* argv[])
{

    // pause
    cin.get();
    return 0;
}