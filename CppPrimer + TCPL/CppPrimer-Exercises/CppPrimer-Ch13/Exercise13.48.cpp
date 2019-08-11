// Exercise13.48.cpp
// Ad147
// init: 18Dec06
// Define a vector<String> and call push_back serval times on that vector.
// Run your program and see how often Strings are copied.

#include <memory>   // std::allocator
#include <iostream> // std::cout / std::endl
#include <vector>   // std::vector

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

// main ========================================================================

int main()
{
    std::vector<String> vs;
    std::cout << "before push_back() 1st" << std::endl;
    vs.push_back("string1");
    std::cout << "after push_back() 1st" << std::endl;
    vs.push_back("I am string 2");
    std::cout << "after push_back() 2nd" << std::endl;

    system("pause");
    return 0;
}
