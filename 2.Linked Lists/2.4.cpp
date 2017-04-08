// Partition: Write code to partition a linked list around a value x, such that all nodes less than x come
// before all nodes greater than or equal to x. If x is contained within the list, the values of x only need
// to be after the elements less than x (see below). The partition element x can appear anywhere in the
// "right partition"; it does not need to appear between the left and right partitions.
// EXAMPLE
// Input:
//  3 -> 5 -> 8 -> 5 -> 10 -> 2 -> 1 [partition= 5]
// Output:
//  3 -> 1 -> 2 -> 10 -> 5 -> 5 -> 8

#include "all.hpp"

template <typename T>
using Node = typename forward_list<T>::Node;

template <typename T>
void swap(T &l, T &r)
{
    T tmp = l;
    l = r;
    r = tmp;
}

template <typename T>
bool partition(Node<T> *head, T x)
{
    Node<T> *current = head;
    Node<T> *next = head;

    while (next)
    {
        if (next->value < x)
        {
            if (current != next)
                swap(current->value, next->value);
            current = current->next;
        }
        next = next->next;
    }
    return true;
}

template <typename T>
void printList(bool result, const forward_list<T> &list)
{
    const char *sep = "";
    for (auto &c : list)
    {
        std::cout << sep << c;
        sep = ", ";
    }
}

int main()
{
    forward_list<int> list({3, 7, 2, 8, 1, 9, 0, 10, 5, 5, 4});
    printList<int>(true, list);
    std::cout << " --> ";

    auto detached = list.detach();
    partition(detached, 5);
    list.attach(detached);

    printList<int>(true, list);
    std::cout << std::endl;

    list = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    printList<int>(true, list);
    std::cout << " --> ";

    detached = list.detach();
    partition(detached, 5);
    list.attach(detached);

    printList<int>(true, list);
    std::cout << std::endl;

    list = {3, 5, 8, 5, 10, 2, 1};
    printList<int>(true, list);
    std::cout << " --> ";

    detached = list.detach();
    partition(detached, 5);
    list.attach(detached);

    printList<int>(true, list);
    std::cout << std::endl;

    return 0;
}
