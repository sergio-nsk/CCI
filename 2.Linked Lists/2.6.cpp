// Palindrome: Implement a function to check if a linked list is a palindrome.

#include "all.hpp"

template <typename T>
bool isPalindromeRec(const typename forward_list<T>::Node *node, const typename forward_list<T>::Node *&forward, int len)
{
    if ((len -= 2) == 0)
    {
        forward = node->next->next;
        return node->value == node->next->value;
    }
    else if (len < 0)
    {
        forward = node->next;
        return true;
    }
    else
    {
        bool ret = isPalindromeRec<T>(node->next, forward, len) && (node->value == forward->value);
        forward = forward->next;
        return ret;
    }
}

template <typename T>
bool isPalindrome(forward_list<T> &list)
{
    const typename forward_list<T>::Node *forward = nullptr;
    auto len = list.length();
    auto head = list.detach();
    bool ret = isPalindromeRec<T>(head, forward, len);
    list.attach(head);
    return ret;
}

template <typename T>
void printResult(bool result, const forward_list<T> &list)
{
    std::cout << "{";
    const char *sep = "";
    for (auto &c : list)
    {
        std::cout << sep << c;
        sep = ", ";
    }
    std::cout << "} is " << (result ? "" : "NOT ") << "palindrome" << std::endl;

}

int main()
{
    forward_list<int> list = forward_list<int>({0});
    test(isPalindrome<int>, printResult<int>, list);

    list = {1, 1};
    test(isPalindrome<int>, printResult<int>, list);

    list = {1, 0};
    test(isPalindrome<int>, printResult<int>, list);

    list = {1, 0, 1};
    test(isPalindrome<int>, printResult<int>, list);

    list = {1, 0, 2};
    test(isPalindrome<int>, printResult<int>, list);

    list = {1, 0, 0, 1};
    test(isPalindrome<int>, printResult<int>, list);

    list = {1, 0, 0, 2};
    test(isPalindrome<int>, printResult<int>, list);

    list = {1, 0, 2, 0, 1};
    test(isPalindrome<int>, printResult<int>, list);

    list = {1, 0, 2, 1, 1};
    test(isPalindrome<int>, printResult<int>, list);

    list = {1, 0, 2, 0, 2};
    test(isPalindrome<int>, printResult<int>, list);

    list = {1, 0, 2, 2, 0, 1};
    test(isPalindrome<int>, printResult<int>, list);

    list = {1, 0, 2, 2, 2, 1};
    test(isPalindrome<int>, printResult<int>, list);

    list = {1, 0, 2, 2, 0, 2};
    test(isPalindrome<int>, printResult<int>, list);

    list = {1, 0, 2, 3, 2, 0, 1};
    test(isPalindrome<int>, printResult<int>, list);

    list = {1, 0, 2, 3, 3, 0, 1};
    test(isPalindrome<int>, printResult<int>, list);

    list = {1, 0, 2, 3, 2, 3, 1};
    test(isPalindrome<int>, printResult<int>, list);

    list = {1, 0, 2, 3, 2, 0, 3};
    test(isPalindrome<int>, printResult<int>, list);

    return 0;
}
