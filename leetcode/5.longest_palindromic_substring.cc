// 5. Longest Palindromic Substring
// Given a string s, find the longest palindromic substring in s. You may assume
// that the maximum length of s is 1000.
//
// Example 1:
//  Input: "babad"
//  Output: "bab"
//  Note: "aba" is also a valid answer.
//
// Example 2:
// Input: "cbbd"
// Output: "bb"
//
// Hint 1
// How can we reuse a previously computed palindrome to compute a larger
// palindrome?
//
// Hint 2
// If “aba” is a palindrome, is “xabax” and palindrome? Similarly is “xabay” a
// palindrome?
//
// Hint 3
// Complexity based hint:
// If we use brute-force and check whether for every start and end position a
// substring is a palindrome we have O(n^2) start - end pairs and O(n)
// palindromic checks. Can we reduce the time for palindromic checks to O(1) by
// reusing some previous computation.

#include <iostream>
#include <string>
#include "playground.h"

class Solution {
 public:
  std::string longestPalindrome(const std::string& s) {
    if (s.length() <= 1)
      return s.substr(0);
    int pb = 0, pl = 1;
    for (int b = 0; b < s.length() - 1; ++b) {
      // Odd lengths.
      for (int i = 1; i <= b; i++) {
        if (s[b - i] == s[b + i]) {
          if (2 * i + 1 > pl) {
            pb = b - i;
            pl = 2 * i + 1;
          }
        } else {
          break;
        }
      }
      // Even lengths.
      for (int i = 0; i <= b; i++) {
        if (s[b - i] == s[b + i + 1]) {
          if (2 * (i + 1) > pl) {
            pb = b - i;
            pl = 2 * (i + 1);
          }
        } else {
          break;
        }
      }
    }
    return s.substr(pb, pl);
  }
};

int main() {
  std::string line;
  while (std::getline(std::cin, line)) {
    std::string s = stringToString(line);

    std::string ret = Solution().longestPalindrome(s);

    std::string out = (ret);
    std::cout << out << std::endl;
  }
  return 0;
}
