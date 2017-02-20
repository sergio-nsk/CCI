// First Common Ancestor: Design an algorithm and write code to find the first common ancestor
// of two nodes in a binary tree. Avoid storing additional nodes in a data structure. NOTE: This is not
// necessarily a binary search tree.

#include <vector>
#define INCLUDE_HELPER
#include "tree.hpp"

enum FindResult
{
    NotFound,
    FoundLeft,
    FoundRight,
    FoundEqual
};

template <typename T>
FindResult findNodeFrom(const NodePtr<T> &startNode, const NodePtr<T> &node)
{
    if (!startNode)
        return NotFound;
    if (startNode == node)
        return FoundEqual;
    if (findNodeFrom<T>(startNode->getLeft(), node) != NotFound)
        return FoundLeft;
    else if (findNodeFrom<T>(startNode->getRight(), node) != NotFound)
        return FoundRight;
    return NotFound;
}

template <typename T>
NodePtr<T> findCommonAncestor(const Tree<T> &tree, const NodePtr<T> &one, const NodePtr<T> &two)
{
    if (one == two)
        return one;
    
    auto startNode = tree.getRoot();

    auto firstResult = findNodeFrom<T>(startNode, one);
    if (firstResult == NotFound)
        return nullptr;
    auto secondResult = findNodeFrom<T>(startNode, two);
    if (secondResult == NotFound)
        return nullptr;

    while (firstResult == secondResult)
    {
        startNode = (firstResult == FoundLeft) ? startNode->getLeft() : startNode->getRight();
        firstResult = findNodeFrom<T>(startNode, one);
        secondResult = findNodeFrom<T>(startNode, two);
    }
    return startNode;
}

int main()
{
    std::vector<int> array();
    auto tree = treeFromArray({10, 1, 12, 3, 14, 25, 16, 27, 18, 29, 10, 13, 2, 15, 4, 5, 17, 7, 19, 9});
    tree.printTree();

    for (auto one : tree)
        for (auto two : tree)
        {
            auto ancestor = findCommonAncestor<int>(tree, one, two);
            std::cout << one->getValue() << ", " << two->getValue() << " <-- ";
            std::cout << (ancestor ? std::to_string(ancestor->getValue()) : "NOT FOUND") << std::endl;
        }

    // auto one = tree.getRoot();
    // auto two = tree.getRoot();
    // auto ancestor = findCommonAncestor<int>(tree, one, two);
    // std::cout << one->getValue() << ", " << two->getValue() << " <-- ";
    // std::cout << (ancestor ? std::to_string(ancestor->getValue()) : "NOT FOUND") << std::endl;

    // one = tree.getRoot()->getLeft();
    // two = tree.getRoot();
    // ancestor = findCommonAncestor<int>(tree, one, two);
    // std::cout << one->getValue() << ", " << two->getValue() << " <-- ";
    // std::cout << (ancestor ? std::to_string(ancestor->getValue()) : "NOT FOUND") << std::endl;

    // one = tree.getRoot();
    // two = tree.getRoot()->getLeft();
    // ancestor = findCommonAncestor<int>(tree, one, two);
    // std::cout << one->getValue() << ", " << two->getValue() << " <-- ";
    // std::cout << (ancestor ? std::to_string(ancestor->getValue()) : "NOT FOUND") << std::endl;

    // one = tree.getRoot()->getLeft();
    // two = tree.getRoot()->getRight();
    // ancestor = findCommonAncestor<int>(tree, one, two);
    // std::cout << one->getValue() << ", " << two->getValue() << " <-- ";
    // std::cout << (ancestor ? std::to_string(ancestor->getValue()) : "NOT FOUND") << std::endl;

    // one = tree.getRoot()->getRight();
    // two = tree.getRoot()->getRight();
    // ancestor = findCommonAncestor<int>(tree, one, two);
    // std::cout << one->getValue() << ", " << two->getValue() << " <-- ";
    // std::cout << (ancestor ? std::to_string(ancestor->getValue()) : "NOT FOUND") << std::endl;

    return 0;
}