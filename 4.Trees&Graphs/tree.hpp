#pragma once

#include "treenode.hpp"

template <typename T,
          bool WithParent = false,
          typename Node = Node<T, WithParent>>
class Tree {
 public:
  const Node* getRoot() const {
    if (isEmpty())
      throw TreeIsEmptyException();
    return root.get();
  }
  Node* getRoot() {
    return const_cast<Node*>(static_cast<const Tree*>(this)->getRoot());
  }

  void setRoot(std::unique_ptr<Node> node) { root = std::move(node); }

  bool isEmpty() const { return !root; }

  class TreeIsEmptyException {};

 protected:
  std::unique_ptr<Node> root;
};
