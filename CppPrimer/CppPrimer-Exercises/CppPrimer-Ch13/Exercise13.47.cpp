// Exercise13.47.cpp
// Ad147
// init: 18Dec06
// Give the copy constructor and copy-assignment operator in your String class from exercise 13.44 a statement that prints a message each time the function is executed.

#include <memory>   // std::allocator
#include <iostream> // std::cout / std::endl

// class =======================================================================

class String
{
  public:
    String() : b(nullptr), e(nullptr) {}
    // the allocator member is default initialized
    String(const char *);
    // copy constructor
    String(const String &) { std::cout << "Copy Construcotr Executing" << std::endl; }
    //copy assignment
    String &operator=(const String &) { std::cout << "Copy Assignment Executing" << std::endl; }
    // destructor
    ~String() { std::cout << "Destructor Executing" << std::endl; }

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
