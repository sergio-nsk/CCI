// Intersect two C++ sets

#include <iostream>
#include <set>

template <typename T>
std::set<T> intersect(const std::set<T>& one, const std::set<T>& two) {
  auto i = one.begin();
  auto j = two.begin();
  std::set<T> r;

  while (i != one.end() && j != two.end()) {
    if (*j == *i) {
      r.insert(*i);
      ++i;
      ++j;
    } else if (*i < *j)
      ++i;
    else
      ++j;
  }

  return r;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::set<T>& cont) {
  os << "{ ";
  for (auto v : cont)
    os << v << ' ';
  os << "}";
  return os;
}

int main() {
  std::set<int> one = {2, 4, 6, 8, 10, 12, 14, 16, 18, 20};
  std::set<int> two = {3, 6, 9, 12, 15, 18, 21};

  auto r = intersect(one, two);
  std::cout << r << std::endl;
}
