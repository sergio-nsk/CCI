// Check Balanced: Implement a function to check if a binary tree is balanced. For the purposes of
// this question, a balanced tree is defined to be a tree such that the heights of the two subtrees of any
// node never differ by more than one.

#include <vector>
#include <limits>

#include "tree.hpp"

template <typename T, size_t N>
using Node = typename Tree<T, N>::Node;

template <typename T, size_t N>
using NodePtr = std::shared_ptr<Node<T, N>>;

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
bool walkTree(const NodePtr<T, N> &node, int height, size_t &minHeight, size_t &maxHeight)
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

template <typename T>
NodePtr<T, 2> subtreeFromArray(const T *array, int start, int end)
{
    if (end < start)
        return nullptr;

    int i = (start + end) / 2;
    auto node = std::make_shared<Node<T, 2>>(array[i]);
    node->getLeft() = subtreeFromArray<T>(array, start, i - 1);
    node->getRight() = subtreeFromArray(array, i + 1, end);
    return node;
}

template <typename T>
Tree<T, 2> treeFromArray(const T *array, size_t size)
{
    Tree<T, 2> tree;
    tree.setRoot(subtreeFromArray<T>(array, 0, size - 1));

    return tree;
}

int main()
{
    auto array = std::vector<int>({0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19});
    auto tree = treeFromArray(&array[0], array.size()); // balanced tree
    std::cout << "Tree is " << (isTreeBalanced<int>(tree) ? "" : "NOT ") << "balanced" << std::endl;

    auto r = tree.getRoot()->getRight();
    tree.getRoot()->getRight() = std::make_shared<Node<int, 2>>(100); // not balanced
    std::cout << "Tree is " << (isTreeBalanced<int>(tree) ? "" : "NOT ") << "balanced" << std::endl;

    tree.getRoot()->getRight() = r; // balanced
    std::cout << "Tree is " << (isTreeBalanced<int>(tree) ? "" : "NOT ") << "balanced" << std::endl;

    tree.getRoot()->getRight().reset(); // not balanced
    std::cout << "Tree is " << (isTreeBalanced<int>(tree) ? "" : "NOT ") << "balanced" << std::endl;
    return 0;
}