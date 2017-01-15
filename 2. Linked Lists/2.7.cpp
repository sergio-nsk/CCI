// Intersection: Given two (singly) linked lists, determine if the two lists intersect. Return the inter­
// secting node. Note that the intersection is defined based on reference, not value. That is, if the kth
// node of the first linked list is the exact same node (by reference) as the jth node of the second
// linked list, then they are intersecting.

#include <iostream>

#include "forward_list.hpp"
#include <test.hpp>

template <typename T>
const typename forward_list<T>::Node *findIntersectEq(const typename forward_list<T>::Node *first, const typename forward_list<T>::Node *second, int &Kth)
{
    Kth = 0;
    while (first)
    {
        if (first == second)
            return first;
        first = first->next;
        second = second->next;
        ++Kth;
    }
    Kth = -1;
    return nullptr;
}

template <typename T>
const typename forward_list<T>::Node *findIntersect(forward_list<T> &first, forward_list<T> &second, int &firstKth, int &secondKth)
{
    auto firstLen = first.length();
    auto secondLen = second.length();

    auto firstHead = first.headNode();
    auto secondHead = second.headNode();

    size_t diffLen = 0;

    if (firstLen > secondLen)
    {
        diffLen = firstLen - secondLen;
        for (auto i = 0U; i < diffLen; ++i)
            firstHead = firstHead->next;
    }
    else
    {
        diffLen = secondLen - firstLen;
        for (auto i = 0U; i < diffLen; ++i)
            secondHead = secondHead->next;
    }

    int Kth = 0;
    auto node = findIntersectEq<T>(firstHead, secondHead, Kth);
    if (node)
    {
        if (firstLen > secondLen)
        {
            firstKth = Kth + diffLen;
            secondKth = Kth;
        }
        else
        {
            secondKth = Kth + diffLen;
            firstKth = Kth;
        }
    }
    else
        firstKth = secondKth = 0;
    return node;
}

template <typename T>
void printList(const forward_list<T> &list)
{
    std::cout << "{";
    const char *sep = "";
    for (auto &c : list)
    {
        std::cout << sep << c;
        sep = ", ";
    }
    std::cout << "}";
}

template <typename T>
void printResult(const typename forward_list<T>::Node *result, forward_list<T> &first, forward_list<T> &second, int &firstKth, int &secondKth)
{
    if (result)
    {
        std::cout << firstKth << "th element of ";
        printList(first);
        std::cout << " intersects with " << secondKth << "th element of ";
        printList(second);
        std::cout << std::endl;
    }
    else
    {
        printList(first);
        std::cout << " and ";
        printList(second);
        std::cout << " DO NOT intersect" << std::endl;
    }
}

int main()
{
    int firstKth;
    int secondKth;
    forward_list<int> first = forward_list<int>({10, 11, 12, 13, 14, 15, 16, 17, 18, 19});
    forward_list<int> second = forward_list<int>({20, 21, 22, 23, 24, 25, 26, 27, 28, 29});
    test(findIntersect<int>, printResult<int>, first, second, firstKth, secondKth);

    second = {20, 21, 22, 23, 24, 25};
    test(findIntersect<int>, printResult<int>, first, second, firstKth, secondKth);

    auto firstHead = first.headNode();
    auto secondHead = second.detach();
    secondHead->next->next->next->next->next->next = firstHead->next->next;
    second.attach(secondHead);
    test(findIntersect<int>, printResult<int>, first, second, firstKth, secondKth);
    secondHead = second.detach();
    secondHead->next->next->next->next->next->next = nullptr;
    second.attach(secondHead);

    auto firstHead2 = first.detach();
    auto secondHead2 = second.headNode();
    firstHead2->next->next->next->next->next->next = secondHead2->next->next;
    first.attach(firstHead2);
    test(findIntersect<int>, printResult<int>, first, second, firstKth, secondKth);
    firstHead2 = first.detach();
    firstHead2->next->next->next->next->next->next = nullptr;
    first.attach(firstHead2);

    return 0;
}