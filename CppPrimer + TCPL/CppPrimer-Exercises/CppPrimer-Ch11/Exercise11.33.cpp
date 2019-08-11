// Exercise11.33.cpp
// Ad
// Implement your own version of the word-transformation program.

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>

// function --------------------------------------------------------------------

std::map<std::string, std::string> buildMap(std::ifstream &finput)
{
    std::map<std::string, std::string> ret;

    std::string key, value;
    while (finput >> key >> value)
        ret.insert({key, value});

    return ret;
}

const std::string &transform(std::string &str,
                             std::map<std::string, std::string> &rule)
{
    if (rule.find(str) == rule.end())
        return str;
    else
        return rule[str];
}

void transformWord(std::ifstream &rulefile, std::ifstream &textfile)
{
    auto ruleMap = buildMap(rulefile);

    std::string line;
    while (std::getline(textfile, line))
    {
        std::istringstream sstm(line);
        std::string word;
        sstm >> word;
        std::cout << transform(word, ruleMap);
        while (sstm >> word)
            std::cout << ' ' << transform(word, ruleMap);
        std::cout << std::endl;
    }
}

// main ------------------------------------------------------------------------

int main(int argc, char *argv[])
{
    std::ifstream inputRule("rule.file");
    std::ifstream inputText("text.file");

    transformWord(inputRule, inputText);

    // pause
    system("pause");
    return 0;
}
