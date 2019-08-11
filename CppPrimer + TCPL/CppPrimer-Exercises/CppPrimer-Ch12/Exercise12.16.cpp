// Exercise12.16.cpp
// Ad
// Compilers dont always give easy-to-understand error messages if we attemp to copy or assign a unique_ptr.
// Write a program that contains these errors to see how your compiler diagnoses them.

#include <iostream>
#include <memory>

// main ========================================================================

int main(int argc, char *argv[])
{
    std::unique_ptr<int> p1(new int(7));
    std::unique_ptr<int> p2(p1);
    std::unique_ptr<int> p3;
    p3 = p2;

    // pause
    system("pause");
    return 0;
}