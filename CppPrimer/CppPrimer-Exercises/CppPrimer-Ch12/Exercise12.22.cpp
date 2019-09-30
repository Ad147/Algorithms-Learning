// Exercise12.22.cpp
// Ad
// What changes would need to be made to ConstStrBlobPtr to create a class that can be used with a const StrBlob?
// Define a class named ConstStrBlobPtr that can point to a const StrBlob.

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <memory>

// class =======================================================================

class ConstStrBlobPtr;

class StrBlob
{
  public:
    // type
    using SizeType = std::vector<std::string>::size_type;

    // constructor
    StrBlob();
    StrBlob(std::initializer_list<std::string> il);

    // function
    SizeType size() const { return data->size(); }
    bool empty() const { return data->empty(); }

    void push_back(const std::string &s) { data->push_back(s); }
    void pop_back();

    ConstStrBlobPtr begin();
    ConstStrBlobPtr end();

    std::string &front();
    const std::string &front() const;
    std::string &back();
    const std::string &back() const;

  private:
    // data
    std::shared_ptr<std::vector<std::string>> data;

    // function
    void check(SizeType i, const std::string &msg) const;

    // friend
    friend class ConstStrBlobPtr;
};

// -----------------------------------------------------------------------------

class ConstStrBlobPtr
{
  public:
    // constructor
    ConstStrBlobPtr() : curr(0) {}
    ConstStrBlobPtr(StrBlob &a, size_t sz = 0) : wptr(a.data), curr(sz) {}

    // need to add a constructor that takes a const StrBlob
    ConstStrBlobPtr(const StrBlob &a, size_t sz = 0) : wptr(a.data), curr(sz) {}

    // function
    std::string &deref() const;
    ConstStrBlobPtr &incr();

  private:
    // data
    std::weak_ptr<std::vector<std::string>> wptr;
    std::size_t curr;

    // function
    std::shared_ptr<std::vector<std::string>>
    check(std::size_t, const std::string &) const;
};

// member ----------------------------------------------------------------------

StrBlob::StrBlob() : data(std::make_shared<std::vector<std::string>>()) {}

StrBlob::StrBlob(std::initializer_list<std::string> il)
    : data(std::make_shared<std::vector<std::string>>(il)) {}

void StrBlob::pop_back()
{
    check(0, "pop_back on empty StrBlob");
    data->pop_back();
}

ConstStrBlobPtr StrBlob::begin()
{
    return ConstStrBlobPtr(*this);
}

ConstStrBlobPtr StrBlob::end()
{
    auto ret = ConstStrBlobPtr(*this, data->size());
    return ret;
}

std::string &StrBlob::front()
{
    check(0, "front on empty StrBlob");
    return data->front();
}

const std::string &StrBlob::front() const
{
    check(0, "front on empty StrBlob");
    return data->front();
}

std::string &StrBlob::back()
{
    check(0, "back on empty StrBlob");
    return data->back();
}

const std::string &StrBlob::back() const
{
    check(0, "back on empty StrBlob");
    return data->back();
}

void StrBlob::check(SizeType i, const std::string &msg) const
{
    if (i >= data->size())
        throw std::out_of_range(msg);
}

// -----------------------------------------------------------------------------

std::string &ConstStrBlobPtr::deref() const
{
    auto p = check(curr, "dereference past end");
    return (*p)[curr];
}

ConstStrBlobPtr &ConstStrBlobPtr::incr()
{
    check(curr, "increment past end of ConstStrBlobPtr");
    ++curr;
    return *this;
}

std::shared_ptr<std::vector<std::string>>
ConstStrBlobPtr::check(std::size_t i, const std::string &msg) const
{
    auto ret = wptr.lock();
    if (!ret)
        throw std::runtime_error("unbound ConstStrBlobPtr");
    if (i >= ret->size())
        throw std::out_of_range(msg);

    return ret;
}

// main ========================================================================

int main(int argc, char *argv[])
{
    const StrBlob object;

    ConstStrBlobPtr p(object, 0);

    // pause
    system("pause");
    return 0;
}