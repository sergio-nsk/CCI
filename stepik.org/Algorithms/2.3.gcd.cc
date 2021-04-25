#include <cassert>
#include <cstdint>
#include <iostream>
#include <utility>

template <class Int>
Int gcd(Int a, Int b) {
  assert(a > 0 && b > 0);
  if (a < b)
    std::swap(a, b);
  do {
    a = a % b;
    std::swap(a, b);
  } while (b > 0);
  return a;
}

int main(void) {
  std::int32_t a, b;
  std::cin >> a >> b;
  std::cout << gcd(a, b) << std::endl;
  return 0;
}
