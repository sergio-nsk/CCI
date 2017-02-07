// List of Depths: Given a binary tree, design an algorithm which creates a linked list of all the nodes
// at each depth (e.g., if you have a tree with depth D, you'll have D linked lists).

// This task is mostly done in the function printTree :-)

#include <list>
#define INCLUDE_HELPER
#include "tree.hpp"

template <typename T>
using NodeList = std::list<NodePtr<T>>;

template <typename T>
std::list<NodeList<T>> getNodes(const BinaryTree<T> &tree)
{
    std::list<NodeList<T>> result;

    result.emplace_back();
    auto list = &result.back();
    list->push_back(tree.getRoot());

    do
    {
        result.emplace_back();
        auto &childs = result.back();
        for (const auto &n : *list)
        {
            if (n->getLeft())
                childs.push_back(n->getLeft());
            if (n->getRight())
                childs.push_back(n->getRight());
        }
        if (childs.empty())
        {
            result.pop_back();
            break;
        }
        list = &childs;
    } while (true);

    return result;
}

template <typename T>
void printNodes(const std::list<NodeList<T>> &nodes)
{
    int depth = 0;
    for (const auto &line : nodes)
    {
        std::cout << depth << ": ";
        auto sep = "";
        for (const auto &n : line)
        {
            std::cout << sep << n->getValue();
            sep = ", ";
        }
        std::cout << std::endl;
        ++depth;
    }
}

int main()
{
    std::vector<int> array({0});
    auto tree = treeFromArray(&array[0], array.size());
    auto nodes = getNodes(tree);
    // printTree(tree, 1);
    // printNodes<int>(nodes);

    array = {0, 1};
    tree = treeFromArray(&array[0], array.size());
    tree.printTree(3);
    nodes = getNodes(tree);
    printNodes<int>(nodes);

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
    nodes = getNodes(tree);
    printNodes<int>(nodes);

    array = {0, 1, 2, 3, 4, 5, 6, 7};
    tree = treeFromArray(&array[0], array.size());
    // printTree(tree, 15);

    array = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
    tree = treeFromArray(&array[0], array.size());
    // printTree(tree, 15);

    array = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19};
    tree = treeFromArray(&array[0], array.size());
    tree.printTree(31);
    nodes = getNodes(tree);
    printNodes<int>(nodes);
    return 0;
}