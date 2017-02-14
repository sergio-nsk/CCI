#include <array>
#include <memory>
#include <utility>
#include <queue>
#include <stack>
#include <iostream>
#include <iomanip>

template <typename T, size_t N, bool WithParentRefs = false>
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

    class Node : public NodeBase<Node, WithParentRefs>
    {
    public:
        Node(T &&v) : value(std::move(v))
        {
        }

        Node(const T &v) : value(v)
        {
        }

        Node(T &&v, const std::shared_ptr<Node> &p) : NodeBase<Node, WithParentRefs>(p), value(std::move(v))
        {
        }

        Node(const T &v, const std::shared_ptr<Node> &p) : NodeBase<Node, WithParentRefs>(p), value(v)
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

    class Iterator : public IteratorBase<Iterator, WithParentRefs>
    {
        using Base = IteratorBase<Iterator, WithParentRefs>;

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

    Iterator end()
    {
        return Iterator();
    }

    Iterator begin()
    {
        return Iterator(getRoot());
    }

    class TreeIsEmptyException {};
    
protected:
    std::shared_ptr<Node> root;
};

template <typename T, bool WithParent = false>
class BinaryTree : public Tree<T, 2, WithParent>
{
public:
    void printTree(size_t size)
    {
        using Node = typename Tree<T, 2, WithParent>::Node;
        const int w = 3; // width of a node and space between nodes
        int margin = size / 2;
        std::queue<std::shared_ptr<Node>> queue;
        std::queue<std::shared_ptr<Node>> childs;
        queue.push(Tree<T, 2, WithParent>::root);
        std::cout << "Tree:" << std::endl;

        do 
        {
            std::cout << std::string(margin * w, ' ');
            while (!queue.empty())
            {
                if (!queue.front())
                    std::cout << std::string(2 * (margin  + 1)* w, ' ');
                else
                {
                    std::cout << std::setw(3) << queue.front()->getValue() << std::string((2 * margin + 1) * w, ' ');
                    childs.push(queue.front()->getLeft());
                    childs.push(queue.front()->getRight());
                }
                queue.pop();

            }
            std::cout << std::endl;
            queue.swap(childs);
            if (margin == 0)
                break;
            margin = (margin - 1) / 2;
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
BinaryTree<T, WithParent> treeFromArray(const T *array, size_t size)
{
    BinaryTree<T, WithParent> tree;
    tree.setRoot(subtreeFromArray<T, WithParent>(array, nullptr, 0, size - 1));

    return tree;
}

#endif
