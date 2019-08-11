// Exercise9.51.cpp
// Ad
// Write a class that has three unsigned members representing year, month and day.
// Write a constructor that takes a string representing a date.
// Your constructor should handle a variety of data formats, such as January 1, 1900, 1/1/1900, Jan 1, 1900 and so on.

#include <iostream>
#include <string>

// class -----------------------------------------------------------------------

class Date
{
  public:
    Date() = default;
    Date(const std::string &s);

  private:
    unsigned year;
    unsigned month;
    unsigned day;
};

Date::Date(const std::string &s)
{
    std::string m{"JFMAMSOND"};
    std::string nums{"0123456789"};
    size_t i{0};
    if (s.find_first_of(m) != std::string::npos)
    {
        if (s.substr(0, 3) == "Jan")
            month = 1;
        i = s.find_first_of(nums, i);
        day = stoul(s.substr(i));
        i = s.find_first_not_of(nums, i);
        year = stoul(s.substr(++i));
    }
    else
    {
        i = s.find_first_of(nums, i);
        month = stoul(s.substr(i));
        i = s.find_first_not_of(nums, i);
        day = stoul(s.substr(++i));
        i = s.find_first_not_of(nums, i);
        year = stoul(s.substr(++i));
    }
    std::cout << "date(y.m.d): " << year << '.'
              << month << '.' << day << std::endl;
}

// test ------------------------------------------------------------------------

int main(int argc, char *argv[])
{
    Date date0{"12/31/2000"};
    Date date1{"January 1, 2001"};

    // pause
    system("pause");
    return 0;
}