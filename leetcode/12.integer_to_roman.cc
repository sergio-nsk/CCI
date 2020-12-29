// 12. Integer to Roman
// Roman numerals are represented by seven different symbols: I, V, X, L, C, D
// and M.
//   Symbol        Value
//     I             1
//     V             5
//     X             10
//     L             50
//     C             100
//     D             500
//     M             1000
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
// Given an integer, convert it to a roman numeral. Input is guaranteed to be
// within the range from 1 to 3999.
//
// Example 1:
//  Input: 3
//  Output: "III"
//
// Example 2:
//  Input: 4
//  Output: "IV"
//
// Example 3:
//  Input: 9
//  Output: "IX"
//
// Example 4:
//  Input: 58
//  Output: "LVIII"
//  Explanation: L = 50, V = 5, III = 3.
//
// Example 5:
//  Input: 1994
//  Output: "MCMXCIV"
//  Explanation: M = 1000, CM = 900, XC = 90 and IV = 4.

#include <iostream>
#include <string>

#include "playground.h"

class Solution {
 public:
  std::string intToRoman(int num) {
    if (num < 1000)
      return int999ToRoman(num);
    std::string r = kThousands[num / 1000];
    return (num % 1000) ? r + int999ToRoman(num % 1000) : r;
  }

 private:
  std::string int9ToRoman(int num) {
    return kDigits[num];
  }

  std::string int99ToRoman(int num) {
    if (num < 10)
      return int9ToRoman(num);
    std::string r = kTens[num / 10];
    return (num % 10) ? r + int9ToRoman(num % 10) : r;
  }

  std::string int999ToRoman(int num) {
    if (num < 100)
      return int99ToRoman(num);
    std::string r = kHundreds[num / 100];
    return (num % 100) ? r + int99ToRoman(num % 100) : r;
  }

  constexpr static char* kDigits[10] =
    {".", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"};
  constexpr static char* kTens[10] =
    {".", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"};
  constexpr static char* kHundreds[10] =
    {".", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"};
  constexpr static char* kThousands[10] =
    {".", "M", "MM", "MMM"};
};

int main() {
  std::string line;
  while (std::getline(std::cin, line)) {
    int num = stringToInteger(line);

    std::string ret = Solution().intToRoman(num);

    std::string out = (ret);
    std::cout << out << std::endl;
  }
  return 0;
}
