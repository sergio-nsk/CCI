// 13. Roman to Integer
//
// Roman numerals are represented by seven different symbols: I, V, X, L, C, D
// and M.
//  Symbol       Value
//    I             1
//    V             5
//    X            10
//    L            50
//    C           100
//    D           500
//    M          1000
// For example, two is written as II in Roman numeral, just two one's added
// together. Twelve is written as, XII, which is simply X + II. The number
// twenty seven is written as XXVII, which is XX + V + II.
//
// Roman numerals are usually written largest to smallest from left to right.
// However, the numeral for four is not IIII. Instead, the number four is
// written as IV. Because the one is before the five we subtract it making four.
// The same principle applies to the number nine, which is written as IX. There
// are six instances where subtraction is used:
//
// I can be placed before V (5) and X (10) to make 4 and 9.
// X can be placed before L (50) and C (100) to make 40 and 90.
// C can be placed before D (500) and M (1000) to make 400 and 900.
// Given a roman numeral, convert it to an integer. Input is guaranteed to be
// within the range from 1 to 3999.
//
// Example 1:
//  Input: "III"
//  Output: 3
//
// Example 2:
//  Input: "IV"
//  Output: 4
//
// Example 3:
//  Input: "IX"
//  Output: 9
//
// Example 4:
//  Input: "LVIII"
//  Output: 58
//  Explanation: L = 50, V= 5, III = 3.
//
// Example 5:
//  Input: "MCMXCIV"
//  Output: 1994
//  Explanation: M = 1000, CM = 900, XC = 90 and IV = 4.
//
// Hint 1
//  I - 1
//  V - 5
//  X - 10
//  L - 50
//  C - 100
//  D - 500
//  M - 1000
//
// Hint 2
//  Rules:
//  * If I comes before V or X, subtract 1 eg: IV = 4 and IX = 9
//  * If X comes before L or C, subtract 10 eg: XL = 40 and XC = 90
//  * If C comes before D or M, subtract 100 eg: CD = 400 and CM = 900

#include <iostream>
#include <string>

#include "playground.h"

class Solution {
 public:
  int romanToInt(const std::string s) {
    int thousands = 0, hundreds = 0, tens = 0, digits = 0;
    for (const char c : s) {
      switch (c) {
        case 'M':
          thousands += 1000;
          if (hundreds) {
            thousands -= 100;
            hundreds = 0;
          }
          break;

        case 'D':
          hundreds = hundreds ? 400 : 500;
          break;

        case 'C':
          hundreds += 100;
          if (tens) {
            hundreds -= 10;
            tens = 0;
          }
          break;

        case 'L':
          tens = tens ? 40 : 50;
          break;

        case 'X':
          tens += 10;
          if (digits) {
            tens--;
            digits = 0;
          }
          break;

        case 'V':
          digits = digits ? 4 : 5;
          break;

        case 'I':
          digits++;
          break;
      }
    }
    return thousands + hundreds + tens + digits;
  }
};

int main() {
  std::string line;
  while (std::getline(std::cin, line)) {
    std::string s = stringToString(line);

    int ret = Solution().romanToInt(s);

    std::string out = std::to_string(ret);
    std::cout << out << std::endl;
  }
  return 0;
}