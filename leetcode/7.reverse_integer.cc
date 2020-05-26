// 7. Reverse Integer
//
// Given a 32-bit signed integer, reverse digits of an integer.
//
// Example 1:
//  Input: 123
//  Output: 321
//
// Example 2:
//  Input: -123
//  Output: -321
//
// Example 3:
//  Input: 120
//  Output: 21
//
// Note:
// Assume we are dealing with an environment which could only store integers
// within the 32-bit signed integer range: [−2**31,  2**31 − 1]. For the purpose
// of this problem, assume that your function returns 0 when the reversed
// integer overflows.

#include <cstdint>
#include <iostream>
#include <limits>
#include <string>
#include "playground.h"

class Solution {
 public:
  unsigned int reverse(unsigned long long x) {
    unsigned long r = 0;
    while (x > 0) {
      r = 10u * r + x % 10;
      x /= 10u;
    }
    return (r <= std::numeric_limits<int>::max()) ? r : 0;
  }

  int reverse(int x) {
    if (x == std::numeric_limits<int>::min())  // Can't get -x: overflow.
      return 0;
    if (x < 0)
      return -static_cast<int>(reverse(static_cast<unsigned long long>(-x)));
    else
      return reverse(static_cast<unsigned long long>(x));
  }
};

int main() {
  std::string line;
  while (std::getline(std::cin, line)) {
    int x = stringToInteger(line);

    int ret = Solution().reverse(x);

    std::string out = std::to_string(ret);
    std::cout << out << std::endl;
  }
  return 0;
}
