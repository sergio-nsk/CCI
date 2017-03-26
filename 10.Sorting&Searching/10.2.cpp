// Group Anagrams: Write a method to sort an array ot strings so that all tne anagrams are next to
// each other.

#include <string>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <iostream>

std::string sortString(const std::string &s)
{
    auto r = s;
    std::sort(r.begin(), r. end());
    return r;
}

void sort(std::vector<std::string> &array)
{
    std::unordered_multimap<std::string, std::string> map;
    for (auto &s : array)
        map.emplace(sortString(s), s);

    unsigned i = 0;
    for (auto &s : map)
        array[i++] = std::move(s.second);
}

int main()
{
    std::vector<std::string> array = {"apple", "banana", "carrot", "ele", "duck", "papel", "tarroc", "cudk", "eel", "lee"};
    sort(array);
    for (auto &s : array)
        std::cout << s << '\n';
}
