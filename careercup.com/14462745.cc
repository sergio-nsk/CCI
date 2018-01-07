// https: //www.careercup.com/question?id=14462745
// Amazon
// Find the minimum element in a stack in O(1) time complexity and O(n) space complexity

#include <stack>
#include <iostream>

class MinStack {
 public:
  void push(int n) {
    stack_.push(n);
    // track all multiple min values
    if (min_stack_.empty() || n <= min_stack_.top())
      min_stack_.push(n);
  }

  void pop() {
    if (stack_.empty())
      return;

    auto n = stack_.top();
    stack_.pop();
    if (n == min_stack_.top())
      min_stack_.pop();
  }

  int top() {
    return stack_.top();
  }

  int min() {
    return min_stack_.top();
  }

  bool empty() {
    return stack_.empty();
  }

private:
  std::stack<int> stack_;
  std::stack<int> min_stack_;
};

int main() {
  MinStack stack;
  for (auto n : {10, 9, 20, 8, 8, 30, 8, 7}) {
    stack.push(n);
    std::cout << "stack.top() is " << stack.top() << ", stack.min() is " << stack.min() << std::endl;
  }
  std::cout << std::endl;
  while (!stack.empty())
  {
    std::cout << "stack.top() is " << stack.top() << ", stack.min() is " << stack.min() << std::endl;
    stack.pop();
  }
}
