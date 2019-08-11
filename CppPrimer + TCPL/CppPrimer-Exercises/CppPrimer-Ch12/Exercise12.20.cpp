// Exercise12.20.cpp
// Ad
// Write a program that reads an input file a line at a time into a StrBlob and uses a StrBlobPtr to print each element in that StrBlob.

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <memory>

// class =======================================================================

class StrBlobPtr;

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

    StrBlobPtr begin();
    StrBlobPtr end();

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
    friend class StrBlobPtr;
};

// -----------------------------------------------------------------------------

class StrBlobPtr
{
  public:
    // constructor
    StrBlobPtr() : curr(0) {}
    StrBlobPtr(StrBlob &a, size_t sz = 0) : wptr(a.data), curr(sz) {}

    // function
    std::string &deref() const;
    StrBlobPtr &incr();

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

StrBlobPtr StrBlob::begin()
{
    return StrBlobPtr(*this);
}

StrBlobPtr StrBlob::end()
{
    auto ret = StrBlobPtr(*this, data->size());
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

std::string &StrBlobPtr::deref() const
{
    auto p = check(curr, "dereference past end");
    return (*p)[curr];
}

StrBlobPtr &StrBlobPtr::incr()
{
    check(curr, "increment past end of StrBlobPtr");
    ++curr;
    return *this;
}

std::shared_ptr<std::vector<std::string>>
StrBlobPtr::check(std::size_t i, const std::string &msg) const
{
    auto ret = wptr.lock();
    if (!ret)
        throw std::runtime_error("unbound StrBlobPtr");
    if (i >= ret->size())
        throw std::out_of_range(msg);

    return ret;
}

// main ========================================================================

int main(int argc, char *argv[])
{
    StrBlob object;

    std::ifstream inputFile("test.file");
    std::string line;
    while (std::getline(inputFile, line))
        object.push_back(line);

    StrBlobPtr p(object, 0);
    for (StrBlob::SizeType i{0}; i != object.size(); ++i)
    {
        std::cout << p.deref() << std::endl;
        p.incr();
    }

    // pause
    system("pause");
    return 0;
}