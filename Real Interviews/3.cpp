// Each goods has a category, that is a subcategory of a parent category.
// For example "Laptops" and "PCs" are in "Computers" and "TVs" and "Computers"
// are in "Electronics". Draw categories tree like below: Electronics
//     Computers
//         Laptops
//         PCs
//     TVs

#include <algorithm>
#include <iostream>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

struct Edge {
  std::string parent;
  std::string child;
};

void printSubtree(
    const std::string& root,
    const std::unordered_multimap<std::string, std::string>& edges,
    size_t indent) {
  std::vector<std::string> childs;
  std::cout << std::string(indent, ' ') << root << "\n";

  auto ranges = edges.equal_range(root);
  std::transform(ranges.first, ranges.second, std::back_inserter(childs),
                 [](auto c) { return c.second; });
  std::sort(childs.begin(), childs.end());

  for (const auto& child : childs)
    printSubtree(child, edges, indent + 4);
}

int main() {
  std::vector<Edge> edges = {
      {"Electronics", "Computers"}, {"Computers", "Laptops"},
      {"Computers", "PCs"},         {"Electronics", "Playstations"},
      {"Electronics", "TVs"},       {"Kitchen-wares", "Knifes"},
      {"Kitchen-wares", "Wares"},   {"Wares", "Glasses"},
      {"Wares", "Plates"}};

  std::unordered_multimap<std::string, std::string> hashEdges;
  std::set<std::string> parents;
  std::set<std::string> childs;
  std::vector<std::string> roots;

  for (auto& e : edges) {
    hashEdges.emplace(e.parent, e.child);
    parents.emplace(e.parent);
    childs.emplace(e.child);
  }
  if (hashEdges.empty())
    return 0;

  std::set_difference(parents.begin(), parents.end(), childs.begin(),
                      childs.end(), std::back_inserter(roots));
  for (const auto& root : roots)
    printSubtree(root, hashEdges, 0);
}
