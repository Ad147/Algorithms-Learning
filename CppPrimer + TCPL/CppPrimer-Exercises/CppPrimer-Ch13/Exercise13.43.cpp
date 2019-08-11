// Exercise13.43.cpp
// Ad147
// init: Dec0518
// Rewrite the free member to use for_each and a lambda in place of the for loop to destroy the elements.

#include <string>
#include <algorithm> // std::for_each

// class =======================================================================

class StrVec
{
  public:
    StrVec() : elements(nullptr), first_free(nullptr), cap(nullptr) {}
    // the allocator member is default initialized
    StrVec(const std::initializer_list<std::string> il)
        : elements(il.begin()), first_free(il.end()), cap(il.end()) {}
    StrVec(const StrVec &);            // copy constructor
    StrVec &operator=(const StrVec &); //copy assignment
    ~StrVec();                         // destructor

    void push_back(const std::string &); // copy the element
    size_t size() const { return first_free - elements; }
    size_t capacity() const { return cap - elements; }
    std::string *begin() const { return elements; }
    std::string *end() const { return first_free; }
    void reserve(size_t n); // allocate space for at least n elements
    void resize(size_t n);  // resize to have n elements. if n < size, the excess elements are discarded

  private:
    std::allocator<std::string> alloc; // allocates the elements
    // used by the functions that add elements to the StrVec
    void chk_n_alloc()
    {
        if (size() == capacity())
            reallocate();
    }
    // ultilities used by the copy constructor, assignment operator, and destructor
    std::pair<std::string *, std::string *>
    alloc_n_copy(const std::string *, const std::string *);
    void free();             // destroy the elements and free the space
    void reallocate();       // get more space and copy the existing elements
    std::string *elements;   // pointer to the first element in the array
    std::string *first_free; // pointer to the first free element in the array
    std::string *cap;        // pointer to one past the end of the array
};

// memeber function ============================================================

void StrVec::free()
{
    if (elements)
    {
        std::for_each(elements, first_free,
                      [this](std::string *p) { alloc.destroy(p); });
        alloc.deallocate(elements, cap - elements);
    }
}
