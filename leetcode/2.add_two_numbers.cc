// 2. Add Two Numbers
//
// You are given two non-empty linked lists representing two non-negative
// integers. The digits are stored in reverse order and each of their nodes
// contain a single digit. Add the two numbers and return it as a linked list.
//
// You may assume the two numbers do not contain any leading zero, except the
// number 0 itself.
//
// Example:
//  Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
//  Output: 7 -> 0 -> 8
//  Explanation: 342 + 465 = 807.

#include <iostream>
#include <string>
#include "playground.h"

class Solution {
 public:
  ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    int r = l1->val + l2->val;
    int add = r > 9;
    ListNode* sum = new ListNode(add ? r - 10 : r);
    ListNode* last = sum;
    l1 = l1->next;
    l2 = l2->next;
    while (l1 && l2) {
      r = l1->val + l2->val + add;
      add = r > 9;
      last->next = new ListNode(add ? r - 10 : r);
      last = last->next;
      l1 = l1->next;
      l2 = l2->next;
    }
    if (l2)
      l1 = l2;
    while (l1) {
      r = l1->val + add;
      add = r > 9;
      last->next = new ListNode(add ? r - 10 : r);
      last = last->next;
      l1 = l1->next;
    }
    if (add)
      last->next = new ListNode(1);
    return sum;
  }
};

int main() {
  std::string line;
  while (std::getline(std::cin, line)) {
    ListNode* l1 = stringToListNode(line);
    std::getline(std::cin, line);
    ListNode* l2 = stringToListNode(line);

    ListNode* ret = Solution().addTwoNumbers(l1, l2);

    std::string out = listNodeToString(ret);
    std::cout << out << std::endl;
  }
  return 0;
}
