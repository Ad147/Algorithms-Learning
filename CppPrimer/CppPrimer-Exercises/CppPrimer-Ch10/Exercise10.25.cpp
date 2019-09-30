// Exercise10.25.cpp
// Ad
// In the exercises for 10.3.2 you wrote a version of biggies that uses partition.
// Rewrite that function to use check_size and bind.

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>

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

bool check_size(const std::string &s, size_t n)
{
    return s.size() >= n;
}

void biggies(std::vector<std::string> &words, size_t sz)
{
    elimDups(words);
    sort(words.begin(), words.end(), isShorter);

    auto end{partition(words.begin(), words.end(),
                       bind(check_size, std::placeholders::_1, sz))};

    auto cnt{end - words.begin()};
    std::cout << cnt << ' ' << "word(s) of length " << sz << " or longer"
              << std::endl;

    for_each(words.begin(), end,
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