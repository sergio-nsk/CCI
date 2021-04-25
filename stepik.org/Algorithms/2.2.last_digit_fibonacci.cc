#include <cassert>
#include <iostream>
#include <limits>

class Fibonacci final {
 public:
  static int get_last_digit(int n) {
    assert(n >= 1);

    unsigned m[2] = {0, 1};
    for (; n > 1; --n) {
      unsigned m2 = m[0] + m[1];
      if (m2 > static_cast<unsigned>(std::numeric_limits<int>::max())) {
        m2 %= 10;
        m[0] = m[1] % 10;
      } else {
        m[0] = m[1];
      }
      m[1] = m2;
    }
    return m[n] % 10;
  }
};

int main(void) {
  int n;
  std::cin >> n;
  std::cout << Fibonacci::get_last_digit(n) << std::endl;
  return 0;
}
