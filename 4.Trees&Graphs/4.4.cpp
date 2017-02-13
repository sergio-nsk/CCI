// Check Balanced: Implement a function to check if a binary tree is balanced. For the purposes of
// this question, a balanced tree is defined to be a tree such that the heights of the two subtrees of any
// node never differ by more than one.

#include <limits>

#define INCLUDE_HELPER
#include "tree.hpp"

template <typename T, size_t N>
using NodeN = typename Tree<T, N>::Node;

template <typename T, size_t N>
using NodeNPtr = std::shared_ptr<NodeN<T, N>>;

bool checkHeight(size_t height, size_t &minHeight, size_t &maxHeight)
{
    if (height < minHeight)
        minHeight = height;
    if (height > maxHeight)
        maxHeight = height;
    if (maxHeight - minHeight > 1)
        return false;
    return true;
}

template <typename T, size_t N>
bool walkTree(const NodeNPtr<T, N> &node, int height, size_t &minHeight, size_t &maxHeight)
{
    if (node->getChilds().empty()) // leaf
    {
        if (!checkHeight(height, minHeight, maxHeight))
            return false;
    }

    for (const auto &c : node->getChilds())
    {
        if (c)
        {
            if (!walkTree<T, N>(c, height + 1, minHeight, maxHeight))
                return false;
        }
        else if (!checkHeight(height, minHeight, maxHeight))
        {
            return false;
        }
    }
    return true;
}

template <typename T, size_t N>
bool isTreeBalanced(const Tree<T, N> &tree)
{
    size_t minHeight = std::numeric_limits<size_t>::max();
    size_t maxHeight = 0;
    return walkTree<T, N>(tree.getRoot(), 0, minHeight, maxHeight);
}

int main()
{
    auto array = std::vector<int>({0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19});
    auto tree = treeFromArray(&array[0], array.size()); // balanced tree
    std::cout << "Tree is " << (isTreeBalanced<int>(tree) ? "" : "NOT ") << "balanced" << std::endl;

    auto r = tree.getRoot()->getRight();
    tree.getRoot()->getRight() = std::make_shared<NodeN<int, 2>>(100); // not balanced
    std::cout << "Tree is " << (isTreeBalanced<int>(tree) ? "" : "NOT ") << "balanced" << std::endl;

    tree.getRoot()->getRight() = r; // balanced
    std::cout << "Tree is " << (isTreeBalanced<int>(tree) ? "" : "NOT ") << "balanced" << std::endl;

    tree.getRoot()->getRight().reset(); // not balanced
    std::cout << "Tree is " << (isTreeBalanced<int>(tree) ? "" : "NOT ") << "balanced" << std::endl;
    return 0;
}