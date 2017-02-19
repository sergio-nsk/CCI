#include <array>
#include <memory>
#include <utility>
#include <queue>
#include <stack>
#include <iostream>
#include <iomanip>
#include <limits>
#include <cmath>

template <typename T, size_t N, bool NodeWithParent = false>
class Tree
{
private:
    template <typename Node, bool WithParent>
    class NodeBase
    {
    public:
        NodeBase()
        {
        }

        NodeBase(const std::shared_ptr<Node> &p) : parent(p)
        {
        }

        std::shared_ptr<Node> getParent()
        {
            return parent.lock();
        }
    private:
        std::weak_ptr<Node> parent;
    };

    template <typename Node>
    class NodeBase<Node, false>
    {
    public:
        NodeBase()
        {
        }

        NodeBase(const std::shared_ptr<Node> &p)
        {
        }

    private:
    };

public:
    class Node : public NodeBase<Node, NodeWithParent>
    {
    public:
        Node(T &&v) : value(std::move(v))
        {
        }

        Node(const T &v) : value(v)
        {
        }

        Node(T &&v, const std::shared_ptr<Node> &p) : NodeBase<Node, NodeWithParent>(p), value(std::move(v))
        {
        }

        Node(const T &v, const std::shared_ptr<Node> &p) : NodeBase<Node, NodeWithParent>(p), value(v)
        {
        }

        const T& getValue() const
        {
            return value;
        }

        const std::array<std::shared_ptr<Node>, N> &getChilds() const
        {
            return childs;
        }

        std::array<std::shared_ptr<Node>, N> &getChilds()
        {
            return childs;
        }

        const std::shared_ptr<Node> &getLeft() const
        {
            return childs[0];
        }

        std::shared_ptr<Node> &getLeft()
        {
            return childs[0];
        }

        const std::shared_ptr<Node> &getRight() const
        {
            return childs[childs.size() - 1];
        }

        std::shared_ptr<Node> &getRight()
        {
            return childs[childs.size() - 1];
        }

        template <typename U>
        void setLeftChild(U &&node)
        {
            childs[0] = std::forward<U>(node);
        }

        template <typename U>
        void setRightChild(U &&node)
        {
            childs[childs.size() - 1] = std::forward<U>(node);
        }

    protected:
        T value;
        std::array<std::shared_ptr<Node>, N> childs;
    };

    const std::shared_ptr<Node> &getRoot() const
    {
        if (isEmpty())
            throw TreeIsEmptyException();
        return root;
    }

    template <typename U>
    void setRoot(U &&node)
    {
        root = std::forward<U>(node);
    }

    bool isEmpty() const
    {
        return !root;
    }

    class TreeIsEmptyException {};
    
protected:
    std::shared_ptr<Node> root;
};

template <typename T, bool NodeWithParent = false>
class BinaryTree : public Tree<T, 2, NodeWithParent>
{
public:
    using Node = typename Tree<T, 2, NodeWithParent>::Node;

private:
    template <typename Iterator, bool WithParent>
    class IteratorBase
    {
    public:
        IteratorBase()
        {
        }
        
        IteratorBase(const std::shared_ptr<Node> &node) : currNode(node)
        {
        }

        Iterator &operator ++ ()
        {
            auto node = currNode.lock();
            if (!node)
                currNode = std::shared_ptr<Node>();
            if (node->getLeft())
                currNode = node->getLeft();
            else if (node->getRight())
                currNode = node->getRight();
            else
            {
                while (node->getParent() && node == node->getParent()->getRight())
                    node = node->getParent();
                currNode = node->getParent() ? node->getParent()->getRight() : node->getParent();
            }
            return *this;
        }

    protected:
        std::weak_ptr <Node> currNode;
    };

    template <typename Iterator>
    class IteratorBase<Iterator, false>
    {
    public:
        IteratorBase()
        {
        }
        
        IteratorBase(const std::shared_ptr<Node> &node) : currNode(node)
        {
        }

        Iterator &operator ++ ()
        {
            auto node = currNode.lock();
            if (!node)
                currNode = std::shared_ptr<Node>();
            if (node->getLeft())
            {
                parents.emplace(node);
                currNode = node->getLeft();
            }
            else if (node->getRight())
            {
                parents.emplace(node);
                currNode = node->getRight();
            }
            else
            {
                while (!parents.empty() && node == parents.top()->getRight())
                {
                    node = parents.top();
                    parents.pop();
                }
                currNode = !parents.empty() ? parents.top()->getRight() : std::shared_ptr<Node>();
            }
            return *static_cast<Iterator *>(this);
        }

