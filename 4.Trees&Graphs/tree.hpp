#include <array>
#include <memory>
#include <utility>

template <typename T>
class BinaryTree
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

        const T& getValue() const
        {
            return value;
        }

        const std::shared_ptr<Node> &getLeft() const
        {
            return childs[0];
        }

        const std::shared_ptr<Node> &getRight() const
        {
            return childs[1];
        }

        template <typename U>
        void setLeftChild(U &&node)
        {
            childs[0] = std::forward<U>(node);
        }

        template <typename U>
        void setRightChild(U &&node)
        {
            childs[1] = std::forward<U>(node);
        }

      private:
        T value;
        std::array<std::shared_ptr<Node>, 2> childs;
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

  private:
    std::shared_ptr<Node> root;
};