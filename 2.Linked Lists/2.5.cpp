// Sum Lists: You have two numbers represented by
// a linked list, where each node contains a single
// digit. The digits are stored in reverse order, such that the 1 's digit is at the head of the list. Write a
// function that adds the two numbers and returns the sum as a linked list.
// EXAMPLE
// Input:(7-> 1 -> 6) + (5 -> 9 -> 2).That is,617 + 295.
// Output: 2 -> 1 -> 9. That is, 912.
// FOLLOW UP
// Suppose the digits are stored in forward order. Repeat the above problem.
// EXAMPLE
// lnput:(6 -> 1 -> 7) + (2 -> 9 -> 5).That is,617 + 295.
// Output: 9 -> 1 -> 2. That is, 912.

#include "all.hpp"

template<typename T>
auto sum0N(const forward_list<T> &first, const forward_list<T> &second)
{
    forward_list<T> result;
    auto overflow = false;

    auto l = first.begin(), r = second.begin();
    while (l != first.end() || r != second.end())
    {
        T a = l != first.end() ? *l++ : 0;
        T b = r != second.end() ? *r++ : 0;
        T s = a + b + overflow;
        if ((overflow = (s > 9)))
            s -= 10;
        result.push_back(s);
    }
    if (overflow)
        result.push_back(1);

    return result;
}

template<typename T>
bool sumTail(const typename forward_list<T>::Node *left, const typename forward_list<T>::Node *right, forward_list<T> &result)
{
    assert((left->next && right->next) || (!left->next && !right->next));
    bool overflow = false;

    if (left->next)
        overflow = sumTail(left->next, right->next, result);

    T s = left->value + right->value + overflow;
    if ((overflow = (s > 9)))
        s -= 10;
    result.push_front(s);
    return overflow;
}

template<typename T>
forward_list<T> sumN0(forward_list<T> &first, forward_list<T> &second)
{
    auto lLen = first.length();
    auto rLen = second.length();

    if (lLen < rLen)
        return sumN0(second, first);

    forward_list<T> result;
    lLen -= rLen;

    // pad the shorter list with leading zeros
    for (auto i = lLen; i > 0; --i)
        second.push_front(0);

    const auto left = first.detach();
    const auto right = second.detach();

    bool overflow = sumTail(left, right, result);
    if (overflow)
        result.push_front(1);

    first.attach(left);
    second.attach(right);

    // remove the padded leading zeros
    while (lLen-- > 0)
        second.erase(second.begin());

    return result;
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


int main()
{
    // left to right

    forward_list<int> first({7, 1, 6});
    forward_list<int> second({5, 9, 2});

    auto result = sum0N(first, second);

    printList(first);
    std::cout << " + ";
    printList(second);
    std::cout << " = ";
    printList(result);
    std::cout << std::endl;

    second = {5, 9, 2, 3};

    result = sum0N(first, second);

    printList(first);
    std::cout << " + ";
    printList(second);
    std::cout << " = ";
    printList(result);
    std::cout << std::endl;

    first = {9, 7, 8};
    second = {6, 8, 5};

    result = sum0N(first, second);

    printList(first);
    std::cout << " + ";
    printList(second);
    std::cout << " = ";
    printList(result);
    std::cout << std::endl;

    // right  to left
    first = {6, 1, 7};
    second = {2, 9, 5};

    result = sumN0(first, second);

    printList(first);
    std::cout << " + ";
    printList(second);
    std::cout << " = ";
    printList(result);
    std::cout << std::endl;

    second = {3, 2, 9, 5};

    result = sumN0(first, second);

    printList(first);
    std::cout << " + ";
    printList(second);
    std::cout << " = ";
    printList(result);
    std::cout << std::endl;

    first = {8, 7, 9};
    second = {5, 8, 6};

    result = sumN0(first, second);

    printList(first);
    std::cout << " + ";
    printList(second);
    std::cout << " = ";
    printList(result);
    std::cout << std::endl;

    return 0;
}
