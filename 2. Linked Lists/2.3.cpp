// Delete Middle Node: Implement an algorithm to delete a node in the middle (i.e., any node but
// the first and last node, not necessarily the exact middle) of a singly linked list, given only access to
// that node.
// EXAMPLE
// lnput:the node c from the linked lista->b->c->d->e->f
// Result: nothing is returned, but the new linked list looks likea->b->d->e- >f

#include <iostream>

#include "forward_list.hpp"

template <typename T>
using Node = typename forward_list<T>::Node;

template <typename T>
bool deleteMiddleNode(Node<T> *node)
{
    Node<T> *next = node->next;
    node->value = next->value;
    node->next = next->next;
    delete next;
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
    forward_list<int> list({0, 1, 2, 3, 4, 5, 6, 7, 8, 9});
    auto i = list.begin();
    ++i;
    ++i;
    ++i;
    ++i;
    ++i;
    printList<int>(true, list);
    std::cout << " --> ";
    deleteMiddleNode<int>(i.get()); // i becomes invalid
    printList<int>(true, list);
    std::cout << std::endl;

    return 0;
}