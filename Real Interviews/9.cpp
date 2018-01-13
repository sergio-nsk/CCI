// Find the nearest common ancestor of two nodes of the same tree.

#include <algorithm>

struct Node {
  Node* parent;
  Node* left;
  Node* right;
};

int getDepth(const Node* node) {
  int depth = 0;
  while (node->parent) {
    node = node->parent;
    ++depth;
  }
  return depth;
}

const Node* findAncestor(const Node* first, const Node* second) {
  int depthFirst = getDepth(first);
  int depthSecond = getDepth(second);
  int diff = 0;
  if (depthFirst > depthSecond) {
    std::swap(first, second);
    diff = depthFirst - depthSecond;
  } else
    diff = depthSecond - depthFirst;

  // The second branch is always longer here
  for (; diff > 0; --diff)
    second = second->parent;
  while (first != second) {
    first = first->parent;
    second = second->parent;
  }
  return first;
}
