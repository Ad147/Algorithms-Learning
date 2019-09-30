// Exercise10.16.cpp
// Ad
// Write your own version of the biggies function using lambda.

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

// function --------------------------------------------------------------------

void elimDups(std::vector<std::string> &svec)
{
    sort(svec.begin(), svec.end());

    auto era{unique(svec.begin(), svec.end())};
    svec.erase(era, svec.end());
}

bool isShorter(const std::string &s1, const std::string &s2)
{
    return s1.size() < s2.size();
}

void biggies(std::vector<std::string> &words, size_t sz)
{
    elimDups(words);
    stable_sort(words.begin(), words.end(), isShorter);

    auto wc = find_if(words.begin(), words.end(),
                      [sz](const std::string &s) { return s.size() >= sz; });

    auto cnt{words.end() - wc};
    std::cout << cnt << ' ' << "word(s) of length " << sz << " or longer"
              << std::endl;

    for_each(wc, words.end(),
             [](const std::string &s) { std::cout << s << ' '; });
    std::cout << std::endl;
}

// test ------------------------------------------------------------------------

int main(int argc, char *argv[])
{
    std::vector<std::string> words{"the", "quick", "red", "fox", "jumps",
                                   "over", "the", "slow", "red", "turtle"};
    biggies(words, 5);

    // pause
    system("pause");
    return 0;
}