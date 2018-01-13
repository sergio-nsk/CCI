// Compress long string.
// Example:  "AAAAAAAAAAAAAAABBCD" -> "A15B2CD"

#include <iostream>
#include <string>

std::string::iterator Replace(std::string& str,
                              std::string::iterator from,
                              const std::string& substr) {
  str.replace(from, from + substr.length(), substr);
  return from + substr.length();
}

std::string& Compress(std::string& str) {
  if (str.size() <= 1)
    return str;

  auto dst = str.begin();
  auto src = dst + 1;
  auto c = *dst;
  std::size_t cnt = 1;

  while (src != str.end()) {
    if (*src == c) {
      ++src;
      ++cnt;
    } else {
      *dst++ = c;
      if (cnt > 1)
        dst = Replace(str, dst, std::to_string(cnt));
      c = *src++;
      cnt = 1;
    }
  }
  *dst++ = c;
  if (cnt > 1)
    dst = Replace(str, dst, std::to_string(cnt));
  str.erase(dst, str.end());
  return str;
}

int main() {
  std::string str = "AAAAAAAAAAAAAAABBCD";
  std::cout << Compress(str) << std::endl;
}
