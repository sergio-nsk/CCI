// http://www.modernescpp.com/index.php/atomic-smart-pointers

#include <memory>
#include <atomic>

#if __cplusplus == 201703L
#   define CPP17 = 1
#endif
// Or
// #if __cplusplus > 201402L
// #   define CPP17 = 1
// #endif

template <typename T> class concurrent_stack
{
    struct Node
    {
        T t;
        std::shared_ptr<Node> next;
    };

# if CPP17
    std::atomic_shared_ptr<Node> head;
#else
    std::atomic<std::shared_ptr<Node>> head;
#endif
    concurrent_stack(const concurrent_stack &) = delete;
    void operator = (const concurrent_stack &) = delete;

public:
    concurrent_stack() = default;
    ~concurrent_stack() = default;

    class reference
    {
        std::shared_ptr<Node> p;

    public:
        reference(std::shared_ptr<Node> &&pp): p(pp)
        {
        }

        T& operator * ()
        {
            return p->t;
        }

        T* operator -> ()
        {
            return &p->t;
        }
    };

    reference find(const T &t) const
    {
#     if CPP17
        auto p = head.load();
#     else
        auto p = std::atomic_load(&head);
#     endif
        while (p && p->t != t)
            p = p->next;
        return reference(std::move(p));
    }

    reference front() const
    {
#     if CPP17
        return reference(head);
#     else
        return reference(std::atomic_load(&head));
#     endif
    }

    void push_front(T t)
    {
        auto p = std::make_shared<Node>();
        p->t = t;
#     if CPP17
        p->next = head;
        while (!head.compare_exchange_weak(p->next, p))
        {
        }
#     else
        p->next = std::atomic_load(&head);
        while (!std::atomic_compare_exchange_weak(&head, &p->next, p))
        {
        }
#     endif
    }

    void pop_front()
    {
        auto p = head.load();
        #     if CPP17
        while (!head.compare_exchange_weak(p, p->next))
        {
        }
#     else
        while (!std::atomic_compare_exchange_weak(&head, &p, p->next))
        {
        }
#     endif
    }
};

int main()
{
    concurrent_stack<int> stack;
    stack.push_front(0);
    auto p = stack.front();
    stack.find(*p);
    stack.pop_front();
}