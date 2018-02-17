#pragma once

#include <stack>
#include "tree.hpp"

template <typename Iterator, typename T, bool WithParent>
class IteratorBase {
  using NodeT = Node<T, WithParent>;

 public:
  IteratorBase() = default;

  IteratorBase(const NodeT* node) : currNode(node) {}

  Iterator& operator++() {
    auto node = currNode;
    if (node) {
      if (node->getLeft())
        currNode = node->getLeft();
      else if (node->getRight())
        currNode = node->getRight();
      else {
        while (node->getParent() && node == node->getParent()->getRight())
          node = node->getParent();
        currNode = node->getParent() ? node->getParent()->getRight()
                                     : node->getParent();
      }
    }
    return *static_cast<Iterator*>(this);
  }

 protected:
  const NodeT* currNode;
};

template <typename Iterator, typename T>
class IteratorBase<Iterator, T, false> {
 public:
  IteratorBase() = default;

  IteratorBase(const Node<T, false>* node) : currNode(node) {}

  Iterator& operator++() {
    auto node = currNode;
    if (node) {
      if (node->getLeft()) {
        parents.emplace(node);
        currNode = node->getLeft();
      } else if (node->getRight()) {
        parents.emplace(node);
        currNode = node->getRight();
      } else {
        while (!parents.empty() && node == parents.top()->getRight()) {
          node = parents.top();
          parents.pop();
        }
        currNode = !parents.empty() ? parents.top()->getRight() : nullptr;
      }
    }
    return *static_cast<Iterator*>(this);
  }

 protected:
  const Node<T, false>* currNode;
  std::stack<const Node<T, false>*> parents;
};

template <typename T, bool WithParent>
class Iterator : public IteratorBase<Iterator<T, WithParent>, T, WithParent> {
  using Super = IteratorBase<Iterator<T, WithParent>, T, WithParent>;
  using Node = Node<T, WithParent>;

 public:
  Iterator() = default;

  Iterator(const Node* node) : Super(node) {}

  const Node* operator*() { return Super::currNode; }

  bool operator!=(const Iterator& rh) {
    return Super::currNode != rh.currNode;
  }
};

template <typename T, bool WithParent, typename P>
auto begin(const Tree<T, WithParent, P>& tree) {
  return Iterator<T, WithParent>(tree.getRoot());
}

template <typename T, bool WithParent, typename P>
auto end(const Tree<T, WithParent, P>&) {
  return Iterator<T, WithParent>();
}
