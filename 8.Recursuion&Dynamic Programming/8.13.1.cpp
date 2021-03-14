// Stack of Boxes: You have a stack of n boxes, with widths w1 , heights h i,
// and depths d i . The boxes cannot be rotated and can only be stacked on top
// of one another if each box in the stack is strictly larger than the box above
// it in width, height, and depth. Implement a method to compute the height of
// the tallest possible stack. The height of a stack is the sum of the heights
// of each box.

#include <algorithm>
#include <cmath>
#include <deque>
#include <vector>

#include "8.13.hpp"

int createStack(const std::deque<Box>& boxes,
                unsigned bottomIndex,
                std::vector<int>& map);

int createStack(std::deque<Box>& boxes) {
  // Sort in decending order by height.
  std::sort(boxes.begin(), boxes.end(), [](const Box& left, const Box& right) {
    return left.height < right.height;
  });
  std::vector<int> map(boxes.size());
  int maxHeight = 0;
  for (auto i = 0U; i < boxes.size(); ++i) {
    int height = createStack(boxes, i, map);
    maxHeight = std::max(maxHeight, height);
  }
  return maxHeight;
}

int createStack(const std::deque<Box>& boxes,
                unsigned bottomIndex,
                std::vector<int>& map) {
  if (bottomIndex < boxes.size() && map[bottomIndex] > 0)
    return map[bottomIndex];

  auto& bottom = boxes.at(bottomIndex);
  int maxHeight = 0;
  for (auto i = bottomIndex + 1; i < boxes.size(); ++i) {
    if (boxes.at(i).canBeAbove(bottom)) {
      int height = createStack(boxes, i, map);
      maxHeight = std::max(height, maxHeight);
    }
  }
  maxHeight += bottom.height;
  map[bottomIndex] = maxHeight;
  return maxHeight;
}
