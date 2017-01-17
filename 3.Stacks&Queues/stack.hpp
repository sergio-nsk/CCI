#include <utility>

template <typename T>
class Stack
{
public:
    Stack() : top(nullptr), size(0)
    {
    }

    template <typename U>
    void push(U &&value)
    {
        auto n = new Node(std::move(value), top);
        top = n;
        ++size;
    }

    T &peek()
    {
        if (!top)
            throw StackIsEmptyException();
        return top->value;
    }

    T pop()
    {
        if (!top)
            throw StackIsEmptyException();
        auto value = top->value;
        auto n = top;
        top = n->next;
        delete n;
        --size;
        return value;
    }

    bool isEmpty()
    {
        return !top;
    }

    class StackIsEmptyException
    {
    };

private:
    struct Node
    {
        Node(T &&v, Node *n): value(v), next(n)
        {
        }

        T value;
        Node *next;
    };

    Node *top;
    size_t size;
};