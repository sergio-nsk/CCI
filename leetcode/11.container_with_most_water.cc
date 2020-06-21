// 11. Container With Most Water
// Given n non-negative integers a1, a2, ..., an, where each represents a point
// at coordinate (i, ai). n vertical lines are drawn such that the two endpoints
// of line i is at (i, ai) and (i, 0). Find two lines, which together with
// x-axis forms a container, such that the container contains the most water.
// Note: You may not slant the container and n is at least 2.
// 8   |_________|___
// 7   |         |   |
// 6   | |       |   |
// 5   | |   |   |   |
// 4   | |   | | |   |
// 3   | |   | | | | |
// 2   | | | | | | | |
// 1 |_|_|_|_|_|_|_|_|
//   0 1 2 3 4 5 6 7 8 <- i
// The above vertical lines are represented by array [1,8,6,2,5,4,8,3,7]. In
// this case, the max area of water (blue section) the container can contain
// is 49.
//
// Example:
//  Input: [1,8,6,2,5,4,8,3,7]
//  Output: 49

#include <algorithm>
#include <iostream>

#include "playground.h"

class Solution {
 public:
  int maxArea(std::vector<int>& height) {
    if (height.size() < 2)
      return 0;
    size_t l = 0, r = height.size() - 1;
    int h = std::min(height[l], height[r]);
    int maxarea = h * (r - l);
    while (l < r - 1) {
      if (height[l] == h)
        ++l;
      else
        --r;
      h = std::min(height[l], height[r]);
      int V = h * (r - l);
      if (V > maxarea)
        maxarea = V;
    }
    return maxarea;
  }
};

int main() {
    std::string line;
    while (std::getline(std::cin, line)) {
        std::vector<int> height = stringToIntegerVector(line);

        int ret = Solution().maxArea(height);

        std::string out = std::to_string(ret);
        std::cout << out << std::endl;
    }
    return 0;
}
