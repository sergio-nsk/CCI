// https://www.careercup.com/question?id=5727834596179968
// Google
// Find whether string S is periodic.
// Periodic indicates S = nP.
// e.g.
// S = "ababab", then n = 3, and P = "ab"
// S = "xxxxxx", then n = 1, and P = "x"
// S = "aabbaaabba", then n = 2, and P = "aabba"
// follow up:
// Given string S, find out the P (repetitive pattern) of S.

#include <iostream>
#include <string>

bool isPeriodic(const std::string& str) {
  std::string test = str.substr(1) + str.substr(0, str.length() / 2);
  return test.find(str) != test.npos;
}

auto findPeriod1(const std::string& str) {
  auto len = 0;
  std::string test = str.substr(1) + str.substr(0, str.length() / 2);
  for (; test.find(str) != test.npos; ++len) {
    test.erase(test.length() - 1);
  }
  if (!len)
    return std::string();
  return str.substr(0, 1 + str.length() / 2 - len);
}

auto findPeriod2(const std::string& str) {
  auto len = 1;
  std::string test = str.substr(1) + str[0];
  for (;  len <= str.length() / 2 && test.find(str) == test.npos; ++len) {
    test += str[len];
  }
  if (len > str.length() / 2)
    return std::string();
  return str.substr(0, len);
}

int main() {
  std::cout << std::boolalpha;
  auto s = std::string("ababab");
  std::cout << s << " " << isPeriodic(s) << " (" << findPeriod1(s) << ") ("
            << findPeriod2(s) << ")" << std::endl;
  s = "xxxxxx";
  std::cout << s << " " << isPeriodic(s) << " (" << findPeriod1(s) << ") ("
            << findPeriod2(s) << ")" << std::endl;
  s = "aabbaaabba";
  std::cout << s << " " << isPeriodic(s) << " (" << findPeriod1(s) << ") ("
            << findPeriod2(s) << ")" << std::endl;
  s = "abc";
  std::cout << s << " " << isPeriodic(s) << " (" << findPeriod1(s) << ") ("
            << findPeriod2(s) << ")" << std::endl;
  s = "aa";
  std::cout << s << " " << isPeriodic(s) << " (" << findPeriod1(s) << ") ("
            << findPeriod2(s) << ")" << std::endl;
  s = "a";
  std::cout << s << " " << isPeriodic(s) << " (" << findPeriod1(s) << ") ("
            << findPeriod2(s) << ")" << std::endl;
}
