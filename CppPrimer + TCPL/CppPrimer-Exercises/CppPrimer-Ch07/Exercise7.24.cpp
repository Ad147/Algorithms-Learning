// Exercise7.24.cpp
// Ad
// Give your Screen class three constructors: a default constructor; a 
// constructor that takes values for height and width and initializes the 
// contents to hold the given number of blank; and a constructor that takes 
// values for height, width, and a character to use as the contents of the 
// screen.

#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::endl;

// class declaration -----------------------------------------------------------

class Screen
{
  public:
    // type member
    using pos = std::string::size_type;

    // constructors
    Screen() = default;
    Screen(pos ht, pos wd) : height(ht), width(wd), contents(ht * wd, ' ') { }
    Screen(pos ht, pos wd, char c) : height(ht), width(wd),
                                     contents(ht * wd, c) { }

    // member functions
    char get() const { return contents[cursor]; }
    inline char get(pos ht, pos wd) const;
    inline Screen &move(pos r, pos c);

  private:
    pos cursor{0};
    pos height{0};
    pos width{0};
    std::string contents;
};

// member function definitioins
inline char Screen::get(pos r, pos c) const
{
    pos row = r * width;
    return contents[row + c];
}

inline Screen &Screen::move(pos r, pos c)
{
    pos row = r * width;
    cursor = row + c;
    return *this;
}

// main ------------------------------------------------------------------------

int main(int argc, char* argv[])
{

    // pause
    cin.get();
    return 0;
}