// 14. Longest Common Prefix
//
// Write a function to find the longest common prefix string amongst an array of
// strings.
// If there is no common prefix, return an empty string "".
//
// Example 1:
//  Input: ["flower","flow","flight"]
//  Output: "fl"
//
// Example 2:
//  Input: ["dog","racecar","car"]
//  Output: ""
//  Explanation: There is no common prefix among the input strings.
//
// Note:
// All given inputs are in lowercase letters a-z.

#include <iostream>
#include <string>
#include <vector>
#include "playground.h"

class Solution {
 public:
  std::string longestCommonPrefix(const std::vector<std::string>& strs) {
    if (strs.empty())
      return ""s;
    size_t l{0};
    for (const char c : strs[0]) {
      for (int i{}; i < strs.size(); ++i) {
        if (strs[i].size() == l || strs[i][l] != c)
          return strs[0].substr(0, l);
      }
      ++l;
    }
    return strs[0].substr(0, l);
  }
};

int main() {
  std::string line;
  while (std::getline(std::cin, line)) {
    std::vector<std::string> strs = stringToStringVector(line);

    std::string out = Solution().longestCommonPrefix(strs);

    std::cout << out << std::endl;
  }
  return 0;
}