    protected:
        std::weak_ptr<Node> currNode;
        std::stack<std::shared_ptr<Node>> parents;
    };

public:
    class Iterator : public IteratorBase<Iterator, NodeWithParent>
    {
        using Base = IteratorBase<Iterator, NodeWithParent>;

    public:
        Iterator()
        {
        }

        Iterator(const std::shared_ptr<Node> &node) : Base(node)
        {
        }

        std::shared_ptr<Node> operator * ()
        {
            return Base::currNode.lock();
        }

        bool operator != (const Iterator &rh)
        {
            return Base::currNode.lock() != rh.currNode.lock();
        }
    };

    Iterator end() const
    {
        return Iterator();
    }

    Iterator begin() const
    {
        return Iterator(Tree<T, 2, NodeWithParent>::getRoot());
    }

    size_t getDepth(T &minValue, T &maxValue, const std::shared_ptr<Node> &node) const
    {
        if (!node)
            return 0;

        auto depth = std::max(getDepth(minValue, maxValue, node->getLeft()), getDepth(minValue, maxValue, node->getRight())) + 1;
        minValue = std::min(minValue, node->getValue());
        maxValue = std::max(maxValue, node->getValue());
        return depth;
    }

    void printTree() const
    {
        T minValue = std::numeric_limits<T>::max(), maxValue = std::numeric_limits<T>::min();
        size_t depth = getDepth(minValue, maxValue, Tree<T, 2, NodeWithParent>::getRoot());

        // bottommost max leaf count
        size_t size = std::pow(2, depth - 1);

        // width of node, in digits
        size_t digits = (maxValue != 0 || minValue != 0) ? std::log10(std::max(maxValue, std::abs(minValue))) + 1  : 1;
        if (minValue < 0)
            ++digits;

        // placeholder width
        const size_t w = digits + 1;
        
        std::queue<std::shared_ptr<Node>> queue;
        std::queue<std::shared_ptr<Node>> childs;
        queue.push(Tree<T, 2, NodeWithParent>::root);
        std::cout.imbue(std::locale("en_US.utf8"));
        std::cout << "Tree:" << std::endl;
        do 
        {
            size_t space = (size - 1) * w + 1;
            int margin = space / 2;
            std::cout << std::string(margin, ' ');
            while (!queue.empty())
            {
                if (!queue.front())
                    std::cout << std::string(w, ' ');
                else
                {
                    std::cout << std::setw(digits) << std::right
                        << queue.front()->getValue() << std::string(space, ' ');
                    childs.push(queue.front()->getLeft());
                    childs.push(queue.front()->getRight());
                }
                queue.pop();
            }
            std::cout << std::endl;
            queue.swap(childs);
            if (margin == 0)
                break;
            size /= 2;
        } while (true);
    }
};

template <typename T, bool WithParent = false>
using Node = typename BinaryTree<T, WithParent>::Node;

template <typename T, bool WithParent = false>
using NodePtr = std::shared_ptr<Node<T, WithParent>>;

#ifdef INCLUDE_HELPER

// The function treeFromArray from the task 4.2 helps us to fill test trees.
template <typename T, bool WithParent = false>
NodePtr<T, WithParent> subtreeFromArray(const T *array, const NodePtr<T, WithParent> &parent, int start, int end)
{
    if (end < start)
        return nullptr;

    int i = (start + end) / 2;
    auto node = std::make_shared<Node<T, WithParent>>(array[i], parent);
    node->setLeftChild(subtreeFromArray<T, WithParent>(array, node, start, i - 1));
    node->setRightChild(subtreeFromArray<T, WithParent>(array, node, i + 1, end));
    return node;
}

template <typename T, bool WithParent = false>
BinaryTree<T, WithParent> treeFromArray(std::initializer_list<T> array)
{
    BinaryTree<T, WithParent> tree;
    tree.setRoot(subtreeFromArray<T, WithParent>(array.begin(), nullptr, 0, array.size() - 1));

    return tree;
}

#endif
