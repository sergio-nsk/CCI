#include <cassert>
#include <iostream>

class Fibonacci {
 public:
  static int get(int n) {
    assert(n >= 0);
    int m[2] = {0, 1};
    for (; n > 1; --n) {
      const int m2 = m[0] + m[1];
      m[0] = m[1];
      m[1] = m2;
    }
    return m[n];
  }
};

int main(void) {
  int n;
  std::cin >> n;
  std::cout << Fibonacci::get(n) << std::endl;
  return 0;
}
