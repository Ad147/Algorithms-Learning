// Exercise7.23.cpp
// Ad
// Write your own version of the Screen class

#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::endl;

// class declaration -----------------------------------------------------------

class Screen
{
  public:
    using pos = std::string::size_type;

  private:
    pos cursor{0};
    pos height{0};
    pos width{0};
    std::string contents;
};

// main ------------------------------------------------------------------------

int main(int argc, char* argv[])
{

    // pause
    cin.get();
    return 0;
}