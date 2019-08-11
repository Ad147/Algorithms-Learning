// Exercise12.14.cpp
// Ad
// Write your own version of a function that uses a shared_ptr to manage a connection.

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

void endConnection(Connection *p)
{
    disconnect(*p);
}

void f(Destination &d)
{
    Connection c = connect(&d);
    std::shared_ptr<Connection> p(&c, endConnection);
}

// main ========================================================================

int main(int argc, char *argv[])
{

    // pause
    system("pause");
    return 0;
}