// 4. Median of Two Sorted Arrays
//
// There are two sorted arrays nums1 and nums2 of size m and n respectively.
//
// Find the median of the two sorted arrays. The overall run time complexity
// should be O(log (m+n)).
//
// You may assume nums1 and nums2 cannot be both empty.
//
// Example 1:
//  nums1 = [1, 3]
//  nums2 = [2]
//  The median is 2.0

// Example 2:
//
//  nums1 = [1, 2]
//  nums2 = [3, 4]
//  The median is (2 + 3)/2 = 2.5

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include "playground.h"

class Solution {
 public:
  double findMedianSortedArrays(const std::vector<int>& nums1,
                                const std::vector<int>& nums2) {
    const size_t s1 = nums1.size();
    const size_t s2 = nums2.size();
    if (s1 > s2)
      return findMedianSortedArrays(nums2, nums1);

    int l = 0, h = s1;
    while (l <= h) {
      int part_1 = (l + h) / 2;
      int part_2 = (s1 + s2 + 1) / 2 - part_1;
      int max_1 = (part_1 == 0) ? INT_MIN : nums1[part_1 - 1];
      int min_1 = (part_1 == s1) ? INT_MAX : nums1[part_1];
      int max_2 = (part_2 == 0) ? INT_MIN : nums2[part_2 - 1];
      int min_2 = (part_2 == s2) ? INT_MAX : nums2[part_2];

      if (max_1 <= min_2 && max_2 <= min_1) {
        if (((s1 + s2) & 1) == 0)
          return (0.0 + std::max(max_1, max_2) + std::min(min_1, min_2)) / 2;
        else
          return std::max(max_1, max_2);

      } else if (max_1 > min_2) {
        h = part_1 - 1;
      } else {
        l = part_1 + 1;
      }
    }
    return -1;
  }
};

int main() {
  std::string line;
  while (std::getline(std::cin, line)) {
    std::vector<int> nums1 = stringToIntegerVector(line);
    std::getline(std::cin, line);
    std::vector<int> nums2 = stringToIntegerVector(line);

    double ret = Solution().findMedianSortedArrays(nums1, nums2);

    std::string out = std::to_string(ret);
    std::cout << out << std::endl;
  }
  return 0;
}
