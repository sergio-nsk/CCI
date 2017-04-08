// Return Kth to Last: Implement an algorithm to find the kth to last element of a singly linked list.

#include "all.hpp"

template <typename T>
bool kthToLast(const forward_list<T> &list, int k, T &value)
{
    if (k < 0)
        return false;

    auto ahead = list.begin();
    for (; k >= 0; --k)
    {
        if (ahead == list.end())
            return false;
        ++ahead;
    }

    auto kthToLast = list.begin();
    while (ahead != list.end())
    {
        ++kthToLast;
        ++ahead;
    }

    value = *kthToLast;
    return true;
}

template <typename T>
void print(bool result, const forward_list<T> &list, int k, const T &value)
{
    if (k == 0)
        std::cout << "last: ";
    else if (k == 1)
        std::cout << "1st to last: ";
    else if (k == 2)
        std::cout << "2nd to last: ";
    else if (k == 3)
        std::cout << "3d to last: ";
    else
        std::cout << k << "th to last: ";
    if (result)
        std::cout << value;
    else
        std::cout << "not found";
    std::cout << std::endl;
}

int main()
{
    forward_list<int> list({0, 1, 2, 3, 4, 5, 6, 7, 8, 9});
    for (int k = -2; k < 12; ++k)
    {
        int value;
        test(kthToLast<int>, print<int>, list, k, value);
    }
    return 0;
}
