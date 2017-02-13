// Successor: Write an algorithm to find the "next" node (i.e., in-order successor) of a given node in a
// binary search tree. You may assume that each node has a link to its parent.

#include <vector>
#define INCLUDE_HELPER
#include "tree.hpp"

template <typename T>
NodePtr<T> getMin(NodePtr<T> node)
{
    if (!node)
        return nullptr;
    while (node->getLeft())
        node = node->getLeft();
    return node;
}

template <typename T>
NodePtr<T> nextNode(NodePtr<T> node)
{
    if (!node)
        return nullptr;
    if (node->getRight())
        return getMin<T>(node->getRight());
    auto next = node->getParent();
    while (next && node == next->getRight())
    {
        // right subtree is traversed -> parent and all its childs were traversed
        node = next;
        next = next->getParent();
    }
    return next;
}

int main()
{
    // valid BST
    std::vector<int> array({0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19});
    auto tree = treeFromArray(&array[0], array.size());
    tree.printTree(31);
    auto node = getMin<int>(tree.getRoot());
    while (node)
    {
        std::cout << node->getValue() << " --> ";
        node = nextNode<int>(node);
        if (node)
            std::cout << node->getValue();
        std::cout << std::endl;
    }
    return 0;
}