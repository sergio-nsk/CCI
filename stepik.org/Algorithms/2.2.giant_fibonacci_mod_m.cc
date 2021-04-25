#include <array>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <limits>

class Fibonacci final {
 public:
  static int get_remainder(int64_t n, int m) {
    assert(n >= 1);
    assert(m >= 2);

    const std::array<int, 2> tmpl = {0, 1};
    std::array<int, 2> fib = {0, 1};
    int l = 1;
    for (; l < n; ++l) {
      const unsigned fib2 = fib[0] + fib[1];
      fib[0] = fib[1];
      fib[1] = fib2 % m;
      if (fib == tmpl)
        break;
    }
    if (l == n)
      return fib[1] % m;
    n %= l;
    uint64_t mod[2] = {0, 1};
    for (; n > 1; --n) {
      uint64_t mod2 = mod[0] + mod[1];
      if (mod2 > static_cast<unsigned>(std::numeric_limits<int64_t>::max())) {
        mod2 %= m;
        mod[0] = mod[1] % m;
      } else {
        mod[0] = mod[1];
      }
      mod[1] = mod2;
    }
    return mod[n] % m;
  }
};

int main(void) {
  int64_t n;
  int m;
  std::cin >> n >> m;
  std::cout << Fibonacci::get_remainder(n, m) << std::endl;
  return 0;
}
