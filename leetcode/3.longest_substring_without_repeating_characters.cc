// 3. Longest Substring Without Repeating Characters
//
// Given a string, find the length of the longest substring without repeating
// characters.
//
// Example 1:
//  Input: "abcabcbb"
//  Output: 3
//  Explanation: The answer is "abc", with the length of 3.
//
// Example 2:
//  Input: "bbbbb"
//  Output: 1
//  Explanation: The answer is "b", with the length of 1.
//
// Example 3:
//  Input: "pwwkew"
//  Output: 3
//  Explanation: The answer is "wke", with the length of 3. Note that the answer
//  must be a substring, "pwke" is a subsequence and not a substring.

#include <array>
#include <iostream>
#include <string>
#include "playground.h"

class Solution {
 public:
  int lengthOfLongestSubstring(const std::string& s) {
    if (s.empty())
      return 0;
    std::array<int, 128> chars;
    chars.fill(-1);
    int len = 0, b = 0, e = 0;
    for (e = 0; e < s.length(); ++e) {
      if (chars[s[e]] != -1) {
        // Char met before.
        b = std::max(b, chars[s[e]]);
      }
      len = std::max(len, e - b + 1);
      chars[s[e]] = e + 1;
    }
    return len;
  }
};

int main() {
  std::string line;
  while (std::getline(std::cin, line)) {
    std::string s = stringToString(line);

    int ret = Solution().lengthOfLongestSubstring(s);

    std::string out = std::to_string(ret);
    std::cout << out << std::endl;
  }
  return 0;
}
