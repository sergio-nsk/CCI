#include <utility>

template <typename T>
class Stack
{
public:
    Stack() : top(nullptr), stackSize(0)
    {
    }

    Stack(Stack &&other)
    {
        top = other.top;
        stackSize = other.stackSize;
        other.top = nullptr;
        other.stackSize = 0;
    }

    ~Stack()
    {
        while (!isEmpty())
            pop();
    }

    template <typename U>
    void push(U &&value)
    {
        auto n = new Node(std::forward<T>(value), top);
        top = n;
        ++stackSize;
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
        auto value(std::move(top->value));
        auto n = top;
        top = n->next;
        delete n;
        --stackSize;
        return value;
    }

    bool isEmpty() const
    {
        return !top;
    }

    size_t size() const
    {
        return stackSize;
    }

    class StackIsEmptyException
    {
    };

private:
    struct Node
    {
        Node(T &&v, Node *n): value(std::forward<T>(v)), next(n)
        {
        }

        T value;
        Node *next;
    };

    Node *top;
    size_t stackSize;
};