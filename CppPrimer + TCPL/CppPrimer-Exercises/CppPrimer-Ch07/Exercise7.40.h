// Exercise7.40.h
// Ad
// Choose one of the following abstractions. Determine what data are needed in
// the class. Provide an appropriate set of constructors.

#ifndef EXERCISE_7_40_H
#define EXERCISE_7_40_H

#include <string>

using std::string;

class Book
{
  public:
    // constructor
    Book() = default; // default constructor
    // constructor with title, author and isbn
    Book(string tit, string aut, string isbn)
        : title(tit), edition(1), author(aut), ISBN(isbn) {}
    // constructor with all data
    Book(string tit, unsigned edi, string aut, string pub, unsigned pby,
         string isbn, unsigned pri)
        : title(tit),
          edition(edi),
          author(aut),
          publisher(pub),
          yearPub(pby),
          ISBN(isbn),
          price(pri){}

  private: 
    string title;
    unsigned edition;
    string author;
    string publisher;
    unsigned yearPub;
    string ISBN;
    unsigned price;
};

#endif