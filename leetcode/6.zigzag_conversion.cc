// 6. ZigZag Conversion
//
// The string "PAYPALISHIRING" is written in a zigzag pattern on a given number
// of rows like this: (you may want to display this pattern in a fixed font for
// better legibility)
//
// P   A   H   N
// A P L S I I G
// Y   I   R
// And then read line by line: "PAHNAPLSIIGYIR"
//
// Write the code that will take a string and make this conversion given a
// number of rows:
//  string convert(string s, int numRows);
//
// Example 1:
//  Input: s = "PAYPALISHIRING", numRows = 3
//  Output: "PAHNAPLSIIGYIR"
//
// Example 2:
//  Input: s = "PAYPALISHIRING", numRows = 4
//  Output: "PINALSIGYAHRPI"
//  Explanation:
//  P     I    N
//  A   L S  I G
//  Y A   H R
//  P     I

#include <iostream>
#include <string>
#include "playground.h"

class Solution {
 public:
  std::string convert(const std::string& s, int numRows) {
    if (numRows < 2)
      return s;
    std::string r;
    for (int i = 0; i < s.size(); i += 2 * (numRows - 1))
      r += s[i];
    for (int b = 1; b < numRows - 1; ++b) {
      for (int i = 0; i < s.size() + b; i += 2 * (numRows - 1)) {
        if (i - b >= 0)
          r += s[i - b];
        if (i + b < s.size())
          r += s[i + b];
      }
    }
    for (int i = numRows - 1; i < s.size(); i += 2 * (numRows - 1))
      r += s[i];
    return r;
  }
};

int main() {
  std::string line;
  while (std::getline(std::cin, line)) {
    std::string s = stringToString(line);
    std::getline(std::cin, line);
    int numRows = stringToInteger(line);

    std::string ret = Solution().convert(s, numRows);

    std::string out = (ret);
    std::cout << out << std::endl;
  }
  return 0;
}
