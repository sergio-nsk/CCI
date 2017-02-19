// Validate BST: Implement a function to check if a binary tree is a binary search tree.

#include <vector>
#define INCLUDE_HELPER
#include "tree.hpp"

template <typename T>
bool checkNode(const NodePtr<T> &node, const T *minValue, const T *maxValue)
{
    if (!node)
        return true;
    if (minValue && node->getValue() <= *minValue)
        return false;
    if (maxValue && node->getValue() > *maxValue)
        return false;

    return checkNode<T>(node->getLeft(), minValue, &node->getValue()) && checkNode<T>(node->getRight(), &node->getValue(), maxValue);
}

template <typename T>
bool isValidBST(const BinaryTree<T> &tree)
{
    return checkNode<T>(tree.getRoot(), nullptr, nullptr);
}

int main()
{
    // valid BST
    auto tree = treeFromArray({0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19});
    tree.printTree();
    std::cout << "The tree is " << (isValidBST<int>(tree) ? "" : "NOT ") << "binary search tree" << std::endl;

    // invalid BST
    tree.getRoot()->getRight()->getRight()->getRight()->setLeftChild(std::make_shared<Node<int>>(19));
    tree.printTree();
    std::cout << "The tree is " << (isValidBST<int>(tree) ? "" : "NOT ") << "binary search tree" << std::endl;

    // invalid BST
    tree.getRoot()->getRight()->getRight()->getRight()->setLeftChild(std::make_shared<Node<int>>(15));
    tree.printTree();
    std::cout << "The tree is " << (isValidBST<int>(tree) ? "" : "NOT ") << "binary search tree" << std::endl;
    return 0;
}