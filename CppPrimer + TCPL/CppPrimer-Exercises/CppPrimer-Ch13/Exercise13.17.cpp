// Exercise13.17.cpp
// Ad
// Write versions of numbered and f1 corresponding to the previous three exercises and check whether you correctly predicted the output.

#include <iostream>

// class =======================================================================

class Numbered1
{
  public:
    Numbered1() = default;
    Numbered1(const Numbered1 &) = default;
    Numbered1 &operator=(const Numbered1 &) = default;
    ~Numbered1() = default;

    // data
    int mysn;
};

class Numbered2
{
  public:
    Numbered2() : mysn(0) {}
    Numbered2(const Numbered2 &n) : mysn(n.mysn + 1){};
    Numbered2 &operator=(const Numbered2 &) = default;
    ~Numbered2() = default;

    // data
    int mysn;
};

// function ====================================================================

void f1(Numbered1 s) { std::cout << s.mysn << std::endl; }

void f1(Numbered2 s) { std::cout << s.mysn << std::endl; }

void f2(const Numbered2 &s) { std::cout << s.mysn << std::endl; }

// main ========================================================================

int main(int argc, char *argv[])
{
    Numbered1 a, b = a, c = b;
    f1(a);
    f1(b);
    f1(c);

    Numbered2 d, e = d, f = e;
    f1(d);
    f1(e);
    f1(f);

    f2(d);
    f2(e);
    f2(f);

    // pause
    system("pause");
    return 0;
}