// 8. String to Integer (atoi)
//
// Implement atoi which converts a string to an integer.
//
// The function first discards as many whitespace characters as necessary until
// the first non-whitespace character is found. Then, starting from this
// character, takes an optional initial plus or minus sign followed by as many
// numerical digits as possible, and interprets them as a numerical value.
//
// The string can contain additional characters after those that form the
// integral number, which are ignored and have no effect on the behavior of this
// function.
//
// If the first sequence of non-whitespace characters in str is not a valid
// integral number, or if no such sequence exists because either str is empty or
// it contains only whitespace characters, no conversion is performed.
//
// If no valid conversion could be performed, a zero value is returned.
//
// Note:
// Only the space character ' ' is considered as whitespace character.
// Assume we are dealing with an environment which could only store integers
// within the 32-bit signed integer range: [−231,  231 − 1]. If the numerical
// value is out of the range of representable values, INT_MAX (231 − 1) or
// INT_MIN (−231) is returned.
//
// Example 1:
//  Input: "42"
//  Output: 42
//
// Example 2:
//  Input: "   -42"
//  Output: -42
//  Explanation: The first non-whitespace character is '-', which is the minus
//  sign. Then take as many numerical digits as possible, which gets 42.
//
// Example 3:
//  Input: "4193 with words"
//  Output: 4193
//  Explanation: Conversion stops at digit '3' as the next character is not a
//  numerical digit.
//
// Example 4:
//  Input: "words and 987"
//  Output: 0
//  Explanation: The first non-whitespace character is 'w', which is not a
//  numerical digit or a +/- sign. Therefore no valid conversion could be
//  performed.

#include <cstdint>
#include <iostream>
#include <string>
#include "playground.h"


class Solution {
 public:
  int myAtoi(std::string& str) {
    long long r = 0;
    int i = 0;
    bool s = false;
    while (i < str.size() && str[i] == ' ')
      ++i;
    s = (str[i] == '-');
    if (s)
      ++i;
    else if (str[i] == '+')
      ++i;
    while (i < str.size() && str[i] >= '0' && str[i] <= '9') {
      r = 10 * r + (str[i++] - '0');
      if (!s) {
        if (r > INT_MAX)
          return INT_MAX;
      } else if (r > -static_cast<long long>(INT_MIN)) {
        return INT_MIN;
      }
    }
    return s ? -r : r;
  }
};

int main() {
  std::string line;
  while (std::getline(std::cin, line)) {
    std::string str = stringToString(line);

    int ret = Solution().myAtoi(str);

    std::string out = std::to_string(ret);
    std::cout << out << std::endl;
  }
  return 0;
}
