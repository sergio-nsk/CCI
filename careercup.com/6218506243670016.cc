// https://careercup.com/question?id=6218506243670016
// Amazon
// Given an ArrayList of Nodes, with each Node having an ID and a parent ID, determine whether the List is given in preorder.
//
// In preorder a parent must show up earlier than its child

#include <list>
#include <unordered_set>

struct Node {
  int ID = 0;  // >= 0
  int parentID = -1;  // no parent
};

// Create a hash set to store traversing nodes.
// Insert node[i] into the set once node[i] has its parent in the set.
// If parent of node[i] is not found in the set, then the list is not given in preorder.

bool IsInPreorder(const std::list<Node> &list) {
  if (list.empty())
    return true;
  if (list.size() == 1)
    return list.front().parentID == -1;

  std::unordered_set<decltype(Node::parentID)> parents;
  parents.insert(list.front().ID);
  auto i = list.begin();
  for (++i; i != list.end(); ++i) {
    if (parents.find(i->parentID) == parents.end())
      return false;
    parents.insert(i->ID);
  }
  return true;
}
