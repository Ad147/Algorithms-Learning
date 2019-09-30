//  Exercise2.5.cpp
//  Ad
//  Explain the differences among the literals in each of the four examples.

#include <iostream>
#include <typeinfo>

int main()
{
    std::cout << "Literal\t" << "type\t" << "size" << std::endl;
    std::cout << 'a' << '\t' << typeid('a').name() << '\t' << sizeof('a') << std::endl;
    std::cout << L'a' << '\t' << typeid(L'a').name() << '\t' << sizeof(L'a') << std::endl;
    std::cout << "a" << '\t' << typeid("a").name() << '\t' << sizeof("a") << std::endl;
    std::cout << L"a" << '\t' << typeid(L"a").name() << '\t' << sizeof(L"a") << std::endl;
    std::cout << 10 << '\t' << typeid(10).name() << '\t' << sizeof(10) << std::endl;
    std::cout << 10u << '\t' << typeid(10u).name() << '\t' << sizeof(10u) << std::endl;
    std::cout << 10L << '\t' << typeid(10L).name() << '\t' << sizeof(10L) << std::endl;
    std::cout << 10uL << '\t' << typeid(10uL).name() << '\t' << sizeof(10uL) << std::endl;
    std::cout << 012 << '\t' << typeid(012).name() << '\t' << sizeof(012) << std::endl;
    std::cout << 0xC << '\t' << typeid(0xC).name() << '\t' << sizeof(0xC) << std::endl;
    std::cout << 3.14 << '\t' << typeid(3.14).name() << '\t' << sizeof(3.14) << std::endl;
    std::cout << 3.14f << '\t' << typeid(3.14f).name() << '\t' << sizeof(3.14f) << std::endl;
    std::cout << 3.14L << '\t' << typeid(3.14L).name() << '\t' << sizeof(3.14L) << std::endl;
    std::cout << 10 << '\t' << typeid(10).name() << '\t' << sizeof(10) << std::endl;
    std::cout << 10u << '\t' << typeid(10u).name() << '\t' << sizeof(10u) << std::endl;
    std::cout << 10. << '\t' << typeid(10.).name() << '\t' << sizeof(10.) << std::endl;
    std::cout << 10e-2 << '\t' << typeid(10e-2).name() << '\t' << sizeof(10e-2) << std::endl;

    //  Pause
    std::cin.get();
    return 0;
}