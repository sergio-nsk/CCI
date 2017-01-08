#include <initializer_list>

template <typename T>
class forward_list
{
public:
    forward_list(std::initializer_list<T> &&initVals)
    {
        Node *lastNode = nullptr;
        for (auto &v : initVals)
        {
            auto newNode = new Node(v);
            if (!lastNode)
                head = lastNode = newNode;
            else
                lastNode = lastNode->next = newNode;
        }
    }

    forward_list<T> &operator = (forward_list<T> &&r)
    {
        while (begin() != end())
            erase(begin());
        head = r.head;
        r.head = nullptr;
        return *this;
    }

    ~forward_list()
    {
        while (begin() != end())
            erase(begin());
        head = nullptr;
    }

  private:
    struct Node
    {
        T value;
        Node *next;

        Node(T v) : value(v), next(nullptr)
        {
        }
    };

public:
    class iterator
    {
    public:
        iterator(Node *node) : ptr(node), prev(nullptr)
        {
        }

        bool operator == (const iterator &r)
        {
            return ptr == r.ptr;
        }

        bool operator != (const iterator &r)
        {
            return ptr != r.ptr;
        }

        const iterator &operator ++()
        {
            prev = ptr;
            ptr = ptr->next;
            return *this;
        }

        iterator operator ++(int)
        {
            iterator cur = *this;
            prev = ptr;
            ptr = ptr->next;
            return cur;
        }

        T &operator *()
        {
            return ptr->value;
        }

        const T &operator *() const
        {
            return ptr->value;
        }

      private:
        Node *ptr;
        Node *prev;

        iterator() : ptr(nullptr), prev(nullptr)
        {
        }

        iterator(Node *node, Node *parent) : ptr(node), prev(parent)
        {
        }

      friend class forward_list;
    };

    typedef const iterator const_iterator;

    iterator begin()
    {
        return iterator(head);
    }

    iterator end()
    {
        return iterator(nullptr);
    }

    const_iterator end() const
    {
        return iterator(nullptr);
    }

    const_iterator begin() const
    {
        return iterator(head);
    }

    // makes other iterators on next element invalid
    const iterator erase(const_iterator i)
    {
        Node *d = i.ptr;
        Node *prev = i.prev;
        Node *next = i.ptr->next;
        if (prev)
            prev->next = next;
        if (head == d)
            head = next;
        delete d;
        return iterator(next, prev);
    }

private:
    Node *head;
};