// 15. 3Sum
// Given an array nums of n integers, are there elements a, b, c in nums such
// that a + b + c = 0? Find all unique triplets in the array which gives the sum
// of zero.
//
// Note:
// The solution set must not contain duplicate triplets.
//
// Example:
// Given array nums = [-1, 0, 1, 2, -1, -4],
// A solution set is:
// [
//   [-1, 0, 1],
//   [-1, -1, 2]
// ]
//
// Hint 1
// So, we essentially need to find three numbers x, y, and z such that they add
// up to the given value. If we fix one of the numbers say x, we are left with
// the two-sum problem at hand!
//
// Hint 2
// For the two-sum problem, if we fix one of the numbers, say `x`, we have to
// scan the entire array to find the next number `y` which is value `-x` where
// value is the input parameter. Can we change our array somehow so that this
// search becomes faster?
//
// Hint 3
// The second train of thought for two-sum is, without changing the array, can
// we use additional space somehow? Like maybe a hash map to speed up the
// search?

#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "playground.h"

class Solution {
 public:
  std::vector<std::vector<int>> threeSum(std::vector<int> nums) {
    if (nums.size() < 3)
      return {};
    std::unordered_map<int, int> num_counts;
    for (const int n : nums)
      num_counts[n]++;

    std::sort(nums.begin(), nums.end());
    nums.erase(std::unique(nums.begin(), nums.end()), nums.end());

    std::vector<std::vector<int>> res;

    for (auto i = nums.cbegin(); i != nums.end(); ++i) {
      const auto a = *i;
      --num_counts[a];  // remove one used, decrease use count
      for (auto j = i; j != nums.end(); ++j) {
        const auto b = *j;
        const auto c = -(a + b);

        // Consider only a <= b <= c and previous unused numbers.
        if ( c < b || num_counts[b] == 0)
          continue;

        --num_counts[b];
        const auto& k = num_counts.find(c);
        if (k != num_counts.end() && k->second > 0)
          res.push_back({a, b, c});
        ++num_counts[b];  // restore
      }
      num_counts[a] = 0;  // mark used
    }
    return res;
  }
};

int main() {
    std::string line;
    while (std::getline(std::cin, line)) {
        std::vector<int> nums = stringToIntegerVector(line);

        std::vector<std::vector<int>> ret = Solution().threeSum(nums);

        std::string out = vectorOfIntegerVectorsToString(ret);
        std::cout << out << std::endl;
    }
    return 0;
}
