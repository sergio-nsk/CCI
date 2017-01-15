// Loop Detection: Given a circular linked list, implement an algorithm that returns the node at the
// beginning of the loop.

#include <iostream>

#include "forward_list.hpp"
#include <test.hpp>

template <typename T>
using Node = typename forward_list<T>::Node;

template <typename T>
const Node<T> *isLooped(const Node<T> *head)   // returns node in the loop where fast pointer met slow pointer
{
    auto node = head;
    auto fast = head;

    while (fast && fast->next)
    {
        node = node->next;
        fast = fast->next->next;
        if (fast == node)
            return node;
    }
    return nullptr;
}

template <typename T>
const Node<T> *findLoop(const Node<T> *head)   // returns start loop node
{
    auto metNode = isLooped<T>(head);
    if (!metNode)
        return nullptr;

    while (head != metNode)
    {
        metNode = metNode->next;
        head = head->next;
    }
    return head;
}

template <typename T>
void printList(const Node<T> *head, size_t len)
{
    std::cout << "{";
    const char *sep = "";
    while (head && len-- > 0)
    {
        std::cout << sep << head->value;
        sep = ", ";
        head = head->next;
        if (head && len == 0)
        {
            std::cout << sep << head->value << sep << "...";
        }
    }
    std::cout << "}";
}

template <typename T>
void printResult(const Node<T> *loopNode, const Node<T> *head)
{
    if (!loopNode)
        std::cout << " is NOT a circular linked list" << std::endl;
    else
        std::cout << " is a circular linked list, loop begins at node with value " << loopNode->value << std::endl;
}

int main()
{
    auto list = forward_list<int>();
    printList<int>(list.headNode(), list.length());
    test(findLoop<int>, printResult<int>, list.headNode());

    list = forward_list<int>({0});
    auto len = list.length();
    auto last = list.lastNode();
    auto head = list.detach();
    printList<int>(head, len);
    test(findLoop<int>, printResult<int>, head);
    last->next = head;
    printList<int>(head, len);
    test(findLoop<int>, printResult<int>, head);
    last->next = nullptr;
    list.attach(head);

    list = forward_list<int>({0, 1});
    len = list.length();
    last = list.lastNode();
    head = list.detach();
    printList<int>(head, len);
    test(findLoop<int>, printResult<int>, head);
    last->next = head;
    printList<int>(head, len);
    test(findLoop<int>, printResult<int>, head);
    last->next = head->next;
    printList<int>(head, len);
    test(findLoop<int>, printResult<int>, head);
    last->next = nullptr;
    list.attach(head);

    list = forward_list<int>({0, 1, 2});
    len = list.length();
    last = list.lastNode();
    head = list.detach();
    printList<int>(head, len);
    test(findLoop<int>, printResult<int>, head);
    last->next = head;
    printList<int>(head, len);
    test(findLoop<int>, printResult<int>, head);
    last->next = head->next;
    printList<int>(head, len);
    test(findLoop<int>, printResult<int>, head);
    last->next = head->next->next;
    printList<int>(head, len);
    test(findLoop<int>, printResult<int>, head);
    last->next = nullptr;
    list.attach(head);

    list = forward_list<int>({0, 1, 2, 3});
    len = list.length();
    last = list.lastNode();
    head = list.detach();
    printList<int>(head, len);
    test(findLoop<int>, printResult<int>, head);
    last->next = head;
    printList<int>(head, len);
    test(findLoop<int>, printResult<int>, head);
    last->next = head->next;
    printList<int>(head, len);
    test(findLoop<int>, printResult<int>, head);
    last->next = head->next->next;
    printList<int>(head, len);
    test(findLoop<int>, printResult<int>, head);
    last->next = head->next->next->next;
    printList<int>(head, len);
    test(findLoop<int>, printResult<int>, head);
    last->next = nullptr;
    list.attach(head);

    list = forward_list<int>({0, 1, 2, 3, 4, 5, 6, 7, 8, 9});
    len = list.length();
    last = list.lastNode();
    head = list.detach();
    printList<int>(head, len);
    test(findLoop<int>, printResult<int>, head);
    last->next = head;
    printList<int>(head, len);
    test(findLoop<int>, printResult<int>, head);
    last->next = head->next;
    printList<int>(head, len);
    test(findLoop<int>, printResult<int>, head);
    last->next = head->next->next;
    printList<int>(head, len);
    test(findLoop<int>, printResult<int>, head);
    last->next = head->next->next->next;
    printList<int>(head, len);
    test(findLoop<int>, printResult<int>, head);
    last->next = head->next->next->next->next;
    printList<int>(head, len);
    test(findLoop<int>, printResult<int>, head);
    last->next = head->next->next->next->next->next;
    printList<int>(head, len);
    test(findLoop<int>, printResult<int>, head);
    last->next = head->next->next->next->next->next->next;
    printList<int>(head, len);
    test(findLoop<int>, printResult<int>, head);
    last->next = head->next->next->next->next->next->next->next;
    printList<int>(head, len);
    test(findLoop<int>, printResult<int>, head);
    last->next = head->next->next->next->next->next->next->next->next;
    printList<int>(head, len);
    test(findLoop<int>, printResult<int>, head);
    last->next = head->next->next->next->next->next->next->next->next->next;
    printList<int>(head, len);
    test(findLoop<int>, printResult<int>, head);
    last->next = nullptr;
    last->next = head->next->next->next->next->next->next->next->next->next->next;
    printList<int>(head, len);
    test(findLoop<int>, printResult<int>, head);

    last->next = nullptr;
    list.attach(head);

    return 0;
}