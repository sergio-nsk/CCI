// https://www.careercup.com/question?id=5840146736873472
// Write a function that given a string would print the 'expanded' version of it.
// For example a2[bc2[c]]d would print out abcccbcccd
// Note:
// The number before the opening and closing square brackets is the multiplier for the characters within the square brackets
// public String expanded(String str)

#include <string>
#include <locale>
#include <iostream>

std::locale loc("C");

std::string::const_iterator expanded(const std::string &str, std::string::const_iterator start, std::string &out) {
  while (start != str.end()) {
    if (std::isalpha(*start, loc))
      out.push_back(*start++);
    else if (std::isdigit(*start)) {
      char *end = nullptr;
      auto cnt = std::strtol(&*start, &end, 10);
      if (cnt == 0 || *end != '[')
        return str.end();
      start += end - &*start + 1;
      std::string::const_iterator ret;
      for (; cnt > 0; --cnt)
        ret = expanded(str, start, out);
      start = ret;
    }
    else if (*start == ']')
      return start + 1;
  }
  return start;
}

std::string expanded(const std::string &str)
{
  std::string res;
  expanded(str, str.begin(), res);
  return res;
}

int main() {
  auto r = expanded("a2[bc2[c]]d");
  auto expected = "abcccbcccd";
  std::cout << "\"" << r << "\" == \"" << expected << "\" is " << std::boolalpha << (r == expected) << std::endl;
}
