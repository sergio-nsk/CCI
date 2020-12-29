// 9. Palindrome Number
//
// Determine whether an integer is a palindrome. An integer is a palindrome when
// it reads the same backward as forward.
//
// Example 1:
//  Input: 121
//  Output: true
//
// Example 2:
//  Input: -121
//  Output: false
//  Explanation: From left to right, it reads -121. From right to left, it
//  becomes 121-. Therefore it is not a palindrome.
//
// Example 3:
//  Input: 10
//  Output: false
//  Explanation: Reads 01 from right to left. Therefore it is not a palindrome.
//
// Follow up:
// Coud you solve it without converting the integer to a string?
//
// Hint 1
// Beware of overflow when you reverse the integer.

#include <iostream>
#include <limits>
#include "playground.h"

class Solution {
 private:
  // Copied from 7. Reverse Integer.
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

 public:
  bool isPalindrome(int x) {
    if (x < 0)
      return false;
    if (x != 0 && x % 10 == 0)
      return false;
    return reverse(x) == x;
  }
};

int main() {
  std::string line;
  while (std::getline(std::cin, line)) {
    int x = stringToInteger(line);

    bool ret = Solution().isPalindrome(x);

    std::string out = boolToString(ret);
    std::cout << out << std::endl;
  }
  return 0;
}
