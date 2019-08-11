// Exercise12.30.cpp
// Ad
// Define your own versions of the TextQuery and QueryResult classes and execute the runQueries function from page 486.

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
    std::shared_ptr<std::vector<std::string>> pText;
    std::map<std::string, std::shared_ptr<std::set<size_t>>> wordMap;
};

// -----------------------------------------------------------------------------

class QueryResult
{
  public:
    // constructor
    QueryResult(std::string s, std::shared_ptr<std::set<size_t>> ps,
                std::shared_ptr<std::vector<std::string>> pv)
        : word(s), pSet(ps), pText(pv) {}

  private:
    std::string word;
    std::shared_ptr<std::set<size_t>> pSet;
    std::shared_ptr<std::vector<std::string>> pText;

    friend std::ostream &print(std::ostream &, const QueryResult &);
};

// members =====================================================================

TextQuery::TextQuery(std::ifstream &ifs) : pText(new std::vector<std::string>)
{
    std::string s;
    while (std::getline(ifs, s))
    {
        pText->push_back(s);
        std::istringstream line(s);
        std::string w;
        while (line >> w)
        {
            auto &lines = wordMap[w];
            if (!lines)
                lines.reset(new std::set<size_t>);
            lines->insert(pText->size() - 1);
        }
    }
}

QueryResult TextQuery::query(const std::string &s) const
{
    static std::shared_ptr<std::set<size_t>> nodata(new std::set<size_t>);
    auto loc = wordMap.find(s);
    if (loc == wordMap.end())
        return QueryResult(s, nodata, pText);
    else
        return QueryResult(s, loc->second, pText);
}

// functions ===================================================================

std::ostream &print(std::ostream &os, const QueryResult &qr)
{
    os << qr.word << " occurs " << qr.pSet->size() << " time(s)" << std::endl;
    for (auto n : *qr.pSet)
        os << "\t(line " << n + 1 << ") " << *(qr.pText->begin() + n) << std::endl;
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