// String Compression: Implement a method to perform basic string compression
// using the counts of repeated characters. For example, the string aabcccccaaa
// would become a2blc5a3. If the "compressed" string would not become smaller
// than the original string, your method should return the original string. You
// can assume the string has only uppercase and lowercase letters (a - z).

#include "all.hpp"

void replaceAt(std::string& str, std::string::iterator& at, int num) {
  if (num < 2)
    return;
  std::string count(std::to_string(num));
  str.replace(at, at + count.length(), count);
  at += count.length();
}

// I decided do not compress single characters like b --> b1
bool compress(std::string& str) {
  // check if string could be compressed, i.e. at least triple char exists
  char prevChar = '\0';
  auto charCount = 0;
  for (const char& c : str) {
    if (c != prevChar) {
      prevChar = c;
      charCount = 1;
    } else
      ++charCount;
    if (charCount > 2)
      break;
  }

  if (charCount < 3)
    return false;  // str is not compressible

  auto to = str.begin();
  charCount = 1;
  for (auto from = to + 1; from != str.end(); ++from) {
    if (*from != *to) {
      replaceAt(str, ++to, charCount);
      *to = *from;
      charCount = 1;
    } else
      ++charCount;
  }

  replaceAt(str, ++to, charCount);
  str.erase(to, str.end());
  return true;
}

size_t sizeOfCompressedString(const std::string& str) {
  size_t len = 0;
  int charCount = 0;
  for (auto i = str.begin(); i != str.end(); ++i) {
    ++charCount;
    if (i + 1 == str.end() || *i != *(i + 1)) {
      len += 1;
      if (charCount > 1)
        len += std::to_string(charCount).length();
      charCount = 0;
    }
  }
  return len;
}

std::string compress2(const std::string& str) {
  if (sizeOfCompressedString(str) >= str.length())
    return str;

  std::stringstream stringBuilder;
  int charCount = 0;
  for (auto i = str.begin(); i != str.end(); ++i) {
    ++charCount;
    if (i + 1 == str.end() || *i != *(i + 1)) {
      stringBuilder << *i;
      if (charCount > 1)
        stringBuilder << charCount;
      charCount = 0;
    }
  }

  return stringBuilder.str();
}

void print(bool result, const std::string& str) {
  if (result)
    std::cout << " --> \"" << str << std::endl;
  else
    std::cout << " is not compressible" << std::endl;
}

void print2(const std::string& result, const std::string& str) {
  std::cout << '"' << str << "\" --> \"" << result << '"' << std::endl;
}

int main() {
  std::string str("aabcccccaaa");
  test(compress2, print2, str);
  std::cout << '"' << str << '"';
  test(compress, print, str);

  str = "aabccccccccccaaa";
  test(compress2, print2, str);
  std::cout << '"' << str << '"';
  test(compress, print, str);

  str = "aaag";
  test(compress2, print2, str);
  std::cout << '"' << str << '"';
  test(compress, print, str);

  str = "aabbccdd";
  test(compress2, print2, str);
  std::cout << '"' << str << '"';
  test(compress, print, str);
  return 0;
}
