// Validate BST: Implement a function to check if a binary tree is a binary search tree.

#include <list>
#include "tree.hpp"

template <typename T>
using Node = typename BinaryTree<T>::Node;

template <typename T>
using NodePtr = std::shared_ptr<Node<T>>;

template <typename T>
using NodeList = std::list<NodePtr<T>>;

// The function treeFromArray from the task 4.2 helps us to fill test trees.
template <typename T>
NodePtr<T> subtreeFromArray(const T *array, int start, int end)
{
    if (end < start)
        return nullptr;

    int i = (start + end) / 2;
    auto node = std::make_shared<Node<T>>(array[i]);
    node->setLeftChild(subtreeFromArray(array, start, i - 1));
    node->setRightChild(subtreeFromArray(array, i + 1, end));
    return node;
}

template <typename T>
BinaryTree<T> treeFromArray(const T *array, size_t size)
{
    BinaryTree<T> tree;
    tree.setRoot(subtreeFromArray(array, 0, size - 1));

    return tree;
}

template <typename T>
bool checkNode(const NodePtr<T> &node)
{
    if (!node)
        return true;

    auto &left = node->getLeft();
    auto &right = node->getRight();
    
    if (left && node->getValue() < left->getValue())
        return false;
    if (right && node->getValue() >= right->getValue())
        return false;
    return checkNode<T>(left) && checkNode<T>(right);
}

template <typename T>
bool isValidBST(const BinaryTree<T> &tree)
{
    return checkNode<T>(tree.getRoot());
}

int main()
{
    std::vector<int> array({0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19});
    auto tree = treeFromArray(&array[0], array.size());
    tree.printTree(31);
    std::cout << "The tree is " << (isValidBST<int>(tree) ? "" : "NOT ") << "binary search tree" << std::endl;

    tree.getRoot()->getRight()->getRight()->getRight()->setLeftChild(std::make_shared<Node<int>>(19));
    tree.printTree(31);
    std::cout << "The tree is " << (isValidBST<int>(tree) ? "" : "NOT ") << "binary search tree" << std::endl;
    return 0;
}