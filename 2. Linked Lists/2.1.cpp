// Remove Dups: Write code to remove duplicates from an unsorted linked list.

#include <test.hpp>
#include <list>
#include <iostream>

template <typename T>
bool removeDups(std::list<int> &list)
{
    for (auto i = list.begin(); i != list.end(); ++i)
    {
        auto j = i;
        for (++j; j != list.end();)
            if (*j == *i)
                j = list.erase(j);
            else
                ++j;
    }
    return true;
}

template <typename T>
void printResult(bool result, const std::list<T> &list)
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
    std::list<int> list({1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 2, 4, 6, 8, 10, 3, 6, 9, 4, 8, 5, 10});
    printResult<int>(true, list);
    std::cout << " --> ";
    test(removeDups<int>, printResult<int>, list);
    std::cout << std::endl;

    list = {2, 4, 6, 8, 10, 3, 6, 9, 4, 8, 5, 10, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    printResult<int>(true, list);
    std::cout << " --> ";
    test(removeDups<int>, printResult<int>, list);
    std::cout << std::endl;

    return 0;
}
