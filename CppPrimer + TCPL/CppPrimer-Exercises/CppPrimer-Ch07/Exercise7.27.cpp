// Exercise7.27.cpp
// Ad
// Add the move, set, and display operations to your version of Screen and test.

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
    inline char get(pos r, pos c) const;
    inline Screen &move(pos r, pos c);
    inline Screen &set(char c);
    inline Screen &set(pos r, pos c, char cha);
    inline Screen &display(std::ostream &os);
    inline const Screen &display(std::ostream &os) const;

  private:
    pos cursor{0};
    pos height{0};
    pos width{0};
    std::string contents;

    // private functions
    void doDisplay(std::ostream &os) const { os << contents; }
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

inline Screen &Screen::set(char c)
{
    contents[cursor] = c;
    return *this;
}

inline Screen &Screen::set(pos r, pos c, char cha)
{
    contents[r * width + c] = cha;
    return *this;
}

inline Screen &Screen::display(std::ostream &os)
{
    doDisplay(os);
    return *this;
}

inline const Screen &Screen::display(std::ostream &os) const
{
    doDisplay(os);
    return *this;
}

// main ------------------------------------------------------------------------

int main(int argc, char* argv[])
{
    Screen myScreen(5, 5, 'x');
    myScreen.move(4, 0).set('#').display(cout);
    cout << endl;
    myScreen.display(cout);
    cout << endl;

    // pause
    cin.get();
    return 0;
}