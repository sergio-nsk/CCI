#pragma once

#include <queue>
#include <unordered_map>
#include "9.2-pathnode.hpp"

class BFSData {
 public:
  std::queue<PathNode> toVisit;
  std::unordered_map<int, PathNode> visited;
  BFSData(Person root) {
    PathNode sourcePath(std::make_shared<PathNodeImpl>(root, nullptr));
    toVisit.push(sourcePath);
    visited.emplace(root->getID(), sourcePath);
  }
  bool isFinished() const { return toVisit.empty(); }
};
