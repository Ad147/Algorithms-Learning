// Exercise13.13.cpp
// Ad
// Add the copy-assignment operator and destructor to X and write a program using X objects in various ways: Pass them as nonreference and reference parameters; dynamically allocate them; put them in containers; and so forth.
// Study the output until you certain understand when and why each copy-control member is used.
// As you read the output, rememeber that the compiler can omit calls to copy constructor.

#include <iostream>
#include <vector>

// class =======================================================================

class X
{
  public:
    X() { std::cout << "default constructor: X()" << std::endl; }
    X(const X &) { std::cout << "copy constructor: X(const X &)" << std::endl; }
    X &operator=(const X &) { std::cout << "assignment operator=: X &operator=(const X &)" << std::endl; }
    ~X() { std::cout << "destructor: ~X()" << std::endl; }
};

X fcn1(X x)
{
    return x;
}

X &fcn2(X &x)
{
    return x;
}

// main ========================================================================

int main(int argc, char *argv[])
{
    std::cout << "begin" << std::endl;
    X x1;
    std::cout << "==================" << std::endl;
    {
        X x2(x1);
        X x3 = x2;
        X x4{x3};
        X x5 = {x4};
        x5 = x1;
    }
    std::cout << "==================" << std::endl;
    {
        X *px1 = new X;
        X *px2 = new X();
        X *px3 = new X(x1);
        delete px1;
        delete px2;
        delete px3;
    }
    std::cout << "==================" << std::endl;
    {
        std::vector<X> xv1{x1};
        std::vector<X> xv2 = {x1};
        xv1.push_back(x1);
    }
    std::cout << "==================" << std::endl;
    fcn1(x1);
    fcn2(x1);
    auto x2 = fcn1(x1);
    auto &x3 = fcn2(x1);
    std::cout << "end" << std::endl;

    // pause
    system("pause");
    return 0;
}