#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using Segment = std::pair<int, int>;

std::vector<int> get_covering_set(std::vector<Segment> segments) {
  std::vector<int> result;
  std::sort(
      segments.begin(), segments.end(),
      [](const Segment& l, const Segment& r) { return l.second < r.second; });

  int x = -1;
  for (const auto& s : segments) {
    if (s.first <= x)
      continue;
    x = s.second;
    result.push_back(s.second);
  }

  return result;
}

int main(void) {
  int segments_count;
  std::cin >> segments_count;
  std::vector<Segment> segments(segments_count);
  for (auto& s : segments) {
    std::cin >> s.first >> s.second;
  }

  const auto& points = get_covering_set(std::move(segments));
  std::cout << points.size() << std::endl;
  for (const auto point : points) {
    std::cout << point << " ";
  }
  std::cout << std::endl;
}
