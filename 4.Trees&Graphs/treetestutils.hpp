#pragma once

#include <algorithm>
#include <functional>
#include <iomanip>
#include <iostream>
#include <limits>
#include <numeric>
#include <queue>
#include "tree.hpp"

namespace TestUtils {
template <typename T, bool WithParent, typename Node>
void printTree(const Tree<T, WithParent, Node>& tree) {
  T minValue = std::numeric_limits<T>::max(),
    maxValue = std::numeric_limits<T>::min();

  // Lambda function is used to hide it from externall access
  std::function<size_t(const Node*)> getDepth =
      [&](const Node* node) -> size_t {
    if (!node)
      return 0;

    auto depth =
        std::max(getDepth(node->getLeft()), getDepth(node->getRight())) + 1;
    minValue = std::min(minValue, node->getValue());
    maxValue = std::max(maxValue, node->getValue());
    return depth;
  };

  size_t depth = getDepth(tree.getRoot());

  // bottommost max leaf count
  size_t size = static_cast<size_t>(std::pow(2, depth - 1));

  // width of node, in digits
  size_t digits =
      (maxValue != 0 || minValue != 0)
          ? static_cast<size_t>(
                std::log10(std::max(maxValue, std::abs(minValue))) + 1)
          : 1;
  if (minValue < 0)
    ++digits;

  const std::string placeholder(digits, ' ');

  std::queue<const Node*> queue;
  std::queue<const Node*> childs;
  queue.push(tree.getRoot());
  std::cout << "Tree:" << std::endl;

  do {
    // space between nodes
    std::string space((size - 1) * (placeholder.length() + 1) + 1, ' ');

    // margin
    std::cout << std::string(space.length() / 2, ' ');
    ;
    while (!queue.empty()) {
      if (!queue.front()) {
        std::cout << placeholder << space;
        childs.emplace();
        childs.emplace();
      } else {
        std::cout << std::setw(digits) << std::right
                  << queue.front()->getValue() << space;
        childs.push(queue.front()->getLeft());
        childs.push(queue.front()->getRight());
      }
      queue.pop();
    }
    std::cout << std::endl;
    queue.swap(childs);
    size /= 2;
  } while (size > 0);
}

// The function treeFromArray from the task 4.2 helps us to fill test trees.
template <typename T, bool WithParent = false>
auto treeFromArray(const T* array, size_t size) {
  using Node = Node<T, WithParent>;

  std::function<std::unique_ptr<Node>(const T*, Node*, int, int)>
      subtreeFromArray = [&subtreeFromArray](const T* array, Node* parent,
                                             int start,
                                             int end) -> std::unique_ptr<Node> {
    if (end < start)
      return nullptr;

    int i = (start + end) / 2;
    auto node = std::make_unique<Node>(array[i], parent);
    node->setLeft(subtreeFromArray(array, node.get(), start, i - 1));
    node->setRight(subtreeFromArray(array, node.get(), i + 1, end));
    return node;
  };

  Tree<T, WithParent> tree;
  tree.setRoot(
      subtreeFromArray(&array[0], nullptr, 0, static_cast<int>(size) - 1));
  return tree;
}

template <typename T, bool WithParent = false>
auto treeFromArray(std::initializer_list<T> array) {
  return treeFromArray<T, WithParent>(array.begin(), array.size());
}

template <typename T, bool WithParent = false>
auto getSampleTree(size_t nodeCount) {
  std::vector<T> v(nodeCount);
  std::iota(std::begin(v), std::end(v),
            0);  // Fill with 0, 1, ..., nodeCount - 1.
  return treeFromArray<T, WithParent>(&v[0], v.size());
}
}  // namespace TestUtils
