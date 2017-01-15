#include <initializer_list>

template <typename T>
class forward_list
{
public:
    forward_list() : head(nullptr), last(nullptr), len(0)
    {
    }

    forward_list(forward_list &&rhv)
    {
        head = rhv.head;
        last = rhv.last;
        len = rhv.len;
        rhv.head = rhv.last = nullptr;
        rhv.len = 0;
    }

    forward_list(std::initializer_list<T> &&initVals) : forward_list()
    {
        for (auto &v : initVals)
            push_back(v);
    }

    forward_list<T> &operator = (forward_list<T> &&r)
    {
        clear();
        head = r.head;
        len = r.len;
        r.head = nullptr;
        r.len = 0;
        return *this;
    }

    ~forward_list()
    {
        clear();
    }

  public:
    // template <typename T>
    // class Node : std::pair<T, Node<T> *>
    // {
    // };

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
        --len;
        return iterator(next, prev);
    }

    void clear()
    {
        while (begin() != end())
            erase(begin());
        head = nullptr;
        last = nullptr;
        len = 0;
    }

    Node *detach()
    {
        Node *detached = head;
        head = nullptr;
        last = nullptr;
        len = 0;
        return detached;
    }

    void attach(Node *detached)
    {
        if (head != nullptr)
            clear();
        head = detached;
    }

    const Node *headNode() const
    {
        return head;
    }

    void push_front(const T &value)
    {
        Node *node = new Node(value);
        if (!head)
            last = head = node;
        else
        {
            node->next = head;
            head = node;
        }
        ++len;
    }

    void push_back(const T &value)
    {
        Node *node = new Node(value);
        if (!head)
            last = head = node;
        else
        {
            if (!last)
            {
                last = head;
                while (last->next)
                    last = last->next;
            }
            last->next = node;
            last = node;
        }
        ++len;
    }

    size_t length() const
    {
        if (len == 0 && head)
        {
            last = head;
            len = 1;
            while (last->next)
            {
                last = last->next;
                ++len;
            }
        }
        return len;
    }

  private:
    Node *head;
    mutable Node *last; // initialized delayed, used for fast push_back()
    mutable size_t len;
};