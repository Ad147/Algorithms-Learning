// Exercise7.42h
// Ad
// For the class you wrote for exercise 7.40, write the delegating constructors.

#ifndef EXERCISE_7_42_H
#define EXERCISE_7_42_H

#include <string>

using std::string;

class Book
{
  public:
    // constructor
    Book() = default; // default constructor
    // constructor with title, author and isbn
    Book(string tit, string aut, string isbn)
        : Book(tit, 1, aut, "\0", 0, "\0", 0) {}
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