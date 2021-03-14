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
                const Box* bottom,
                unsigned offset,
                std::vector<int>& map);

int createStack(std::deque<Box>& boxes) {
  // Sort in decending order by height.
  std::sort(boxes.begin(), boxes.end(), [](const Box& left, const Box& right) {
    return left.height < right.height;
  });
  std::vector<int> map(boxes.size());
  return createStack(boxes, nullptr, 0, map);
}

int createStack(const std::deque<Box>& boxes,
                const Box* bottom,
                unsigned offset,
                std::vector<int>& map) {
  if (offset >= boxes.size())
    return 0;

  // height with this bottom
  auto newBottom = &boxes.at(offset);
  int heightWithBottom = 0;
  if (!bottom || newBottom->canBeAbove(*bottom)) {
    if (map[offset] == 0) {
      map[offset] = createStack(boxes, newBottom, offset + 1, map);
      map[offset] += newBottom->height;
    }
    heightWithBottom = map[offset];
  }

  // without this bottom
  int heightWithoutBottom = createStack(boxes, bottom, offset + 1, map);
  return std::max(heightWithBottom, heightWithoutBottom);
}
