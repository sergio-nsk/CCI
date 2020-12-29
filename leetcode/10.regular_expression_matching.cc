// 10. Regular Expression Matching
// Given an input string (s) and a pattern (p), implement regular expression
// matching with support for '.' and '*'.
//  '.' Matches any single character.
//  '*' Matches zero or more of the preceding element.
// The matching should cover the entire input string (not partial).
//
// Note:
//  s could be empty and contains only lowercase letters a-z.
//  p could be empty and contains only lowercase letters a-z, and characters
//    like . or *.
//
// Example 1:
//  Input:
//   s = "aa"
//   p = "a"
//  Output: false
// Explanation: "a" does not match the entire string "aa".
//
// Example 2:
//  Input:
//   s = "aa"
//   p = "a*"
//  Output: true
// Explanation: '*' means zero or more of the preceding element, 'a'. Therefore,
// by repeating 'a' once, it becomes "aa".
//
// Example 3:
//  Input:
//   s = "ab"
//   p = ".*"
//  Output: true
// Explanation: ".*" means "zero or more (*) of any character (.)".
//
// Example 4:
//  Input:
//   s = "aab"
//   p = "c*a*b"
//  Output: true
// Explanation: c can be repeated 0 times, a can be repeated 1 time. Therefore,
// it matches "aab".
//
// Example 5:
//  Input:
//   s = "mississippi"
//   p = "mis*is*p*."
//  Output: false

#include <deque>
#include <iostream>

#include "playground.h"

class CharPattern {
 public:
  CharPattern(char ch) : pattern(ch) {}
  bool IsMatch(char ch) const {
    if (pattern == '.')
      return true;
    std::cout << ch << '-' << pattern << '\n';
    return ch == pattern;
  }
  char pattern{};
  bool is_mult{};
};

class Solution {
 public:
  bool isMatch(std::string s, std::string p) {
    if (!InitRegex(p))
      return false;
    return isMatch(s.begin(), s.end(), regex_.begin());
  }

 private:
  bool InitRegex(const std::string& p) {
    for (const char ch : p) {
      if (ch == '*') {
        if (regex_.empty())
          return false;
        if (regex_.back().is_mult)
          return false;
        if (regex_.size() > 1 && (regex_.end() - 2)->is_mult &&
            regex_.back().pattern == (regex_.end() - 2)->pattern)
          regex_.pop_back();
        regex_.back().is_mult = true;
      } else {
        regex_.emplace_back(ch);
      }
    }
    return true;
  }

  bool isMatch(std::string::const_iterator b,
               std::string::const_iterator e,
               std::deque<CharPattern>::const_iterator p) const {
    if (b == e) {
      while (p != regex_.end() && p->is_mult)
        ++p;
      return p == regex_.end();
    }
    if (p == regex_.end())
      return false;
    if (p->IsMatch(*b)) {
      if (p->is_mult) {
        if (isMatch(b + 1, e, p))
          return true;
      }
      if (isMatch(b + 1, e, p + 1))
        return true;
    }
    if (p->is_mult) {
      if (isMatch(b, e, p + 1))
        return true;
    }
    return false;
  }

  std::deque<CharPattern> regex_;
};

int main() {
  std::string line;
  while (std::getline(std::cin, line)) {
    std::string s = stringToString(line);
    std::getline(std::cin, line);
    std::string p = stringToString(line);

    bool ret = Solution().isMatch(s, p);

    std::string out = boolToString(ret);
    std::cout << out << std::endl;
  }
  return 0;
}
