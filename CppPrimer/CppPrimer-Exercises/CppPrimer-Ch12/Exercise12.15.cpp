// Exercise12.15.cpp
// Ad
// Rewrite the first exercise to use a lambda in place of the end_connection function.

#include <iostream>
#include <memory>

// class =======================================================================

struct Destination;

struct Connection
{
    int i;
};

// function ====================================================================

Connection connect(Destination *);

void disconnect(Connection);

void f(Destination &d)
{
    Connection c = connect(&d);
    std::shared_ptr<Connection> p(&c, [](Connection *p) { disconnect(*p); });
}

// main ========================================================================

int main(int argc, char *argv[])
{

    // pause
    system("pause");
    return 0;
}