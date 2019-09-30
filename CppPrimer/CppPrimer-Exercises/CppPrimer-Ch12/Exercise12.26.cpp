// Exercise12.26.cpp
// Ad
// Rewrite the program on page 481 using an allocator.

#include <iostream>
#include <string>

// main ========================================================================

int main(int argc, char *argv[])
{
    std::allocator<std::string> salloc;
    int n = {10};
    auto const p = salloc.allocate(n);
    std::string s;
    auto q = p;
    while (std::cin >> s && q != p + n)
        salloc.construct(q++, s);
    const size_t size = q - p;
    // use the array
    std::cout << *p << std::endl;

    while (q != p)
        salloc.destroy(--q);
    salloc.deallocate(p, n);

    // pause
    system("pause");
    return 0;
}