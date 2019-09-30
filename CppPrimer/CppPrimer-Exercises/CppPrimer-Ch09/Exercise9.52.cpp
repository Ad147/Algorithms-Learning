// Exercise9.52.cpp
// Ad
// Use a stack to process parenthesized expressions.
// When you see an open parenthesis, note that is was seen.
// When you see a close parenthesis after an open parenthesis, pop elements down to and including the open parenthesis off the stack.
// push a value onto the stack to indicate that a parenthesis expression was replaced.

#include <iostream>
#include <stack>

// -----------------------------------------------------------------------------

int main(int argc, char *argv[])
{
    std::string str{"(a-(b-c))*e"};
    std::stack<char> stk;
    for (const auto c : str)
    {
        stk.push(c);
        if (c == ')')
        {
            std::string result;
            while (stk.top() != '(')
            {
                result += stk.top();
                stk.pop();
            }
            result += stk.top();
            stk.pop();
            std::cout << std::string(result.rbegin(), result.rend()) << " = r" << std::endl;
            stk.push('r');
        }
    }
    std::string result;
    while (!stk.empty())
    {
        result += stk.top();
        stk.pop();
    }
    std::cout << std::string(result.rbegin(), result.rend()) << " = answer" << std::endl;

    // pause
    system("pause");
    return 0;
}