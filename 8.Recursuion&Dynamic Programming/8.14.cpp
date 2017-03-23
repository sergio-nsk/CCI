// Boolean Evaluation: Given a boolean expression consisting of the symbols 0 (false), 1 (true), &
// (AND), I (OR), and /\ (XOR), and a desired boolean result value result, implement a function to
// count the number of ways of parenthesizing the expression such that it evaluates to result. The
// expression should be fully parenthesized (e.g., ( 0) A( 1)) but not extraneously (e.g., ( ( ( 0))/\ ( 1))).
// EXAMPLE
// countEval("1^0|0|1", false) -> 2
// countEval("0&0&0&1^1|0", true) -> 10

#include <string>
#include <unordered_map>
#include <cassert>
#include <iostream>

bool toBool(const std::string &x);

int countEval(const std::string &s, bool result, std::unordered_map<std::string, int> &map)
{
    if (s.empty())
        return 0;
    if (s.length() == 1)
        return toBool(s) == result ? 1 : 0;

    std::string key = (result ? "1" : "0") + s;
    if (map.find(key) != map.end())
        return map[key];

    int ways= 0;
    for (size_t i = 1; i < s.length(); i += 2)
    {
        char c = s.at(i);
        auto left = s.substr(0, i);
        auto right = s.substr(i + 1);

        // Evaluate each side for each result.
        int leftTrue = countEval(left, true, map);
        int leftFalse = countEval(left, false, map);
        int rightTrue = countEval(right, true, map);
        int rightFalse = countEval(right, false, map);
        int total= (leftTrue + leftFalse) * (rightTrue + rightFalse);
        int totalTrue = 0;
        switch (c)
        {
        case '^': // required: one true and one false
            totalTrue = leftTrue * rightFalse + leftFalse * rightTrue;
            break;
        case '&': //required: both true
            totalTrue = leftTrue * rightTrue;
            break;
        case '|': // required: anything but both false
            totalTrue = leftTrue * rightTrue + leftFalse * rightTrue + leftTrue * rightFalse;
            break;
        }
        int subWays = result ? totalTrue : total - totalTrue;
        ways += subWays;
    }
    map[key] = ways;
    return ways;
}

bool toBool(const std::string &x)
{
    assert(x == "0" || x == "1");
    return x == "1";
}

int main()
{
    std::unordered_map<std::string, int> map;
    std::cout << countEval("1^0|0|1", false, map) << std::endl;      // 2
    map.clear();
    std::cout << countEval("0&0&0&1^1|0", true, map) << std::endl;   // 10
}
