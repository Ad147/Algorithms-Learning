// Exercise13.44.cpp
// Ad147
// init: Dec0518
// Write a class named String that is a simplyfied version of the library string class.
// Your class should hava at least a default constructor and a constructor that takes a pointer to a C-style string.
// Use an allocator to allocate memory that your String class uses.

#include <string>

// class =======================================================================

class String
{
  public:
    String() : b(nullptr), e(nullptr) {}
    // the allocator member is default initialized
    String(const char *);
    String(const String &);            // copy constructor
    String &operator=(const String &); //copy assignment
    ~String();                         // destructor

    size_t size() const { return e - b; }

  private:
    std::allocator<char> alloc;
    void free();
    char *b;
    char *e;
};

// memeber function ============================================================

String::String(const char *s)
{
    auto p = s;
    size_t sz = {0};
    while (*p++ != '\0')
        ++sz;

    e = b = alloc.allocate(sz);

    p = s;
    for (size_t i = 0; i != sz; ++i)
        alloc.construct(e++, *p++);
}
