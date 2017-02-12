#include <array>
#include <memory>
#include <utility>
#include <queue>
#include <iostream>
#include <iomanip>

template <typename T, size_t N>
class Tree
{
public:
    class Node
    {
    public:
        Node(T &&v) : value(std::move(v))
        {
        }

        Node(const T &v) : value(v)
        {
        }

        Node(T &&v, const std::shared_ptr<Node> &p) : value(std::move(v)), parent(p)
        {
        }

        Node(const T &v, const std::shared_ptr<Node> &p) : value(v), parent(p)
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

        std::shared_ptr<Node> getParent()
        {
            return parent.lock();
        }

    protected:
        T value;
        std::array<std::shared_ptr<Node>, N> childs;
        std::weak_ptr<Node> parent;
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

    class Iterator
    {
    public:
        Iterator()
        {
        }
        Iterator(const std::shared_ptr<Node> &node) : currNode(node)
        {
        }
        std::shared_ptr<Node> operator * ()
        {
            return currNode.lock();
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

        bool operator != (const Iterator &rh)
        {
            return currNode.lock() != rh.currNode.lock();
        }

    private:
        std::weak_ptr <Node> currNode;
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

template <typename T>
class BinaryTree : public Tree<T, 2>
{
public:
    void printTree(size_t size)
    {
        using Node = typename Tree<T, 2>::Node;
        const int w = 3; // width of a node and space between nodes
        int margin = size / 2;
        std::queue<std::shared_ptr<Node>> queue;
        std::queue<std::shared_ptr<Node>> childs;
        queue.push(Tree<T, 2>::root);
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

template <typename T>
using Node = typename BinaryTree<T>::Node;

template <typename T>
using NodePtr = std::shared_ptr<Node<T>>;

#ifdef INCLUDE_HELPER

// The function treeFromArray from the task 4.2 helps us to fill test trees.
template <typename T>
NodePtr<T> subtreeFromArray(const T *array, const NodePtr<T> &parent, int start, int end)
{
    if (end < start)
        return nullptr;

    int i = (start + end) / 2;
    auto node = std::make_shared<Node<T>>(array[i], parent);
    node->setLeftChild(subtreeFromArray(array, node, start, i - 1));
    node->setRightChild(subtreeFromArray(array, node, i + 1, end));
    return node;
}

template <typename T>
BinaryTree<T> treeFromArray(const T *array, size_t size)
{
    BinaryTree<T> tree;
    tree.setRoot(subtreeFromArray(array, nullptr, 0, size - 1));

    return tree;
}

#endif
