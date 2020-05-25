// 1. Two Sum
//
// Given an array of integers, return indices of the two numbers such that they
// add up to a specific target.
//
// You may assume that each input would have exactly one solution, and you may
// not use the same element twice.
//
// Example:
//  Given nums = [2, 7, 11, 15], target = 9,
//  Because nums[0] + nums[1] = 2 + 7 = 9,
//  return [0, 1].
//
// Hint 1
// A really brute force way would be to search for all possible pairs of numbers
// but that would be too slow. Again, it's best to try out brute force solutions
// for just for completeness. It is from these brute force solutions that you
// can come up with optimizations.
//
// Hint2
// So, if we fix one of the numbers, say
// x
// , we have to scan the entire array to find the next number
// y
// which is
// value - x
// where value is the input parameter. Can we change our array somehow so that
// this search becomes faster?
//
// Hint 3
// The second train of thought is, without changing the array, can we use
// additional space somehow? Like maybe a hash map to speed up the search?

#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
#include "playground.h"

class Solution {
 public:
  std::vector<int> twoSum(std::vector<int>& nums, int target) {
    std::unordered_map<int, int> map;
    const int size = nums.size();
    map[target - nums.front()] = 0;
    for (int i = 1; i < size; ++i) {
      const auto& j = map.find(nums[i]);
      if (j != map.end())
        return {j->second, i};
      map[target - nums[i]] = i;
    }
    return {};
  }
};

std::string run(std::istream& in) {
  std::string line;
  while (getline(in, line)) {
    std::vector<int> nums = stringToIntegerVector(line);
    getline(in, line);
    int target = stringToInteger(line);

    std::vector<int> ret = Solution().twoSum(nums, target);

    std::string out = integerVectorToString(ret);
    return out;
  }
  return "";
}

int main() {
  run(std::stringstream("[2, 7, 11, 15]")) == "[0, 1]";
}
