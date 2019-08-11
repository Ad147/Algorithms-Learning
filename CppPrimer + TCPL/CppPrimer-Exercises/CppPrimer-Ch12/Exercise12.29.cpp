// Exercise12.29.cpp
// Ad
// Rewrite the loop to use a do while.
// Explain which version you prefer and why.

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <memory>

// function ====================================================================

void runQueries(std::ifstream &infile)
{
    TextQuery tq(infile);
    do
    {
        std::cout << "enter word to look for, or q to quit: ";
        std::string s;
        if (!(std::cin >> s) || s == "q")
            break;
        print(std::cout, tq.query(s)) << std::endl;
    } while (true);
    // actually no differences I can find
}

// main ========================================================================

int main(int argc, char *argv[])
{
    std::ifstream infile("testfile1227");
    runQueries(infile);

    // pause
    system("pause");
    return 0;
}