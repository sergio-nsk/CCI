#include <cassert>
#include <cmath>
#include <iostream>

#if 0

int main() {
  int n = 0;
  std::cin >> n;
  if (n < 3) {
    std::cout << 1 << "\n" << n << std::endl;
    return 0;
  }

  int k = static_cast<int>((-1.0 + std::sqrt(1.0 + 8.0 * n)) / 2.0 + 0.000001);
  std::cout << k << "\n" << 1;
  int r = n - (1 + k) * k / 2;
  if (r != 0) {
    r += k;
    k--;
  }
  for (int i = 2; i <= k; ++i)
    std::cout << " " << i;
  if (r != 0)
    std::cout << " " << r;
  return 0;
}

#else

int main() {
  long long n;
  std::cin >> n;
  const long long k =
      static_cast<long long>((sqrt(8 * n + 1) - 1) / 2 + 0.000001);
  std::cout << k << std::endl;
  for (int i = 1; i < k; ++i)
    std::cout << i << ' ';
  std::cout << (n - k * (k - 1) / 2);
}

#endif
