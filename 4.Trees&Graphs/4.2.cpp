// Minimal Tree: Given a sorted (increasing order) array with unique integer elements, write an
// algorithm to create a binary search tree with minimal height.

#include <vector>
#include "tree.hpp"

template <typename T>
using Node = typename BinaryTree<T>::Node;

template <typename T>
using NodePtr = std::shared_ptr<Node<T>>;

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

int main()
{
    std::vector<int> array({0});
    auto tree = treeFromArray(&array[0], array.size());
    // printTree(tree, 1);

    array = {0, 1};
    tree = treeFromArray(&array[0], array.size());
    // printTree(tree, 3);

    array = {0, 1, 2};
    tree = treeFromArray(&array[0], array.size());
    // printTree(tree, 3);

    array = {0, 1, 2, 3};
    tree = treeFromArray(&array[0], array.size());
    // printTree(tree, 7);

    array = {0, 1, 2, 3, 4};
    tree = treeFromArray(&array[0], array.size());
    // printTree(tree, 7);

    array = {0, 1, 2, 3, 4, 5};
    tree = treeFromArray(&array[0], array.size());
    // printTree(tree, 7);

    array = {0, 1, 2, 3, 4, 5, 6};
    tree = treeFromArray(&array[0], array.size());
    tree.printTree(7);

    array = {0, 1, 2, 3, 4, 5, 6, 7};
    tree = treeFromArray(&array[0], array.size());
    // printTree(tree, 15);

    array = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
    tree = treeFromArray(&array[0], array.size());
    // printTree(tree, 15);

    array = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19};
    tree = treeFromArray(&array[0], array.size());
    tree.printTree(31);
    return 0;
}