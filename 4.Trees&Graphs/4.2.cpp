// Minimal Tree: Given a sorted (increasing order) array with unique integer
// elements, write an algorithm to create a binary search tree with minimal
// height.

#include <array>
#include <numeric>
#include "tree.hpp"
#include "treetestutils.hpp"

template <typename T>
std::unique_ptr<Node<T>> subtreeFromArray(const T* array, int start, int end) {
  if (end < start)
    return nullptr;

  int i = (start + end) / 2;
  auto node = std::make_unique<Node<T>>(array[i]);
  node->setLeft(subtreeFromArray(array, start, i - 1));
  node->setRight(subtreeFromArray(array, i + 1, end));
  return node;
}

template <typename T>
Tree<T> treeFromArray(const T* array, size_t size) {
  Tree<T> tree;
  tree.setRoot(subtreeFromArray(array, 0, size - 1));

  return tree;
}

int main() {
  std::array<int, 63> array;
  std::iota(array.begin(), array.end(), 0);  // Fill with 0 .. 62

  for (auto i : {1, 2, 3, 6, 7, 8, 14, 15, 16, 29, 30, 31}) {
    std::cout << '\n';
    auto tree = treeFromArray(&array[0], i);
    TestUtils::printTree(tree);
  }
  return 0;
}
