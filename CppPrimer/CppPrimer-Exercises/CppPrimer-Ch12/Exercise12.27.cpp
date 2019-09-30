// Exercise12.27.cpp
// Ad
// The TextQuery and QueryResult classes use only capabilities that we have already covered.
// Without looking ahead, write your own versions of these classes.

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <memory>

// classes =====================================================================

class QueryResult;

class TextQuery
{
  public:
    // constructor
    TextQuery(std::ifstream &);

    // member function
    QueryResult query(const std::string &) const;

  private:
    std::shared_ptr<std::vector<std::string>> pv;
    std::map<std::string, std::shared_ptr<std::set<int>>> map;
};

// -----------------------------------------------------------------------------

class QueryResult
{
  public:
    QueryResult(const std::string &s, std::shared_ptr<std::set<int>> l,
                std::shared_ptr<std::vector<std::string>> v)
        : word(s), ps(l), pv(v) {}

  private:
    std::string word;
    std::shared_ptr<std::set<int>> ps;
    std::shared_ptr<std::vector<std::string>> pv;

    friend std::ostream &print(std::ostream &os, const QueryResult &qr);
};

// class members ===============================================================

TextQuery::TextQuery(std::ifstream &infile) : pv(new std::vector<std::string>)
{
    // store the text
    std::string s;
    while (std::getline(infile, s))
        pv->push_back(s);

    // build the map
    for (int i = {0}; i != pv->size(); ++i)
    {
        std::istringstream iss((*pv)[i]);
        while (iss >> s)
        {
            auto &lines = map[s];
            if (!lines)
                lines.reset(new std::set<int>);
            lines->insert(i + 1);
        }
    }
}

QueryResult TextQuery::query(const std::string &s) const
{
    auto ps = map.find(s);
    return QueryResult(s, ps->second, pv);
}

// function ====================================================================

std::ostream &print(std::ostream &os, const QueryResult &qr)
{
    os << qr.word << " occurs " << qr.ps->size() << " time(s)" << std::endl;
    int i = {0};
    for (const auto &n : *qr.ps)
        os << "(line " << n << ") " << (*qr.pv)[i] << std::endl;

    return os;
}

// -----------------------------------------------------------------------------

void runQueries(std::ifstream &infile)
{
    TextQuery tq(infile);
    while (true)
    {
        std::cout << "enter word to look for, or q to quit: ";
        std::string s;
        if (!(std::cin >> s) || s == "q")
            break;
        print(std::cout, tq.query(s)) << std::endl;
    }
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