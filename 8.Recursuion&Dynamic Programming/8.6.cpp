// Towers of Hanoi: In the classic problem of the Towers of Hanoi, you have 3
// towers and N disks of different sizes which can slide onto any tower. The
// puzzle starts with disks sorted in ascending order of size from top to bottom
// (i.e., each disk sits on top of an even larger one). You have the following
// constraints:
// (1) Only one disk can be moved at a time.
// (2) A disk is slid off the top of one tower onto another tower.
// (3) A disk cannot be placed on top of a smaller disk.
// Write a program to move the disks from the first tower to the last using
// Stacks.

#include <array>
#include <iostream>
#include <stack>

class Tower {
  std::stack<int> disks;
  int index;

 public:
  Tower(int i) : index(i) {}
  void add(int i) {
    if (!disks.empty() && disks.top() <= i)
      std::cerr << "Error placing disk " << i << std::endl;
    else
      disks.push(i);
  }
  void moveDisks(int n, Tower& destination, Tower& buffer) {
    if (n <= 0)
      return;
    moveDisks(n - 1, buffer, destination);
    moveTopTo(destination);
    buffer.moveDisks(n - 1, destination, *this);
  }
  void moveTopTo(Tower& to) {
    to.add(disks.top());
    disks.pop();
  }
};

int main() {
  int n = 3;
  std::array<Tower, 3> towers = {Tower(1), Tower(2), Tower(3)};
  for (int i = n; i > 0; --i)
    towers[0].add(i);
  towers[0].moveDisks(n, towers[2], towers[1]);
}
