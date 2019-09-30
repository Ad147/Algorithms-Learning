// Exercise12.02.cpp
// Ad
// Write your own version of the StrBlob class including the const versions of front and back.

#include <iostream>
#include <vector>
#include <string>
#include <memory>

// class =======================================================================

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

    std::string &front();
    const std::string &front() const;
    std::string &back();
    const std::string &back() const;

  private:
    // data
    std::shared_ptr<std::vector<std::string>> data;

    // function
    void check(SizeType i, const std::string &msg) const;
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

// main ========================================================================

int main(int argc, char *argv[])
{

    // pause
    system("pause");
    return 0;
}