#include <algorithm>
#include <iostream>

template <typename ForwardIterator>
void qsort(ForwardIterator first, ForwardIterator last)
{
    if (first == last)
        return;

    auto pivot = *std::next(first, std::distance(first, last) / 2);
    ForwardIterator mid1 = std::partition(first, last, [pivot](const decltype(pivot) &v) { return v < pivot; });
    ForwardIterator mid2 = std::partition(mid1, last, [pivot](const decltype(pivot) &v) { return pivot >= v; });

    // Values between mid1 and mid2 are equal.
    qsort(first, mid1);
    qsort(mid2, last);
}

int main()
{
    std::array<int, 11> array = {3, 7, 2, 8, 1, 9, 0, 10, 5, 5, 4};
    qsort(array.begin(), array.end());
    for (auto v : array)
        std::cout << v << ' ';
    std::cout << std::endl;
}
