#include <string>
#include <vector>
#include <unordered_map>
#include <typeinfo>
#include <iostream>

struct Edge
{
    std::string parent;
    std::string child;
};

int main()
{
    std::vector<Edge> edges = {{"Electronics", "Computers"}, {"Computers", "Laptops"}, {"Electronics", "Playstations"}, {"Electronics", "TV"}};
    std::unordered_multimap<std::string, std::string> hashEdges;

    for (auto &e : edges)
        hashEdges.emplace(e.parent, e.child);
    if (hashEdges.empty())
        return 0;

    auto root = edges[0].parent;
}
