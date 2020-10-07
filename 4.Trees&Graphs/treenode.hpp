#pragma once

#include <memory>

template <typename T,
          bool WithParent = false,
          bool R = WithParent>  // R is a child type selector.
class Node;

template <typename T, bool R>
class Node<T, false, R> {
 public:
  using NodeT = Node<T, R, R>;

  Node(T&& v) : value(std::move(v)) {}

  Node(const T& v) : value(v) {}

  Node(T&& v, Node*) : value(std::move(v)) {}

  Node(const T& v, Node*) : value(v) {}

  const T& getValue() const { return value; }

  const NodeT* getLeft() const { return childs.first.get(); }

  NodeT* getLeft() { return childs.first.get(); }

  std::unique_ptr<Node> extractLeft() { return std::move(childs.first); }

  const NodeT* getRight() const { return childs.second.get(); }

  NodeT* getRight() { return childs.second.get(); }

  std::unique_ptr<Node> extractRight() { return std::move(childs.second); }

  void setLeft(std::unique_ptr<NodeT> node) { childs.first = std::move(node); }

  void setRight(std::unique_ptr<NodeT> node) { childs.second = std::move(node); }

 protected:
  T value;
  std::pair<std::unique_ptr<NodeT>, std::unique_ptr<NodeT>> childs;
};

template <typename T>
class Node<T, true, true> : public Node<T, false, true> {
 public:
  Node(T&& v, Node* p) : Node<T, false, true>(std::move(v)), parent(p) {}

  Node(const T& v, Node* p) : Node<T, false, true>(v), parent(p) {}

  Node* getParent() { return parent; }

  const Node* getParent() const { return parent; }

 protected:
  Node* parent;
};
